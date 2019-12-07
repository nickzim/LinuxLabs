#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void Signal_handler(int signal_num){
	switch(signal_num){
		case SIGFPE: {
			cout << "Ошибка: неверная операция\n";
			kill(getpid(), SIGHUP);
		}
		case SIGSEGV: {
			cout << "Ошибка: нарушение защиты памяти\n";
			kill(getpid(), SIGINT);
		}		
		default: {
			cout << "Ошибка: неизвестный сигнал\n";
			kill(getpid(), SIGINT);
		}
	}
}

int main (int argc, char *argv[]){
	
	sigset_t mask;
	int signal_num = atoi(argv[1]);

	signal (signal_num, Signal_handler);
	
	if (signal_num == 8){
		int a = 5/0;
		pause();
		sigaddset(&mask,SIGHUP);
		sigprocmask(SIG_BLOCK, &mask, 0);
		alarm(1);
		pause();
		cout << "Завершение процесса\n";
	}

	if (signal_num == 11){
		main(0,NULL);	
		pause();
		sigaddset(&mask,SIGINT);
		sigprocmask(SIG_BLOCK, &mask, 0);
		alarm(1);
		pause();
		cout << "Завершение процесса\n";
	}

}
