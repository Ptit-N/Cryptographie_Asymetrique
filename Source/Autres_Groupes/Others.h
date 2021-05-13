#pragma once

#include <iostream>
#include <string>

struct lentier
{
	unsigned int* p;
	unsigned int size;

	lentier operator%=(lentier a);
};

/*
 * E: Un lentier
 * S: vide
 * R: Affiche le lentier pass� en param�tre dans la console
 */
void Affiche_lentier(const lentier a);

/*
 * E: un entier (nsize) la nouvelle taille du tableau
 * ES:un lentier dont la taille du tableau doit �tre modifi�e
 * R:R�alloue dynamiquement de l'espace m�moire pour le tableau, toutes les nouvelles cases m�moires auront pour valeur 0
 */
void lAdjust(lentier& a, const unsigned int nsize);

/*
 * E: deux lentiers
 * S: un lentier (la somme des deux param�tres)
 * R: fait la somme des deux lentiers pass�s en param�tre
 */
lentier add_lentier(const lentier a, const lentier b);

lentier operator+(const lentier a, const lentier b);

/*
 * E: deux lentiers
 * S: un lentier (la diff�rence des deux param�tres)
 * R: fait la diff�rence des deux lentiers pass�s en param�tre, si la taille du premier lentier est inf�rieur � celle du second, renvoie un lentier vide
 */
lentier sub_lentier(const lentier a, const lentier b);

lentier operator-(const lentier a, const lentier b);

/*
 * E: Deux lentiers
 * S: Un charact�re
 * R: Compare la valeur des deux lentiers pass�s en param�tre, renvoie 1 si premier > second, 0 si �gaux et -1 si premier < second 
 */
char cmp_lentier(const lentier a, const lentier b);

bool operator>(const lentier a, const lentier b);
bool operator<(const lentier a, const lentier b);
bool operator==(const lentier a, const lentier b);
bool operator!=(const lentier a, const lentier b);
bool operator>=(const lentier a, const lentier b);
bool operator<=(const lentier a, const lentier b);

/*
 * E: deux lentiers
 * S: un lentier
 * R: Renvoie le produit des deux lentiers pass�s en param�tre
 */
lentier mult_classique(const lentier a, const lentier b);

lentier operator*(lentier a, lentier b);

lentier mul_mod(const lentier a, const lentier b, const lentier N);

lentier exp_mod(lentier a, lentier b, lentier N);

lentier dec2lentier(const std::string nombre_dec);