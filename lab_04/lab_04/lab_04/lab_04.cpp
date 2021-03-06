// lab_04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include<stdlib.h>
#include<time.h>


#include <cstdlib> // содержит srand() и rand()
#include <windows.h>


#include <intrin.h>
#pragma intrinsic(__rdtsc)

#define low_board_array -100
#define hith_board_array 100
#define amount_of_sample 1000
#define min_element -1000

using namespace std;
// Для работы замера времени
unsigned __int64 rdtsc()
{
	return __rdtsc();
}


int get_random_int(int low_bord, int high_bord)
{
	return(low_bord + rand() % (abs(low_bord - high_bord) + 1));
}

void get_simple_array(int *a, int amount)
{
	for (int i = 0; i < amount; i++)
		a[i] = 0;
}

void get_random_array(int *a, int amount)
{
	for (int i = 0; i < amount; i++)
		a[i] = get_random_int(low_board_array, hith_board_array);
}

void get_low_to_high_array(int *a, int amount)
{
	for (int i = 0; i < amount; i++)
		a[i] = i;
}

void get_high_to_low_array(int *a, int amount)
{
	int k = 0;
	for (int i = amount - 1; i >= 0; i--)
	{
		a[k] = i;
		k = k + 1;
	}
}

void get_no_dubles_array(int *a, int amount)
{
	for (int i = 0; i < amount; i++)
		a[i] = i*3;
}

void print_array(int *a, int amount)
{
	for (int i = 0; i < amount; i++)
		cout << a[i] << "     ";
	cout << endl;
		
}

unsigned __int64 sort_insert_board(int *b, int amount)
{
	//Получили массив с добавленной компонентой 
	int *a = new int[amount + 1];
	for (int i = amount; i > 0; i--)
		a[i] = b[i-1];

	a[0] = min_element;

	int j = 0;

	unsigned __int64 time = 0; // Результирующее время

	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	start = rdtsc();
	for (int i = 2; i < amount + 1; i++)
	{

		if (a[i-1] > a[i])
		{
			a[0] = a[i];
			j = i - 1;
			while (a[j] > a[0])
			{
				a[j + 1] = a[j];
				j = j - 1;
			}
			a[j + 1] = a[0];
		}
	}

	end = rdtsc();

	for (int i = 1; i < amount + 1; i++)
		b[i-1] = a[i];

	delete a;

	time = time + (end - start);

	return(time);
}


unsigned __int64 comb_sort(int* data, int count)
   {
	double gap = count;
	bool swaps = true;

	unsigned __int64 time = 0; // Результирующее время
	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	start = rdtsc();
	while (gap > 1 || swaps)
	{
		gap /= 1.247330950103979;

		if (gap < 1)
			gap = 1;

		int i = 0;
		swaps = false;

		while (i + gap < count)
		{
			int igap = i + (int)gap;

			if (data[i] > data[igap])
			{
				int temp = data[i];
				data[i] = data[igap];
				data[igap] = temp;
				swaps = true;
			}

			++i;
		}
	}

	end = rdtsc();
	time = time + (end - start);
	return(time);
}


void test_time_insert(int start, int stop, int step)
{
	unsigned __int64 result_insert = 0;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_insert = 0;
		for (int j = 0; j < amount_of_sample; j++)
		{
			get_random_array(array_1, i);
			result_insert += sort_insert_board(array_1, i);
		}
		result_insert /= amount_of_sample;
		cout << "Время работы сортировки в случайном массиве алгоритмом простых вставок с барьером при N " << i << " = "
			<< result_insert << endl;
		delete array_1;
	}

	cout << endl;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_insert = 0;


		for (int j = 0; j < amount_of_sample; j++)
		{
			get_low_to_high_array(array_1, i);
			result_insert += sort_insert_board(array_1, i);
		}
		result_insert /= amount_of_sample;
		cout << "Время работы сортировки в лучшем случае для алгоритма простых вставок с барьером при N " << i << " = "
			<< result_insert << endl;
		delete array_1;
	}

	cout << endl;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_insert = 0;


		for (int j = 0; j < amount_of_sample; j++)
		{
			get_high_to_low_array(array_1, i);
			result_insert += sort_insert_board(array_1, i);
		}
		result_insert /= amount_of_sample;
		cout << "Время работы сортировки в худшем случае для алгоритма простых вставок с барьером при N " << i << " = "
			<< result_insert << endl;
		delete array_1;
	}

	cout << endl;
}

