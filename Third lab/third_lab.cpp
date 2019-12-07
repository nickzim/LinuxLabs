#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

    ofstream fout(argv[1]);
    fout << "Задержки процессов\n";
    fout << "Родительский процесс: " << argv[2] << "\n";
    fout << "Процесс вызванный с помощью fork: " << argv[3] << "\n";
    fout << "Процесс вызванный с помощью vfork: " << argv[4] << "\n\n";
    fout.close();
  
    if (fork() == 0) {
	sleep(stoi(argv[3]));	
	ofstream cout(argv[1]);
        cout << "\nПроцесс вызванный с помощью fork():\n";
        cout << "Идентификатор процесса: " << getpid() << "\n";
        cout << "Идентификатор предка: " << getppid() << "\n";
        cout << "Идентификатор сессии процесса: " << getsid(getpid()) << "\n";
        cout << "Идентификатор группы процессов: " << getpgid(getpid()) << "\n";
        cout << "Реальный идентификатор процессов: " << getuid() << "\n";
        cout << "Эффективный идентификатор процессов: " << geteuid() << "\n";
        cout << "Реальный групповой идентификатор: " << getgid() << "\n";
        cout << "Эффективный групповой идентификатор: " << getegid() << "\n";
		cout.close();
		exit(1);
    }

    if (vfork() == 0){
		sleep(stoi(argv[4]));
		ofstream cout(argv[1]);
        cout << "\nПроцесс вызванный с помощью vfork():\n";
        cout << "Идентификатор процесса: " << getpid() << "\n";
        cout << "Идентификатор предка: " << getppid() << "\n";
        cout << "Идентификатор сессии процесса: " << getsid(getpid()) << "\n";
        cout << "Идентификатор группы процессов: " << getpgid(getpid()) << "\n";
        cout << "Реальный идентификатор процессов: " << getuid() << "\n";
        cout << "Эффективный идентификатор процессов: " << geteuid() << "\n";
        cout << "Реальный групповой идентификатор: " << getgid() << "\n";
        cout << "Эффективный групповой идентификатор: " << getegid() << "\n";
        cout.close();
        
        if (execl("process.cpp", " ", NULL) == -1)
        	exit(1);
	} else {
		sleep(stoi(argv[2]));	
		ofstream cout(argv[1]);
        cout << "\nРодительский процесс:\n";
        cout << "Идентификатор процесса: " << getpid() << "\n";
        cout << "Идентификатор предка: " << getppid() << "\n";
        cout << "Идентификатор сессии процесса: " << getsid(getpid()) << "\n";
        cout << "Идентификатор группы процессов: " << getpgid(getpid()) << "\n";
        cout << "Реальный идентификатор процессов: " << getuid() << "\n";
        cout << "Эффективный идентификатор процессов: " << geteuid() << "\n";
        cout << "Реальный групповой идентификатор: " << getgid() << "\n";
        cout << "Эффективный групповой идентификатор: " << getegid() << "\n";
		cout.close();
	}
	
    return 0;
}
