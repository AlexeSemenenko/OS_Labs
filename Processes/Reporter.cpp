#include <iostream>
#include <fstream>

using namespace std;

struct employee{
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* argv[])
{
	const char* nameSourceBinFile = argv[1];

	const char* nameReportFile = argv[2];

	double moneyPerHour = atof(argv[3]);

	ifstream in(nameSourceBinFile, ios::binary);
	ofstream out(nameReportFile);

	employee worker;

	if (out.is_open()) {
		out << "Report on the " << nameSourceBinFile << endl;

		if (in.is_open()) {
			while (in.read((char*)&worker, sizeof(employee)))
				out << worker.num << " " << worker.name << " " << worker.hours << " "
				<< worker.hours * moneyPerHour << endl;
		}
		else {
			cout << "Something went wrong with input file";
			return 1;
		}
	}
	else {
		cout << "Something went wrong with output file";
		return 1;
	}

	in.close();
	out.close();

    return 0;
}
