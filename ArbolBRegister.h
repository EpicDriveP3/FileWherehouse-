/* 
 * File:   ArbolBRegister.h
 * Author: ellioth
 *
 * Created on June 15, 2016, 11:24 PM
 */

#ifndef ARBOLBREGISTER_H
#define	ARBOLBREGISTER_H
#include "Constantes.h"
#include "structs.h"
#include <string.h>
#include <string>

template <typename Dp>
class ArbolBRegister : public Constantes{
public:
    ArbolBRegister(int pKeys);
    virtual ~ArbolBRegister();
    void insertData(Dp pData);
    void borrarData(Dp pData);
    bool findData(Dp pData);
    void printTree();
private:
    //nodo raiz
    NodoBTree<Dp> _root;
    //numero de Keys que usamos en el arbol.
    int _keys;
    int _sizeOfRegister;
    void insertHelper(NodoBTree<Dp>* pNodo,NodoBTree<Dp>* pPadre,Dp pDato);
    NodoBTree<Dp>* breakNode(NodoBTree<Dp>* pNodo);
    void desplacementNode(NodoBTree<Dp>* pNodo, Dp pDato);
    void deleteHelper(NodoBTree<Dp>* pNodo, NodoBTree<Dp>* pPadre,Dp pDato);
    bool findHelper(NodoBTree<Dp>* pNodo, Dp pDato);
    void printTreeHelper(NodoBTree<Dp>* pNodo, int pNodoNumber);
};

#endif	/* ARBOLBREGISTER_H */

