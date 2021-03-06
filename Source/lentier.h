#pragma once
#include <iostream>
#include <string>

struct lentier
{
	unsigned int* p;
	unsigned int size;

	lentier operator%=(lentier a);
	lentier operator/=(lentier a);
	lentier operator*=(lentier a);
	lentier operator-=(lentier a);
};

/*
 * E: Un lentier
 * S: vide
 * R: Affiche le lentier pass? en param?tre dans la console
 */
void Affiche_lentier(const lentier a);

/*
 * E: un entier (nsize) la nouvelle taille du tableau
 * ES:un lentier dont la taille du tableau doit ?tre modifi?e
 * R:R?alloue dynamiquement de l'espace m?moire pour le tableau, toutes les nouvelles cases m?moires auront pour valeur 0
 */
void lAdjust(lentier& a, const unsigned int nsize);

/*
 * E: deux lentiers
 * S: un lentier (la somme des deux param?tres)
 * R: fait la somme des deux lentiers pass?s en param?tre
 */
lentier add_lentier(const lentier a, const lentier b);

/*
 * E: deux lentiers
 * S: un lentier (la diff?rence des deux param?tres)
 * R: fait la diff?rence des deux lentiers pass?s en param?tre, si la taille du premier lentier est inf?rieur ? celle du second, renvoie un lentier vide
 */
lentier sub_lentier(const lentier a, const lentier b);

/*
 * E: Deux lentiers
 * S: Un charact?re
 * R: Compare la valeur des deux lentiers pass?s en param?tre, renvoie 1 si premier > second, 0 si ?gaux et -1 si premier < second
 */
char cmp_lentier(const lentier a, const lentier b);

/*
 * E: deux lentiers
 * S: un lentier
 * R: Renvoie le produit des deux lentiers pass?s en param?tre
 */
lentier mult_classique(const lentier a, const lentier b);

lentier mul_mod(const lentier a, const lentier b, const lentier N);

lentier exp_mod(lentier a, lentier b, lentier N);

lentier dec2lentier(const char* nombre_dec);

char* lentier2dec(const lentier a);

//////////////////////////////////////////
//////////////////////////////////////////

lentier operator+(const lentier a, const lentier b);

lentier operator-(const lentier a, const lentier b);

lentier operator*(lentier a, lentier b);

lentier operator/(const lentier a, const lentier b);

lentier operator%(const lentier a, const lentier b);

bool operator>(const lentier a, const lentier b);
bool operator<(const lentier a, const lentier b);
bool operator==(const lentier a, const lentier b);
bool operator!=(const lentier a, const lentier b);
bool operator>=(const lentier a, const lentier b);
bool operator<=(const lentier a, const lentier b);

/*
 * R: Calcul le reste de la division euclidienne du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un lentier: le reste de a par b
 */
lentier div_eucl(const lentier a, const lentier b, const bool deux = 0);

/*
 * R: Cr?e un lentier de deux cases m?moire qui contient l'adresse d'un tableau r?unissant les lentiers pass?s en param?tre
 * E: deux lentiers: a, b
 * S: un lentier qui contient une adresse (n?cessite sa retransformation ? l'aide d'un cast pour r?cup?rer le tableau)
 */
lentier merge_2lentiers(const lentier a, const lentier b);

/*
 * R: Calcul le quotient entier et le reste de la division du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un pointeur lentier pointant vers deux lentiers: [0]: le quotient, [1]: le reste
 */
lentier* div_lentier(const lentier a, const lentier b);