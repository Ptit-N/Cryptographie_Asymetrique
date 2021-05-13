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
 * R: Affiche le lentier passé en paramètre dans la console
 */
void Affiche_lentier(const lentier a);

/*
 * E: un entier (nsize) la nouvelle taille du tableau
 * ES:un lentier dont la taille du tableau doit être modifiée
 * R:Réalloue dynamiquement de l'espace mémoire pour le tableau, toutes les nouvelles cases mémoires auront pour valeur 0
 */
void lAdjust(lentier& a, const unsigned int nsize);

/*
 * E: deux lentiers
 * S: un lentier (la somme des deux paramètres)
 * R: fait la somme des deux lentiers passés en paramètre
 */
lentier add_lentier(const lentier a, const lentier b);

lentier operator+(const lentier a, const lentier b);

/*
 * E: deux lentiers
 * S: un lentier (la différence des deux paramètres)
 * R: fait la différence des deux lentiers passés en paramètre, si la taille du premier lentier est inférieur à celle du second, renvoie un lentier vide
 */
lentier sub_lentier(const lentier a, const lentier b);

lentier operator-(const lentier a, const lentier b);

/*
 * E: Deux lentiers
 * S: Un charactère
 * R: Compare la valeur des deux lentiers passés en paramètre, renvoie 1 si premier > second, 0 si égaux et -1 si premier < second 
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
 * R: Renvoie le produit des deux lentiers passés en paramètre
 */
lentier mult_classique(const lentier a, const lentier b);

lentier operator*(lentier a, lentier b);

lentier mul_mod(const lentier a, const lentier b, const lentier N);

lentier exp_mod(lentier a, lentier b, lentier N);

lentier dec2lentier(const std::string nombre_dec);