#include <iostream>
#include <cstdlib>

#include <cmath>
#include <limits>
#include <climits>

#include "ACO.h"

#define ITERATIONS		(int) 5

#define NUMBEROFANTS	(int) 4
#define NUMBEROFCITIES	(int) 8

#define ALPHA			(double) 0.5 // Стпень, в которую возводим количество феромонов на ребре i,j. Стадность алгоритма
// if (BETA  == 0) { sub-optimal route }
#define BETA			(double) 0.8 // Степень, в которую возводим параметр "привлекательность" пути (нач значение 1/d i,j). Жадность
// Константа
#define Q				(double) 80
// Pheromones evaporation. Скорость испарения феромонов (для обновления)
#define RO				(double) 0.2
// Maximum pheromone random number. Максимальное число феромонов, которое можно отложить муравьем.
#define TAUMAX			(int) 2
#define INITIALCITY		(int) 0


void function_alpha(int start, int end, float step)
{
	for (double i = 0; i <= end+0.1; i = i + step)
	{
		ACO *ANTS = new ACO(NUMBEROFANTS, NUMBEROFCITIES,
			i, BETA, Q, RO, TAUMAX,
			INITIALCITY);


		ANTS->init();
		// Связи между городами
		ANTS->connectCITIES(0, 1);
		ANTS->connectCITIES(0, 2);
		ANTS->connectCITIES(0, 3);
		ANTS->connectCITIES(0, 7);
		ANTS->connectCITIES(1, 3);
		ANTS->connectCITIES(1, 5);
		ANTS->connectCITIES(1, 7);
		ANTS->connectCITIES(2, 4);
		ANTS->connectCITIES(2, 5);
		ANTS->connectCITIES(2, 6);
		ANTS->connectCITIES(4, 3);
		ANTS->connectCITIES(4, 5);
		ANTS->connectCITIES(4, 7);
		ANTS->connectCITIES(6, 7);
		/* ANTS -> connectCITIES(8, 2);
		ANTS -> connectCITIES(8, 6);
		ANTS -> connectCITIES(8, 7); */

		// Установить положение городов
		ANTS->setCITYPOSITION(0, 1, 1);
		ANTS->setCITYPOSITION(1, 10, 10);
		ANTS->setCITYPOSITION(2, 20, 10);
		ANTS->setCITYPOSITION(3, 10, 30);
		ANTS->setCITYPOSITION(4, 15, 5);
		ANTS->setCITYPOSITION(5, 10, 1);
		ANTS->setCITYPOSITION(6, 20, 20);
		ANTS->setCITYPOSITION(7, 20, 30);
		// ANTS -> setCITYPOSITION(8, 26, 20);

		ANTS->optimize(ITERATIONS);
		std::cout << "alpha =" << i << "  ";
		ANTS->printRESULTS();


	}
}


void function_beta(int start, int end, float step)
{
	for (double i = 0; i <= end + 0.1; i = i + step)
	{
		ACO *ANTS = new ACO(NUMBEROFANTS, NUMBEROFCITIES,
			ALPHA, i, Q, RO, TAUMAX,
			INITIALCITY);


		ANTS->init();
		// Связи между городами
		ANTS->connectCITIES(0, 1);
		ANTS->connectCITIES(0, 2);
		ANTS->connectCITIES(0, 3);
		ANTS->connectCITIES(0, 7);
		ANTS->connectCITIES(1, 3);
		ANTS->connectCITIES(1, 5);
		ANTS->connectCITIES(1, 7);
		ANTS->connectCITIES(2, 4);
		ANTS->connectCITIES(2, 5);
		ANTS->connectCITIES(2, 6);
		ANTS->connectCITIES(4, 3);
		ANTS->connectCITIES(4, 5);
		ANTS->connectCITIES(4, 7);
		ANTS->connectCITIES(6, 7);
		/* ANTS -> connectCITIES(8, 2);
		ANTS -> connectCITIES(8, 6);
		ANTS -> connectCITIES(8, 7); */

		// Установить положение городов
		ANTS->setCITYPOSITION(0, 1, 1);
		ANTS->setCITYPOSITION(1, 10, 10);
		ANTS->setCITYPOSITION(2, 20, 10);
		ANTS->setCITYPOSITION(3, 10, 30);
		ANTS->setCITYPOSITION(4, 15, 5);
		ANTS->setCITYPOSITION(5, 10, 1);
		ANTS->setCITYPOSITION(6, 20, 20);
		ANTS->setCITYPOSITION(7, 20, 30);
		// ANTS -> setCITYPOSITION(8, 26, 20);

		ANTS->optimize(ITERATIONS);
		std::cout << "beta =" << i << "  ";
		ANTS->printRESULTS();


	}
}

