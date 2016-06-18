/* 
 * File:   ArbolBRegister.cpp
 * Author: ellioth
 * 
 * Created on June 15, 2016, 11:24 PM
 */

#include "ArbolBRegister.h"

template<typename Dp>
ArbolBRegister<Dp>::ArbolBRegister(int pKeys) {
    if(pKeys<DOS || (pKeys%DOS==0)){
        _keys=pKeys;
        _root=NULL;
        _sizeOfRegister=(_keys-UNO)*CUATRO + _keys*CUATRO+ CUATRO*TRES;
    }
}

template<typename Dp>
ArbolBRegister<Dp>::~ArbolBRegister() {

}

template<typename Dp>
void ArbolBRegister<Dp>::insertData(Dp pData) {

}

template<typename Dp>
void ArbolBRegister<Dp>::insertHelper(NodoBTree<Dp>* pNodo, NodoBTree<Dp>* pPadre, Dp pDato) {

}

template<typename Dp>
NodoBTree<Dp>* ArbolBRegister<Dp>::breakNode(NodoBTree<Dp>* pNodo) {

}

template<typename Dp>
void ArbolBRegister<Dp>::desplacementNode(NodoBTree<Dp>* pNodo, Dp pDato) {

}

template<typename Dp>
void ArbolBRegister<Dp>::borrarData(Dp pData) {

}

template<typename Dp>
void ArbolBRegister<Dp>::deleteHelper(NodoBTree<Dp>* pNodo, NodoBTree<Dp>* pPadre, Dp pDato) {

}

template<typename Dp>
bool ArbolBRegister<Dp>::findData(Dp pData) {

}

template<typename Dp>
bool ArbolBRegister<Dp>::findHelper(NodoBTree<Dp>* pNodo, Dp pDato) {

}

template<typename Dp>
void ArbolBRegister<Dp>::printTree() {

}

template<typename Dp>
void ArbolBRegister<Dp>::printTreeHelper(NodoBTree<Dp>* pNodo, int pNodoNumber) {

}
