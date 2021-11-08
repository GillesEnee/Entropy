/*
** matrice.h
** 
** Made by Gilles Enée
** Login   <genee@genee-laptop>
** 
** Started on  Wed Oct 10 17:28:12 2007 Gilles Enée
** Last update Wed Oct 10 17:32:52 2007 Gilles Enée
*/

#ifndef   	MATRICE_H_
#define   	MATRICE_H_

#include "element.h"

typedef struct type_matrice {
  unsigned int n;
  unsigned int lg;
  union {
    struct type_matrice ** matrice;
    t_elem * elements;
  };
} t_matrice;

typedef t_elem (* f_remplir) (void);
typedef t_elem (* f_applique) (t_elem);
typedef t_elem (* f_recursif) (t_elem, t_elem);

t_matrice * Cree_Matrice(unsigned int, unsigned int *);
t_matrice * Copie_Cree_Matrice(t_matrice *);
t_matrice * Copie_Matrice(t_matrice *);

void Remplir_Matrice(t_matrice *, f_remplir);
void Afficher_Matrice(t_matrice *);
void Liberer_Matrice(t_matrice *);
void Applique_Matrice(t_matrice *, f_applique, unsigned int *);

t_elem Recursif_Matrice(t_matrice *, f_recursif);
t_elem Valeur(t_matrice *, unsigned int *);
t_matrice * Somme_Matrices(t_matrice *, t_matrice *);

#endif 	    /* !MATRICE_H_ */
