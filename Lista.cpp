/* 
 * File:   Lista.cpp
 * Author: ellioth
 * 
 * Created on June 1, 2016, 3:46 PM
 */

#include "Lista.h"

template<class Dp>
Lista<Dp>::Lista() {
    
}

template<class Dp>
Lista<Dp>::~Lista() {
    if(_head!=NULL){
        delete _head;
        delete _tail;
    }
}

template<class Dp>
void Lista<Dp>::insert(Dp pDato) {
    if(_head==NULL){
        _head=new Nodo<Dp>(pDato);
        _size++;
        return;
    }
    Nodo<Dp>* temp=_head;
    for(int i =0; i<(_size-UNO); i++){
        temp=temp->getNext();
    }
    Nodo<Dp>* nuevo= new Nodo<Dp>(pDato);
    temp->SetNext(nuevo);
    _size++;
}

template<class Dp>
void Lista<Dp>::borrar(Dp pDato) {

}

template<class Dp>
int Lista<Dp>::size() {
    return _size;
}
