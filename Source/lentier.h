#pragma once

#include "Autres_Groupes/Others.h"


lentier operator%(lentier a, lentier b);

/*
 * R: Calcul le reste de la division euclidienne du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un lentier: le reste de a par b
 */
lentier div_eucl(const lentier a, const lentier b, const bool deux = 0);

/*
 * R: Calcul le quotient entier et le reste de la division du lentier a par b
 * E: Deux lentiers: a et b
 * S: Un pointeur lentier pointant vers deux lentiers: [0]: le quotient, [1]: le reste
 */
lentier* div_lentier(const lentier a, const lentier b);

/*
 * R: Détruit le contenu d'un pointeur lentier renvoyé par la fonction div_lentier et libère la mémoire utiliser
 * E: Un pointeur lentier: le pointeur renvoyé par la fonction div_lentier, aucune mémoire dynamiquement allouée ne doit avoir été libérée avant
 * S: Vide
 */
void del_lentier_pointer(lentier*);