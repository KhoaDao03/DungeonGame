//#include <cstring>
#include "character.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>


using namespace std;

character :: character (){
    xCoord = 0;
    yCoord = 0;
    static int code = 0;
    reward = 0;
    id = ++code;
    name = new char[1];
    name[0] = '\0';    
    
}

character :: ~character(){
    delete [] name;
}

int character::getXCoord() {
    return xCoord;
}
int character::getYCoord() {
    return yCoord;
} 
int character::getHealth() const{
    return health;
} 
int character::getPower() const{
    return power;
} 
int character::getReward() const{
    return reward;
} 
int character::getId() const{
    return id;
} 

char* character::getName() const{
    return name;
}

const char* character::getType() const{
    return type;
}


void character::setXCoord(int xValue){
    xCoord = xValue;
}
void character::setYCoord(int yValue){
    yCoord = yValue;
}
void character::adjustHealth(int amount){
    health += amount;
}




void character :: print() const{

    cout << "Name: "<< name << endl;
    cout << "Position: ("<< xCoord + 1 << "," << yCoord + 1 << ")"  << endl;
    cout << "Health: "<< health << endl;
    cout << "Power: "<< power << endl;
}



fighter :: fighter(){
    
    type = "fighter";
    health = 80 + (rand() % 21);
    power = 4 + (rand() % 8);
    
    stringstream ss;
    ss << id;
    string temp = "Fighter" + ss.str();
    delete [] name;
    name = new char[strlen(temp.c_str())+1];
    strncpy(name, temp.c_str(), strlen(temp.c_str())+1);


}

healer :: healer (){
    type = "healer";
    health = 80 + (rand() % 21);
    power = 4 + (rand() % 8);

    stringstream ss;
    ss << id;
    string temp = "Healer" + ss.str();
    delete [] name;
    name = new char[strlen(temp.c_str())+1];
    strncpy(name, temp.c_str(), strlen(temp.c_str())+1);

    
}

monster :: monster (){
    type = "monster";
    reward = 1 + (rand()%10);
    health = 15 + (rand() % 21);
    power = 4 + (rand() % 8);
    delete [] name;
    name = new char[2];
    name[0] = 'M';
    name[1] = '\0'; 

}


treasure :: treasure (){
    type = "treasure";
    reward = 1 + (rand()%10);
    health = 0;
    power = 0;

    delete [] name;
    name = new char[2];
    name[0] = 'T'; 
    name[1] = '\0'; 

}

void monster :: print() const{
    cout << "Name: "<< name << endl;
    cout << "Type: " << type << endl;
    cout << "Position: ("<< xCoord + 1 << "," << yCoord + 1 << ")"  << endl;
    cout << "Health: "<< health << endl;
    cout << "Power: "<< power << endl;
}

void treasure :: print() const{

    cout << "Name: "<< name << endl;
    cout << "ID: " << id << endl;
    cout << "Position: ("<< xCoord + 1 << "," << yCoord + 1 << ")"  << endl;
    cout << "Type: " << type << endl;
    cout << "Reward: " << reward;
}

 
ostream & operator << (ostream& out, const character* p){
    p->print();
}

trap :: trap (){
    type = "trap";
    power = 1 + (rand()%10);

    health = 0;
    reward = (rand()%100);

    delete [] name;
    name = new char[2];
    name[0] = 'R'; 
    name[1] = '\0'; 

}

void trap :: print() const{

    cout << "Name: "<< name << endl;
    cout << "ID: " << id << endl;
    cout << "Position: ("<< xCoord + 1 << "," << yCoord + 1 << ")"  << endl;
    cout << "Power: "<< power << endl;
    cout << "Type: " << type << endl;
}