void function_po(int start, int end, float step)
{
	for (double i = 0; i <= end + 0.1; i = i + step)
	{
		ACO *ANTS = new ACO(4, 4,
			ALPHA, BETA, Q, i, TAUMAX,
			INITIALCITY);


		ANTS->init();
		// Связи между городами
		ANTS->connectCITIES(0, 1);
		ANTS->connectCITIES(0, 2);
		ANTS->connectCITIES(0, 3);
		ANTS->connectCITIES(0, 7);
		ANTS->connectCITIES(1, 3);
		ANTS->connectCITIES(1, 5);
		ANTS->connectCITIES(1, 7);
		ANTS->connectCITIES(2, 4);
		ANTS->connectCITIES(2, 5);
		ANTS->connectCITIES(2, 6);
		ANTS->connectCITIES(4, 3);
		ANTS->connectCITIES(4, 5);
		ANTS->connectCITIES(4, 7);
		ANTS->connectCITIES(6, 7);
		/* ANTS -> connectCITIES(8, 2);
		ANTS -> connectCITIES(8, 6);
		ANTS -> connectCITIES(8, 7); */

		// Установить положение городов
		ANTS->setCITYPOSITION(0, 1, 1);
		ANTS->setCITYPOSITION(1, 10, 10);
		ANTS->setCITYPOSITION(2, 20, 10);
		ANTS->setCITYPOSITION(3, 10, 30);
		ANTS->setCITYPOSITION(4, 15, 5);
		ANTS->setCITYPOSITION(5, 10, 1);
		ANTS->setCITYPOSITION(6, 20, 20);
		ANTS->setCITYPOSITION(7, 20, 30);
		// ANTS -> setCITYPOSITION(8, 26, 20);

		ANTS->optimize(ITERATIONS);
		std::cout << "RO =" << i << "  ";
		ANTS->printRESULTS();


	}
}

void function_double_cicle_1(int start, int end, float step)
{
	for (double i = start; i <= end + 0.1; i = i + step)
	{
		for (double j = start; j <= end + 0.1; j = j + step)
		{
			ACO *ANTS = new ACO(NUMBEROFANTS, NUMBEROFCITIES,
				i, j, Q, RO, TAUMAX,
				INITIALCITY);


			ANTS->init();
			// Связи между городами
			ANTS->connectCITIES(0, 1);
			ANTS->connectCITIES(0, 2);
			ANTS->connectCITIES(0, 3);
			ANTS->connectCITIES(0, 7);
			ANTS->connectCITIES(1, 3);
			ANTS->connectCITIES(1, 5);
			ANTS->connectCITIES(1, 7);
			ANTS->connectCITIES(2, 4);
			ANTS->connectCITIES(2, 5);
			ANTS->connectCITIES(2, 6);
			ANTS->connectCITIES(4, 3);
			ANTS->connectCITIES(4, 5);
			ANTS->connectCITIES(4, 7);
			ANTS->connectCITIES(6, 7);
			/* ANTS -> connectCITIES(8, 2);
			ANTS -> connectCITIES(8, 6);
			ANTS -> connectCITIES(8, 7); */

			// Установить положение городов
			ANTS->setCITYPOSITION(0, 1, 1);
			ANTS->setCITYPOSITION(1, 10, 10);
			ANTS->setCITYPOSITION(2, 20, 10);
			ANTS->setCITYPOSITION(3, 10, 30);
			ANTS->setCITYPOSITION(4, 15, 5);
			ANTS->setCITYPOSITION(5, 10, 1);
			ANTS->setCITYPOSITION(6, 20, 20);
			ANTS->setCITYPOSITION(7, 20, 30);
			// ANTS -> setCITYPOSITION(8, 26, 20);

			ANTS->optimize(ITERATIONS);
			std::cout << "alpha =" << i << "  " << "beta = " << j << "  length = ";
			ANTS->printRESULTS();
		}


	}
}

void function_double_cicle_2(int start, int end, float step)
{
	for (double i = start; i <= end + 0.1; i = i + step)
	{
		for (double j = start; j <= end +0.1; j = j + step)
		{
			ACO *ANTS = new ACO(4, 9,
				i, j, Q, RO, TAUMAX,
				0);

			ANTS->init();
			// Связи между городами
			ANTS->connectCITIES(0, 1);
			ANTS->connectCITIES(0, 2);
			ANTS->connectCITIES(0, 3);
			ANTS->connectCITIES(0, 7);
			ANTS->connectCITIES(1, 3);
			ANTS->connectCITIES(1, 5);
			ANTS->connectCITIES(1, 7);
			ANTS->connectCITIES(2, 4);
			ANTS->connectCITIES(2, 5);
			ANTS->connectCITIES(2, 6);
			ANTS->connectCITIES(4, 3);
			ANTS->connectCITIES(4, 5);
			ANTS->connectCITIES(4, 7);
			ANTS->connectCITIES(6, 7);
			ANTS->connectCITIES(8, 2);
			ANTS->connectCITIES(8, 6);
			ANTS->connectCITIES(8, 7); 

			// Установить положение городов
			ANTS->setCITYPOSITION(0, 1, 1);
			ANTS->setCITYPOSITION(1, 10, 10);
			ANTS->setCITYPOSITION(2, 20, 10);
			ANTS->setCITYPOSITION(3, 10, 30);
			ANTS->setCITYPOSITION(4, 15, 5);
			ANTS->setCITYPOSITION(5, 10, 1);
			ANTS->setCITYPOSITION(6, 20, 20);
			ANTS->setCITYPOSITION(7, 20, 30);
			ANTS->setCITYPOSITION(8, 26, 20);
			

			ANTS->optimize(ITERATIONS);
			std::cout << "alpha = " << i << "  " << "beta = " << j << "  length = ";
			ANTS->printRESULTS();
		}


	}
}

int main()
{
	function_double_cicle_1(0, 1, 0.1);
	//std::cout << "second graph" << std::endl;
	//function_double_cicle_2(0, 1, 0.1);
	return 0;
}