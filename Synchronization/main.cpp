#include <iostream>
#include <windows.h>

DWORD WINAPI marker(void* id);

using namespace std;

CRITICAL_SECTION cs;

HANDLE hStartThreads;

HANDLE* impossibleContinue;
HANDLE* stopped;
HANDLE* continued;

int size;
int* array;

int main()
{
	cout << "Enter the size of array: ";
	cin >> ::size;

	::array = new int[::size];
	for (int i = 0; i < ::size; i++)
		::array[i] = 0;

	int currentAmount;

	cout << "Enter the number of therads: ";
	cin >> currentAmount;
	cout << endl << endl;

	unsigned int threads = currentAmount;

	HANDLE* hThread = new HANDLE[currentAmount];
	DWORD* IDThread = new DWORD[currentAmount];

	::impossibleContinue = new HANDLE[currentAmount];
	::stopped = new HANDLE[currentAmount];
	::continued = new HANDLE[currentAmount];

	::hStartThreads = CreateEvent(NULL, TRUE, FALSE, NULL);

	int* finalStopped = new int[currentAmount];
	int* ids = new int[currentAmount];

	for (int i = 0; i < currentAmount; i++) {
		finalStopped[i] = INT_MIN;
		ids[i] = i + 1;
	}

	InitializeCriticalSection(&::cs);

	EnterCriticalSection(&::cs);

	for (int i = 0; i < currentAmount; i++) {
		hThread[i] = CreateThread(NULL, 0, &marker, &ids[i], NULL, &IDThread[i]);

		::impossibleContinue[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		::stopped[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		::continued[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	SetEvent(::hStartThreads);

	int numStoppedThread;

	LeaveCriticalSection(&::cs);

	while (currentAmount != 0) {
		WaitForMultipleObjects(threads, ::impossibleContinue, TRUE, INFINITE);

		EnterCriticalSection(&::cs);

		cout << "Array: ";
		for (int i = 0; i < ::size; i++)
			cout << ::array[i] << " ";

		cout << endl << "Which thread should be stopped? ";
		cin >> numStoppedThread;

		SetEvent(::stopped[numStoppedThread - 1]);

		LeaveCriticalSection(&::cs);


		WaitForSingleObject(hThread[numStoppedThread - 1], INFINITE);

		EnterCriticalSection(&::cs);

		cout << "Array: ";
		for (int i = 0; i < ::size; i++)
			cout << ::array[i] << " ";
		cout << endl << endl;

		finalStopped[threads - currentAmount] = numStoppedThread - 1;
		currentAmount--;
		
		for (int i = 0; i < threads; i++) {
			bool founded = false;

			for (int j = 0; j < threads; j++)
				if (finalStopped[j] == i) 
					founded = true;

			if (!founded)
				ResetEvent(impossibleContinue[i]);
		}
		
		for (int i = 0; i < threads; i++) 
			SetEvent(::continued[i]);

		LeaveCriticalSection(&::cs);
	}

	DeleteCriticalSection(&::cs);

	CloseHandle(::hStartThreads);
	for (int i = 0; i < currentAmount; i++) {
		CloseHandle(hThread[i]);
		CloseHandle(::impossibleContinue[i]);
		CloseHandle(::stopped[i]);
		CloseHandle(::continued[i]);
	}

	delete[] ::array;
	delete[] hThread;
	delete[] IDThread;
	delete[] ::impossibleContinue;
	delete[] ::stopped;
	delete[] ::continued;
	delete[] finalStopped;
	delete[] ids;
	
	return 0;
}