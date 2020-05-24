#pragma once

#include <windows.h>
#include <iostream>

using namespace std;

extern CRITICAL_SECTION cs;

extern HANDLE hStartThreads;

extern HANDLE* impossibleContinue;
extern HANDLE* stopped;
extern HANDLE* continued;

extern int size;
extern int* array;

DWORD WINAPI marker(void* id) {
	int* isMarked = new int[::size];

	int markedNumber = 0;

	while (true) {
		WaitForSingleObject(::hStartThreads, INFINITE);

		EnterCriticalSection(&::cs);

		int currentId = *((int*)id);

		srand(currentId);

		int num = rand();
		num %= ::size;

		if (::array[num] == 0) {
			Sleep(5);

			::array[num] = currentId;
			isMarked[markedNumber] = num;
			markedNumber++;

			Sleep(5);

			LeaveCriticalSection(&::cs);
		}
		else {
			cout << "Id: " << currentId << ", number of marked elemnts: " << markedNumber << ", impossible to mark this element: " << num + 1 << endl;

			LeaveCriticalSection(&::cs);

			SetEvent(::impossibleContinue[currentId - 1]);

			HANDLE waiting[] = { ::stopped[currentId - 1], ::continued[currentId - 1] };

			if (WaitForMultipleObjects(2, waiting, FALSE, INFINITE) == WAIT_OBJECT_0 + 0) {
				EnterCriticalSection(&::cs);

				for (int i = 0; i < markedNumber; i++)
					::array[isMarked[i]] = 0;

				delete[] isMarked;

				LeaveCriticalSection(&::cs);

				break;
			}
		}
	}

	return 0;
}