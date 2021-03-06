// AA_lab_01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <windows.h>

#include "MyMatrix.h"
#include "MyMatrix.cpp"
#include <set>
#include <math.h>
#include <intrin.h>
#pragma intrinsic(__rdtsc)


using namespace std;

int count_rec = 0;
int count_max= 0;

unsigned __int64 rdtsc()
{
	return __rdtsc();
}

int get_amount(string &string_1, string &string_2)
{
	string S_3 = string_1 + string_2;
	set <char> mySet;
	for (int i = 0; i < S_3.length(); i++)
		mySet.insert(S_3[i]);

	return mySet.size();

}



void print_named_matrix(MyMatrix<int> &matrix, string &T, string &S)
{
	cout << '\t' << '\t';
	for (int i = 0; i < S.length(); i++)
		cout << S[i] << '\t';
	cout << endl;

	for (int i = 0; i < matrix.get_rows(); i++)
	{
		// Вывод боковой строки
		if (i != 0)
		{
			if (i <= T.length()+1)
				cout << T[i-1] << '\t';
			else
				cout << ' ' << '\t';
		}
		else
			cout << ' ' << '\t';

		for (int j = 0; j < matrix.get_columns(); j++)
			    cout << matrix[i][j] << '\t';
		cout << endl;
	}


}

void print_named_matrix_2(MyMatrix<int> &matrix, string &T, string &S)
{



	cout << '\t' << '\t';
	for (int i = 0; i < S.length(); i++)
		cout << S[i] << '\t';

	for (int i = 0; i < matrix.get_rows(); i++)
	{
		// Вывод боковой строки
		if (i != 0)
		{
			if (i <= T.length() + 2 && i > 1)
				cout << T[i - 2] << '\t';
			else
				cout << ' ' << '\t';
		}
		else
			cout << ' ' << '\t';

		for (int j = 0; j < matrix.get_columns(); j++)
			if (matrix[i][j] != S.length() + T.length())
			    cout << matrix[i][j] << '\t';
		cout << endl;
	}


}

// Инициализация строк
int initial_data(string &string_1, string &string_2)
{
	cout << "Введите первое слово" << endl;
	getline(cin, string_1);
	cout << "Введите второе слово" << endl;
	getline(cin, string_2);

	return(0);
}

// Итеративный метод расстояния левенштейна
int iteration_try(string &S1, string &S2)
{
	int m = S1.size();
	int n = S2.size();

	if (n == 0)
		return(m);
	if (m == 0)
		return(n);

	MyMatrix<int> matrix(m+1, n+1, 0);


	// Проинциализировали первый столбец возрастающей последовательностью
	for (int j = 1; j <= n; j++)
		matrix[0][j] = matrix[0][j - 1] + 1; // Вставка

	// На каждом шаге инициализируем очередной элемент 1-ой строки как предыдущий + 1 
	for (int i = 1; i <= m; i++)
	{
		matrix[i][0] = matrix[i - 1][0] + 1; // Удаление

		// Вычисляем само расстояние левинштейна
		for (int j = 1; j <= n; j++)
			if (S1[i - 1] != S2[j - 1])
				matrix[i][j] = min(min((matrix[i - 1][j] + 1), // Удаление
				                       (matrix[i][j - 1] + 1)), // Вставка
				                       (matrix[i - 1][j - 1] + 1)); // Замена
			else
				matrix[i][j] = matrix[i - 1][j - 1]; // Совпадение

	}

	if ( n != 0 && m != 0)
		print_named_matrix(matrix, S1, S2);
	//matrix.print_matrix();


	return(matrix[m][n]);
}


// Итеративный метод расстояния левенштейна (Тест)
int iteration_try_Test(string &S1, string &S2, MyMatrix<int> &matrix)
{
	int m = S1.size();
	int n = S2.size();

	if (n == 0)
		return(m);
	if (m == 0)
		return(n);

	// Проинциализировали первый столбец возрастающей последовательностью
	for (int j = 1; j <= n; j++)
		matrix[0][j] = matrix[0][j - 1] + 1; // Вставка

	// На каждом шаге инициализируем очередной элемент 1-ой строки как предыдущий + 1 
	for (int i = 1; i <= m; i++)
	{
		matrix[i][0] = matrix[i - 1][0] + 1; // Удаление

		// Вычисляем само расстояние левинштейна
		for (int j = 1; j <= n; j++)
			if (S1[i - 1] != S2[j - 1])
				matrix[i][j] = min(min((matrix[i - 1][j] + 1), // Удаление
				(matrix[i][j - 1] + 1)), // Вставка
					(matrix[i - 1][j - 1] + 1)); // Замена
			else
				matrix[i][j] = matrix[i - 1][j - 1]; // Совпадение

	}


	return(matrix[m][n]);
}

