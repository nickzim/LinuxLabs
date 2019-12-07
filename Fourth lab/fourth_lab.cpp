#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <linux/sched.h>

using namespace std;

void* threadFunction(void* thread_arg){

	string buffer;
	ifstream* file = static_cast<ifstream*>(thread_arg);
	int policy;
	struct sched_param param;
	pthread_getschedparam(pthread_self(),&policy,&param);
	
	string schedule_class = (sched_getscheduler(getpid()) == SCHED_FIFO) ? "SCHED_FIFO":
				 (sched_getscheduler(getpid()) == SCHED_RR) ? "SCHED_RR":
				 (sched_getscheduler(getpid()) == SCHED_OTHER) ? "SCHED_OTHER": "UNKNOWN";
	
	cout << "\nКласс планирования процесса: " << schedule_class << "\n";
	cout << "Текущий приоритет: " << param.sched_priority << "\n";
	cout << "Минимальный приоритет: " << sched_get_priority_min(policy) << "\n";
	cout << "Максимальный приоритет: " << sched_get_priority_max(policy) << "\n\n";
	if (file->is_open()){
		cout << "Содержание файла: \n";
		while (!file->eof()){
			getline(*file,buffer);
			cout << buffer << "\n";
		}
	} else {
		cout << "Error \n";	
	}
	//file->close();
	pthread_exit(0);
}

int main(int argc, char *argv[]){
	ifstream file(argv[1]);	
	
	void* thread_arg = &file;	

	pthread_t thread;

	pthread_create(&thread, NULL, threadFunction, thread_arg); 
	pthread_join(thread, NULL);
 
	if (file.is_open()){
		cout << "Файл открыт\n";
		file.close();
		if (!file.is_open()){
			cout << "Файл принудительно закрыт\n";
		} else {
			cout << "Ошибка\n";
		}
	} else {
		cout << "Файл закрыт\n";
	} 

	return 0;
}
