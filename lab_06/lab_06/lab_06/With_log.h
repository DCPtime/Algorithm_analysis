#pragma once
#pragma once

#include <queue>
#include <string>
#include <random>
#include <iostream>
#include "strings_fucntions.h"
#include<mutex> 
#include<thread>
#include <fstream>

using namespace std;



// Заполнение очередки строками длины length_word и количеством amount_word
void fill_vector_log(vector<string>& obj, int amount_word, int length_word)
{
	const int alphabet_len = 26;
	char alphabet[alphabet_len] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						 'h', 'i', 'j', 'k', 'l', 'm', 'n',
						 'o', 'p', 'q', 'r', 's', 't', 'u',
						 'v', 'w', 'x', 'y', 'z' };

	string var = "";
	for (int i = 0; i < amount_word; i++)
	{
		var = "";
		for (int j = 0; j < length_word; j++)
			var = var + alphabet[rand() % alphabet_len];
		var = var + std::to_string(i);
		obj.push_back(var);
	}
}

void from_vector_to_start_log(vector<string> &initial_vector, queue<string> &myQueue_initial, mutex &my_mutex, bool &finished, ofstream &fout)
{

	for (int i = 0; i < initial_vector.size(); i++)
	{
		string current_string = initial_vector[i];
		my_mutex.lock();
		myQueue_initial.push(initial_vector[i]);
		fout << current_string[current_string.length() - 1] << "  was pushed in queue_0" << endl;
		my_mutex.unlock();
		Sleep(500);
	}

	finished = true;
}

void from_init_to_up_log(queue<string> &myQueue_initial, queue<string> &myQueue_up, mutex &my_mutex, bool &previous_over,
	bool &finished, ofstream &fout)
{
	// Пока очередь не пуста
	while (myQueue_initial.size() != 0 || previous_over == 0)
	{
		if (myQueue_initial.size() != 0)
		{
			// Извлекли очередную строку
			string current_string = myQueue_initial.front();
			// Применили функцию приведения к новому регистру
			up_string(current_string);

			my_mutex.lock();
			fout << current_string[current_string.length()-1] << "  was thrown out of the queue_0 and pushed to queue_1" << endl;
			// Убрали текущий элемент из  очереди
			myQueue_initial.pop();
			// Добавили этот элемент в следующую очередь очередь (повышения регистра)
			myQueue_up.push(current_string);
			my_mutex.unlock();
		}
	}

	finished = true;
}

void from_up_to_change_log(queue<string> &myQueue_up, queue<string> &myQueue_exchg, mutex &my_mutex, bool &previous_over,
	bool &finished, ofstream &fout)
{
	// Пока очередь не пуста
	while (myQueue_up.size() != 0 || previous_over == 0)
	{
		if (myQueue_up.size() != 0)
		{
			// Извлекли очередную строку
			string current_string = myQueue_up.front();
			// Меняем буквы
			exchange_symbol(current_string, "A", "B");

			my_mutex.lock();
			fout << current_string[current_string.length() - 1] << "  was thrown out of the queue_1 and pushed to queue_2" << endl;
			// Убрали текущий элемент из очереди
			myQueue_up.pop();
			// Добавили этот элемент в следующую очередь очередь (готовые строки)
			myQueue_exchg.push(current_string);
			my_mutex.unlock();
		}
	}
	finished = true;
}

void from_exchg_to_result_log(queue<string> &myQueue_exchg, vector<string> &result_vector, mutex &my_mutex, bool &previous_over, ofstream &fout)
{
	// Пока очередь не пуста
	while (myQueue_exchg.size() != 0 || previous_over == 0)
	{
		if (myQueue_exchg.size() != 0)
		{
			Sleep(1000);
			my_mutex.lock();
			// Извлекли очередную строку
			string current_string = myQueue_exchg.front();
			fout << current_string[current_string.length() - 1] << "  was thrown out of the queue_2 and pushed to vector" << endl;
			// Дополнили результирующий вектор
			result_vector.push_back(current_string);
			// Убрали текущий элемент из  очереди
			myQueue_exchg.pop();
			my_mutex.unlock();
		}
	}
}

unsigned __int64 multy_thread_log(int words_amount, int length_string)
{
	queue<string> myQueue_initial;
	queue<string> myQueue_up;
	queue<string> myQueue_exchg;
	vector<string> initial_vector;
	vector<string> result_vector;

	mutex my_mutex;

	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;
	unsigned __int64 time = 0;

	// Флаги конца работы функций
	bool initializing_over(false);
	bool upper_over(false);
	bool exchange_over(false);

	fill_vector_log(initial_vector, words_amount, length_string);
	//print_vector_multy(initial_vector);

	ofstream fout;
	fout.open("log.txt");


	start = rdtsc();
	thread stage1(from_vector_to_start_log, ref(initial_vector), ref(myQueue_initial), ref(my_mutex), ref(initializing_over), ref(fout));

	thread stage2(from_init_to_up_log, ref(myQueue_initial), ref(myQueue_up), ref(my_mutex), ref(initializing_over),
		ref(upper_over), ref(fout));

	thread stage3(from_up_to_change_log, ref(myQueue_up), ref(myQueue_exchg), ref(my_mutex), ref(upper_over),
		ref(exchange_over), ref(fout));

	thread stage4(from_exchg_to_result_log, ref(myQueue_exchg), ref(result_vector), ref(my_mutex), ref(exchange_over), ref(fout));

	if (stage1.joinable())
	{
		stage1.join();
	}
	if (stage2.joinable())
	{
		stage2.join();
	}
	if (stage3.joinable())
	{
		stage3.join();
	}
	if (stage4.joinable())
	{
		stage4.join();
	}

	fout.close();

	end = rdtsc();

	time = time + (end - start);

	return(time);

	//print_vector_multy(result_vector);
}