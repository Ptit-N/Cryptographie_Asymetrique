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
 * R: D�truit le contenu d'un pointeur lentier renvoy� par la fonction div_lentier et lib�re la m�moire utiliser
 * E: Un pointeur lentier: le pointeur renvoy� par la fonction div_lentier, aucune m�moire dynamiquement allou�e ne doit avoir �t� lib�r�e avant
 * S: Vide
 */
void del_lentier_pointer(lentier*);