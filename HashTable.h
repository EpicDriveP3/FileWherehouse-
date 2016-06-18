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
#include <sys/types.h>
#include <dirent.h>
#include <cstdlib>


class HashTable{
    public:
	HashTable();
	virtual ~HashTable();
        HashTable(const HashTable& orig);
	void Write(int key, std::string data, std::string name);
	void Display(std::string name);
	void Delete(int key, std::string name);
        void search(int key, std::string name);
        void WriteControl();
        void ReadControl();
        void AllFiles();
        void QuantityOfFiles(int proccess);
        std::string GeneratedNameFile();
        void Removee(std::string name);
	int key;
	char * data;
        int buckets;
        int * elements_for_bucket;
};

 /* namespace std */

#endif /* STUDENT_H_ */