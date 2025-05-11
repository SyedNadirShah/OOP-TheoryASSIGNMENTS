#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#define MAX_SEATS 60
#define MAX_VEHICLES 10
#define MAX_USERS 20

class IncompletePaymentException : public exception
{
    const char *what() const noexcept override
    {
        return "Cannot proceed: Payment is not complete.";
    }
};

class AlreadyReservedSeatException : public exception
{
    const char *what() const noexcept override
    {
        return "This seat has already been reserved.";
    }
};

class UserTypeConflictException : public exception
{
    const char *what() const noexcept override
    {
        return "User type conflict: Students and Faculty cannot share the same seat category.";
    }
};

class SeatUnit
{
public:
    int seatNo;
    string allowedUserType;
    bool booked;

    SeatUnit() : booked(false) {}
    SeatUnit(int no, string userType) : seatNo(no), allowedUserType(userType), booked(false) {}
};

class Transport;
class Journey;

class Person
{
public:
    string userID, fullName, emailAddress;
    bool paymentStatus;

    Person() {}
    Person(string id, string name, string email, bool paid) : userID(id), fullName(name), emailAddress(email), paymentStatus(paid) {}

    virtual string getUserCategory() const = 0;
    virtual int calculateFare(bool airConditioned) const = 0;
};

class Pupil : public Person
{
public:
    Pupil() {}
    Pupil(string id, string name, string email, bool paid) : Person(id, name, email, paid) {}

    string getUserCategory() const override { return "Student"; }
    int calculateFare(bool airConditioned) const override
    {
        return airConditioned ? 7000 : 5000;
    }
};

class Professor : public Person
{
public:
    Professor() {}
    Professor(string id, string name, string email, bool paid) : Person(id, name, email, paid) {}

    string getUserCategory() const override { return "Faculty"; }
    int calculateFare(bool airConditioned) const override
    {
        return airConditioned ? 5000 : 3000;
    }
};

class Journey
{
public:
    string origin, destination;
    int journeyLength;

    Journey() {}
    Journey(string from, string to, int dist) : origin(from), destination(to), journeyLength(dist) {}

    bool isExtendedRoute() const { return journeyLength > 20; }
};

class Operator
{
public:
    string driverID, driverName, licenseID;
    Operator() {}
    Operator(string id, string name, string license) : driverID(id), driverName(name), licenseID(license) {}
};

class Transport
{
public:
    string transportID, transportType;
    bool ACenabled;
    SeatUnit seats[MAX_SEATS];
    int totalSeats;
    Journey *assignedJourney;
    Operator *assignedDriver;

    Transport() {}
    Transport(string id, string type, bool ac, int seatTotal, string userType) : transportID(id), transportType(type), ACenabled(ac), totalSeats(seatTotal), assignedJourney(nullptr), assignedDriver(nullptr)
    {
        for (int i = 0; i < seatTotal; ++i)
        {
            seats[i] = SeatUnit(i + 1, userType);
        }
    }

    void linkJourney(Journey *j) { assignedJourney = j; }
    void linkDriver(Operator *op) { assignedDriver = op; }

    void reserveSeat(Person *person, int seatNumber)
    {
        if (!person->paymentStatus)
            throw IncompletePaymentException();
        if (seatNumber < 1 || seatNumber > totalSeats)
            throw out_of_range("Invalid seat selection.");
        SeatUnit &seat = seats[seatNumber - 1];
        if (seat.booked)
            throw AlreadyReservedSeatException();
        if (seat.allowedUserType != person->getUserCategory())
            throw UserTypeConflictException();

        seat.booked = true;
        cout << person->fullName << " has successfully reserved seat " << seatNumber << " on transport " << transportID << endl;
    }
};

int main()
{
    Pupil student1("ST001", "Ali", "ali@fast.edu.pk", true);
    Professor prof1("FC001", "Dr. Ahmed", "ahmed@fast.edu.pk", true);

    Journey trip1("North Nazimabad", "FAST-NUCES", 25);
    Operator driver1("DRV001", "Nadeem", "LIC1234");

    Transport bus1("BUS001", "Bus", true, 52, "Student");
    bus1.linkJourney(&trip1);
    bus1.linkDriver(&driver1);

    try
    {
        bus1.reserveSeat(&student1, 10);
        bus1.reserveSeat(&prof1, 11);
    }
    catch (exception &ex)
    {
        cout << "Exception occurred: " << ex.what() << '\n';
    }

    return 0;
}
