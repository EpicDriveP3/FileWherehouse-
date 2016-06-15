/* 
 * File:   NodoB.h
 * Author: ellioth
 *
 * Created on June 1, 2016, 5:47 PM
 */

#ifndef NODOB_H
#define	NODOB_H
#include "Constantes.h"

template <class Dp>
class NodoB : public Constantes{
public:
    NodoB(int pSizeOfKies);
    virtual ~NodoB();
    void insertNode(Dp pDato);
    int getSize();
    void reventar(Dp pDato);
    NodoB<Dp>* getSon(int pSon);
private:
    Dp* _Dato;
    NodoB<Dp>* _Hijos;
    int _size;
    int _Kies;
};

#endif	/* NODOB_H */

