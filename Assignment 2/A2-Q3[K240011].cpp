#include <iostream>
#include <string>
using namespace std;

// Base class for all delivery vehicles
class Vehicle {
protected:
    string vehicleCode;
    static int activeDeliveries;

public:
    Vehicle(string code) : vehicleCode(code) { activeDeliveries++; }
    virtual ~Vehicle() { activeDeliveries--; }

    virtual void calculateRoute() = 0;
    virtual void estimateDeliveryTime() = 0;
    virtual void move() { cout << "Vehicle in motion" << endl; }

    static int getActiveDeliveries() { return activeDeliveries; }
    string getVehicleCode() { return vehicleCode; }

    friend bool operator==(const Vehicle& v1, const Vehicle& v2);
};

int Vehicle::activeDeliveries = 0;

bool operator==(const Vehicle& v1, const Vehicle& v2) {
    return v1.vehicleCode == v2.vehicleCode;
}

// Derived class for aerial delivery
class EidDrone : public Vehicle {
public:
    EidDrone(string code) : Vehicle(code) {}

    void calculateRoute() override {
        cout << "EidDrone : calculating drone flight path..." << endl;
    }

    void estimateDeliveryTime() override {
        cout << "EidDrone : estimated delivery time is 12 minutes" << endl;
    }

    void move() override {
        cout << "EidDrone is soaring through the skies" << endl;
    }
};

// Derived class for time-based delivery
class EidTimeShifter : public Vehicle {
public:
    EidTimeShifter(string code) : Vehicle(code) {}

    void calculateRoute() override {
        cout << "EidTimeShifter : scanning timelines for optimal path..." << endl;
    }

    void estimateDeliveryTime() override {
        cout << "EidTimeShifter : instantaneous delivery via time jump" << endl;
    }

    void move() override {
        cout << "EidTimeShifter is shifting through temporal space" << endl;
    }
};

// Derived class for high-speed tunnel delivery
class EidHyperTunnel : public Vehicle {
public:
    EidHyperTunnel(string code) : Vehicle(code) {}

    void calculateRoute() override {
        cout << "EidHyperTunnel : calculating underground hyperloop route..." << endl;
    }

    void estimateDeliveryTime() override {
        cout << "EidHyperTunnel : estimated delivery time is 18 minutes" << endl;
    }

    void move() override {
        cout << "EidHyperTunnel is zipping through tunnels" << endl;
    }
};

// Overloaded command function
void command(string action, int parcelID) {
    cout << "Executing " << action << " for Parcel ID: " << parcelID << endl;
}

void command(string action, int parcelID, string priorityLevel) {
    cout << "Executing " << action << " for Parcel ID: " << parcelID
         << " with priority: " << priorityLevel << endl;
}

int main() {
    // Student ID and Name
    cout << "STUDENT ID: 24K-0011" << endl;
    cout << "STUDENT NAME: Syed Nadir Shah" << endl << endl;

    EidDrone droneUnit("EDR-101");
    EidTimeShifter timeUnit("ETS-204");
    EidHyperTunnel tunnelUnit("EHT-309");

    droneUnit.calculateRoute();
    droneUnit.estimateDeliveryTime();
    droneUnit.move();

    timeUnit.calculateRoute();
    timeUnit.estimateDeliveryTime();
    timeUnit.move();

    tunnelUnit.calculateRoute();
    tunnelUnit.estimateDeliveryTime();
    tunnelUnit.move();

    command("Deliver", 5011);
    command("Deliver", 5012, "High");

    if (droneUnit == timeUnit)
        cout << "droneUnit and timeUnit are identical" << endl;
    else
        cout << "droneUnit and timeUnit are different" << endl;

    cout << "Total active deliveries: " << Vehicle::getActiveDeliveries() << endl;

    return 0;
}
