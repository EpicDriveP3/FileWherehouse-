/* 
 * File:   servidor.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 1:52 PM
 */

#include "servidor.h"

servidor::servidor(int port) {
    _portno= port;
    _listOfSocket=new Lista<int>();
    if(pthread_create(&_AceptThread, NULL, servidor::startMainThread,this)!=CERO)
        error(ERROR6);
}

servidor::~servidor() {
    free(_dataRecivedFromSocket);
}

void* servidor::startAcepting() {
    _dataRecivedFromSocket= malloc(CIENTO_VEINTE_OCHO);
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
        //_listOfSocket->insert(_newsockfd);
        ThreadClienteData nuevo={_newsockfd, this};
        if(pthread_create(&_ListenThread,NULL, &servidor::startListeningThread
                ,&nuevo)!=CERO)
            error(ERROR7);
    }
    close(_sockfd);
}

void* servidor::startListening(void* Data) {
    int sockFD= ((ThreadClienteData*)Data)->_sockFd;
    bzero(_dataRecivedFromSocket, CIENTO_VEINTE_OCHO);
    _n = recv(_newsockfd,_dataRecivedFromSocket,
            CIENTO_VEINTE_OCHO-UNO,0);
    if(_n<CERO)
        error(ERROR5);
    
    ///falta hacer el salvado de datos
}

void servidor::sendMsg(char* pMsg, int pSize) {
    _n=send(_newsockfd, pMsg, pSize,0);
    if (_n < CERO) 
        error(ERROR4);
    if(DEBUG)
        cout<<"mensaje enviado"<<endl;
}

const char* servidor::listenMsg() {
    bzero(_dataRecivedFromSocket, CIENTO_VEINTE_OCHO);
    _n = recv(_newsockfd,_dataRecivedFromSocket,
            CIENTO_VEINTE_OCHO-UNO,0);
    if(_n<CERO)
        error(ERROR5);
    return (const char*)_dataRecivedFromSocket;   
}

void servidor::error(const char* msg) {
    perror(msg);
    exit(UNO);
}
