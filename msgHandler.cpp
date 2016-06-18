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
    _arbolB= new ArbolBS<int>(3);
    int CantOfPeopleConnect=0;
    pthread_t starter;
    while(true){
        if(CantOfPeopleConnect<_server->getCantPersConnect()){
            cout<<"prueba de conexion"<<endl;
            ThreadClienteData temp={CantOfPeopleConnect,(void*)this};
            pthread_create(&starter, NULL, mainLoopHelper,(void*)&temp);
            CantOfPeopleConnect++;
        }
    }
}

msgHandler::~msgHandler() {
    
}

void* msgHandler::mainLoop(void* pData) {
    ThreadClienteData temp = *((ThreadClienteData*)pData);
    
    ClienteConnect<char*> AtributosClientes=_server->getSockFd(
    temp._NumberOfThread);
    
    while(true){
        _server->listenMsg(&AtributosClientes);
        rapidjson::Document _JsonDocument;
        _JsonDocument.Parse((const char*)AtributosClientes._dato);
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
                string datoTemp=AtributosClientes._dato;
                write(datoTemp.c_str());
            }*/
        }
        //bloque de lectura
        else if(op==READ){
            read(data.GetString(), AtributosClientes._sockFd);
        }
        //bloque de borrado
        else if(op==DEL){
            eliminar((const char*)data.GetString());
        }
    }
}

void msgHandler::read(const char* msg, int sockfd) {
    
}

void msgHandler::write(const char* msg) {

}

void msgHandler::eliminar(const char* msg) {

}
