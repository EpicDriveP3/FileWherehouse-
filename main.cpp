/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on June 1, 2016, 2:16 PM
 */

#include <cstdlib>
#include "HashTable.h"
#include "structs.h"
#include <sys/types.h>
#include <dirent.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*
    int ch, key, indice, type;
    string tmp2;
    HashTable HT;
    cout<<"Total de buckets de la HashTable: "<<endl;
    cin>>HT.buckets;
    
    while(1){
        cout<<"1. Insertar  2. Borrar"<<endl;
        cout<<"3. Buscar    4. Visualizar HashTable"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Escriba la opcion: "<<endl;
        cin>>ch;
        
        switch(ch){

            case 1:
                cout<<"Escriba el key a insertar: "<<endl;
                cin>>key;
                indice=key%HT.buckets;
                cout<<"1. String  2. Int"<<endl;
                cout<<"3. Float   4. Double"<<endl;
                cout<<"5. Image   6. Binary"<<endl;
                cout<<"Escriba el tipo de dato del key: "<<endl;
                cin>>type;
                
                if(type<=4 && type>=1){
                    cout<<"Escriba el dato del key: "<<endl;
                    cin>>tmp2;  
                    HT.Write(key, tmp2, indice);
                }
                
                if(type==5){
                    ifstream fin("foo.png", ios::in | ios::binary);
                    ostringstream oss;
                    oss<<fin.rdbuf();
                    string data(oss.str());
                    HT.Write(key, data, indice);                 
                }
                
                
                break;

            case 2:
                cout<<"Escriba el key a borrar: "<<endl;
                cin>>key;
                indice=key%HT.buckets;
                HT.Delete(key, indice);
                break;

            case 3:
                cout<<"Escriba el key a buscar: "<<endl;
                cin>>key;
                indice=key%HT.buckets;
                HT.Search(key, indice);
                break;

            case 4:
                
                for(int indice=0; indice<HT.buckets; indice++){
                    HT.Display(indice);                
                }
                
                break;
                
            case 5:
                
                for(int indice=0; indice<HT.buckets; indice++){
                    string str="Indice "+to_string(indice);
                    char * file=new char[str.size()+1];
                    copy(str.begin(), str.end(), file);
                    file[str.size()]='\0'; 
                    remove(file);
                }
                
                exit(0);
                    
            default:
                cout<<"Escriba alguna opcion correcta (1-5): "<<endl;
                break; 
                    
        }
    
    }
     * *
    int key=4;
    RegisterBTree<int> regPrueba;
    regPrueba._datas= (int*)calloc(sizeof(int),(key-1));
    regPrueba._sons=(int*)calloc(sizeof(int),key);
    regPrueba._datas[0]=23;
    regPrueba._key=key;
    regPrueba._NofDatas++;
    regPrueba._father=0;
    int sizeReg= (key-1)*4 + key*4 + 12;
    fstream file;
    file.open("FilesPlaces.dat", ios::binary|ios::app);
    file.write((const char*)&regPrueba, sizeReg);
    
    RegisterBTree<int> regPruebaRead;
    file.read((char*)&regPruebaRead, sizeReg);
    cout<<regPruebaRead._father<<endl;
    cout<<regPruebaRead._key<<endl;
    cout<<regPruebaRead._NofDatas<<endl;
    for(int i =0; i<key; i++)
        cout<<regPruebaRead._datas[i]<<endl;
    for(int i =0; i<key; i++)
        cout<<regPruebaRead._sons[i]<<endl;
    file.close();*/
    /*char* dir="/home/ellioth/NetBeansProjets2/FileWarehouse++\0";
    struct dirent *dp;
    DIR *fd;
    if ((fd = opendir(dir)) == NULL) {
      fprintf(stderr, "listdir: can't open %s\n", dir);
      return 0;
    }
    while ((dp = readdir(fd)) != NULL) {
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
      continue;    /* skip self and parent 
    printf("%s/%s\n", dir, dp->d_name);
    }
    closedir(fd);*/
    
    return 0;
}
