// Desvio Padrão com openMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <omp.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#define N 1000 //quantidade de valores float no conjunto

int main()
{
	setlocale(LC_ALL, "Portuguese");
	printf("-------------ATIVIDADE 7 - C0021-------------\n");
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
	float soma_dos_elementos = 0, soma = 0, media, DP;
	for (int i = 0; i < N; i++)
		soma_dos_elementos += v[i];
	media = soma_dos_elementos / N;

	printf("Calculando desvio padrão\n");
	//cálculo do desvio padrão com openMP
	#pragma omp parallel
	{
		for (int i = 0; i < N; i += 2)
		{
			soma += float(sqrt((v[i] - v[i + 1])));
		}
	}
	soma /= N;
	DP = float(sqrt(soma));
	free(v);
	printf("Desvio padrão: %.2f\n", DP);
	printf("Média: %.2f\n", media);
	printf("Soma dos elementos: %.2f\n", soma_dos_elementos);
	op = _getch();
}
