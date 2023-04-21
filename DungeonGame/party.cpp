#include "party.h"
#include <iostream>
party::party(){
    size = 0;
    id = 0;
    numTreasure = 0;
    member = new character* [size];
}


party::~party(){

    for(int i = 0; i < size; i++){
        delete member[i];
    }
    delete [] member;
}

party::party(const party& o){
    size = o.size;
    character** member = new character* [size];
    for (int i = 0 ; i < size ; i ++){
        member[i] = o.member[i];
    }
}

void party::operator = (const party& o){
    size = o.size;
    delete [] member;
    character** member = new character* [size];
    for (int i = 0 ; i < size ; i ++){
        member[i] = o.member[i];
    }
}

void party::addMember(character* add){
    character** temp = new character*[++size];
    for (int i = 0 ; i < size-1 ; i ++){
        temp[i] = member[i];
    }
    
    delete [] member;
    member = temp;
    member[size-1] = add;
}

void party::removeMemberId(int id){
    int pos;
    for (int i = 0; i < size; i++){
        if (id == member[i]->getId()){
            pos = i;
            break;
        }
    }
    size--;
    character** temp = new character*[size];
    for (int i = pos; i < size; i++){
        member[i] = member[i+1];
    }
    for (int i = 0; i < size; i++){
        temp[i] = member[i];
    }
    delete [] member;
    member = temp;
}

void party::removeMember(int id){
    size--;
    character** temp = new character*[size];
    for (int i = id; i < size; i++){
        member[i] = member[i+1];
    }
    for (int i = 0; i < size; i++){
        temp[i] = member[i];
    }
    delete [] member;
    member = temp;
}

std::ostream & operator << (std::ostream& out, const party& p){
    for (int i = 0 ; i < p.size ; i ++){
        //p.member[i]->print();
        std::cout << i << ". " << std::endl; 
        std::cout << p.member[i]; 
        std::cout << std::endl; 

    }
    return out;
}

character*& party::getChar(int num){
    return member[num];
}

int party::getSize() const{
    return size;
}

int party::getNumTreasure() const{
    return numTreasure;
}

void party::addNumTreasure(int num){
    numTreasure += num;
}

int party::getId() const{
    return id;
}
    
void party::setId(int num){
    id = num;
}

character*& party::getCharId(int num){
    int pos;
    for (int i = 0; i < size; i++){
        if (num == member[i]->getId()){
            pos = i;
            break;
        }
    }
    return member[pos];
}