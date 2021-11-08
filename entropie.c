/*
** entropie.c
** 
** Made by (Gilles Enée)
** Login   <genee@genee-laptop>
** 
** Started on  Wed Oct 10 16:26:52 2007 Gilles Enée
** Last update Tue Oct 23 13:53:02 2007 Gilles Enée
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entropie.h"

t_elem RecNewP(t_matrice *M, unsigned int *indices)
{
  unsigned int i;
  t_elem somme = Double_E(0.0);

  for(i=0; i < M->lg; i++) {

    if(i == indices[0]) /* Am�liorable */
      if(M->n > 1)
	E_Copie(& somme, E_Ajoute(somme, RecNewP(M->matrice[i], &indices[1])));

    if(M->n == 1)
      E_Copie(& somme, E_Ajoute(somme, M->elements[i]));
    else
      E_Copie(& somme, E_Ajoute(somme, Valeur(M->matrice[i], &indices[1])));
  }

  return somme;
}

t_elem NewP(t_matrice *M, unsigned int *indices)
{
  t_elem aux = Valeur(M, indices); /* Acc�l�re le calcul en divisant
				      par deux la r�cursivit� */
  t_elem diviseur = E_Multiplie(E_Soustrait(RecNewP(M, indices), Entier_E(M->n - 1)), aux);

  if(E_Double(diviseur) == 0.0)
    return 0.0;
  else
    return E_Divise(aux, diviseur);
}

t_elem OldP(t_matrice *M, unsigned int *indices)
{
  // static t_elem diviseur = Double_E(0.0);
  static double diviseur = 0.0;

  if(diviseur == 0.0)
    diviseur = E_Double(Recursif_Matrice(M, E_Ajoute));

  if(diviseur == 0.0)
    return 0.0;
  else
    return E_Divise(Valeur(M, indices), diviseur);
}

t_elem SommeP(t_elem e)
{
  double aux = E_Double(e);

  if(aux == 0.0)
    return Double_E(aux);
  else
    return Double_E(- ( aux * log(aux) / log(2.0)));
}

double Rec_Entropie(t_matrice *M, unsigned int *indices, unsigned int Profondeur, CalculPk CPk, SommePk SPk)
{
  unsigned int i;
  double SommeH = 0.0;

  /* Calcul de la quantit� d'information de la matrice : Entropie H
     (somme des p * log(p)) */

  for(i = 0; i < M->lg; i++) {
    indices[Profondeur] = i;
    if(M->n - Profondeur > 1)
      SommeH += E_Double(Rec_Entropie(M, indices, Profondeur + 1, CPk, SPk));
    else
      SommeH += E_Double(SPk(CPk(M, indices)));
  }

  return SommeH;
}

double Entropie(t_matrice *M, CalculPk CPk, SommePk SPk)
{

  double SommeH;
  unsigned int *indices = (unsigned int *) malloc(M->n * sizeof(unsigned int));

  SommeH = Rec_Entropie(M, indices, 0, CPk, SPk);

  free(indices);

  return SommeH;

}

int main(int argc, char *argv[])
{

  t_matrice *M;
  int i;
  unsigned int n;
  unsigned int *lgrs;

  init_seed();

  if(argc < 3) {
    printf ("Utilisation :\n%s <dimension n> <taille n>...<taille 1>\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);

  if(n < 1) {
    printf("La dimension doit être supérieure à 0 !\n");
    exit(2);
  }

  lgrs = (unsigned int *) malloc(n * sizeof(unsigned int));

  for(i = 0; i < n; i++)
    lgrs[i] = atoi(argv[i+2]);

  M = Cree_Matrice(n, lgrs);

  Remplir_Matrice(M, E_MetsDes1);

  Afficher_Matrice(M);

  for(i = 0; i < n; i++)
    lgrs[i] = 0;

  printf("Calcul de NewP : %f\n", E_Double(NewP(M, lgrs)));
  printf("Calcul de OldP : %f\n", E_Double(OldP(M, lgrs)));
  printf("Calcul de HNew : %f\n", Entropie(M, NewP, SommeP));
  printf("Calcul de HOld : %f\n", Entropie(M, OldP, SommeP));

  Liberer_Matrice(M);

  return 0;
}
