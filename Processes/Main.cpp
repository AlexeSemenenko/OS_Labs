#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[])
{
    wstring creatorProc = L"D:\\University\\4sem\\OC\\Lab1\\Creator\\Debug\\Creator.exe";

    string nameBinFile;

    cout << "Enter name of binary file: ";
    cin >> nameBinFile;
    
    int recordsAmount;
    
    cout << "Enter amount of employees: ";
    cin >> recordsAmount;

	wstring wnameBinFile(nameBinFile.begin(), nameBinFile.end());

	wstring argArrayS1 = creatorProc + L" " + wnameBinFile + L" " + to_wstring(recordsAmount);
	wchar_t* lpszCommandLine1 = const_cast<wchar_t*>(argArrayS1.c_str());


	STARTUPINFO siF;
	PROCESS_INFORMATION piAppF;

	ZeroMemory(&siF, sizeof(STARTUPINFO));
	siF.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(NULL, lpszCommandLine1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siF, &piAppF)){
		cout << "The new process is not created" << endl;
		cout << "Check a name of the process" << endl;
		cout << "Press any key to finish" << endl;

		getchar();
		getchar();

		return 1;
	}
	
	WaitForSingleObject(piAppF.hProcess, INFINITE);

	CloseHandle(piAppF.hThread);
	CloseHandle(piAppF.hProcess);


	cout << endl << endl << "Contents of the binary file: " << endl;
	ifstream in1(nameBinFile, ios::binary);

	employee worker;

	if (in1.is_open()) {
		while (in1.read((char*)&worker, sizeof(employee)))
			cout << worker.num << " " << worker.name << " " << worker.hours << " " << worker.hours << endl;
	}
	else {
		cout << "Something went wrong with opening file";
		return 1;
	}

	in1.close();


	wstring reporterProc = L"D:\\University\\4sem\\OC\\Lab1\\Reporter\\Debug\\Reporter.exe";

	string reportFile;

	cout << endl << endl << "Enter name of report file: ";
	cin >> reportFile;

	double moneyPerHour;

	cout << "Enter amount of money per hour: ";
	cin >> moneyPerHour;

	std::wstring wreportFile(reportFile.begin(), reportFile.end());

	wstring argArrayS2 = reporterProc + L" " + wnameBinFile + L" " + wreportFile + L" " + to_wstring(moneyPerHour);
	wchar_t* lpszCommandLine2 = const_cast<wchar_t*>(argArrayS2.c_str());


	STARTUPINFO siS;
	PROCESS_INFORMATION piAppS;

	ZeroMemory(&siS, sizeof(STARTUPINFO));
	siS.cb = sizeof(STARTUPINFO);

	if (!CreateProcess(NULL, lpszCommandLine2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siS, &piAppS)) {
		cout << "The new process is not created" << endl;
		cout << "Check a name of the process" << endl;
		cout << "Press any key to finish" << endl;

		getchar();
		getchar();
		return 1;
	}

	WaitForSingleObject(piAppS.hProcess, INFINITE);

	CloseHandle(piAppS.hThread);
	CloseHandle(piAppS.hProcess);


	cout << endl << endl << "Report: " << endl;

	string line;

	ifstream in2(reportFile);

	if (in2.is_open()) {
		while (getline(in2, line))
			cout << line << endl;
	}
	else {
		cout << "Something went wrong with opening file";
		return 1;
	}

	in2.close();

	getchar();
	getchar();
	return 0;
}