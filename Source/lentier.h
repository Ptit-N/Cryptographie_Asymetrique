#pragma once
#include <iostream>
#include <string>

struct lentier
{
	unsigned int* p;
	unsigned int size;

	lentier operator*=(const lentier a);
	lentier operator-=(const lentier a);
};

//R: Surcharges d'op�rateurs, permet l'utilisation des op�rateurs surcharg�s pour le type lentier
lentier operator*(const lentier a, const lentier b);

bool operator>(const lentier a, const lentier b);
bool operator<(const lentier a, const lentier b);
bool operator>=(const lentier a, const lentier b);

/*
 * R: Calcul le reste de la division euclidienne du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un lentier: le reste de a par b
 */
lentier div_eucl(const lentier a, const lentier b, const bool deux = 0);

/*
 * R: Cr�e un lentier de deux cases m�moire qui contient l'adresse d'un tableau r�unissant les lentiers pass�s en param�tre
 * E: deux lentiers: a, b
 * S: un lentier qui contient une adresse (n�cessite sa retransformation � l'aide d'un cast pour r�cup�rer le tableau)
 */
lentier merge_2lentiers(const lentier a, const lentier b);

/*
 * R: Calcul le quotient entier et le reste de la division euclidienne du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un pointeur dynamique lentier pointant vers deux lentiers: [0]: le quotient, [1]: le reste
 */
lentier* div_lentier(const lentier a, const lentier b);