#include <fstream>

using namespace std;

int main(){

	ofstream fout;	
	fout.open("crontab_output.txt", ios::app);
	fout << "Тестовая строка\n";
	fout.close();

	return 0;
}
