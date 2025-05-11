#include <iostream>
#include <string>

using namespace std;


class Vehicle {
public:
	
    string model;
    double rentalPrice;
    string licenseRequirement;

    Vehicle(string m, double price, string license) : model(m), rentalPrice(price), licenseRequirement(license) {}
};


class User {
public:
	
    string name;
    int age;
    string licenseType;
    string contactInfo;
    int userID;

    User(string n, int a, string license, string contact, int id) : name(n), age(a), licenseType(license), contactInfo(contact), userID(id) {}
    void updateDetails(string n, int a, string license, string contact) {
        name = n;
        age = a;
        licenseType = license;
        contactInfo = contact;
    }
};


class RentalSystem {
public:
	
    Vehicle* vehicles[5];
    int vehicleCount;

    RentalSystem() : vehicleCount(0) {}

    void addVehicle(string model, double price, string license) {
        if (vehicleCount < 5) {
            vehicles[vehicleCount++] = new Vehicle(model, price, license);
        }
    }

    void showVehicles() {
        for (int i = 0; i < vehicleCount; i++) {
            cout << i + 1 << ". " << vehicles[i]->model << " - $" << vehicles[i]->rentalPrice << " per day - License Required: " << vehicles[i]->licenseRequirement << endl;
        }
    }

    void rentVehicle(User* user, int choice) {
        if (choice > 0 && choice <= vehicleCount) {
            if (vehicles[choice - 1]->licenseRequirement == user->licenseType) {
                cout << user->name << " has rented " << vehicles[choice - 1]->model << " successfully!" << endl;
            } else {
                cout << "You do not meet the license requirement for this vehicle." << endl;
            }
        } else {
            cout << "Invalid vehicle choice." << endl;
        }
    }
};


int main() {
	
	cout << "Name: Syed Nadir Shah" << endl;
    cout << "Student ID: K240011" << endl;
	
    RentalSystem system;
    
    system.addVehicle("Sedan", 40, "Intermediate");
    system.addVehicle("SUV", 60, "Full");
    system.addVehicle("Motorbike", 30, "Learner");
    
    
    User user("Nadir", 25, "Intermediate", "000123000", 101);
    cout << "Welcome " << user.name << "! Available vehicles: " << endl;
    system.showVehicles();
    
    
    int choice;
    
    cout << "Enter vehicle number to rent: ";
    cin >> choice;
    system.rentVehicle(&user, choice);
    
    
    return 0;
}

