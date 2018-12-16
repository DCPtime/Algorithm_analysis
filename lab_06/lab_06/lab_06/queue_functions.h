#pragma once

#include <queue>
#include <string>
#include <random>
#include <iostream>
#include "strings_fucntions.h"
#include <windows.h>
#include <intrin.h>
#pragma intrinsic(__rdtsc)
using namespace std;



void print_vector(vector<string> vector)
{
	for (int i = 0; i < vector.size(); i++)
		cout << vector[i] << endl;

	cout << "\n\n";
}

// ���������� �������� �������� ����� length_word � ����������� amount_word
void fill_vector(vector<string>& obj, int amount_word, int length_word)
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
		obj.push_back(var);
	}
}

void from_vector_to_start(vector<string> &initial_vector, queue<string> &myQueue_initial)
{
	for (int i = 0; i < initial_vector.size(); i++)
		myQueue_initial.push(initial_vector[i]);
}

void from_init_to_up(queue<string> &myQueue_initial, queue<string> &myQueue_up)
{
	// ���� ������� �� �����
	while (myQueue_initial.size() != 0)
	{
		// �������� ��������� ������
		string current_string = myQueue_initial.front();
		// ��������� ������� ���������� � ������ ��������
		up_string(current_string);
		// ������ ������� ������� ��  �������
		myQueue_initial.pop();
		// �������� ���� ������� � ��������� ������� ������� (��������� ��������)
		myQueue_up.push(current_string);
	}
}

void from_up_to_change(queue<string> &myQueue_up, queue<string> &myQueue_exchg)
{
	// ���� ������� �� �����
	while (myQueue_up.size() != 0)
	{
		// �������� ��������� ������
		string current_string = myQueue_up.front();
		// ������ �����
		exchange_symbol(current_string, "A", "B");
		// ������ ������� ������� �� �������
		myQueue_up.pop();
		// �������� ���� ������� � ��������� ������� ������� (������� ������)
		myQueue_exchg.push(current_string);
	}
}

void from_exchg_to_result(queue<string> &myQueue_exchg, vector<string> &result_vector)
{
	// ���� ������� �� �����
	while (myQueue_exchg.size() != 0)
	{
		// �������� ��������� ������
		string current_string = myQueue_exchg.front();
		// ��������� �������������� ������
		result_vector.push_back(current_string);
		// ������ ������� ������� ��  �������
		myQueue_exchg.pop();
	}
}

unsigned __int64 single_thread(int words_amount, int length_string)
{
	queue<string> myQueue_initial;
	queue<string> myQueue_up;
	queue<string> myQueue_exchg;
	vector<string> initial_vector;
	vector<string> result_vector;
	unsigned __int64 start = 0; // ���������� ��� rdtsc
	unsigned __int64 end = 0;
	unsigned __int64 time = 0;

	fill_vector(initial_vector, words_amount, length_string);
	//print_vector(initial_vector);


	start = rdtsc();
	from_vector_to_start(initial_vector, myQueue_initial);
	from_init_to_up(myQueue_initial, myQueue_up);
	from_up_to_change(myQueue_up, myQueue_exchg);
	from_exchg_to_result(myQueue_exchg, result_vector);
	end = rdtsc();

	time = time + (end - start);

	return(time);

	//print_vector(result_vector);
}










