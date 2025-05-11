#include <iostream>

using namespace std;

typedef unsigned long ulong;

// Simple password hashing using DJB2
ulong generateHash(string password) {
    ulong hash = 5381;
    for (size_t i = 0; i < password.length(); i++) {
        hash = hash * 33 + password[i];
    }
    return hash;
}

// Base class for all user types
class User {
protected:
    string fullName, userEmail;
    int userID;
    ulong passwordHash;
    string accessRights[5];
    int accessCount;
public:
    User(string fullName, int userID, string userEmail, string password, string accessRights[], int accessCount)
        : fullName(fullName), userID(userID), userEmail(userEmail), accessCount(accessCount) {
        passwordHash = generateHash(password);
        for (int i = 0; i < accessCount; i++) {
            this->accessRights[i] = accessRights[i];
        }
    }

    virtual void display() {
        cout << "Name: " << fullName << endl << "ID: " << userID << endl << "Email: " << userEmail << endl << "Permissions: ";
        for (int i = 0; i < accessCount; i++) {
            cout << accessRights[i] << " ";
        }
        cout << endl;
    }

    bool authenticate(string password) {
        return passwordHash == generateHash(password);
    }

    bool hasPermission(string right) {
        for (int i = 0; i < accessCount; i++) {
            if (accessRights[i] == right)
                return true;
        }
        return false;
    }

    virtual bool accessLab() {
        return hasPermission("labAccess");
    }

    int getUserID() const {
        return userID;
    }
};

// Derived class for Student
class Student : public User {
protected:
    int assignmentStatus[5]; // 0: not submitted, 1: submitted
public:
    Student(string fullName, int userID, string userEmail, string password)
        : User(fullName, userID, userEmail, password, new string[1]{"submitAssignment"}, 1) {
        for (int i = 0; i < 5; i++) {
            assignmentStatus[i] = 0;
        }
    }

    void display() override {
        cout << "[Student] ";
        User::display();
    }

    void submitAssignment(int index) {
        if (index >= 0 && index < 5) {
            assignmentStatus[index] = 1;
            cout << "Assignment " << index + 1 << " submitted." << endl;
        }
    }
};

// Teaching Assistant
class TA : public Student {
private:
    Student* assignedStudents[10];
    string projectList[2];
    int studentAssignedCount;
    int currentProjects;
public:
    TA(string fullName, int userID, string userEmail, string password)
        : Student(fullName, userID, userEmail, password), studentAssignedCount(0), currentProjects(0) {
        string newRights[] = {"viewProjectList", "manageStudentList", "submitAssignment"};
        for (int i = 0; i < 3; i++) {
            accessRights[i] = newRights[i];
        }
        accessCount = 3;
    }

    void display() override {
        cout << "[TA] ";
        User::display();
    }

    bool assignStudent(Student* student) {
        if (studentAssignedCount < 10) {
            assignedStudents[studentAssignedCount++] = student;
            return true;
        }
        return false;
    }

    bool startProject(string projectTitle) {
        if (currentProjects < 2) {
            projectList[currentProjects++] = projectTitle;
            return true;
        }
        return false;
    }
};

// Professor class
class Professor : public User {
public:
    Professor(string fullName, int userID, string userEmail, string password)
        : User(fullName, userID, userEmail, password, new string[2]{"assignResearch", "labAccess"}, 2) {}

    void display() override {
        cout << "[Professor] ";
        User::display();
    }

    void assignProject(TA& ta, string projectTitle) {
        if (ta.startProject(projectTitle)) {
            cout << "Project '" << projectTitle << "' assigned to TA (ID: " << ta.getUserID() << ")" << endl;
        } else {
            cout << "TA has reached project limit." << endl;
        }
    }
};

// Utility function to check auth + permission before executing action
void authenticateAndPerformAction(User* user, string action, string password) {
    if (user->authenticate(password)) {
        if (user->hasPermission(action)) {
            cout << "Action '" << action << "' performed successfully." << endl;
        } else {
            cout << "Permission denied." << endl;
        }
    } else {
        cout << "Authentication failed." << endl;
    }
}

int main() {
    // STUDENT INFO
    cout << "STUDENT ID: 24K-0011" << endl;
    cout << "STUDENT NAME: Syed Nadir Shah" << endl << endl;

    Student student("Fahad Khan", 1001, "fahad.k@example.com", "pass123");
    TA ta("Sara Malik", 1002, "sara.ta@example.com", "ta456");
    Professor professor("Dr. Amir Qureshi", 1003, "amir.q@example.com", "prof789");

    student.display();
    ta.display();
    professor.display();

    authenticateAndPerformAction(&student, "submitAssignment", "pass123");
    authenticateAndPerformAction(&ta, "manageStudentList", "ta456");
    authenticateAndPerformAction(&professor, "assignResearch", "prof789");

    professor.assignProject(ta, "Data Mining System");
    professor.assignProject(ta, "IoT Security Study");
    professor.assignProject(ta, "AI Ethics Review");

    return 0;
}
