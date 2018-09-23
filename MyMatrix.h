#pragma once

#include <iostream>
using namespace std;

template <typename T>
class MyMatrix
{
private:
	int columns; // Количество столбцов
	int rows; // Количество строк

public:
	T **ptr_array; // Матрица типа T
	MyMatrix(int rows, int columns, T value); // Конструктор матрицы
	~MyMatrix(); // Деструктор матрицы
	void print_matrix(); // Вывести все элементы матрицы
	void print_matrix(int i_1, int j_1, int i_2, int j_2); // Вывести элементы матрицы с (i_1;j_1) до (i_2; j_2)
	T* operator [](const int i) // Перегрузка оператора [] для обращения к элементам матрицы как m[i][j]
	{
		return ptr_array[i];
	}
	int get_columns(); // Вернуть количество столбцов
	int get_rows(); // Вернуть количество строк
	void reset_matrix(T value); // Заполнить матрицу значением value
};

