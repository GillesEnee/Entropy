/*
** element.h
** 
** Made by Gilles Enée
** Login   <genee@genee-laptop>
** 
** Started on  Wed Oct 10 17:34:41 2007 Gilles Enée
** Last update Thu Oct 11 16:00:38 2007 Gilles Enée
*/

#ifndef   	ELEMENT_H_
#define   	ELEMENT_H_

typedef double t_elem;

void init_seed(void);

void E_Copie(t_elem *, t_elem);
t_elem E_Ajoute(t_elem, t_elem);
t_elem E_Multiplie(t_elem, t_elem);
t_elem E_Divise(t_elem, t_elem);
t_elem E_Soustrait(t_elem, t_elem);

t_elem E_MetsDes1(void);
t_elem E_Speciale(void);
t_elem E_MetsHasard(void);
t_elem E_MetsHasard100(void);
t_elem E_MetsDiag1(void);

t_elem Double_E(double);
double E_Double(t_elem);

t_elem Entier_E(long);
long E_Entier(t_elem);

#endif 	    /* !ELEMENT_H_ */
