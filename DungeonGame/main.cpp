#include "party.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <string.h>

using namespace std;

void printGrid(party& hero, party& other, const int xLen, const int yLen);
int** generateCords(const int maxX, const int maxY, const int size);
void clearIntArray(int**& clear, int& size);
void setupHeroes(party& modified);
void setHeroesPos(party& modified, int x, int y);
void setOthersPos(party& modified, int x, int y, int pos);
void setupOthers(party& modified, int numMonster, int numTreasure, int numTrap);
void setOthers(party& modified, int**& list);
int fighterFunction(party*& monster, int size, int pos);
int healerFunction(party& hero);
int askDirection(party*&, party*&);
void processDirection(party& hero, party& other, party*& monster,int choice, int xLen, int yLen, int mSize, bool& nL);
bool processExist(party& hero, party& other, party*& monster, int id, int mSize,int xLen, int yLen);
void generateTwoCoords(party& hero, party& other, int&x, int&y, const int maxX, const int maxY);
void pause();


int main(){
    srand ((unsigned) time(NULL));

    // set the initial level for the game
    int level = 1;

    // the dimensions for the game (which can be changed)
    const int x = 15;
    const int y = 10;

    party heroes;
    setupHeroes(heroes);

    // level 1
    int numMonster = rand()%5 + 6;      // randomize number of monster
    int numTreasure = rand()%5 + 6;     // randomize number of treasures
    int numTraps = rand()%5 + 6;        // randomize number of traps
    int size = numMonster + numTreasure + numTraps;
    int** randomCords = generateCords(x,y,size);    // generate random coordinates
    party others;
    setupOthers(others, numMonster, numTreasure, numTraps); // create entities
    setOthers(others, randomCords);     // set coordinates for entities
    clearIntArray(randomCords, size);   // delete the dma list after setting entities
    party* monsters = new party[numMonster];
    for( int i = 0; i < numMonster; i ++){
        monsters[i].setId(others.getChar(i)->getId());
        for (int z = 0; z < rand()%5 + 1; z++){
            monsters[i].addMember(new monster);
            monsters[i].getChar(z)->setXCoord(others.getChar(i)->getXCoord());
            monsters[i].getChar(z)->setYCoord(others.getChar(i)->getYCoord());
        }
    }



    // level 2
    int numMonster1 = rand()%5 + 6;     // randomize number of monster
    int numTreasure1 = rand()%5 + 6;    // randomize number of treasures
    int numTraps1 = rand()%5 + 6;       // randmize number of traps
    int size1 = numMonster1 + numTreasure1 + numTraps1;
    int** randomCords1 = generateCords(x,y,size1);      // generate random coordinates
    party others1;
    setupOthers(others1, numMonster1, numTreasure1, numTraps1);     // create entities
    setOthers(others1, randomCords1);       // set coordinates for entities
    clearIntArray(randomCords1, size1);     // delete the dma list after setting entities
    party* monsters1 = new party[numMonster1];
    for( int i = 0; i < numMonster1; i ++){
        monsters1[i].setId(others1.getChar(i)->getId());
        for (int z = 0; z < rand()%5 + 1; z++){
            monsters1[i].addMember(new monster);
            monsters1[i].getChar(z)->setXCoord(others1.getChar(i)->getXCoord());
            monsters1[i].getChar(z)->setYCoord(others1.getChar(i)->getYCoord());
        }
    }



    // Start the game
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Welcome to Dungeon the game" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


    cout << "Instructions:" << endl;
    cout << "You are controlling the party named \"P\"." << endl;
    cout << "Control the party and clear all of the instances to win the game" << endl;
    cout << "If your whole party dies, game loses" << endl;
    // ALthough losing in this game is almost impossible unless you change the power of the monsters.
    cout << "There will be 4 fighters and 1 healer" << endl;
    cout << "Fighers can only fight monsters and healers can only heal allies" << endl;
    cout << endl;
    while (true){
        bool nextLevel = false;

        // processing dungeon level 1
        if (level == 1){
            cout << "Level 1" << endl;
            printGrid(heroes, others ,x,y);
            processDirection(heroes, others, monsters, askDirection(monsters,monsters1), x, y, numMonster, nextLevel);
            cout << endl;
            if (nextLevel){
                setHeroesPos(heroes, 0, 0);
                level = 2;
            }
        }

        // processing dungeon level 1
        if (level == 2){
            cout << "Level 2" << endl;
            printGrid(heroes, others1 ,x,y);
            processDirection(heroes, others1, monsters1 , askDirection(monsters,monsters1), x, y, numMonster1, nextLevel);
            cout << endl;
            if (nextLevel){
                setHeroesPos(heroes, 0, 0);
                level = 1;
            }
        }

        // check for losing condition
        if (heroes.getSize() == 0){
            cout << endl << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;  
            cout << "All of the members in the Party Died" << endl;
            cout << "             Game Over              " << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;  

            break;
            
        }

        // check for winning condition
        if (others.getSize() == 0 && others1.getSize() == 0){
            if (level == 1){
                printGrid(heroes, others ,x,y);
            }
            if (level == 2){
                printGrid(heroes, others1 ,x,y);
            }
            cout << endl << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;  
            cout << "All of objectives have been cleared in the dungeon." << endl;
            cout << "                   Congratulations                 " << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;  

            break;
        }

        
    }
    delete [] monsters;
    delete [] monsters1;
    abort;
    
    

    
}



