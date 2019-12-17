#include <fstream>
#include <ctime>

using namespace std;

int main(){

	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);

	ofstream fout;	
	fout.open("crontab_output.txt", ios::app);
	fout << "Current time: " << asctime(timeinfo) << "\n";
	fout.close();

	return 0;
}
