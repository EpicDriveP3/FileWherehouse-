/* 
 * File:   Lista.h
 * Author: ellioth
 *
 * Created on June 1, 2016, 3:46 PM
 */

#ifndef LISTA_H
#define	LISTA_H
#include "Nodo.h"
#include "Constantes.h"

template <class Dp>
class Lista : public Constantes{
public:
    Lista();
    virtual ~Lista();
    void insert(Dp pDato);
    int size();
    void borrar(Dp pDato);
private:
    Nodo<Dp> *_head,*_tail;
    int _size;
};

#endif	/* LISTA_H */

