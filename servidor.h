/* 
 * File:   servidor.h
 * Author: ellioth
 *
 * Created on March 22, 2016, 1:52 PM
 */

#ifndef SERVIDOR_H
#define	SERVIDOR_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <pthread.h>
#include <stdlib.h>
#include "Constantes.h"
#include "structs.h"
#include "Lista.h"

using namespace std;
class servidor : public Constantes{
public:
    servidor(int port);
    virtual ~servidor();
    void sendMsg(char* pMsg, int pSize);
    void listenMsg(ClienteConnect<char*>* pDato);
    int getCantPersConnect();
    int getSockFd(int pNumber);
private:
    pthread_t _AceptThread, _ListenThread;
    pthread_mutex_t _lock;
    //datos propios de la instanciacion del servidor
    int _sockfd, _newsockfd, _portno, _n, _codigos;
    socklen_t _clilen;
    void* _dataRecivedFromSocket;
    Lista<ClienteConnect<char*>>* _listOfClient;
    struct sockaddr_in _serv_addr, _cli_addr;
    void* startListening(void* Data);
    void* startAcepting(void);
    /**
     * metodo para inicializar el hilo principal que esta escuchando
     * conexiones de los clientes.
     * @param Data recibe un this de la clase.
     * @return retorna el acceso a un metodo de la clase.
     */
    static void * startMainThread(void* Data){
        return ((servidor*)Data)->startAcepting();
    };
    
    /**
     * metodo para inicializar el thread que va a escuchar 
     * a los cliente nos realizan pedidos.
     * @param Data recibe un struct conformado por el sockfd 
     * y el this de la clase.
     * @return retorna el acceso al metodo.
     */
    static void * startListeningThread(void* Data){
        ThreadClienteData temp= *(ThreadClienteData*)Data;
        return ((servidor*)temp._clase)->startListening(Data);
    };
};

#endif	/* SERVIDOR_H */

