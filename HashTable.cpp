/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Student.cpp
 * Author: betolan
 * 
 * Created on 4 de junio de 2016, 08:10 AM
 */

#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
    elements_for_bucket=(int*)malloc(sizeof(int)*sizeof(buckets)); 
}

HashTable::HashTable(const HashTable& orig){}

HashTable::~HashTable(){}

void HashTable::Write(int key, string data, string name){
 
    const char* string1 = name.c_str();
    
    int total=0;
    int total2=0;
    int indice;
    indice=key%buckets;
    
    for(int i=0; i<=indice; i++){
        total=total+elements_for_bucket[i];
    }
    
    for(int i=0; i<buckets; i++){
        total2=total2+elements_for_bucket[i];
    }
    
    ifstream inFile;
    inFile.open(string1, ios::binary);
    ofstream outFile;
    outFile.open("/home/betolan/NetBeansProjects/prueba/HashTables/temp.dat", ios::binary|ios::app);
    
    HashTable obj;
    HashTable obj2;
    
    obj2.key=key;
    obj2.data=(char*)malloc(sizeof(char)*sizeof(data));  
    strcpy(obj2.data, data.c_str());
    
    int cont=0;
    bool first=true;
    
    if(total2==0){
        outFile.write((char*)&obj2, sizeof(obj2));
        elements_for_bucket[indice]++;
    }
    
    if(total==0 && total2!=0){
         while(inFile.read((char*)&obj, sizeof(obj))){
            if(first==true){
                outFile.write((char*)&obj2, sizeof(obj2));
                outFile.write((char*)&obj, sizeof(obj));
                elements_for_bucket[indice]++;
                first=false;
            }
            else{
                outFile.write((char*)&obj, sizeof(obj));
            }

        }
    }
    
    else{

        while(inFile.read((char*)&obj, sizeof(obj))){
            cont++;

            if(total==cont){
                outFile.write((char*)&obj, sizeof(obj));
                outFile.write((char*)&obj2, sizeof(obj2));
                elements_for_bucket[indice]++;
            }
            else{
                outFile.write((char*)&obj, sizeof(obj));
            }

        }
    
    }
    
    inFile.close();
    outFile.close();
    
    remove(string1);
    rename("/home/betolan/NetBeansProjects/prueba/HashTables/temp.dat", string1);

}

void HashTable::Display(string name){
    const char* string1 = name.c_str();
    cout<<"------------------------------------------"<<endl;
    ifstream inFile;
    inFile.open(string1, ios::binary);
    HashTable obj;

    while(inFile.read((char*)&obj, sizeof(obj))){
    	cout<<"           "<<"Key:  "<<obj.key<<endl;
    	cout<<"           "<<"Data: "<<obj.data<<endl;
        cout<<endl;
    }
    
    cout<<"------------------------------------------"<<endl;
    inFile.close();
}

void HashTable::Delete(int key, string name){
    const char* string1 = name.c_str();
    
    HashTable obj;
    int indice;
    indice=key%buckets;
    ifstream inFile;
    inFile.open(string1, ios::binary);

    ofstream outFile;
    outFile.open("/home/betolan/NetBeansProjects/prueba/HashTables/temp.dat", ios::out|ios::binary);

    while(inFile.read((char*)&obj, sizeof(obj))){
        
        if(obj.key!=key){
            outFile.write((char*)&obj, sizeof(obj));
            elements_for_bucket[indice]--;
        }
        
    }
    
    inFile.close();
    outFile.close();
    remove(string1);
    rename("/home/betolan/NetBeansProjects/prueba/HashTables/temp.dat", string1);
}

void HashTable::search(int key, string name)
{   
    const char* string1 = name.c_str(); 

    int total=0;
    int indice;
    indice=key%buckets;
    
    ifstream inFile;
    inFile.open(string1, ios::binary);
    
    for(int i=0; i<indice; i++){
        total=total+elements_for_bucket[i];
    }
    
    HashTable obj;
    
    if(elements_for_bucket[indice]==0){ 
        cout<<"No hay elementos en este bucket"<<endl;
    }
    
    else{
    
        for(int i=0; i<total;i++){
            inFile.read((char*)&obj, sizeof(obj));    
        }
        
        bool out=false;
        
        for(int i=0; i<elements_for_bucket[indice] && out==false; i++){
            inFile.read((char*)&obj, sizeof(obj));
            
            if(obj.key == key)
            {
                cout<<"           "<<"Key:  "<<obj.key<<endl;
                cout<<"           "<<"Data: "<<obj.data<<endl;
                out=true;
            }
        }
    }
    
    inFile.close();
}