// Дамерау-Левенштейн итеративно для 1 транспозиции
int Damerau_levensteain(string &S1, string &S2)
{
	int m = S1.size();
	int n = S2.size();
	if (n == 0)
		return(m);
	if (m == 0)
		return(n);
	MyMatrix<int> matrix(m + 1, n + 1, 0);

	for (int i = 0; i <= m; i++)
		matrix[i][0] = i;
	for (int j = 1; j <= n; j++)
		matrix[0][j] = j;

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			if (S1[i - 1] == S2[j - 1]) // Символы совпадают
				matrix[i][j] = matrix[i - 1][j - 1];
			else
				matrix[i][j] = matrix[i - 1][j - 1] + 1; // Замена

			matrix[i][j] = min(min(matrix[i][j],
				                   matrix[i - 1][j] + 1), // Удаление
				                   matrix[i][j - 1] + 1); // Вставка

			if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j-1])
				matrix[i][j] = min(matrix[i][j],
					               matrix[i - 2][j - 2] + 1); // Транспозиция

		}

	if (n != 0 && m != 0)
	    print_named_matrix(matrix, S1, S2);
	//matrix.print_matrix();


	return(matrix[m][n]);
}

// Дамерау-Левенштейн итеративно для 1 транспозиции (Тест времени)
int Damerau_levensteain_Test(string &S1, string &S2, MyMatrix<int> &matrix)
{
	count_rec = count_rec + 1;
	int m = S1.size();
	int n = S2.size();
	if (n == 0)
	{
		
		
		return(m);
	}
	if (m == 0)
	{
		return(n);
	}

	for (int i = 0; i <= m; i++)
		matrix[i][0] = i;
	for (int j = 1; j <= n; j++)
		matrix[0][j] = j;

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
		{
			if (S1[i - 1] == S2[j - 1]) // Символы совпадают
				matrix[i][j] = matrix[i - 1][j - 1];
			else
				matrix[i][j] = matrix[i - 1][j - 1] + 1; // Замена

			matrix[i][j] = min(min(matrix[i][j],
				matrix[i - 1][j] + 1), // Удаление
				matrix[i][j - 1] + 1); // Вставка

			if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1])
				matrix[i][j] = min(matrix[i][j],
					matrix[i - 2][j - 2] + 1); // Транспозиция

		}
	return(matrix[m][n]);
}





// Рекурсивный метод расстояние Левинштейна (Тест времени)
int LevenshteinDistanceRecursiveTest(string &s, int len_s, string &t, int len_t)
{
	int cost;

	count_rec = count_rec + 1;

	// Случай, когда строки пусты
	if (len_s == 0)
	{
		if (count_rec > count_max)
			count_max = count_rec;
		count_rec = 0;
		return len_t;
	}

	if (len_t == 0)
	{
		if (count_rec > count_max)
			count_max = count_rec;
		count_rec = 0;
		return len_s;
	}

	// Тест, если последние буквы строк совпадают
	if (s[len_s - 1] == t[len_t - 1])
		cost = 0;
	else
		cost = 1;

	int insert = LevenshteinDistanceRecursiveTest(s, len_s - 1, t, len_t) + 1;
	int deletion = LevenshteinDistanceRecursiveTest(s, len_s, t, len_t - 1) + 1;
	int replacement = LevenshteinDistanceRecursiveTest(s, len_s - 1, t, len_t - 1) + cost;

	/* Возвращает минимальное из: удаления буквы из s, удаления буквы из t или из обеих строк */
	int x = min(min(insert, deletion), replacement);

	return x;
}


