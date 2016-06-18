/* 
 * File:   ArbolBS.h
 * Author: ellioth
 *
 * Created on June 10, 2016, 11:11 AM
 */

#ifndef ARBOLBS_H
#define	ARBOLBS_H
#include "Constantes.h"
#include "structs.h"
#include <iostream>
#include <string.h>
#include <string>
/**
 * cuando se invoca en el campo este algoritmo proboca que genere un 
 * arbolB con diez mil puntos de vida.
 */
using namespace std;

template <typename Dp>
class ArbolBS: public Constantes {
public:
    ArbolBS(int pKeys);
    virtual ~ArbolBS();
    void insertData(Dp pData);
    void borrarData(Dp pData);
    bool findData(Dp pData);
    void printTree();
    Dp getData(Dp pData);
private:
    //nodo raiz
    NodoBTree<Dp>* _root;
    //numero de Keys que usamos en el arbol.
    int _keys;
    int _sizeOfRegister;
    void insertHelper(NodoBTree<Dp>* pNodo,NodoBTree<Dp>* pPadre,Dp pDato);
    NodoBTree<Dp>* breakNode(NodoBTree<Dp>* pNodo);
    void desplacementNode(NodoBTree<Dp>* pNodo, Dp pDato);
    void deleteHelper(NodoBTree<Dp>* pNodo, NodoBTree<Dp>* pPadre,Dp pDato);
    bool findHelper(NodoBTree<Dp>* pNodo, Dp pDato);
    Dp getDataHelper(NodoBTree<Dp>* pNodo, Dp pDato);
    void printTreeHelper(NodoBTree<Dp>* pNodo, int pNodoNumber);
};

#endif	/* ARBOLBS_H */

