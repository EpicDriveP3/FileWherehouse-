/* 
 * File:   NodoB.cpp
 * Author: ellioth
 * 
 * Created on June 1, 2016, 5:47 PM
 */

#include <stdlib.h>
#include "NodoB.h"

template<class Dp>
NodoB<Dp>::NodoB(int pSizeOfKies) {
    _Dato= (Dp*)malloc(sizeof(Dp)*pSizeOfKies);
    _Hijos=NULL;
    _Kies=pSizeOfKies;
}

template<class Dp>
NodoB<Dp>::~NodoB() {

}

template<class Dp>
int NodoB<Dp>::getSize() {
    return _size;
}

template<class Dp>
NodoB<Dp>* NodoB<Dp>::getSon(int pSon) {
    
}

template<class Dp>
void NodoB<Dp>::insertNode(Dp pDato) {
    if(_size==CERO){
        _Dato[_size]=pDato;
        _Hijos=(NodoB<Dp>*)malloc(sizeof(NodoB<Dp>)*(_Kies));
        _size++;
        return;
    }
    int i=0,j=0;
    for(; i<_Kies; i++){
        if(pDato<_Dato[i])
            break;
    }
    for(j=_size;j!=i;j--){
        _Dato[j]=_Dato[j-1];
    }
    _Dato[i]=pDato;
}

template<class Dp>
void NodoB<Dp>::reventar(Dp pDato) {
    
}

