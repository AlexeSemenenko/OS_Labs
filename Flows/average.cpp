#include <Windows.h>

#include "array_information.h"
#include "average.h"

DWORD WINAPI average(void* info) {
	Array_Information* inf = (Array_Information*)info;

	for (int i = 0; i < inf->size; i++) {
		inf->average += inf->array[i];

		Sleep(12);
	}

	inf->average /= inf->size;

	return 0;
}