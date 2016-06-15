/* 
 * File:   ArbolB.h
 * Author: ellioth
 *
 * Created on June 1, 2016, 2:16 PM
 */

#ifndef ARBOLB_H
#define	ARBOLB_H
#include <stddef.h>
#include "structs.h"
#include "Constantes.h"
#include "NodoB.h"

template <class Dp>
class ArbolB : public Constantes{
public:
    ArbolB(int pClaves);
    virtual ~ArbolB();
    void insertar(Dp pDato);
    void borrar(Dp dato);
    Dp getDato(Dp Dato);
    bool findDato(Dp Dato);
private:
    NodoB<Dp>* _root;
    int _Claves;
    void insertHelp(NodoB<Dp>* pNodo, NodoB<Dp>* pPadre, Dp pDato);
};

#endif	/* ARBOLB_H */

