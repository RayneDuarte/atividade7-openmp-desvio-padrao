// Desvio Padrão com openMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <omp.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <math.h>
constexpr int N = 1000; //quantidade de valores float no conjunto

int main()
{
	setlocale(LC_ALL, "Portuguese");
	printf("-------------ATIVIDADE 7 - CC0021-------------\n");
	printf("-----DESVIO PADRÃO DE UM CONJUNTO DE VALORES FLOAT-----\n\n");
	char op;
	float* v = (float*)malloc(sizeof(float) * N);
	if (v == NULL)
	{
		printf("Não foi possível alocar memória\n");
		op = _getch();
		exit(1);
	}

	//criação do vetor com valores float aleatórios
	time_t secs;
	for (int i = 0; i < N; i++)
	{
		secs = time(NULL);
		v[i] = float(rand() % secs);
	}

	//cálculo da média
	float soma_dos_elementos = 0, soma = 0, soma_total = 0, media, sigma, res;
	#pragma omp parallel for reduction (+: soma_dos_elementos)
	{
		for (int i = 0; i < N; i++)
			soma_dos_elementos += v[i];
	}
	media = soma_dos_elementos / N;

	printf("Calculando desvio padrão\n");
	//cálculo do desvio padrão com openMP
	#pragma omp parallel for reduction (+: soma)
	{
		for (int i = 0; i < N; i++)
		{
			res = v[i] - media;
			soma += (res * res);
		}
		#pragma omp critical
			soma_total += soma;
	}
	sigma = (sqrt(soma_total / N));
	free(v);
	printf("Desvio padrão: %.2f\n", sigma);
	printf("Média: %.2f\n", media);
	printf("Soma dos elementos ao quadrado: %.2f\n", soma_total);
	op = _getch();
}
