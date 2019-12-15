#include <iostream>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int msg_queue_id;

void kill_queue(int sig){
	cout << "Очередь уничтожается\n";
	msgctl(msg_queue_id, IPC_RMID, 0);
	raise(SIGKILL);
}

int main(int argc, char *argv[]) {

	struct msg{
	long mtype;
	pid_t process_id;
	} mes;
	
	msg_queue_id = msgget(190, 0622 | IPC_CREAT);
	
	if (msg_queue_id == -1){
		cout << "Ошибка при создании очереди\n";
		cout << strerror(errno) << "\n";
	}
	
	signal(SIGALRM, kill_queue);
	alarm(atoi(argv[1]));
	for(;;){
		if (msgrcv(msg_queue_id,&mes,256,1,0) == -1){
			cout << "Ошибка при приеме сообщения\n";
			cout << strerror(errno) << "\n";
		} else {
				cout << "Сообщение принято\n";
				cout << mes.mtype << "\n";
				cout << mes.process_id << "\n";
		}
	}
	pause();

	return 0;
}
