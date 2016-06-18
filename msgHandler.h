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
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "HashTable.h"
#include "ArbolBS.h"


class msgHandler : public Constantes{
public:
    msgHandler(int pPort, const char* pIP, const char* pFilesPlace);
    virtual ~msgHandler();
private:
    servidor* _server;
    const char* _FilesPlace;
    HashTable<std::string>* _DataBaseTable;
    ArbolBS<int>* _arbolB;
    void* fileDataBase();
    void* mainLoop(void* pData);
    static void* mainLoopHelper(void* data){
        ThreadClienteData temp= *((ThreadClienteData*)data);
        return ((msgHandler*)(temp._clase))->mainLoop(&temp);
    };
    void write( const char* msg);
    void read(const char* msg, int sockfd);
    void eliminar(const char* msg);
};

#endif	/* MSGHANDLER_H */

