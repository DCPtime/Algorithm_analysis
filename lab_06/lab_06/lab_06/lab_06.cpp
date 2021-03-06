// lab_06.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <random>
#include <time.h>
#include "queue_multy_threads.h"
#include "queue_functions.h"
#include "With_log.h"
#include "order_log.h"

#define start_string_len 10
#define end_string_len 10
#define amount_of_string 10
#define repeat_amount 1

using namespace std;



int main()
{
	srand(time(NULL));
	
	unsigned __int64 single_time = 0;
	unsigned __int64 multy_time =  0;

	ofstream fout; // Объект для работы с файлами

	/*
	fout.open("order.txt");
	cout << "order" << endl;
	for (int i = start_string_len; i <= end_string_len; i = i * 2)
	{
		unsigned __int64 single_time = 0;
		for (int j = 0; j < repeat_amount; j++)
		{
			single_time += single_thread(amount_of_string, i);
		}
		single_time = single_time / repeat_amount;

		cout << "len = " << i << ", time = " << single_time << endl;
		fout << single_time << endl;

	}
	fout.close();

	fout.open("conveyor.txt");
	cout << "conveyor" << endl;
	for (int i = start_string_len; i <= end_string_len; i = i * 2)
	{
		unsigned __int64 multy_time = 0;
		for (int j = 0; j < repeat_amount; j++)
		{
			multy_time += multy_thread(amount_of_string, i);
		}
		multy_time = multy_time / repeat_amount;

		cout << "len = " << i << ", time = " << multy_time << endl;
		fout << multy_time << endl;

	}
	fout.close();
	*/

	cout << "running..." << endl;

	multy_time = multy_thread_log(10, 10);
	cout << "multy was finished, time = " << multy_time << endl;
	single_time = single_thread_order_log(10, 10);
	cout << "order was finished, time = " << single_time << endl;

	


	cout << "input key" << endl;
	char ReadKey = 0;
	cin >> ReadKey;
}
