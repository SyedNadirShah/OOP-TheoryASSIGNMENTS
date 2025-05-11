#include <iostream>
#include <string>

using namespace std;


class Student {
private:
	
    int id;
    string name;
    bool feePaid;
    
public:
	
    Student(int i, string n) : id(i), name(n), feePaid(false) {}
    void payFee() { feePaid = true; }
    bool isFeePaid() { return feePaid; }
    string getName() { return name; }
    int getId() { return id; }
};


class Route {
private:
	
    int routeId;
    string stops[5];
    
public:
	
    Route(int id, string s[5]) : routeId(id) {
        for (int i = 0; i < 5; i++) {
            stops[i] = s[i];
        }
    }
    
    void displayStops() {
        cout << "Route " << routeId << " Stops: ";
        for (int i = 0; i < 5; i++) {
            cout << stops[i] << " ";
        }
        cout << endl;
    }
};


class TransportationSystem {
	
private:
	
    Student* students[10];
    Route* routes[2];
    int studentCount;
    
public:
	
    TransportationSystem() : studentCount(0) {
        string stops1[5] = {"Stop A", "Stop B", "Stop C", "Stop D", "Stop E"};
        string stops2[5] = {"Stop F", "Stop G", "Stop H", "Stop I", "Stop J"};
        routes[0] = new Route(1, stops1);
        routes[1] = new Route(2, stops2);
    }
    
    void registerStudent(int id, string name) {
        if (studentCount < 10) {
            students[studentCount++] = new Student(id, name);
            cout << "Student registered: " << name << endl;
        } else {
            cout << "Registration full!" << endl;
        }
    }
    
    void payFee(int id) {
        for (int i = 0; i < studentCount; i++) {
            if (students[i]->getId() == id) {
                students[i]->payFee();
                cout << "Fee paid for " << students[i]->getName() << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }
    
    void showRoutes() {
        for (int i = 0; i < 2; i++) {
            routes[i]->displayStops();
        }
    }
    
    ~TransportationSystem() {
        for (int i = 0; i < studentCount; i++) delete students[i];
        for (int i = 0; i < 2; i++) delete routes[i];
    }
};


int main() {
	
	cout << "Name: Syed Nadir Shah" << endl;
    cout << "Student ID: K240011" << endl;
	
    TransportationSystem system;
    
    system.registerStudent(101, "Alice");
    system.registerStudent(102, "Bob");
    system.payFee(101);
    system.showRoutes();
    
    return 0;
    
}

