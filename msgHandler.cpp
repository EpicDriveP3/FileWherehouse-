/* 
 * File:   msgHandler.cpp
 * Author: ellioth
 * 
 * Created on June 15, 2016, 1:34 PM
 */

#include "msgHandler.h"

msgHandler::msgHandler(int pPort, const char* pIP, const char* pFilesPlace) {
    _FilesPlace=pFilesPlace;
    _server= new servidor(pPort);
    int CantOfPeopleConnect=0;
    pthread_t starter;
    while(true){
        if(CantOfPeopleConnect<_server->getCantPersConnect()){
            pthread_create(&starter, NULL, mainLoopHelper,this);
            CantOfPeopleConnect++;
        }
    }
}

msgHandler::~msgHandler() {
    
}

void* msgHandler::mainLoop() {
    int sockfd=_server->getSockFd(_server->getCantPersConnect());
    while(true){
        std::string msg;//= _server->listenMsg();
        rapidjson::Document _JsonDocument;
        _JsonDocument.Parse(msg.c_str());
        if(!_JsonDocument.IsObject()){
            std::cout<<"falla, archivo no es tipo json"<<std::endl;
            return NULL;
        }
        //obtenemos la operacion a realizar
        rapidjson::Value & data = _JsonDocument[OPERATION];
        int op= data.GetInt();
        //obtenemos el id procedente del mensaje
        data=_JsonDocument[ID];
        if(op==WRITE){
            //bloque para econtrar repetidos
            /*if(_DataBaseTable->Search(data.GetInt())){}
            else{
                write(msg.c_str());
            }*/
        }
        //bloque de lectura
        else if(op==READ){
            read(data.GetString(),sockfd);
        }
        //bloque de borrado
        else if(op==DEL){
            eliminar(data.GetString());
        }
    }
}

void msgHandler::read(const char* msg, int sockfd) {
    
}

void msgHandler::write(const char* msg) {

}

void msgHandler::eliminar(const char* msg) {

}
