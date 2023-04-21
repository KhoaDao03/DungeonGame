#include <iostream>

class character
{
    public:
        friend std::ostream& operator<<(std::ostream&, const character*);
        character();
        ~character();

        
        virtual void print() const;
        
    
        int getXCoord();    
        int getYCoord();
        int getPower() const;
        int getHealth() const;
        int getReward() const;
        int getId() const;
        char* getName() const;
        const char* getType() const;

        void setXCoord(int);
        void setYCoord(int);

        void adjustHealth(int);

        
        
    protected:
   
    int health;
    int power;
    int xCoord;
    int yCoord;
    int id;
    int reward;
    const char* type;
    char* name;
    int getXCoord() const;
    int getYCoord() const;

};

class fighter : public character{
    
    public:
    fighter();
    
};

class healer : public character{

    public:
    healer();
};

class monster : public character{

    public:
    monster();
    void print() const;

};

class treasure : public character{

    public:
    treasure();
    void print() const;

};

class trap : public character{

    public:
    trap();
    void print() const;

};

/***
g++ -c character.cpp
g++ -c party.cpp
g++ -c run7.cpp
g++ character.o party.o run7.o
a.out
**/