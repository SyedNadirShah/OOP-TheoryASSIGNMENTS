#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Ghost {
protected:
    string actorName;         // Name of the actor playing the ghost
    int scarePower;           // Level of how scary the ghost is

public:
    Ghost(string name) : actorName(name), scarePower(rand() % 10 + 1) {}

    virtual void haunt() const = 0; // Pure virtual function for haunting behavior
    virtual ~Ghost() {}

    int getScarePower() const { return scarePower; }

    friend ostream& operator<<(ostream& os, const Ghost& g) {
        os << "Ghost played by " << g.actorName << " with scare level " << g.scarePower;
        return os;
    }

    Ghost& operator+(const Ghost& other) {
        this->scarePower += other.scarePower;
        this->actorName += " & " + other.actorName;
        return *this;
    }
};

class Poltergeist : public virtual Ghost {
public:
    Poltergeist(string name) : Ghost(name) {}

    void haunt() const override {
        cout << actorName << " (Poltergeist) hurls books and chairs!" << endl;
    }
};

class Banshee : public virtual Ghost {
public:
    Banshee(string name) : Ghost(name) {}

    void haunt() const override {
        cout << actorName << " (Banshee) lets out a piercing shriek!" << endl;
    }
};

class ShadowGhost : public virtual Ghost {
public:
    ShadowGhost(string name) : Ghost(name) {}

    void haunt() const override {
        cout << actorName << " (ShadowGhost) emerges from the darkness..." << endl;
    }
};

class ShadowPoltergeist : public Poltergeist, public ShadowGhost {
public:
    ShadowPoltergeist(string name) : Ghost(name), Poltergeist(name), ShadowGhost(name) {}

    void haunt() const override {
        Poltergeist::haunt();
        ShadowGhost::haunt();
    }
};

class Visitor {
public:
    string visitorName;
    int braveryLevel;

    Visitor(string name, int bravery) : visitorName(name), braveryLevel(bravery) {}

    void reactToScare(int scareLevel) {
        if (scareLevel < braveryLevel)
            cout << visitorName << " laughs fearlessly!" << endl;
        else if (scareLevel > braveryLevel)
            cout << visitorName << " shrieks and bolts out!" << endl;
        else
            cout << visitorName << " hesitates but holds ground!" << endl;
    }
};

class HauntedHouse {
public:
    string houseName;
    Ghost* ghostList[3];   // List of ghosts in the house
    int totalGhosts;

    HauntedHouse(string name) : houseName(name), totalGhosts(0) {}

    void addGhost(Ghost* g) {
        if (totalGhosts < 3) {
            ghostList[totalGhosts++] = g;
        }
    }

    void simulateVisit(Visitor visitorArr[], int count) {
        cout << endl << "Visiting " << houseName << "..." << endl;
        for (int i = 0; i < count; i++) {
            cout << visitorArr[i].visitorName << " enters the haunted house..." << endl;
            for (int j = 0; j < totalGhosts; j++) {
                ghostList[j]->haunt();
                visitorArr[i].reactToScare(ghostList[j]->getScarePower());
            }
            cout << "-----------------------------" << endl;
        }
    }

    ~HauntedHouse() {
        for (int i = 0; i < totalGhosts; i++) delete ghostList[i];
    }
};

int main() {
    srand(time(0));

    // Display Student ID and Name
    cout << "STUDENT ID: CS001\n";
    cout << "STUDENT NAME: Nadir Khan\n\n";

    HauntedHouse manorOfDoom("Manor of Doom");
    manorOfDoom.addGhost(new Poltergeist("Zeeshan"));
    manorOfDoom.addGhost(new Banshee("Raza"));

    HauntedHouse cryptKeep("Crypt Keep");
    cryptKeep.addGhost(new ShadowGhost("Yasir"));
    cryptKeep.addGhost(new ShadowPoltergeist("Faisal"));

    Visitor guestList[] = {
        Visitor("Bilal", 4),
        Visitor("Hamza", 7),
        Visitor("Sami", 9)
    };

    manorOfDoom.simulateVisit(guestList, 3);
    cryptKeep.simulateVisit(guestList, 3);

    return 0;
}