// TEST /////////////////////////////////////
int LevenshteinDistanceT(const char *s, int len_s, const char *t, int len_t, MyMatrix<int> &matrix)
{
	int cost;
	count_rec = count_rec + 1;
	// Случай, когда строки пусты
	if (len_s == 0)
	{
		matrix[len_s][len_t] = len_t;
		if (count_rec > count_max)
			count_max = count_rec;
		count_rec = 0;
		return len_t;
	}

	if (len_t == 0)
	{
		matrix[len_s][len_t] = len_s;
		if (count_rec > count_max)
			count_max = count_rec;
		count_rec = 0;
		return len_s;
	}

	// Тест, если последние буквы строк совпадают
	if (s[len_s - 1] == t[len_t - 1])
		cost = 0;
	else
		cost = 1;


	int insert = LevenshteinDistanceT(s, len_s - 1, t, len_t, matrix) + 1;
	int deletion = LevenshteinDistanceT(s, len_s, t, len_t - 1, matrix) + 1;
	int replacement = LevenshteinDistanceT(s, len_s - 1, t, len_t - 1, matrix) + cost;

	/* Возвращает минимальное из: удаления буквы из s, удаления буквы из t или из обеих строк */
	int x = min(min(insert, deletion), replacement);

	matrix[len_s][len_t] = x;


	return x;
}


void time_test(unsigned __int64 &time_iterative_1, unsigned __int64 &time_iterative_2,
	           unsigned __int64 &time_recursion,
	           string &s1, string &s2)
{
	unsigned __int64 start = 0;
	unsigned __int64 end = 0;

	int result;

	int amount = 100;
	MyMatrix<int> matrix(s1.length() + 1, s2.length() + 1, 0);

	// Среднее время для итерационного способа для Левенштейна
	for (int i = 0; i < amount; i++)
	{
		start = rdtsc();
		result = iteration_try_Test(s1, s2, matrix);
		end = rdtsc();
		time_iterative_1 = time_iterative_1 + (end - start);
		matrix.reset_matrix(0);
	}
	time_iterative_1 = time_iterative_1 / amount;

	// Среднее время для итерационного способа для Дамерау-Левенштейна
	for (int i = 0; i < amount; i++)
	{
		start = rdtsc();
		result = Damerau_levensteain_Test(s1, s2, matrix);
		end = rdtsc();
		time_iterative_2 = time_iterative_2 + (end - start);
		matrix.reset_matrix(0);
	}
	time_iterative_2 = time_iterative_2 / amount;

	// Среднее время для рекурсивного способа для Левенштейна
	for (int i = 0; i < amount; i++)
	{
		start = rdtsc();
		result = LevenshteinDistanceRecursiveTest(s1, s1.length(), s2, s2.length());
		end = rdtsc();
		time_recursion = time_recursion + (end - start);
	}
	time_recursion = time_recursion / amount;

}

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	// Инициализация данных
	string S;
	string T;
	initial_data(S, T);
	int result = 0;

	// Итеративный метод для расстояния Левинштейна
	//result = iteration_levenshtein(S, T);
	cout << "Итеративный способ расстояния Левенштейна" << endl;
	result = iteration_try(S, T);
	cout << "Расстояние Левенштейна для перевода строки " << S << " в строку " << T 
		<< " = " << result << endl << endl;

	// Расстояние Дамерау-Левинштейна итеративно
	cout << "Итеративный способ расстояния Дамерау-Левенштейна" << endl;
	result = Damerau_levensteain(S, T);
	cout << "Расстояние Дамерау-Левенштейна для перевода строки " << S << " в строку " <<
		T << " = " << result << endl << endl;

	// Рекурсивный метод для расстояния левинштейна
	int m = S.length();
	int n = T.length();
	MyMatrix<int> matrix(m + 1, n + 1, 0);
	cout << "Рекурсивный способ расстояния Левенштейна" << endl;
	//result = LevenshteinDistance(S, S.length(), T, T.length(), matrix);
	//const char* strS = S.c_str();
	result = LevenshteinDistanceT(S.c_str(), S.length(), T.c_str(), T.length(), matrix);
	if (n!= 0 && m != 0 )
	    print_named_matrix(matrix, S, T);
	cout << "Расстояние Левенштейна рекурсивным способом для перевода строки " << S << " в строку " <<
		T << " = " << result << endl << endl << endl;


	// Замеры времени
	unsigned __int64 time_levenstein = 0;
	unsigned __int64 time_damerau = 0;
	unsigned __int64 time_recursion = 0;

	time_test(time_levenstein, time_damerau, time_recursion, S, T);

	cout << "Время для Левенштейна итеративно: " << time_levenstein << endl;
	cout << "Время для Дамерау-Левенштейна итеративно: " << time_damerau << endl;
	cout << "Время для Левенштейна рекурсивно: " << time_recursion << endl;

	system("pause");
	return(0);
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
