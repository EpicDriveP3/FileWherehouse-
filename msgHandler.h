/* 
 * File:   msgHandler.h
 * Author: ellioth
 *
 * Created on June 15, 2016, 1:34 PM
 */

#ifndef MSGHANDLER_H
#define	MSGHANDLER_H
#include "servidor.h"
#include "structs.h"
#include "Constantes.h"
#include "ArbolBS.h"
#include "HashTable.h"
#include <string>
#include <pthread.h>

class msgHandler : public Constantes{
public:
    msgHandler(int pPort, const char* pIP);
    virtual ~msgHandler();
    
private:
    servidor* _server;
    void write( const char* msg);
    void read(const char* msg);
    void eliminar(const char* msg);
};

#endif	/* MSGHANDLER_H */

