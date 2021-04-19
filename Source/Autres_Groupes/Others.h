#pragma once

#include <iostream>

struct lentier
{
	unsigned int* p;
	unsigned int size;
};

void Affiche_lentier(lentier a);


/*
 * E: un entier (nsize) la nouvelle taille du tableau
 * ES:un lentier dont la taille du tableau doit être modifiée
 * R:Réalloue dynamiquement de l'espace mémoire pour le tableau, toutes les nouvelles cases mémoires auront pour valeur 0
 */
void lAdjust(lentier& a, unsigned int nsize);

lentier add_lentier(lentier a, lentier b);

lentier sub_entier(lentier a, lentier b);

char cmp_lentier(lentier a, lentier b);

lentier mult_classique(lentier a, lentier b);

lentier mul_mod(lentier a, lentier b, lentier N);

lentier exp_mod(lentier a, lentier b, lentier N);