#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string.h>

#define SIZE 200

using namespace std;

int main(){

	int fields[2];

	if (pipe(fields) < 0){
		exit(1);
	} else {
		cout << "Pipe is open\n\n";
	}

	pid_t pid_1, pid_2;
	
	pid_1 = fork();
	if (pid_1 == 0){

		pid_2 = fork();
		if (pid_2 == 0){
			//Первый процесс-потомок

			execl("input1", "input1", "input_1.txt", &fields[1], NULL);
			exit(0);
		}
		else{
			//Второй процесс-потомок

			execl("input2", "input2", "input_2.txt", &fields[1], NULL);
			exit(0);
		}
	} else {
		//Родительский процесс


        wait(&pid_1);
		wait(&pid_2);
		
		ofstream fout("output.txt");
	
	
		close (fields[1]);

		char output;
		while (read (fields[0],&output,1) > 0){	
			if (output != '\0'){	
				fout << output;
			}
			
		}

		close(fields[0]);
		
		fout.close();
	}

	return 0;
}
