#pragma once

#include <iostream>
using namespace std;

template <typename T>
class MyMatrix
{
private:
	int columns; // ���������� ��������
	int rows; // ���������� �����

public:
	T **ptr_array; // ������� ���� T
	MyMatrix(int rows, int columns, T value); // ����������� �������
	~MyMatrix(); // ���������� �������
	void print_matrix(); // ������� ��� �������� �������
	void print_matrix(int i_1, int j_1, int i_2, int j_2); // ������� �������� ������� � (i_1;j_1) �� (i_2; j_2)
	T* operator [](const int i) // ���������� ��������� [] ��� ��������� � ��������� ������� ��� m[i][j]
	{
		return ptr_array[i];
	}
	int get_columns(); // ������� ���������� ��������
	int get_rows(); // ������� ���������� �����
	void reset_matrix(T value); // ��������� ������� ��������� value
};

