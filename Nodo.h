/* 
 * File:   Nodo.h
 * Author: ellioth
 *
 * Created on June 1, 2016, 3:47 PM
 */

#ifndef NODO_H
#define	NODO_H
#include <stddef.h>
template<class Dp>
class Nodo {
public:
    Nodo(Dp data);
    virtual ~Nodo();
    void SetNext(Nodo* pNodo);
    Dp getData();
    void setData(Dp dato);
    Nodo* getNext();
private:
    Nodo* _Next;
    Dp _data;
};

template<class Dp>
Nodo<Dp>::Nodo(Dp data) {
    _data=data;
}

template<class Dp>
Nodo<Dp>::~Nodo() {
    if(_Next!=NULL)
        delete _Next;
}

template<class Dp>
void Nodo<Dp>::SetNext(Nodo* pNodo) {
    _Next=pNodo;
}

template<class Dp>
void Nodo<Dp>::setData(Dp dato){
    _data=dato;
}

template<class Dp>
Dp Nodo<Dp>::getData() {
    return _data;
}

template<class Dp>
Nodo<Dp>* Nodo<Dp>::getNext() {
    return _Next;
}

#endif	/* NODO_H */