/*==========================================================================*/
void printGrid(party& hero, party& other, const int xLen,const int yLen)
{

    const int spacing = 5;
    string grid[yLen][xLen];        // initialize the 2d array for the dungeon

    cout << "Dungeon: " << endl;   // prints out the title
    cout << "Number of Treasures: " << hero.getNumTreasure() << endl;

    const int sizeY = sizeof(grid) / sizeof(grid[0]) ;  // calculate the size of grid Y
    const int sizeX = sizeof(grid[0]) / sizeof(grid[0][0]);  // calculate the size of grid X

    
    // set up the grid by filling empty space with blanks
    for (int y = 0; y < sizeY; y++){
        for (int x = 0; x < sizeX; x++){
            grid [y][x] = "";   // fill blanks
        }
    }

    // fill in the grids with entities 
    grid[hero.getChar(0)->getYCoord()][hero.getChar(0)->getXCoord()] = "P"; 
    grid[yLen-1][xLen-1] = "S"; 
    for (int i = 0; i < other.getSize(); i++){
        string n(other.getChar(i)->getName());
        grid[other.getChar(i)->getYCoord()][other.getChar(i)->getXCoord()] = n;
    }
    
    // prints out the x coordinates
    cout << setw(2) << 0 << setw(spacing+1);
    for (int i = 1; i < sizeX+1; i++){
        cout << i << setw(spacing);
    }

    
    // prints out the grid
    cout << endl;       // skip line to easier to read 
    cout << setw(4);
    for (int i = 0; i < (sizeX+1)*spacing; i++){
        //cout << setw(7) << i << setw(7);    // prints out the x coordinates
        cout <<  "_" ;
    }
    cout << endl;
    cout << endl;
    for (int y = 0; y < sizeY; y++){
        cout << setw(2)<< y+1 ;    // print out the label for y coordinates
        
        if ( y > 0){
            cout << "|"; // printing out the borders 
        }else {
            cout << "=" ;
        }
        for (int x = 0; x < sizeX; x++){
            if (grid [y][x] == ""){
                grid [y][x] = ".";     // fill the empty space with dots
            }
            cout <<setw(spacing) << grid[y][x] << setw(spacing);    // prints the content out
        }

        cout << "|" << endl << endl; // prints the border

    }
    cout << setw(4);
    // print out the label for x coordinates
    for (int i = 0; i < (sizeX+1)*spacing; i++){
        cout <<  "_" ;
    }
}
// This function will print out the grid along with the blobs on the grid appropriately


