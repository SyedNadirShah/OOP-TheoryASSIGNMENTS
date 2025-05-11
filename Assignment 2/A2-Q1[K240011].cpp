#include <iostream>
using namespace std;

const int MaxStops = 10;

class User {
protected:
    string userID, fullName, email, phoneNumber;
    bool isCardActive;

public:
    User(string id, string name, string mail, string phone)
        : userID(id), fullName(name), email(mail), phoneNumber(phone), isCardActive(false) {}

    virtual void payTransportFees() = 0; // Pure virtual function

    void registerForTransport() {
        isCardActive = true;
        cout << fullName << " registered for transportation." << endl;
    }

    void tapCard() {
        if (isCardActive) {
            cout << fullName << " - Attendance recorded." << endl;
        } else {
            cout << fullName << " - Access denied! Payment required." << endl;
        }
    }
};

class Student : public User {
    string pickupLocation, dropoffLocation;

public:
    Student(string id, string name, string mail, string phone, string pickup, string dropoff)
        : User(id, name, mail, phone), pickupLocation(pickup), dropoffLocation(dropoff) {}

    void payTransportFees() override {
        isCardActive = true;
        cout << fullName << " - Transport fees paid for this semester." << endl;
    }

    void displayStudentInfo() {
        cout << "STUDENT ID: " << userID << endl;
        cout << "STUDENT NAME: " << fullName << endl;
    }
};

class Teacher : public User {
public:
    Teacher(string id, string name, string mail, string phone)
        : User(id, name, mail, phone) {}

    void payTransportFees() override {
        isCardActive = true;
        cout << fullName << " - Transport fees paid for this month." << endl;
    }
};

class Bus {
    int busID, routeNumber, capacity, currentPassengers;
    string stops[MaxStops];
    int stopCount;

public:
    Bus(int id, int route, int cap)
        : busID(id), routeNumber(route), capacity(cap), currentPassengers(0), stopCount(0) {}

    void assignStopToBus(string stop) {
        if (stopCount < MaxStops) {
            stops[stopCount++] = stop;
            cout << "Stop " << stop << " added to Bus " << busID << endl;
        } else {
            cout << "Cannot add more stops. Maximum limit reached." << endl;
        }
    }

    void recordAttendance() {
        cout << "Recording attendance for Bus " << busID << endl;
    }
};

class Route {
    int routeNumber;
    string stops[MaxStops];
    int stopCount;

public:
    Route(int number) : routeNumber(number), stopCount(0) {}

    void addStop(string stop) {
        if (stopCount < MaxStops) {
            stops[stopCount++] = stop;
            cout << "Stop " << stop << " added to Route " << routeNumber << endl;
        } else {
            cout << "Cannot add more stops. Maximum limit reached." << endl;
        }
    }

    bool operator==(const Route &other) const {
        if (routeNumber != other.routeNumber || stopCount != other.stopCount) {
            return false;
        }
        for (int i = 0; i < stopCount; i++) {
            if (stops[i] != other.stops[i])
                return false;
        }
        return true;
    }
};

class Admin {
    string adminID, adminName;

public:
    Admin(string id, string name) : adminID(id), adminName(name) {}

    void manageRoutes(Route &route, string stop) {
        route.addStop(stop);
    }
};

int main() {
    // Creating a student object
    Student student1("24K-0011", "Syed Nadir Shah", "nadir.ece@gmail.com", "0112232", "Gulshan", "Johar");

    // Display Student Info
    student1.displayStudentInfo();
    cout << endl;

    // Register and Pay Fees
    student1.registerForTransport();
    student1.payTransportFees();
    student1.tapCard();

    cout << endl;

    // Creating a teacher object
    Teacher teacher1("T456", "Prof. Harris", "harris.prof@gmail.com", "092682");

    // Register and Pay Fees
    teacher1.registerForTransport();
    teacher1.payTransportFees();
    teacher1.tapCard();

    cout << endl;

    // Creating a bus object and assigning stops
    Bus bus1(1, 101, 50);
    bus1.assignStopToBus("Gulshan");
    bus1.recordAttendance();

    cout << endl;

    // Creating and comparing routes
    Route route1(101), route2(102);
    route1.addStop("Gulshan");
    route1.addStop("Johar");

    route2.addStop("Gulshan");
    route2.addStop("Johar");

    if (route1 == route2) {
        cout << "Both routes are identical." << endl;
    } else {
        cout << "Routes are different." << endl;
    }

    cout << endl;

    // Admin managing routes
    Admin admin1("A001", "Shafeeq");
    admin1.manageRoutes(route1, "Nazimabad");

    return 0;
}
