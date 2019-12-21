#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string.h>


using namespace std;

pid_t pid_1, pid_2;
int fields[2];
ofstream fout_one("output_1.txt");
ofstream fout_two("output_2.txt");

void Signal_handler(int signal_num){
	
	switch(signal_num){
	
		case SIGUSR1: {
			if (pid_1 == 0){
				char output;
				if (read (fields[0],&output,1) == -1){
					cout << strerror(errno) << "\n";
				}
						
				if ((int)output != -1){	
				   fout_one << output;
				   cout << "Symbol: " << (int)output << endl;
				}
				
			}
			break;
		}
		
		case SIGUSR2: {
			if (pid_2 == 0){
				char output;
				if (read (fields[0],&output,1) == -1){
					cout << strerror(errno) << "\n";
				}
					
				if ((int)output != -1){	
				   fout_two << output;
				   cout << "Symbol: " << (int)output << endl;
				}

			}
			break;
		}	
			
	}
}

int main(){

	
	if (pipe(fields) < 0){
		exit(1);
	} else {
		cout << "Pipe is open\n\n";
	}
	
	ifstream fin; 
	fin.open("input.txt");
	
	pid_1 = vfork();
	pid_2 = vfork();
	
	signal (SIGUSR1, Signal_handler);
	signal (SIGUSR2, Signal_handler);

	char buf;
	int count = 0;
	
	while (!fin.eof()){
	
		buf = fin.get();
		write (fields[1],&buf,1);	
		
		if (count % 2 == 0){
			raise (SIGUSR1);
		} else {
			raise (SIGUSR2);
		}
		
		count++;
	}
	
	fout_one.close();
	fout_two.close();
	
	kill(pid_1,SIGTERM);
	kill(pid_2,SIGTERM);
	
	return 0;
}
	
