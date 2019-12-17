#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>

using namespace std;


void signal_handler(int signal_num){
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	
	pid_t pid = fork();
	if (pid == 0){
		cout << "Идентификатор процесса: " << getpid() << endl;
		cout << "Дата и время старта: " << asctime(timeinfo) << "\n";
		exit(0);
	} 
	
}

int main(int argc, char *argv[]){

	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask,SIGTSTP);
	sigprocmask(SIG_BLOCK,&mask,0);

	signal(SIGALRM,signal_handler);
	
	struct itimerval timer, current_timer;
	timer.it_interval.tv_sec = atoi(argv[2]);
	timer.it_interval.tv_usec = atoi(argv[3]);
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 0;
	
	for (int i = 0; i < atoi(argv[1]) ; i++){
		if (setitimer(ITIMER_REAL, &timer, &current_timer) == -1){
			cout << "Error" << endl;
		}
		alarm(atoi(argv[2]));
		pause();
	}

	sleep(1);
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	cout << "Дата и время завершения программы: " << asctime(timeinfo) << "\n";
	
	return 0;
}
