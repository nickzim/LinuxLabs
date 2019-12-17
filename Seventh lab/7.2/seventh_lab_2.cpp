#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string.h>


using namespace std;

int main(){

	int fields[2];
	
	if (pipe(fields) < 0){
		exit(1);
	} else {
		cout << "Pipe is open\n\n";
	}

	char buf[128];
	
	ifstream fin; 
	fin.open("input.txt");
	
	pid_t pid_1, pid_2;
	while (!fin.eof()){
	
		fin.getline(buf,128);
		strcat(buf, "\n");
		write (fields[1],buf,strlen(buf) + 1);	
		
		pid_1 = vfork();
		if (pid_1 == 0){
			ofstream fout("output_1.txt");
			close (fields[1]);

			char output;
			read (fields[0],&output,1);	
			if (output != '\0'){	
				fout << output;
				cout << output;
			}
			exit(1);
		}

		pid_2 = vfork();
		if (pid_2 == 0){
			ofstream fout("output_2.txt");
			close (fields[1]);

			char output;
			read (fields[0],&output,1);	
			if (output != '\0'){	
				fout << output;
				cout << output;
			}
			exit(1);
		}
		
		
	}
	
	return 0;
}
	
