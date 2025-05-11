#include <iostream>
#include <string>

using namespace std;


class Skill {
public:
    int skillID;
    string skillName, description;
    
    void updateDescription(string newDesc) {
        description = newDesc;
    }
};


class Sport {
public:
    int sportID;
    string name, description;
    string requiredSkills[3];
    
    void addSkill(string skill) {
        for (int i = 0; i < 3; i++) {
            if (requiredSkills[i].empty()) {
                requiredSkills[i] = skill;
                break;
            }
        }
    }
};


class Student;

class Mentor {
public:
    int mentorID, maxLearners, assignedCount;
    string name;
    string sportsExpertise[3];
    Student* assignedLearners[3];
    
    Mentor(int id, string n, int max) : mentorID(id), name(n), maxLearners(max), assignedCount(0) {}
    
    bool assignLearner(Student* s);
    void removeLearner(Student* s);
    void viewLearners();
};


class Student {
public:
    int studentID;
    string name;
    string sportsInterests[3];
    Mentor* mentorAssigned;
    
    Student(int id, string n) : studentID(id), name(n), mentorAssigned(NULL) {}
    
    void registerForMentorship(Mentor* m) {
        if (m->assignLearner(this)) {
            mentorAssigned = m;
        }
    }
    
    void viewMentorDetails() {
        if (mentorAssigned) {
            cout << "Mentor: " << mentorAssigned->name << endl;
        } else {
            cout << "No mentor assigned." << endl;
        }
    }
    
    void updateSportsInterest(string sport) {
        for (int i = 0; i < 3; i++) {
            if (sportsInterests[i].empty()) {
                sportsInterests[i] = sport;
                break;
            }
        }
    }
};


bool Mentor::assignLearner(Student* s) {
    if (assignedCount < maxLearners) {
        assignedLearners[assignedCount] = s;
        assignedCount++;
        return true;
    }
    return false;
}


void Mentor::removeLearner(Student* s) {
    for (int i = 0; i < assignedCount; i++) {
        if (assignedLearners[i] == s) {
            for (int j = i; j < assignedCount - 1; j++) {
                assignedLearners[j] = assignedLearners[j + 1];
            }
            assignedLearners[assignedCount - 1] = NULL;
            assignedCount--;
            break;
        }
    }
}


void Mentor::viewLearners() {
    cout << "Learners under " << name << ":\n";
    for (int i = 0; i < assignedCount; i++) {
        cout << assignedLearners[i]->name << endl;
    }
}


int main() {
	
    cout << "Your Name: John Doe" << endl;
    cout << "Your Student ID: 123456" << endl;
    
    Mentor ali(1, "Ali", 3);
    Student saad(101, "Saad");
    saad.updateSportsInterest("Tennis");
    saad.registerForMentorship(&ali);
    ali.viewLearners();
    
    return 0;
}

