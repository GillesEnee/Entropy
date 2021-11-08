/*
** entropie.h
** 
** Made by Gilles Enée
** Login   <genee@genee-laptop>
** 
** Started on  Wed Oct 10 16:59:35 2007 Gilles Enée
** Last update Wed Oct 10 17:01:42 2007 Gilles Enée
*/

#ifndef   	ENTROPIE_H_
#define   	ENTROPIE_H_

#include "matrice.h"

typedef t_elem (* CalculPk)(t_matrice *, unsigned int *);
typedef t_elem (* SommePk)(t_elem);

/* Calcul de l'entropie */

t_elem RecNewP(t_matrice *, unsigned int *);
t_elem NewP(t_matrice *, unsigned int *);

double Entropie(t_matrice *, CalculPk, SommePk);

#endif 	    /* !ENTROPIE_H_ */
