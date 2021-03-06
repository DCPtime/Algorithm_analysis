// lab_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

#include "MyMatrix.h"
#include "MyMatrix.cpp"

#include <cstdlib> // содержит srand() и rand()
#include <windows.h>

#include <intrin.h>
#pragma intrinsic(__rdtsc)


#define amount_of_sample 1

// Для работы замера времени
unsigned __int64 rdtsc()
{
	return __rdtsc();
}


int get_random_int(int low_bord, int high_bord)
{
	return(low_bord + rand() % (abs(low_bord - high_bord) + 1));
}

void get_random_matrix(MyMatrix<int> &result_matrix, int low_border, int high_border)
{
	int rows = result_matrix.get_rows();
	int columns = result_matrix.get_columns();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			result_matrix[i][j] = get_random_int(low_border, high_border);
}

void classic_mult(MyMatrix<int> &a, MyMatrix<int> &b, MyMatrix<int> &result,
	              int a_rows, int b_columns, int a_columns)
{
	for (int i = 0; i < a_rows; i++)
		for (int j = 0; j < b_columns; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < a_columns; k++)
				result[i][j] += a[i][k] * b[k][j];
		}

	//result.print_matrix();
}

void classic_mult_time_test(int start_size, int end_size, int step)
{
	unsigned __int64 time; // Результирующее время

	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	int current_size = start_size;

	for (int i = start_size; i <= end_size; i = i + 100)
	{
		// Получаем матрицы размерности iter
		current_size = i;
		MyMatrix<int> a(current_size, current_size, 0);
		MyMatrix<int> b(current_size, current_size, 0);
		MyMatrix<int> result(current_size, current_size, 0);

		// Заполняем матрицы a и b случайными значениями от -100 до 100
		get_random_matrix(a, -100, 100);
		get_random_matrix(b, -100, 100);

		// Обнуляем переменные, связанные с замером времени
		start = 0; // Переменные для rdtsc
		end = 0;
		time = 0;

		for (int j = 0; j < amount_of_sample; j++)
		{
			start = rdtsc();
			classic_mult(a, b, result, a.get_rows(), b.get_columns(), a.get_rows());
			end = rdtsc();
			time = time + (end - start);
		}
		time = time / amount_of_sample;
		cout << "Время для классического алгоритма при размерах матриц " << current_size << " = " << time << endl;
	}
}

void vinograd_mult(MyMatrix<int> &G, MyMatrix<int> &H, MyMatrix<int> &result,
	int a, int b, int c, int *rowFactor, int *columnFactor)
{

	// Вычисление rowFactors для G
	for (int i = 0; i < a; i++)
	{
		rowFactor[i] = G[i][0] * G[i][1];
		for (int j = 2; j < b - 1; j = j + 2)
			rowFactor[i] = rowFactor[i] + G[i][j] * G[i][j+1];
	}

	// вычисление columnFactors для H
	for (int i = 0; i < c; i++ )
	{
		columnFactor[i] = H[0][i] * H[1][i];
		for (int j = 2; j < b - 1; j = j + 2)
			columnFactor[i] = columnFactor[i] + H[j][i] * H[j][i+1];
	}

	// Вычисление матрицы R
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < c; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < b - 1; k = k + 2)
			{
				result[i][j] = result[i][j] + (G[i][k] + H[j][k+1]) * (G[i][k+1] + H[k][j]);
			}

			result[i][j] = result[i][j] - rowFactor[i] - columnFactor[j];
		}
	}

	// Прибавление членов в случае нечетной общей размерности
	if (b % 2 != 0)
	{
		for (int i = 0; i < a; i++)
			for (int j = 0; j < c; j++)
				result[i][j] = result[i][j] + G[i][b/2] * H[b/2][j];
	}

	//result.print_matrix();
}

void vinograd_mult_time_test(int start_size, int end_size, int step)
{
	unsigned __int64 time; // Результирующее время

	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	int current_size = start_size;

	for (int i = start_size; i <= end_size; i = i + 100)
	{
		// Получаем матрицы размерности iter
		current_size = i;
		MyMatrix<int> a(current_size, current_size, 0);
		MyMatrix<int> b(current_size, current_size, 0);
		MyMatrix<int> result(current_size, current_size, 0);
		int *rowFactor = new int[a.get_rows()];
		int *columnFactor = new int[b.get_columns()];

		// Заполняем матрицы a и b случайными значениями от -100 до 100
		get_random_matrix(a, -100, 100);
		get_random_matrix(b, -100, 100);

		// Обнуляем переменные, связанные с замером времени
		start = 0; // Переменные для rdtsc
		end = 0;
		time = 0;

		for (int j = 0; j < amount_of_sample; j++)
		{
			start = rdtsc();
			vinograd_mult(a, b, result, a.get_rows(), a.get_columns(), b.get_columns(), rowFactor, columnFactor);
			end = rdtsc();
			time = time + (end - start);
		}
		time = time / amount_of_sample;
		cout << "Время для неулучшенного алгоритма винограда при размерах матриц " << current_size << " = " << time << endl;
	}
}

