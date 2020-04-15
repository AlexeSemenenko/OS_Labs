#include <Windows.h>

#include "array_information.h"
#include "min_max.h"

DWORD WINAPI min_max(void* info) {
	Array_Information* inf = (Array_Information*)info;

	for (int i = 0; i < inf->size; i++) {
		if (inf->array[i] > inf->array[inf->max_index])
			inf->max_index = i;

		Sleep(7);

		if (inf->array[i] < inf->array[inf->min_index])
			inf->min_index = i;

		Sleep(7);
	}

	return 0;
}