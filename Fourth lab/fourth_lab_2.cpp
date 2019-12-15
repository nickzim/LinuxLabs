#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string>

using namespace std;

void* thread1_Function(void* thread_arg){
	string* line = static_cast<string*>(thread_arg);
	ofstream fout ("output_1.txt",ios_base::app);
	fout << *line << "\n";
	fout.close();
	pthread_exit(0);
}

void* thread2_Function(void* thread_arg){
	string* line = static_cast<string*>(thread_arg);
	ofstream fout ("output_2.txt",ios_base::app);
	fout << *line << "\n";
	fout.close();
	pthread_exit(0);
}

int main(){

	ifstream file("input.txt");
	pthread_t thread_1, thread_2;
	void* thread_arg;
	string buffer;
		
	int i = 0;
	while (!file.eof()){
		getline (file,buffer);
		thread_arg = &buffer;
		if (i % 2 == 0){
			pthread_create(&thread_1, NULL, thread1_Function, thread_arg);	
		} else {
			pthread_create(&thread_2, NULL, thread2_Function, thread_arg);
		
		}
		
		pthread_join(thread_1, NULL);
		pthread_join(thread_2, NULL); 
		i++;
	}
	
	file.close();
	return 0;
}
