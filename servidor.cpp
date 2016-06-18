/* 
 * File:   servidor.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 1:52 PM
 */

#include "servidor.h"

servidor::servidor(int port) {
    _portno= port;
    _listOfClient=new Lista<ClienteConnect<char*>>();
    if(pthread_mutex_init(&_lock,NULL)!=CERO)
        error("mutex falied on create");
    if(pthread_create(&_AceptThread, NULL, servidor::startMainThread,this)!=CERO)
        error(ERROR6);
}

servidor::~servidor() {
    free(_dataRecivedFromSocket);
}

void* servidor::startAcepting() {
    //_dataRecivedFromSocket= malloc(CIENTO_VEINTE_OCHO);
    _sockfd = socket(AF_INET, SOCK_STREAM, CERO);
    //resivision de si la conexion del socket 
    // fue positiva o fallida.
    if (_sockfd <CERO)
        error(ERROR1);
    //se escibe 0s en la variables puesta.
    //esto garantiza que no se use memoria sucia.
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    //establecemos los datos que se van a utilizar 
    //en el socket.
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(_portno);
    if (bind(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr))<CERO)
        error(ERROR2);
    //se pone a escuchar en el socket si hay nuevas conexiones.
    listen(_sockfd,CINCO);
    _clilen = sizeof(_cli_addr);
    while(true){
        _newsockfd = accept(_sockfd, (struct sockaddr*) &_cli_addr, &_clilen);
        if (_newsockfd < CERO)
            error(ERROR3);
        if(DEBUG)
            printf("servidor: got connection from %s port %d\n",
                    inet_ntoa(_cli_addr.sin_addr), ntohs(_cli_addr.sin_port));
        ClienteConnect<char*> temp= {_newsockfd, NULL, true};
        pthread_mutex_lock(&_lock);
        _listOfClient->insert(temp);
        pthread_mutex_unlock(&_lock);
    }
    close(_sockfd);
}

void servidor::sendMsg(ClienteConnect<char*>* pData) {
    _n=send(pData->_sockFd, pData->_dato, SPACE_MEMORY,0);
    if (_n < CERO)
        error(ERROR4);
    if(DEBUG)
        cout<<"mensaje enviado"<<endl;
}

void servidor::listenMsg(ClienteConnect<char*>* pData) {
    bzero(pData->_dato, SPACE_MEMORY);
    _n = recv(pData->_sockFd,pData->_dato,
            SPACE_MEMORY-UNO,CERO);
    if(_n<CERO)
        error(ERROR5);
}

int servidor::getCantPersConnect() {
    int size;
    pthread_mutex_lock(&_lock);
    size=_listOfClient->size();
    pthread_mutex_unlock(&_lock);
    return size;
}

ClienteConnect<char*> servidor::getSockFd(int pNumber) {
    ClienteConnect<char*> datas;
    pthread_mutex_lock(&_lock);
    datas=(_listOfClient->get(pNumber))->getData();
    pthread_mutex_unlock(&_lock);
    return datas;
}
