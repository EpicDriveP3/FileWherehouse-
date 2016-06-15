/* 
 * File:   ArbolB.cpp
 * Author: ellioth
 * 
 * Created on June 1, 2016, 2:16 PM
 */

#include "ArbolB.h"

template<class Dp>
ArbolB<Dp>::ArbolB(int pClaves) {
    if(pClaves<DOS)
        return;
    _Claves=pClaves;
    _root=NULL;
}

template<class Dp>
ArbolB<Dp>::~ArbolB() {

}

template<class Dp>
void ArbolB<Dp>::insertar(Dp pDato) {
    ///se verifica si el nodo padre es nulo
    if(_root==NULL){
        _root= new NodoB<Dp>(_Claves);
        _root->insertNode(pDato);
    }
    ///empezamos a recursionar hasta encontrar un hijo donde 
    ///meter al nuevo dato.
    insertHelp(_root, NULL, pDato);
}

template<class Dp>
void ArbolB<Dp>::insertHelp(NodoB<Dp>* pNodo, NodoB<Dp>* pPadre, Dp pDato) {
    ///verifica si queda espacio en el nodo padre
    if(pNodo->getSize()<_Claves){
        pNodo->insertNode(pDato);
        return;
    }
    else{
        
    }
}

template<class Dp>
void ArbolB<Dp>::borrar(Dp dato) {

    
}

template<class Dp>
bool ArbolB<Dp>::findDato(Dp Dato) {

}

template<class Dp>
Dp ArbolB<Dp>::getDato(Dp Dato) {

}
