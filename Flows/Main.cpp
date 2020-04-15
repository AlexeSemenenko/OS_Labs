#include <iostream>
#include <Windows.h>

#include "array_information.h"
#include "min_max.h"
#include "average.h"

using namespace std;

int main()
{
    int size;

    cout << "Enter size of array: ";
    cin >> size;

    double *numbers = new double[size];

    cout << endl << "Enter elements: " << endl;

    for (int i = 0; i < size; i++) {
        cin >> numbers[i];
    }

    Array_Information inf = { size, numbers, 0, 0, 0.0 };

    HANDLE min_max_hthread;
    DWORD min_max_idthread;

    min_max_hthread = CreateThread(NULL, 0, min_max, (void*)&inf, 0, &min_max_idthread);
    WaitForSingleObject(min_max_hthread, INFINITE);
    CloseHandle(min_max_hthread);

    HANDLE average_hthread;
    DWORD average_idthread;

    average_hthread = CreateThread(NULL, 0, average, (void*)&inf, 0, &average_idthread);
    WaitForSingleObject(average_hthread, INFINITE);
    CloseHandle(average_hthread);

    inf.array[inf.min_index] = inf.array[inf.max_index] = inf.average;

    cout << endl << "New array: " << endl;

    for (int i = 0; i < size; i++)
        cout << numbers[i] << " ";

    delete[] numbers;

    getchar();
    getchar();
    return 0;
}
