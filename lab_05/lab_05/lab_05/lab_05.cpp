// lab_05.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include<iostream> 
#include<cstdlib> 
#include<vector> 
#include<mutex> 
#include<thread> 
#include<Windows.h>

#include "MyMatrix.h"
#include "MyMatrix.cpp"

#include <cstdlib> // содержит srand() и rand()
#include <windows.h>
#include <intrin.h>
#pragma intrinsic(__rdtsc)

using namespace std;

const int amount_numbers = 5;

#define amount_of_sample 1
//#define thread_amount 64
#define max_threads 64

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
	int low_board, int high_board, int b_columns, int a_columns)
{
	for (int i = low_board; i < high_board; i++)
		for (int j = 0; j < b_columns; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < a_columns; k++)
				result[i][j] += a[i][k] * b[k][j];
		}

	//result.print_matrix();
}


void count_row_factors(MyMatrix<int> &G, MyMatrix<int> &H, MyMatrix<int> &result,
	int low_board, int high_board, int b, int c, int *rowFactor, int *columnFactor)
{
	// Вычисление rowFactors для G
	for (int i = low_board; i < high_board; i++)
	{
		rowFactor[i] = G[i][0] * G[i][1];
		for (int j = 2; j < b - 1; j = j + 2)
			rowFactor[i] = rowFactor[i] + G[i][j] * G[i][j + 1];
	}

	// вычисление columnFactors для H
	for (int i = low_board; i < high_board; i++)
	{
		columnFactor[i] = H[0][i] * H[1][i];
		for (int j = 2; j < b - 1; j = j + 2)
			columnFactor[i] = columnFactor[i] + H[j][i] * H[j][i + 1];
	}
}

void vinograd_mult(MyMatrix<int> &G, MyMatrix<int> &H, MyMatrix<int> &result,
	int low_board, int high_board, int b, int c, int *rowFactor, int *columnFactor)
{

	// Вычисление матрицы R
	for (int i = low_board; i < high_board; i++)
	{
		for (int j = 0; j < c; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < b - 1; k = k + 2)
			{
				result[i][j] = result[i][j] + (G[i][k] + H[j][k + 1]) * (G[i][k + 1] + H[k][j]);
			}

			result[i][j] = result[i][j] - rowFactor[i] - columnFactor[j];
		}
	}

	// Прибавление членов в случае нечетной общей размерности
	if (b % 2 != 0)
	{
		for (int i = low_board; i < high_board; i++)
			for (int j = 0; j < c; j++)
				result[i][j] = result[i][j] + G[i][b / 2] * H[b / 2][j];
	}

	//result.print_matrix();
}


