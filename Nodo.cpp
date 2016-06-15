/* 
 * File:   Nodo.cpp
 * Author: ellioth
 * 
 * Created on June 1, 2016, 3:47 PM
 */

#include "Nodo.h"

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
Dp Nodo<Dp>::getData() {
    return _data;
}

template<class Dp>
Nodo<Dp>* Nodo<Dp>::getNext() {
    return _Next;
}

