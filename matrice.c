/*
** matrice.c
** 
** Made by (Gilles Enée)
** Login   <genee@genee-laptop>
** 
** Started on  Wed Oct 10 17:02:05 2007 Gilles Enée
** Last update Thu Oct 11 16:23:36 2007 Gilles Enée
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrice.h"

t_matrice * Cree_Matrice(unsigned int dimension, unsigned int * ttaille)
{
  unsigned int i = ttaille[0];
  t_matrice * newM = (t_matrice *) malloc(sizeof(t_matrice));

  newM->n = dimension;
  newM->lg = ttaille[0];

  if(dimension > 1) { /* Cas d'arrêt de la récursivité */
    newM->matrice = (t_matrice **) malloc(ttaille[0] * sizeof(t_matrice *));
    while(i > 0) {
      newM->matrice[i-1] = Cree_Matrice(dimension - 1, &ttaille[1]); /* Récursivité */
      i--;
    }
  } else
    newM->elements = (t_elem *) malloc(ttaille[0] * sizeof(t_elem));

  return newM;

}

t_matrice * Copie_Cree_Matrice(t_matrice *M)
{
  unsigned int n;
  unsigned int *lgrs;
  t_matrice *temp = M, * newM;

  n = M->n;

  lgrs = (unsigned int *) malloc(n * sizeof(unsigned int));

  while(temp->n > 1) {
    lgrs[n - temp->n] = temp->lg;
    temp = M->matrice[0];
  }

  lgrs[n - temp->n] = temp->lg;

  newM = Cree_Matrice(n, lgrs);

  free(lgrs);

  return newM;

}

void Recopie_Matrice(t_matrice *Src_M, t_matrice *Dst_M)
{
  unsigned int i;

  for(i = 0; i < Dst_M->lg; i++) {
    if(Dst_M->n == 1)
      E_Copie(& Dst_M->elements[i], Src_M->elements[i]);
    else
      Recopie_Matrice(Src_M->matrice[i], Dst_M->matrice[i]);
  }

}

t_matrice * Copie_Matrice(t_matrice * M)
{
  t_matrice *copie_M = Copie_Cree_Matrice(M);

  Recopie_Matrice(M, copie_M);

  return copie_M;

}

void Remplir_Matrice(t_matrice * M, f_remplir f)
{
  unsigned int i;

  for(i = 0; i < M->lg; i++)
    if(M->n == 1)
      M->elements[i] = f();
    else
      Remplir_Matrice(M->matrice[i], f);

}

void Afficher_Matrice(t_matrice * M)
{
  unsigned int i;

  printf("Affichage de la dimension : %u\n", M->n);

  for(i = 0; i < M->lg; i++)
    if(M->n == 1)
      printf("%f ", E_Double(M->elements[i]));
    else
      Afficher_Matrice(M->matrice[i]);
  
  if(M->n == 1)
    printf("\n");
}

void Liberer_Matrice(t_matrice * M)
{
  unsigned int i;

  if(M->n == 1)
    free(M->elements);
  else
    for(i = 0; i < M->lg; i++) {
      Liberer_Matrice(M->matrice[i]);
      free(M->matrice[i]);
    }

  fprintf(stderr, "Libération terminée\n");

}

void Applique_Matrice(t_matrice * M, f_applique f, unsigned int *indices)
{

  if(M->n == 1)
    E_Copie(& M->elements[indices[0]], f(M->elements[indices[0]]));
  else
    Applique_Matrice(M->matrice[indices[0]], f, &indices[1]);

}

t_elem Recursif_Matrice(t_matrice * M, f_recursif f)
{
  unsigned int i;
  t_elem cumul = Double_E(0.0);

  for(i = 0; i < M->lg; i++)
    if(M->n == 1)
      E_Copie(& cumul, f(cumul, M->elements[i]));
    else
      E_Copie(& cumul, f(cumul, Recursif_Matrice(M->matrice[i], f)));

  return cumul;

}

t_elem Valeur(t_matrice *M, unsigned int *indices)
{

  if(M->n == 1)
    return M->elements[indices[0]];
  else
    return Valeur(M->matrice[indices[0]], &indices[1]);

}

t_matrice * Somme_Matrices(t_matrice *M1, t_matrice *M2)
{
  unsigned int i;
  t_matrice *newM = NULL;

  if(M1->n == M2->n) {
    newM = Copie_Cree_Matrice(M1);
    for(i=0; i < M1->lg; i++)
      if(M1->n == 1)
	E_Copie(& newM->elements[i], E_Ajoute(M1->elements[i], M2->elements[i]));
      else
	newM->matrice[i] = Somme_Matrices(M1->matrice[i], M2->matrice[i]);
  }

  return newM;
}

