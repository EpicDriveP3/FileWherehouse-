/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Student.h
 * Author: betolan
 *
 * Created on 4 de junio de 2016, 08:10 AM
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

namespace std{

class HashTable{
    public:
	HashTable();
	virtual ~HashTable();
        HashTable(const HashTable& orig);
	void Write(int key, string data, int indice);
	void Display(int indice);
	void Search(int key, int indice);
	void Delete(int key, int indice);
	int key;
	char *data;
        int buckets;
};
/*
template<typename Dp>
struct RegisterData{
int _keyAdmno;
Dp Dato;
int _sizeOfData;
};*/
} /* namespace std */

#endif /* STUDENT_H_ */