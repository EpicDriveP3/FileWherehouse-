/* 
 * File:   structs.h
 * Author: ellioth
 *
 * Created on March 4, 2016, 11:57 AM
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

/**
 * estructura para definir los 
 * datos del cliente cuando se usan 
 * hilos.
 */
struct ThreadClienteData{
    int _sockFd;
    void* _clase;
};

template <typename Dp>
struct ClienteConnect{
    int _sockFd;
    Dp _dato;
    bool dato;
};

template <typename Dp>
struct NodoBTree{
    Dp * _datas;
    NodoBTree<Dp>* _father;
    NodoBTree<Dp>** _Sons;
    int _Keys;
    int _NOfDatas;
};

template <typename Dp>
struct RegisterBTree{
    Dp * _datas;
    int _father;
    int* _sons;
    int _key;
    int _NofDatas;
};
template <typename Dp>
struct RegisterHash{
    public:
        Dp data;
        int _Keys;
};

#endif	/* STRUCTS_H */

