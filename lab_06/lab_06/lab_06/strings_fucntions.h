#pragma once

#include <iostream>
#include <queue>
#include <string>

#include <windows.h>
#include <intrin.h>
#pragma intrinsic(__rdtsc)
using namespace std;

// Для работы замера времени
unsigned __int64 rdtsc()
{
	return __rdtsc();
}

void up_string(string &var)
{
	for (int i = 0; i < var.length(); i++)
		var[i] = var[i] - 32;
}

void exchange_symbol(string &string_var, string symbol_a, string symbol_b)
{
	for (int i = 0; i < string_var.length(); i++)
		if (string_var[i] == symbol_a[0])
			string_var[i] = symbol_b[0];
}