int** generateCords(const int maxX, const int maxY, int size) {

    // generate a DMA list that can store n amount of coordinates
    int** coordinates = new int*[size];
    for (int i = 0; i < size; i++){
        coordinates[i] = new int[2];
    }

    // get the size of the dma arrays
    const int sizeY = sizeof(coordinates) / sizeof(coordinates[0]);
    const int sizeX = sizeof(coordinates[0]) / sizeof(coordinates[0][0]);
    for (int y = 0; y < sizeY; y++){
        for (int x = 0; x < sizeX; x++){
            coordinates[y][x]=-1;
        }
    }

    //generate initial entities positions
    bool sameCoord;     // variable to check for same coordinates
    int temp[2];        // variable for temporary store the coordinates

    for (int a = 0; a < size; a++){     
        sameCoord = true;       // set sameCoordinates
        while (sameCoord){
            temp[0] = rand()%maxX;       // generate random value for X coordinate
            temp[1] = rand()%maxY;       // generate random value for Y coordinate
            for (int i = 0; i < size; i++){  // loop inside the list for same coordinates
                // avoid initial position, "S" position and other entities position
                if ((coordinates[i][0] == temp[0] && coordinates[i][1] == temp[1])
                || (temp[0] == 0 && temp[1] == 0)
                || (temp[0] == sizeX-1 && temp[1] == sizeY-1)){
                    break;      // if found break out of the loop
                }
                if (i==size-1) {     // if not, add into the coordinate lists
                    coordinates[a][0] = temp[0];  // add value
                    coordinates[a][1] = temp[1];  // add value
                    sameCoord = false;      // set sameCoord to false to break out of the loop
                }
            }
        }
        
    }

    return coordinates;
}

// dealocate int dma arrays
void clearIntArray(int**& clear, int& size){
    for(int i = 0; i < size; i++){
        delete clear[i];
    }
    delete [] clear;
}  

// create the Heroes party
void setupHeroes(party& modified){
    modified.addMember(new fighter);
    modified.addMember(new fighter);
    modified.addMember(new fighter);
    modified.addMember(new fighter);
    modified.addMember(new healer);
}

// set the heroes positions
void setHeroesPos(party& modified, int x, int y){
    int size = modified.getSize();
    for (int i = 0; i < size; i++){
        modified.getChar(i)->setXCoord(x);
        modified.getChar(i)->setYCoord(y);
    }
}

// set other entities position
void setOthersPos(party& modified, int x, int y, int pos){
    modified.getChar(pos)->setXCoord(x);
    modified.getChar(pos)->setYCoord(y);
}

// set other entities (monster, treasure, traps)
void setupOthers(party& modified, int numMonster, int numTreasure, int numTrap){
    for (int i = 0; i < numMonster; i ++){
        modified.addMember(new monster);
    }
    for (int i = 0; i < numTreasure; i ++){
        modified.addMember(new treasure);
    }
    for (int i = 0; i < numTrap; i ++){
        modified.addMember(new trap);
    }
}

// set the position of other entities
void setOthers(party& modified, int**& list){

    int size = modified.getSize();

    for (int i = 0; i < size; i++){
        modified.getChar(i)->setXCoord(list[i][0]);
        modified.getChar(i)->setYCoord(list[i][1]);
    }
}

// show and ask functions for fighters
int fighterFunction(party*& monster, int size, int pos){
    int num;
    while (true){
        cout << "Available Functions:" << endl;
        cout << "-1. Run" << endl;
        cout << "Select monster to Attack" << endl << endl;
        cout << monster[pos] << endl;
        cout << "Choose monster to attack using the number in front of the name or -1 to run."
        << endl;
        
        cin >> num;
        if (num > -2 && num < monster[pos].getSize()){
                cin.clear();
                cin.ignore(1000,'\n');
                return num;
        }
        else
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Input is invalid." << endl;
            cout << "Please try again" << endl <<endl;
            
        }
    }
}

// show and ask functions for healers
int healerFunction(party& hero){
    int num;
    while (true){
        cout << "Available Functions:" << endl;
        cout << "-1. Run" << endl;
        cout << "Select hero to Heal" << endl;
        cout << hero << endl;
        cout << "Choose hero to heal using the number in front of the name or -1 to run."
        << endl;
        
        cin >> num;
        if (num > -2 && num < hero.getSize()){
                cin.clear();
                cin.ignore(1000,'\n');
                return num;
        }
        else
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Input is invalid." << endl;
            cout << "Please try again" << endl <<endl;
            
        }
    }
}



