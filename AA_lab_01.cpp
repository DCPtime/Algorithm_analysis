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


using namespace std;

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

// Демарау-Левенштейн итеративно для 1 транспозиции
int Demarau_levensteain(string &S1, string &S2)
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

// Демарау-Левенштейн итеративно
int Demarau_levensteain_2(string &S, string &T)
{
	int M = S.length();
	int N = T.length();

	// Обработка крайних случаев
	if (S == "")
	{
		if (T == "")

			return 0;
		else
			return N;
	}
	else if (T == "")
		return M;

	MyMatrix<int> D(M + 2, N + 2, 0);
	int INF = M + N; // Большая константа
	D[0][0] = INF; 

	// База индукции
	D[0][0] = INF;
	for (int i = 0; i <= M; i++)
	{
		D[i + 1][1] = i;
		D[i + 1][0] = INF;
	}

	for (int j = 0; j <= N; j++)
	{
		D[1][j + 1] = j;
		D[0][j + 1] = INF;
	}

	int range = get_amount(S, T); // Количество различных букв в S и T
	range = 200;
	int *lastPosition = new int[range]; // Массив типа int длины range, инициализированный нулями
	for (int i = 0; i < range; i++)
		lastPosition[i] = 0;

	int last = 0; // Переменные для работы с матрицей
	int i_2 = 0;
	int j_2 = 0;
	for (int i = 1; i <= M; i++)
	{
		last = 0;
		for (int j = 1; j <= N; j++)
		{
			i_2 = lastPosition[T[j-1]];
			j_2 = last;
			if (S[i - 1] == T[j - 1])
			{
				D[i + 1][j + 1] = D[i][j];
				last = j;
			}
			else
				D[i + 1][j + 1] = min(min(D[i][j] + 1, // Замена
					                      D[i + 1][j] + 1), // Вставка
					                      D[i][j + 1] + 1); // Удаление
			D[i + 1][j + 1] = min(D[i + 1][j + 1], D[i_2][j + 2] + (i - i_2 - 1) + 1 + (j - j_2 - 1));
		}
		lastPosition[S[i - 1]] = i;
	}


	print_named_matrix(D, S, T);
	//matrix.print_matrix();


	return(D[M+1][N+1]);
}


int Demarau_levensteain_3(string &a, string &b)
{
	int len_a = a.length();
	int len_b = b.length();

	int range = 10000;
	int *da = new int[range];
	for (int i = 0; i < range; i++)
		da[i] = 0;

	int cost = 0;

	MyMatrix<int> d(len_a + 2, len_b + 2, 0);

	int maxdist = len_a + len_b;
	d[0][0] = maxdist;

	for (int i = 0; i <= len_a; i++)
	{
		d[i + 1][0] = maxdist;
		d[i + 1][1] = i;
	}

	for (int j = 0; j <= len_b; j++)
	{
		d[0][j + 1] = maxdist;
		d[1][j + 1] = j;
	}

	for (int i = 1; i <= len_a; i++)
	{
		int db = 0;
		for (int j = 1; j <= len_b; j++)
		{
			int k = da[abs(b[j-1])];
			int l = db;
			if (a[i - 1] == b[j - 1])
			{
				cost = 0;
				db = j;
			}
			else
				cost = 1;

			d[i + 1][j + 1] = min(min(min(d[i][j] + cost, d[i + 1][j] + 1), d[i][j+1]+1),
				                  d[k][l] + (i-k-1) + 1 + (j-l-1));
			da[abs(a[i-1])] = i;

		}
	}

	//d.print_matrix();
	print_named_matrix_2(d, a, b);
	return d[len_a+1][len_b+1];
}






// Рекурсивный метод расстояние Левинштейна
int LevenshteinDistance(string &s, int len_s, string &t, int len_t, MyMatrix<int> &matrix)
{
	int cost;

	// Случай, когда строки пусты
	if (len_s == 0)
	{
		matrix[len_s][len_t] = len_t;
		return len_t;
	}

	if (len_t == 0)
	{
		matrix[len_s][len_t] = len_s;
		return len_s;
	}

	// Тест, если последние буквы строк совпадают
	if (s[len_s - 1] == t[len_t - 1])
		cost = 0;
	else
		cost = 1;

	int insert = LevenshteinDistance(s, len_s - 1, t, len_t, matrix) + 1;
	int deletion = LevenshteinDistance(s, len_s, t, len_t - 1, matrix) + 1;
	int replacement = LevenshteinDistance(s, len_s - 1, t, len_t - 1, matrix) + cost;

	/* Возвращает минимальное из: удаления буквы из s, удаления буквы из t или из обеих строк */
	int x = min(min(insert, deletion), replacement);

	matrix[len_s][len_t] = x;


	return x;
}


// TEST /////////////////////////////////////
int LevenshteinDistanceT(const char *s, int len_s, const char *t, int len_t, MyMatrix<int> &matrix)
{
	int cost;

	// Случай, когда строки пусты
	if (len_s == 0)
	{
		matrix[len_s][len_t] = len_t;
		return len_t;
	}

	if (len_t == 0)
	{
		matrix[len_s][len_t] = len_s;
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
	result = Demarau_levensteain(S, T);
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
