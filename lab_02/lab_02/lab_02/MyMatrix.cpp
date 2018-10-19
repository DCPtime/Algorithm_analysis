#include "pch.h"
#include "MyMatrix.h"


// ����������� �������
template <typename T>
MyMatrix<T>::MyMatrix(int rows, int columns, T value)
{
	ptr_array = new T*[rows];
	for (int count = 0; count < rows; count++)
		ptr_array[count] = new T[columns];

	this->rows = rows;
	this->columns = columns;

	// ������������� ��������� value
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			ptr_array[i][j] = value;

}

// ���������� �������
template <typename T>
MyMatrix<T>::~MyMatrix()
{
	for (int count = 0; count < rows; count++)
		delete[] ptr_array[count];
}

// ������ ������� �� �����
template <typename T>
void MyMatrix<T>::print_matrix()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << ptr_array[i][j] << '\t';
		}
		cout << endl;
	}
}

// ������ ����� ������� �� (i_1,j_1) �� (i_2, j_2) �� �����
template <typename T>
void  MyMatrix<T>::print_matrix(int i_1, int j_1, int i_2, int j_2)
{
	for (int i = i_1; i < i_2; i++)
	{
		for (int j = j_1; j < j_2; j++)
		{
			cout << ptr_array[i][j] << '\t';
		}
		cout << endl;
	}
}

// �������� ���������� �������
template <typename T>
int MyMatrix<T>::get_columns()
{
	return columns;
}

// �������� ���������� �����
template <typename T>
int MyMatrix<T>::get_rows()
{
	return rows;
}

// ��������� ������� ��������� value
template <typename T>
void MyMatrix<T>::reset_matrix(T value)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			ptr_array[i][j] = value;
}