// ask directions for movements around the game
int askDirection(party*& monster, party*& monster1){
    int num;
    while (true) {

        // prompt the user about available commands
        cout << endl << endl;
        cout << "Available commands are:" << endl;
        cout << "1. Up" << endl;
        cout << "2. Right" << endl;
        cout << "3. Down" << endl;
        cout << "4. Left" << endl;
        cout << "5. View Stats" << endl;
        cout << "Choose 1,2,3,4,5 or -1 to quit the program" << endl;
        cin >> num;
        if (num > 0 && num < 6){
            return num;
        } else if (num == -1) {
            delete [] monster;
            delete [] monster1;
            abort();
        }
        else
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Input is invalid." << endl;
            cout << "Please try again" << endl <<endl;
        }
    }
}

// process the movements input
void processDirection(party& hero, party& other, party*& monster,int choice, const int xLen, const int yLen, int mSize, bool& nL)
{

    nL = false;
    // if player want to view stats
    if (choice == 5){
        cout << hero << endl;
        pause();
        return;
    }
    // store hero position in an array
    int heroPos[2] = {hero.getChar(0) -> getXCoord(), hero.getChar(0) -> getYCoord()};
    int sizeOther = other.getSize();

    // store position of other entities in arrays
    int* xPos = new int[sizeOther];
    int* yPos = new int[sizeOther];     
    for (int i = 0; i < sizeOther; i++){
        xPos[i] = other.getChar(i) -> getXCoord();
        yPos[i] = other.getChar(i) -> getYCoord();

    }

    // process the movement
    int x = 0, y = 0; 
    if (choice == 1){           // up
        y--;
    } else if (choice == 2){    // right
        x++;
    } else if (choice == 3){    // down
        y++;
    } else if (choice == 4){    // left
        x--;
    }

    
    bool exists = false;    // initialize exists and set to false 
    int tempId = -1;          // set temprorary value to -1

    // check for out of bounds
    if (heroPos[1] + y < 0 || heroPos[1] + y > yLen-1 ||
        heroPos[0] + x < 0 || heroPos[0] + x > xLen-1 ){
        // prompt the user
        cout << "Out of bound. Please try again." << endl;  
        delete [] xPos;
        delete [] yPos;
        return;
    } else {

        // check for other entities present
        for (int z = 0; z < sizeOther; z++){
            if (heroPos[1] + y == yPos[z]
            && heroPos[0] + x == xPos[z] ){
                tempId = other.getChar(z)->getId();     // store the entity
                exists = true;  // set exists to true
                break;  // break out of the loop
            }
        }
    } 

    // delete the array to prevent memory leak
    delete [] xPos;
    delete [] yPos;
    // check whether the party land on "S" position
    if (heroPos[1] + y == yLen-1 && heroPos[0] + x == xLen-1 ){
        setHeroesPos(hero, heroPos[0]+x, heroPos[1]+y);
        nL = true;
        return;
    }

    // if there is another entity
    if (exists){
        // process and will let the statement know whether to move or not
        if (processExist(hero, other, monster,tempId, mSize, xLen, yLen)){
            setHeroesPos(hero, heroPos[0]+x, heroPos[1]+y);
        }
    } else {
        // move if none
        setHeroesPos(hero, heroPos[0]+x, heroPos[1]+y);
    }

}
//This function will process the user input for a correct command

