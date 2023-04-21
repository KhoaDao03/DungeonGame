#include "character.h"

class party{

    friend std::ostream & operator << (std::ostream& , const party&);

    private:

        character** member;
        int size;
        int numTreasure;
        int id;

    public:

        party();
        party(const party&);
        ~party();

        void operator = (const party&);

        void addMember(character* add);
        void removeMemberId(int id);
        void removeMember(int id);


        int getSize() const;
        int getNumTreasure() const;

        void addNumTreasure(int);
        character*& getChar(int);
        character*& getCharId(int);

        int getId() const;
        void setId(int);



};
