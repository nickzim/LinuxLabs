#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string.h>

#define SIZE 200

using namespace std;

int main(int argc, char** argv){

	char buf[SIZE];
	ifstream fin; 
	fin.open(argv[1]);

	while (!fin.eof()){
		fin.getline(buf,SIZE);
		strcat(buf, "\n");
		write (*argv[2],buf,strlen(buf) + 1);
		usleep(10000);
	}
	
	fin.close();
	exit(0);
}