void classic_mult_time_test(int start_size, int end_size, int step)
{
	unsigned __int64 time; // Результирующее время

	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;

	int current_size = start_size;

	for (int i = start_size; i <= end_size; i = i + step)
	{
		// Получаем матрицы размерности iter
		current_size = i;
		MyMatrix<int> a(current_size, current_size, 0);
		MyMatrix<int> b(current_size, current_size, 0);
		MyMatrix<int> result(current_size, current_size, 0);

		// Заполняем матрицы a и b случайными значениями от -100 до 100
		/*
		get_random_matrix(a, -100, 100);
		get_random_matrix(b, -100, 100);
		*/

		get_random_matrix(a, 2, 2);
		get_random_matrix(b, 3, 3);

		// Обнуляем переменные, связанные с замером времени
		start = 0; // Переменные для rdtsc
		end = 0;
		time = 0;

		for (int j = 0; j < amount_of_sample; j++)
		{

			for (int thread_amount = 1; thread_amount <= max_threads; thread_amount = thread_amount * 2)
			{
				start = 0; // Переменные для rdtsc
				end = 0;
				time = 0;

				thread *t_array = new thread[thread_amount];
				thread remainder;
				int row_for_thread = current_size / thread_amount;
				start = rdtsc();
				for (int k = 0; k < thread_amount; k++)
					t_array[k] = thread(classic_mult, ref(a), ref(b), ref(result), k*row_for_thread, (k + 1)*row_for_thread, b.get_columns(),
						a.get_rows());

				remainder = thread(classic_mult, ref(a), ref(b), ref(result), thread_amount*row_for_thread,
					a.get_rows(), b.get_columns(), a.get_rows());


				// ждем окончания всех потоков
				for (int k = 0; k < thread_amount; k++)
					t_array[k].join();
				remainder.join();
				end = rdtsc();
				time = time + (end - start);
				//result.print_matrix();

				time = time / amount_of_sample;
				cout << "Время для алгоритма винограда при количестве потоков " << thread_amount << " = " << time << endl;
				
			}
			
		}
		
		
	}

	cout << endl << endl;
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
		/*
		get_random_matrix(a, -100, 100);
		get_random_matrix(b, -100, 100);
		*/

		get_random_matrix(a, 2, 2);
		get_random_matrix(b, 3, 3);

		// Обнуляем переменные, связанные с замером времени
		start = 0; // Переменные для rdtsc
		end = 0;
		time = 0;

		for (int j = 0; j < amount_of_sample; j++)
		{

			for (int thread_amount = 1; thread_amount <= max_threads; thread_amount = thread_amount * 2)
			{
				start = 0; // Переменные для rdtsc
				end = 0;
				time = 0;

				thread *t_array = new thread[thread_amount];
				thread remainder;

				// row_factors
				int row_for_thread = current_size / thread_amount;
				start = rdtsc();
				for (int k = 0; k < thread_amount; k++)
					t_array[k] = thread(count_row_factors, ref(a), ref(b), ref(result), k*row_for_thread, (k + 1)*row_for_thread, b.get_columns(),
						a.get_rows(), ref(rowFactor), ref(columnFactor));

				remainder = thread(count_row_factors, ref(a), ref(b), ref(result), thread_amount*row_for_thread, 
					               a.get_rows(), b.get_columns(), a.get_rows(), ref(rowFactor), ref(columnFactor));

				// ждем окончания всех потоков
				for (int k = 0; k < thread_amount; k++)
					t_array[k].join();
				remainder.join();

				// Основная часть  + остаток, если необходимо
				for (int k = 0; k < thread_amount; k++)
					t_array[k] = thread(vinograd_mult, ref(a), ref(b), ref(result), k*row_for_thread, (k + 1)*row_for_thread, b.get_columns(),
						a.get_rows(), ref(rowFactor), ref(columnFactor));

				remainder = thread(vinograd_mult, ref(a), ref(b), ref(result), thread_amount*row_for_thread,
					a.get_rows(), b.get_columns(), a.get_rows(), ref(rowFactor), ref(columnFactor));

				// ждем окончания всех потоков
				for (int k = 0; k < thread_amount; k++)
					t_array[k].join();
				remainder.join();

				end = rdtsc();
				time = time + (end - start);

				//result.print_matrix();
				time = time / amount_of_sample;
				cout << "Время для алгоритма винограда при количестве потоков " << thread_amount << " = " << time << endl;
				
			}

		}

		

	}
}

/*
void my_print(int i, mutex &flag)
{
	flag.lock();
	cout << "current number = " << i << endl;
	flag.unlock();
}
*/

int main() 
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	/*
	const int amount = 5;
	mutex flag;
	// Массив потоков
	thread t_array[amount];
	for (int i = 0; i < amount; i++)
		t_array[i] = thread(my_print, i, ref(flag)); // ref(параметр) - передача параметра по ссылке в поток

	// Ожидание, пока закончатся все запущенные потоки
	for (int i = 0; i < amount; i++)
		t_array[i].join();


	for (int i = 0; i < 5; i++)
		t_array[i] = thread(my_print, i + amount, ref(flag)); // ref(параметр) - передача параметра по ссылке в поток

	// Ожидание, пока закончатся все запущенные потоки
	for (int i = 0; i < amount; i++)
		t_array[i].join();
    */

	
	cout << endl << "Алгоритм винограда" << endl;
	classic_mult_time_test(600, 600, 100);
	cout << "Классический алгоритм" << endl;
	vinograd_mult_time_test(600, 600, 100);



	return 0;
}

