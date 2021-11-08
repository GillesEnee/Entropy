/*
** element.c
** 
** Made by (Gilles Enée)
** Login   <genee@genee-laptop>
** 
** Started on  Thu Oct 11 09:36:37 2007 Gilles Enée
** Last update Thu Oct 11 16:01:25 2007 Gilles Enée
*/

#include <stdlib.h>
#include <time.h>
#include "element.h"

/* On utilise des doubles donc on peut faire des opérations standards */

void init_seed(void) {
  srand(time(NULL));
}

void E_Copie(t_elem *e_dest, t_elem e_src)
{
  *e_dest = e_src;
}

t_elem E_Ajoute(t_elem e1, t_elem e2)
{
  return e1 + e2;
}

t_elem E_Multiplie(t_elem e1, t_elem e2)
{
  return e1 * e2;
}

t_elem E_Divise(t_elem e1, t_elem e2)
{
  return e1 / e2;
}

t_elem E_Soustrait(t_elem e1, t_elem e2)
{
  return e1 - e2;
}

t_elem E_MetsDes1(void)
{
  return 1.0;
}

double speciale = 5.0;

t_elem E_Speciale(void)
{
  speciale -= 1.0;
  return speciale;
}

t_elem E_MetsHasard(void)
{
  return (double) random() / RAND_MAX;
}

t_elem E_MetsHasard100(void)
{
  return (double) random() / RAND_MAX * 100.0;
}

t_elem E_MetsDiag1(void)
{
  static int i=0;

  if(i++%9==0)
    return 1.0;
  else
    return 0.0;
}

t_elem Double_E(double d)
{
  return d;
}

double E_Double(t_elem e)
{
  return e;
}

t_elem Entier_E(long l)
{
  return (double) l;
}

long E_Entier(t_elem e)
{
  return (long) e;
}