void vinograd_mult_improve(MyMatrix<int> &G, MyMatrix<int> &H, MyMatrix<int> &result,
	int a, int b, int c, int *rowFactor, int *columnFactor)
{
	int d = b / 2; // Переменная, целью которой является избавление от делений
	int buffer = 0; // Переменная, целью которой является избавление уменьшение обращений по индексам
	int var_minus = b-1; // Переменная, целью которой является избавление от вычитаний в циклах

	// Вычисление rowFactors для G
	for (int i = 0; i < a; i++)
	{
		buffer = G[i][0] * G[i][1]; // Добавили буфер, чтобы уменьшить количество обращений по индексу в циклах
		for (int j = 2; j < var_minus; j += 2) // избавились от вычитания в условии цикла, добавили +=
			buffer += G[i][j] * G[i][j + 1]; // сумма в буфере
		rowFactor[i] = buffer; // присвоили результат из буфера
	}

	// вычисление columnFactors для H
	for (int i = 0; i < c; i++)
	{
		buffer = H[0][i] * H[1][i]; // Добавили буфер, чтобы уменьшить количество обращений по индексу в циклах
		for (int j = 2; j < var_minus; j += 2) // избавились от вычитания в условии цикла, добавили +=
			buffer += H[j][i] * H[j][i + 1]; // сумма в буфере
		columnFactor[i] = buffer; // присвоили результат из буфера

	}

	// Вычисление матрицы R
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < c; j++)
		{
			buffer = 0; // Добавили буфер, чтобы уменьшить количество обращений по индексу в циклах
			for (int k = 0; k < var_minus; k += 2) // добавили +=, убрали вычитание из условия цикла
			{
				buffer += (G[i][k] + H[j][k + 1]) * (G[i][k + 1] + H[k][j]); // Добавили +=, сумма в буфере
			}

			buffer -= (rowFactor[i] + columnFactor[j]); // Добавили -=, уменьшили количество вычитаний, резульат в буфере
			result[i][j] = buffer; // присвоили результат из буфера
		}
	}

	// Прибавление членов в случае нечетной общей размерности
	if (b % 2 != 0)
	{
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < c; j++)
				result[i][j] += G[i][d] * H[d][j]; // убрали деление и добавили +=
		}

	}

	//result.print_matrix();
}

void vinograd_improve_mult_time_test(int start_size, int end_size, int step)
{
	unsigned __int64 time; // Результирующее время

	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	int current_size = start_size;

	for (int i = start_size; i <= end_size; i = i + 100)
	{
		// Получаем матрицы размерности iter
		current_size = i;
		MyMatrix<int> a(current_size, current_size, 0);
		MyMatrix<int> b(current_size, current_size, 0);
		MyMatrix<int> result(current_size, current_size, 0);
		int *rowFactor = new int[a.get_rows()];
		int *columnFactor = new int[b.get_columns()];

		// Заполняем матрицы a и b случайными значениями от -100 до 100
		get_random_matrix(a, -100, 100);
		get_random_matrix(b, -100, 100);

		// Обнуляем переменные, связанные с замером времени
		start = 0; // Переменные для rdtsc
		end = 0;
		time = 0;

		for (int j = 0; j < amount_of_sample; j++)
		{
			start = rdtsc();
			vinograd_mult_improve(a, b, result, a.get_rows(), a.get_columns(), b.get_columns(), rowFactor, columnFactor);
			end = rdtsc();
			time = time + (end - start);
		}
		time = time / amount_of_sample;
		cout << "Время для   улучшенного алгоритма винограда при размерах матриц " << current_size << " = " << time << endl;
	}
}

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	MyMatrix<int> first(2, 2, -1);
	MyMatrix<int> second(2, 2, 3);
	MyMatrix<int> result(2, 2, 0);
	int *rowFactor = new int[first.get_rows()];
	int *columbFactor = new int[second.get_columns()];

	// Пример работы
	/*cout << "Улучшенный виноград" << endl;
	vinograd_mult_improve(first, second, result, first.get_rows(), first.get_columns(), second.get_columns(), rowFactor,
		                  columbFactor);
	cout << "Обычный виноград" << endl;
	vinograd_mult(first, second, result, first.get_rows(), first.get_columns(), second.get_columns(), rowFactor,
		columbFactor);
	cout << "Классическое умножение" << endl;
	classic_mult(first, second, result, first.get_rows(), second.get_columns(), second.get_rows());
	*/

	
	vinograd_mult_time_test(101, 1001, 100);
	cout << endl;
	vinograd_improve_mult_time_test(101, 1001, 100);
	cout << endl;
	classic_mult_time_test(101, 1001, 100);
	cout << endl;
	
	system("pause");
}