void HashTable::WriteControl(){
    ofstream outFile;
    outFile.open("Control.dat", ios::binary|ios::app);
    
    outFile.write((char*)&buckets, sizeof(buckets));
    cout<<buckets<<endl;
    
    for(int i=0; i<buckets; i++){
        outFile.write((char*)&elements_for_bucket[i], sizeof(elements_for_bucket[i]));
        cout<<elements_for_bucket[i]<<endl;
    }
    
    outFile.close();
        
}

void HashTable::ReadControl(){
    ifstream inFile;
    inFile.open("Control.dat", ios::binary);
    
    int temp=0;
    int total_buckets=0;
    
    inFile.read((char*)&total_buckets, sizeof(total_buckets));
    buckets=total_buckets;
    cout<<buckets<<endl;
    
    for(int i=0; i<buckets; i++){
        inFile.read((char*)&temp, sizeof(temp));
        elements_for_bucket[i]=temp;
        cout<<elements_for_bucket[i]<<endl;
    }
    
    inFile.close();
        
}

void HashTable::AllFiles(){  
    char* dir="/home/betolan/NetBeansProjects/prueba/HashTables\0";
    struct dirent *dp;
    DIR *fd;
    if ((fd = opendir(dir)) == NULL) {
      fprintf(stderr, "listdir: can't open %s\n", dir);
      return;
    }
    while ((dp = readdir(fd)) != NULL) {
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
      continue;    /* skip self and parent */
    printf("%s/%s\n", dir, dp->d_name);
    }
    closedir(fd);
}

void HashTable::QuantityOfFiles(int proccess){
    
    int total_of_files=0;
    
    if(proccess==1){
        ofstream outFile;
        outFile.open("QuantityOfFiles.dat", ios::binary|ios::app);
        
        outFile.write((char*)&total_of_files, sizeof(total_of_files));
        outFile.write((char*)&total_of_files, sizeof(total_of_files));
        
        outFile.close();
    }
    
    if (proccess==2){
        ifstream inFile;
        inFile.open("QuantityOfFiles.dat", ios::binary);
        ofstream outFile2;
        outFile2.open("Temp.dat", ios::binary|ios::app);
        
        inFile.read((char*)&total_of_files, sizeof(total_of_files));
        total_of_files=total_of_files+1;
        outFile2.write((char*)&total_of_files, sizeof(total_of_files));
        outFile2.write((char*)&total_of_files, sizeof(total_of_files));
        
        inFile.close();
        outFile2.close();
        
        remove("QuantityOfFiles.dat");
        rename("Temp.dat", "QuantityOfFiles.dat");
    }
    
    else{
        ifstream inFile;
        inFile.open("QuantityOfFiles.dat", ios::binary);    
        
        inFile.read((char*)&total_of_files, sizeof(total_of_files));
        
        if(total_of_files==0){          
            inFile.close();          
        }
        else{
            ofstream outFile2;
            outFile2.open("Temp.dat", ios::binary|ios::app);
            int temp=0;
            
            total_of_files=total_of_files-1;
            outFile2.write((char*)&total_of_files, sizeof(total_of_files));
            inFile.read((char*)&temp, sizeof(temp));
            outFile2.write((char*)&temp, sizeof(temp));
            
            inFile.close();
            outFile2.close();

            remove("QuantityOfFiles.dat");
            rename("Temp.dat", "QuantityOfFiles.dat");
        }
    }   
    
}

string HashTable::GeneratedNameFile(){    
    int total_of_files=0;
    
    ifstream inFile;
    inFile.open("QuantityOfFiles.dat", ios::binary);
    inFile.read((char*)&total_of_files, sizeof(total_of_files));
    inFile.read((char*)&total_of_files, sizeof(total_of_files));
    
    string Result;        
    ostringstream convert;   
    convert << total_of_files;      
    Result = convert.str();
     
    string name="/home/betolan/NetBeansProjects/prueba/HashTables/HashTable"+Result+".dat";
    
    return name;   
}

void  HashTable::Removee(string name){
    
    string nameC="/home/betolan/NetBeansProjects/prueba/HashTables/"+name;
    
    const char* string1 = nameC.c_str();
    
    if (FILE *file = fopen(string1, "r")) {
        fclose(file);
        remove(string1);
    } else {
        cout<<"No existe"<<endl;
    } 
    
}