// process if there is another entity (monster,treasure, trap)
bool processExist(party& hero, party& other, party*& monster, int id, int mSize, int xLen, int yLen){
    bool eliminate = true;
    character*& o = other.getCharId(id);
    const char* type = o->getType();

    // if monster
    if (strcmp(type,"monster") == 0){
        bool exists = true;
        while (exists){
            // check for hero status
            if (hero.getSize() == 0){
                exists = false;
                break;
            }

            // check for mosnter status if dead deallocate
            int pos = -1;
            exists = false;
            for (int i = 0; i < mSize; i ++){
                if (monster[i].getId() == id){
                    pos = i;
                    exists = true;
                    break;
                }
            }
            // if can find the monster in the list
            if (pos != -1){
                int choice = -1;
                cout << endl << endl;
                // let the heroes take first turn
                for (int i = 0; i < hero.getSize(); i++){
                    
                    cout << hero.getChar(i) << endl << endl;
                    const char* hType = hero.getChar(i)->getType();

                    // ask the user depends on the fighter or healer
                    if (strcmp(hType,"fighter") == 0){
                        choice = fighterFunction(monster, mSize, pos);  
                    } else if (strcmp(hType,"healer") == 0){
                        choice = healerFunction(hero);  
                    }

                    // if trying to run away
                    if (choice == -1){
                        if (rand()%100 <= (60-10*monster[pos].getSize())){
                            // if success
                            int x = 0; 
                            int y = 0;
                            // generate new distinctive coordinates                            
                            generateTwoCoords(hero,other, x,y , xLen, yLen);

                            // set the new coordinates
                            other.getCharId(id)->setXCoord(x);
                            other.getCharId(id)->setYCoord(y);
                            for(int z = 0; z < monster[pos].getSize(); z++){
                                monster[pos].getChar(z)->setXCoord(x);
                                monster[pos].getChar(z)->setYCoord(y);
                            }
                            // prompt
                            cout << "Run away successfully" << endl << endl;

                            // exit the look and while loop
                            exists = false;
                            break;
                        } else {
                            // prompt run away fail and move to the next character
                            cout << "Run away failed" << endl << endl;
                            choice = -2;
                        }
                            
                        } else {
                            // if decide not to run
                            if (strcmp(hType,"fighter") == 0){
                                // as a fighter attack other monsters
                                if (int((rand()%100))>=85){
                                    // if missed
                                    cout << hero.getChar(i)->getName() << " attacked missed on " 
                                    << monster[pos].getChar(choice)->getName() << endl; 
                                } else {
                                    // if success
                                    monster[pos].getChar(choice)->adjustHealth(-hero.getChar(i)->getPower());
                                    cout << hero.getChar(i)->getName() << " successfully attacked " 
                                    << monster[pos].getChar(choice)->getName() << endl; 
                                }
                            } else if (strcmp(hType,"healer") == 0){
                                // as a healer, just heal allies
                                hero.getChar(choice)->adjustHealth(hero.getChar(i)->getPower());
                            }
                    }
                    // pause to let the player read the prompt
                    pause();

                    // check for dead monsters and deallocate
                    eliminate = true;
                    while (eliminate){
                        for (int i = 0; i < monster[pos].getSize(); i++){
                            if (monster[pos].getChar(i)->getHealth() <= 0){
                                eliminate = true;
                                monster[pos].removeMember(i);
                                cout << "A monster in the party died" << endl;
                                break;
                            } else {
                                eliminate = false;
                            }
                        }
                        if (monster[pos].getSize()==0){
                            eliminate = false;
                        }
                    }

                    // check if the whole party of monster is killed
                    if (monster[pos].getSize() == 0){
                        cout << "The Monster party has been killed." << endl;
                        hero.addNumTreasure(o->getReward());
                        other.removeMemberId(id);
                        exists = false;
                        return true;
                    }
                    
                }
                // monster's turn
                if (choice != -1){
                    for (int i = 0; i <  monster[pos].getSize(); i++){
                        int h = rand()%hero.getSize();  
                        // target a random hero in the party, can be duplicate (just imagine to monster decide to attack the same person) 
                        if (int((rand()%100))>=50){ 
                            // if hit
                            hero.getChar(h)->adjustHealth(-monster[pos].getChar(i)->getPower());
                            cout << monster[pos].getChar(i)->getName() << " successfully attacked " 
                            << hero.getChar(h)->getName() << " attacked dealt " << monster[pos].getChar(i)->getPower() 
                            << " damage."  << endl; 
                        } else {
                            // if missed
                            cout << monster[pos].getChar(i)->getName() << " attacked missed on " 
                            << hero.getChar(h)->getName() << endl; 
                        }
                    }

                    // check for hero status and deallocate if died
                    eliminate = true;
                    while (eliminate){
                        for (int i = 0; i < hero.getSize(); i++){
                            if (hero.getChar(i)->getHealth() < 0){
                                cout << hero.getChar(i)->getName() << " died." << endl;
                                eliminate = true;
                                hero.removeMember(i);
                                break;
                            } else {
                                eliminate = false;
                            }
                        }
                        if (hero.getSize()==0){
                            eliminate = false;
                        }
                    }
                    // pause for the player to read the prompt
                    pause();
                }
            }
        }
        return false; // return false to prevent the party advance to the square and the monster party moved away

    } else if (strcmp(type,"treasure") == 0){
        // if the entity is a treasure
        cout << "The party encounter a treasure" << endl;
        cout << "Numbers of Treasure added = " << o->getReward() << endl;

        // award the party and deallocate the entity
        hero.addNumTreasure(o->getReward());
        other.removeMemberId(id);
    } else if (strcmp(type,"trap") == 0){
        // if the entity is a trap
        cout << "The party encounter a trap" << endl;
        if (o->getReward() >= 50){
        // if contains treasure
        cout << "It has treasures." << endl;
        cout << "Numbers of Treasure added = " << o->getPower() << endl;
        // award the party 
        hero.addNumTreasure(o->getPower());
        } else {
        // if actually a trap
            cout << "It has traps." << endl;
            cout << "Numbers of damage whole party received = " << o->getPower() << endl;
            // damage the party
            for (int i = 0; i < hero.getSize(); i++){
                hero.getChar(i)->adjustHealth(-o->getPower());

            }
        }
        // deallocate the entity
        other.removeMemberId(id);
    }
    // check for hero status
    eliminate = true;
    while (eliminate){
        for (int i = 0; i < hero.getSize(); i++){
            if (hero.getChar(i)->getHealth() < 0){
                cout << hero.getChar(i)->getName() << " died." << endl;
                eliminate = true;
                hero.removeMember(i);
                break;
            } else {
                eliminate = false;
            }
        }
        if (hero.getSize()==0){
            eliminate = false;
        }
    }

    return true;

}

