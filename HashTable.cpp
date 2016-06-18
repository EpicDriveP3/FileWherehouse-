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

template<typename Dp>
HashTable<Dp>::HashTable() {
    elements_for_bucket=(int*)malloc(sizeof(int)*sizeof(buckets)); 
}

template<typename Dp>
HashTable<Dp>::HashTable(const HashTable& orig) {

}

template<typename Dp>
HashTable<Dp>::~HashTable() {

}


template<typename Dp>
void HashTable<Dp>::Write(int key, Dp data){
    int total=0;
    int total2=0;
    int indice;
    indice=key%buckets;
    
    for(int i=0; i<=indice; i++){
        total=total+elements_for_bucket[i];
        cout<<"total"<<total<<endl;
        cout<<"ele"<<elements_for_bucket[i]<<endl;
    }
    
    for(int i=0; i<buckets; i++){
        total2=total2+elements_for_bucket[i];
        cout<<"total2"<<total2<<endl;
    }
    
    ifstream inFile;
    inFile.open(DISK_LOCATION, ios::binary);
    ofstream outFile;
    outFile.open(DISK_LOCATION_TEMP, ios::binary|ios::app);
    
    HashTable obj;
    HashTable obj2;
    
    obj2.key=key;
    obj2.data=(char*)malloc(sizeof(char)*sizeof(data));  
    memcpy(obj2.data, data, sizeof(data));
    
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
    remove(DISK_LOCATION);
    rename(DISK_LOCATION_TEMP, DISK_LOCATION);

}

template<typename Dp>
void HashTable<Dp>::Display() {
    cout<<"------------------------------------------"<<endl;
    ifstream inFile;
    inFile.open("HashTable.dat", ios::binary);
    HashTable obj;

    while(inFile.read((char*)&obj, sizeof(obj))){
    	cout<<"           "<<"Key:  "<<obj.key<<endl;
    	cout<<"           "<<"Data: "<<obj.data<<endl;
        cout<<endl;
    }
    
    cout<<"------------------------------------------"<<endl;
    inFile.close();
}

template<typename Dp>
void HashTable<Dp>::Delete(int key){
    HashTable obj;
    int indice;
    indice=key%buckets;
    ifstream inFile;
    inFile.open(DISK_LOCATION, ios::binary);

    ofstream outFile;
    outFile.open(DISK_LOCATION_TEMP, ios::out|ios::binary);

    while(inFile.read((char*)&obj, sizeof(obj))){
        
        if(obj.key!=key){
            outFile.write((char*)&obj, sizeof(obj));
            elements_for_bucket[indice]--;
        }
        
    }
    inFile.close();
    outFile.close();
    remove(DISK_LOCATION);
    rename(DISK_LOCATION_TEMP, DISK_LOCATION);
}

template<typename Dp>
void HashTable<Dp>::Search(int key){
    ifstream inFile;
    inFile.open(DISK_LOCATION, ios::binary);
    
    HashTable obj;

    while(inFile.read((char*)&obj, sizeof(obj)))
    {
        if(obj.key == key)
        {
            cout<<"           "<<"Key:  "<<obj.key<<endl;
            cout<<"           "<<"Data: "<<obj.data<<endl;
        }
    }
    inFile.close();
}
