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
#include "structs.h"

/**
 * clase para crear listas de cualquier tipo de dato.
 */
template <class Dp>
class Lista : public Constantes{
public:
    Lista();
    virtual ~Lista();
    void insert(Dp pDato);
    int size();
    void borrar(Dp pDato);
    Nodo<Dp>* get(int place);
    Nodo<Dp>* get(Dp pDato);
    int getPlace(Dp pDato);
    void set(int place, Dp dato);
private:
    Nodo<Dp> *_head,*_tail;
    int _size;
};

template<class Dp>
Lista<Dp>::Lista() {    
}

/**
 * metodo destructor de la lista.
 */
template<class Dp>
Lista<Dp>::~Lista() {
    if(_head!=NULL){
        delete _head;
        delete _tail;
    }
}

/**
 * metodo para insertar datos en la lista
 * @param pDato recibe un dato tipo especificado en el template.
 */
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

/**
 * metodo para borrar datos en la lista.
 * @param pDato
 */
template<class Dp>
void Lista<Dp>::borrar(Dp pDato) {

}

/*
 * metodo para obtener el tamñano de la lista
 */
template<class Dp>
int Lista<Dp>::size() {
    return _size;
}

/**
 * metodo que retorna el dato del espacio de la lista.
 * @param place dato del tipo definido que es el espacio
 * del dato de donde se encuentra en la lista.
 * @return retorna un NULL si el lugar del dato esta fuera de la
 * lista o un dato tipo Nodo si existe.
 */
template<class Dp>
Nodo<Dp>* Lista<Dp>::get(int place) {
    if(place>=_size)
        return NULL;
    Nodo<Dp>* temp=_head;
    for(int i=0; i<place; i++)
        temp=temp->getNext();
    return temp->getData();
}

template<class Dp>
Nodo<Dp>* Lista<Dp>::get(Dp pData) {
    Nodo<Dp>* temp=_head;
    int i=0;
    for(; i<_size; i++)
        if(temp->getData()==pData)
            break;
        temp=temp->getNext();
    return temp;
}

template<class Dp>
int Lista<Dp>::getPlace(Dp pDato) {
    Nodo<Dp>* temp=_head;
    int i=0;
    for(; i<_size; i++)
        if(temp->getData()==pDato)
            break;
        temp=temp->getNext();
    return i;
}


#endif	/* LISTA_H */

