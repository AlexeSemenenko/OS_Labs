#include <iostream>
#include <fstream>

using namespace std;

struct employee{
	int num;
	char name[10];
	double hours;

	employee(int num, const char* name, double hours){
		this->num = num;
		strcpy_s(this->name, name);
		this->hours = hours;
	}
};

int main(int argc, char* argv[])
{
	const char* fileName = argv[1];
	int employees = atoi(argv[2]);

	ofstream out(fileName, ios::binary);

	cout << "Enter the employee number, the employee name  and the employee hours: ";

	if (out.is_open()) {
		for (int i = 0; i < employees; i++) {
			int num;
			char name[10];
			double hours;

			cin >> num;

			cin >> name;

			cin >> hours;

			cout << endl << "Next" << endl << endl;

			employee worker = employee(num, name, hours);

			out.write((char*)&worker, sizeof(employee));
		}
	}
	else {
		cout << "Something went wrong with creating the file";
		return 1;
	}

	out.close();

	return 0;
} 