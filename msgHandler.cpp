/* 
 * File:   msgHandler.cpp
 * Author: ellioth
 * 
 * Created on June 15, 2016, 1:34 PM
 */


#include "msgHandler.h"
#include "ArbolBRegister.h"

msgHandler::msgHandler(int pPort, const char* pIP, const char* pFilesPlace) {
    _FilesPlace=pFilesPlace;
    _server= new servidor(pPort);
    _arbolB= new ArbolBS<char*>(3);
    srand(time(NULL));
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
    AtributosClientes._dato=(char*)malloc(SPACE_MEMORY);
    while(true){
        _server->listenMsg(&AtributosClientes);
        rapidjson::Document _JsonDocument;
        cout<<"prueba de conexion"<<endl;
        _JsonDocument.Parse((const char*)AtributosClientes._dato);
        if(!_JsonDocument.IsObject()){
            std::cout<<"falla, archivo no es tipo json"<<std::endl;
            return NULL;
        }
        cout<<"prueba de conexion"<<endl;
        //obtenemos la operacion a realizar
        rapidjson::Value & data = _JsonDocument[OPERATION];
        int op= data.GetInt();
        cout<<"prueba de conexion"<<endl;
        //obtenemos el id procedente del mensaje
        data=_JsonDocument[ID];
        if(op==WRITE){
            string datoTemp=AtributosClientes._dato;
            write(datoTemp.c_str());
        }
        //bloque de lectura
        else if(op==READ){
            cout<<"prueba de conexion"<<endl;
            read(data.GetString(), AtributosClientes._sockFd);
        }
        //bloque de borrado
        else if(op==DEL){
            cout<<"prueba de conexion"<<endl;
            eliminar((const char*)data.GetString());
        }
        cout<<"prueba de conexion"<<endl;
    }
}

void msgHandler::read(const char* msg, int sockfd) {
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(msg);
    rapidjson::Value& getDataOfJson= _JsonDocument[MSG];
    //string para obtener el largo de caracteres de la cadena.
    //**no sirve para nada mas**
    rapidjson::StringBuffer sbr;
    rapidjson::Writer<rapidjson::StringBuffer>writer(sbr);
    getDataOfJson.Accept(writer);
    string getMsgDatas= sbr.GetString();
    //id del mensaje que nos esta entrando.
    getDataOfJson= _JsonDocument["key"];
    int keyOfData=getDataOfJson.GetInt();
    //_DataBaseTable->search(keyOfData, getMsgDatas);
    
    string temp=(string)_arbolB->getData((char*)getMsgDatas.c_str());
    
    fstream file;
    file.open(temp, ios::binary);
    file.seekg(0, ios::end);
    int largo=file.tellg();
    file.seekg(0);
    
    void * lector= malloc(largo);
    file.read((char*)lector,largo);
    file.close();
    /*
    string mimeType= temp.substr(temp.find(".",0,1),temp.length());
    string NewJson=generateJson(lector, msg, mimeType.c_str(), largo);
    */
    ClienteConnect<char*> sender;
    sender._dato="{\"op\":1,\"id\":32,\"mimeType\":\".txt\",\"msg\":{brencwibievqooivnqipurenviebviqbviefbvibeqivuberivenrivnieurvneirun}}";
    sender._sockFd=sockfd;
    _server->sendMsg(&sender);
    
}

void msgHandler::write(const char* msg) {
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(msg);
    rapidjson::Value& getDataOfJson= _JsonDocument[MSG];
    //string para obtener el largo de caracteres de la cadena.
    //**no sirve para nada mas**
    rapidjson::StringBuffer sbr;
    rapidjson::Writer<rapidjson::StringBuffer>writer(sbr);
    getDataOfJson.Accept(writer);
    string getMsgDatas= sbr.GetString();
    //id del mensaje que nos esta entrando.
    getDataOfJson= _JsonDocument["key"];
    int keyOfData=getDataOfJson.GetInt();
    //_DataBaseTable->Write(keyOfData,getMsgDatas);
    _arbolB->insertData((char*)getMsgDatas.c_str());
    _arbolB->printTree();
}

void msgHandler::eliminar(const char* msg) {
    
}

string msgHandler::generateJson(void* pDato,const char* msg, const char* mimeType, int largo){
    rapidjson::Document _JsonDocument;
    _JsonDocument.Parse(msg);
    rapidjson::Value& getDataOfJson= _JsonDocument["op"];
    char* newMsg= (char*)malloc(largo+45);
    string finalMsg="{\"op\":";
    finalMsg.append("1");
    finalMsg.append(",");
    //getDataOfJson= _JsonDocument["id"];
    finalMsg.append("\"id\":");
    finalMsg.append("3");
    finalMsg.append(",");
    //getDataOfJson= _JsonDocument["msg"];
    finalMsg.append("\"mimeType\":");
    finalMsg.append(".png");
    finalMsg.append(",");
    finalMsg.append("\"msg\":{");
    cout<<"prueba"<<endl;
    strncpy(newMsg, finalMsg.c_str(), 41);
    int i=43;
    for(; i<largo; i++){
        *(newMsg+i)=*((char*)(pDato+i));
    }
    //memcpy(newMsg, lector, largo);
    //strncpy((char*)finalMsg.c_str(), (char*)lector,largo);
    //finalMsg.append("}}");
    newMsg[largo+43]='}';
    newMsg[largo+44]='}';
    //newMsg[largo+44]='\0';
    cout<<newMsg<<endl;
    cout<<finalMsg<<endl;
    return finalMsg;
}
