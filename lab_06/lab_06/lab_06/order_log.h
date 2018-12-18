#pragma once
#pragma once

#include <queue>
#include <string>
#include <random>
#include <iostream>
#include "strings_fucntions.h"
#include <windows.h>
#include <intrin.h>
#include <fstream>
#pragma intrinsic(__rdtsc)
using namespace std;


// Заполнение очередки строками длины length_word и количеством amount_word
void fill_vector_order_log(vector<string>& obj, int amount_word, int length_word)
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

void from_vector_to_start_order_log(vector<string> &initial_vector, queue<string> &myQueue_initial, ofstream &fout)
{
	for (int i = 0; i < initial_vector.size(); i++)
	{
		myQueue_initial.push(initial_vector[i]);
		string current_string = initial_vector[i];
		fout << current_string[current_string.length() - 1] << "  was pushed in queue_0" << endl;
	}

}

void from_init_to_up_order_log(queue<string> &myQueue_initial, queue<string> &myQueue_up, ofstream &fout)
{
	// Пока очередь не пуста
	while (myQueue_initial.size() != 0)
	{
		// Извлекли очередную строку
		string current_string = myQueue_initial.front();
		// Применили функцию приведения к новому регистру
		up_string(current_string);
		// Убрали текущий элемент из  очереди
		myQueue_initial.pop();
		// Добавили этот элемент в следующую очередь очередь (повышения регистра)
		myQueue_up.push(current_string);
		fout << current_string[current_string.length() - 1] << "  was thrown out of the queue_0 and pushed to queue_1" << endl;

	}
}

void from_up_to_change_order_log(queue<string> &myQueue_up, queue<string> &myQueue_exchg, ofstream &fout)
{
	// Пока очередь не пуста
	while (myQueue_up.size() != 0)
	{
		// Извлекли очередную строку
		string current_string = myQueue_up.front();
		// Меняем буквы
		exchange_symbol(current_string, "A", "B");
		// Убрали текущий элемент из очереди
		myQueue_up.pop();
		// Добавили этот элемент в следующую очередь очередь (готовые строки)
		myQueue_exchg.push(current_string);
		fout << current_string[current_string.length() - 1] << "  was thrown out of the queue_1 and pushed to queue_2"  << endl;
	}
}

void from_exchg_to_result_order_log(queue<string> &myQueue_exchg, vector<string> &result_vector, ofstream &fout)
{
	// Пока очередь не пуста
	while (myQueue_exchg.size() != 0)
	{
		// Извлекли очередную строку
		string current_string = myQueue_exchg.front();
		// Дополнили результирующий вектор
		result_vector.push_back(current_string);
		// Убрали текущий элемент из  очереди
		myQueue_exchg.pop();
		fout << current_string[current_string.length() - 1] << "  was thrown out of the queue_2 and pushed to vector "<< endl;
	}
}

unsigned __int64 single_thread_order_log(int words_amount, int length_string)
{
	queue<string> myQueue_initial;
	queue<string> myQueue_up;
	queue<string> myQueue_exchg;
	vector<string> initial_vector;
	vector<string> result_vector;
	unsigned __int64 start = 0; // Переменные для rdtsc
	unsigned __int64 end = 0;
	unsigned __int64 time = 0;

	fill_vector_order_log(initial_vector, words_amount, length_string);
	//print_vector(initial_vector);

	ofstream fout;
	fout.open("log_order.txt");

	start = rdtsc();
	from_vector_to_start_order_log(initial_vector, myQueue_initial, fout);
	from_init_to_up_order_log(myQueue_initial, myQueue_up, fout);
	from_up_to_change_order_log(myQueue_up, myQueue_exchg, fout);
	from_exchg_to_result_order_log(myQueue_exchg, result_vector, fout);
	end = rdtsc();

	fout.close();
	time = time + (end - start);

	return(time);

	//print_vector(result_vector);
}