// generate a random pair of coordinates
void generateTwoCoords(party& hero, party& other, int& x, int& y, const int maxX, const int maxY){
    // set an array of coordinates for the new monster location
    int size = 1+other.getSize();
    int** coordinates = new int*[size];
    for (int i = 0; i < size; i++){
        coordinates[i] = new int[2];
    }
    const int sizeY = sizeof(coordinates) / sizeof(coordinates[0]);
    const int sizeX = sizeof(coordinates[0]) / sizeof(coordinates[0][0]);
    
    // get all of the entities coordinates including party hero to the array
    coordinates[0][0] = hero.getChar(0)->getXCoord();
    coordinates[0][1] = hero.getChar(0)->getYCoord();
    for (int i = 1; i < size; i++){
        coordinates[i][0] = other.getChar(i-1)->getXCoord();
        coordinates[i][1] = other.getChar(i-1)->getYCoord();
    }

    bool sameCoord;     // variable to check for same coordinates
    int temp[2];        // variable for temporary store the coordinates
   
    sameCoord = true;       // set sameCoordinates
    while (sameCoord){
        temp[0] = rand()%maxX;       // generate random value for X coordinate
        temp[1] = rand()%maxY;       // generate random value for Y coordinate
        for (int i = 0; i < size; i++){  // loop inside the list for same coordinates
            if ((coordinates[i][0] == temp[0] && coordinates[i][1] == temp[1])
            || (temp[0] == 0 && temp[1] == 0)
            || (temp[0] == sizeX-1 && temp[1] == sizeY -1)){
                break;      // if found break out of the loop
            }
            if (i==size-1) {     // if not, add into the coordinate lists
                x = temp[0];  // add value
                y = temp[1];  // add value
                sameCoord = false;      // set sameCoord to false to break out of the loop
            }
        }
    }
    clearIntArray(coordinates,size);
    // deallocate the dma array

    
}


// pause function
void pause(){
    cout << endl;
    cout << "Process complete. Press enter to continue...";
    cin.get();
    cin.clear();
    cin.ignore(256,'\n');
}