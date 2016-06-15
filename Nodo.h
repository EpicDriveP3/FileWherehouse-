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
    Nodo* getNext();
private:
    Nodo* _Next;
    Dp _data;
};

#endif	/* NODO_H */

