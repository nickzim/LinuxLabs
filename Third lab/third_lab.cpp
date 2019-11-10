#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
	
	ofstream fout(argv[1]);
	
	pid_t child = fork();
	if (child == -1){
		cout << "Ошибка при создании процесса\n";
		exit(1);
	} else if (child == 0){
		fout << "\n\nПроцесс вызванный с помощью fork()\n";
		fout << "Идентификатор процесса: " << getpid() << "\n";
		fout << "Идентификатор предка: " << getppid() << "\n";
		fout << "Идентификатор сессии процесса: " << getsid(getpid()) << "\n";
		fout << "Идентификатор группы процессов: " << getpgid(getpid()) << "\n";
		fout << "Реальный идентификатор процессов: " << getuid() << "\n";
		fout << "Эффективный идентификатор процессов: " << geteuid() << "\n";
		fout << "Реальный групповой идентификатор: " << getgid() << "\n";
		fout << "Эффективный групповой идентификатор: " << getegid() << "\n";
		sleep(3);
		exit(0);
	} else {
		fout << "Родительский процесс:\n";
		fout << "Идентификатор процесса: " << getpid() << "\n";
		fout << "Идентификатор предка: " << getppid() << "\n";
		fout << "Идентификатор сессии процесса: " << getsid(getpid()) << "\n";
		fout << "Идентификатор группы процессов: " << getpgid(getpid()) << "\n";
		fout << "Реальный идентификатор процессов: " << getuid() << "\n";
		fout << "Эффективный идентификатор процессов: " << geteuid() << "\n";
		fout << "Реальный групповой идентификатор: " << getgid() << "\n";
		fout << "Эффективный групповой идентификатор: " << getegid() << "\n";	
		sleep(1);
		exit(0);
	}


	fout.close();
	exit(0);
}
