#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;

void print(char* filename, int proc_num){

	ofstream file(filename, ios_base::app);
	
	switch (proc_num){
		case 0:{
			file << "\nПроцесс вызванный с помощью fork():\n";
			break;
		}
		case 1:{
			file << "\nПроцесс вызванный с помощью vfork():\n";
			break;
		}
		case 2:{
			file << "\nРодительский процесс:\n";
			break;
		}
	}
	
    file << "Идентификатор процесса: " << getpid() << "\n";
    file << "Идентификатор предка: " << getppid() << "\n";
    file << "Идентификатор сессии процесса: " << getsid(getpid()) << "\n";
    file << "Идентификатор группы процессов: " << getpgid(getpid()) << "\n";
    file << "Реальный идентификатор процессов: " << getuid() << "\n";
    file << "Эффективный идентификатор процессов: " << geteuid() << "\n";
    file << "Реальный групповой идентификатор: " << getgid() << "\n";
    file << "Эффективный групповой идентификатор: " << getegid() << "\n";
    
    file.close();
}

int main(int argc, char *argv[]){

    ofstream fout(argv[1]);
    fout << "Задержки процессов\n";
    fout << "Родительский процесс: " << argv[2] << "\n";
    fout << "Процесс вызванный с помощью fork: " << argv[3] << "\n";
    fout << "Процесс вызванный с помощью vfork: " << argv[4] << "\n\n";
    fout.close();
  
    if (fork() == 0) {
		sleep(stoi(argv[3]));	
		print (argv[1],0);
		exit(1);
    }

    if (vfork() == 0){
		sleep(stoi(argv[4]));
		print (argv[1],1);
	
        if (execl("process.cpp", " ", NULL) == -1)
        	exit(1);
	} else {
		sleep(stoi(argv[2]));
		print (argv[1],2);	
	}
	
    return 0;
}
