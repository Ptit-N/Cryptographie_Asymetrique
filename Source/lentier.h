#pragma once
#include <iostream>
#include <string>

struct lentier
{
	unsigned int* p;
	unsigned int size;

	lentier operator*=(lentier a);
	lentier operator-=(lentier a);
};

lentier operator*(lentier a, lentier b);

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
 * R: Calcul le quotient entier et le reste de la division euclidienne du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un pointeur dynamique lentier pointant vers deux lentiers: [0]: le quotient, [1]: le reste
 */
lentier* div_lentier(const lentier a, const lentier b);