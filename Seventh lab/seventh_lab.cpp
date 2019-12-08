#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string.h>

#define SIZE 200

using namespace std;

int main(int argc, char* argv){

	int fields[2];
	char buf1[SIZE];
	char buf2[SIZE];
	char output;

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
			//Второй процесс-потомок

			ifstream fin; 
			fin.open("input_2.txt");

			while (!fin.eof()){
				fin.getline(buf2,SIZE);
				write (fields[1],buf2,strlen(buf2) + 1);
			}

			fin.close();
			exit(0);
		}
		else{
			//Первый процесс-потомок

			ifstream fin; 
			fin.open("input_1.txt");

			while (!fin.eof()){
				fin.getline(buf1,SIZE);	
				write (fields[1],buf1,strlen(buf1) + 1);
			}

			fin.close();	
			exit(0);
		}
	} else {
		//Родительский процесс

		ofstream fout("output.txt");
	
		close (fields[1]);

		while (read (fields[0],&output,4) > 0){		
			fout << &output;
		}

		wait (&pid_1);
		wait (&pid_2);

		close(fields[0]);
		close(fields[1]);
		
		fout.close();
	}

	return 0;
}