void test_time_comb(int start, int stop, int step)
{
	unsigned __int64 result_comb = 0;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_comb = 0;
		for (int j = 0; j < amount_of_sample; j++)
		{
			get_random_array(array_1, i);
			result_comb += comb_sort(array_1, i);
		}
		result_comb /= amount_of_sample;
		cout << "Время работы сортировки в случайном массиве алгоритмом расчески при N " << i << " = "
			<< result_comb << endl;
		delete array_1;
	}

	cout << endl;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_comb = 0;


		for (int j = 0; j < amount_of_sample; j++)
		{
			get_low_to_high_array(array_1, i);
			result_comb += comb_sort(array_1, i);
		}
		result_comb /= amount_of_sample;
		cout << "Время работы сортировки расческой в отсортированном по возрастанию массиве при N " << i << " = "
			<< result_comb << endl;
		delete array_1;
	}

	cout << endl;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_comb = 0;


		for (int j = 0; j < amount_of_sample; j++)
		{
			get_high_to_low_array(array_1, i);
			result_comb += comb_sort(array_1, i);
		}
		result_comb /= amount_of_sample;
		cout << "Время работы сортировки расческойв отсортированном по убыванию массив при N " << i << " = "
			<< result_comb << endl;
		delete array_1;
	}

	cout << endl;
}


// Функция "просеивания" через кучу - формирование кучи
void siftDown(int *numbers, int root, int bottom)
{
	int maxChild; // индекс максимального потомка
	int done = 0; // флаг того, что куча сформирована
	// Пока не дошли до последнего ряда
	while ((root * 2 <= bottom) && (!done))
	{
		if (root * 2 == bottom)    // если мы в последнем ряду, 
			maxChild = root * 2;    // запоминаем левый потомок
		  // иначе запоминаем больший потомок из двух
		else if (numbers[root * 2] > numbers[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		// если элемент вершины меньше максимального потомка
		if (numbers[root] < numbers[maxChild])
		{
			int temp = numbers[root]; // меняем их местами
			numbers[root] = numbers[maxChild];
			numbers[maxChild] = temp;
			root = maxChild;
		}
		else // иначе
			done = 1; // пирамида сформирована
	}
}
// Функция сортировки на куче
unsigned __int64  heapSort(int *numbers, int array_size)
{
	unsigned __int64 time = 0; // Результирующее время
	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	start = rdtsc();
	// Формируем нижний ряд пирамиды
	for (int i = (array_size / 2) - 1; i >= 0; i--)
		siftDown(numbers, i, array_size - 1);
	// Просеиваем через пирамиду остальные элементы
	for (int i = array_size - 1; i >= 1; i--)
	{
		int temp = numbers[0];
		numbers[0] = numbers[i];
		numbers[i] = temp;
		siftDown(numbers, 0, i - 1);
	}
	end = rdtsc();
	time = end - start;
	return(time);
}

void test_time_heap(int start, int stop, int step)
{
	unsigned __int64 result_heap = 0;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_heap = 0;
		for (int j = 0; j < amount_of_sample; j++)
		{
			get_random_array(array_1, i);
			result_heap += heapSort(array_1, i);
		}
		result_heap /= amount_of_sample;
		cout << "Время работы пирамидальной сортировки в случайном массиве при N " << i << " = "
			<< result_heap << endl;
		delete array_1;
	}

	cout << endl;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_heap = 0;


		for (int j = 0; j < amount_of_sample; j++)
		{
			get_low_to_high_array(array_1, i);
			result_heap += heapSort(array_1, i);
		}
		result_heap /= amount_of_sample;
		cout << "Время работы пирамидальной сортировки в худшем случае при N " << i << " = "
			<< result_heap << endl;
		delete array_1;
	}

	cout << endl;

	for (int i = start; i <= stop; i = i + step)
	{
		int *array_1 = new int[i];
		result_heap = 0;


		for (int j = 0; j < amount_of_sample; j++)
		{
			get_high_to_low_array(array_1, i);
			result_heap += heapSort(array_1, i);
		}
		result_heap /= amount_of_sample;
		cout << "Время работы пирамидальной сортировки в лучшем случае при N " << i << " = "
			<< result_heap << endl;
		delete array_1;
	}

	cout << endl;
}


int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	srand(time(0));
	int amount = 10;
	int *a = new int[amount];
	//get_high_to_low_array(a, amount);
	get_random_array(a, amount);
	cout << "Исходный массив:  ";
	print_array(a, amount);
	cout << "Сортировка вставками    :";
	sort_insert_board(a, amount);
	print_array(a, amount);
	cout << "Сортировка расческой    :";
	comb_sort(a, amount);
	print_array(a, amount);
	cout << "Пирамидальная сортирвка :";
	heapSort(a, amount);
	print_array(a, amount);

	/*
	get_random_array(array, amount);
	print_array(array, amount);
	get_low_to_high_array(array, amount);
	print_array(array, amount);
	get_high_to_low_array(array, amount);
	print_array(array, amount);
	*/

	test_time_insert(100, 1000, 100);
	test_time_comb(100, 1000, 100);
	test_time_heap(100, 1000, 100);


	system("pause");
}

