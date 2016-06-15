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
    
HashTable::HashTable(){}

HashTable::HashTable(const HashTable& orig){}

HashTable::~HashTable(){}

void HashTable::Write(int key, string data, int indice){
    string str="Indice "+to_string(indice);
    ofstream outFile;
    outFile.open(str, ios::binary|ios::app);
    HashTable obj;
    obj.key=key;
    obj.data=(char*)malloc(sizeof(char)*sizeof(data)); 
    strcpy(obj.data, data.c_str()); 
    outFile.write((char*)&obj, sizeof(obj));
    outFile.close();
}

void HashTable::Display(int indice){
    string str="Indice "+to_string(indice);
    cout<<"------------------------------------------"<<endl;
    cout<<str<<endl;
    ifstream inFile;
    inFile.open(str, ios::binary);
    HashTable obj;

    while(inFile.read((char*)&obj, sizeof(obj))){
    	cout<<"           "<<"Key:  "<<obj.key<<endl;
    	cout<<"           "<<"Data: "<<obj.data<<endl;
        cout<<endl;
    }
    
    cout<<"------------------------------------------"<<endl;
    inFile.close();
}

void HashTable::Search(int key, int indice){
    string str="Indice "+to_string(indice);
    cout<<"------------------------------------------"<<endl;
    ifstream inFile;
    inFile.open(str, ios::binary);
    HashTable obj;

    while(inFile.read((char*)&obj, sizeof(obj))){
        
        if(obj.key==key){
            cout<<"Key:  "<<obj.key<<endl;
            cout<<"Data: "<<obj.data<<endl;
            cout<<endl;
        }
        
    }
    
    cout<<"------------------------------------------"<<endl;
    inFile.close();
}

void HashTable::Delete(int key, int indice){
    string str="Indice "+to_string(indice);
    HashTable obj;
    ifstream inFile;
    inFile.open(str, ios::binary);

    ofstream outFile;
    outFile.open("temp.dat", ios::out|ios::binary);

    while(inFile.read((char*)&obj, sizeof(obj))){
        
        if(obj.key!=key){
            outFile.write((char*)&obj, sizeof(obj));
        }
        
    }

    char * writable=new char[str.size()+1];
    copy(str.begin(), str.end(), writable);
    writable[str.size()]='\0'; 
    inFile.close();
    outFile.close();
    remove(writable);
    rename("temp.dat", writable);
}