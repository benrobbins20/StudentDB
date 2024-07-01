#include "roster.h"
#include <iostream>
using namespace std;
#define LOG(x) std::cout << x << std::endl 

// parse each string comma delimited string in studentData[] as defined in main
void Roster::Parse(string record) {
	// Parse record using record.find() and record.substr()
    // record [0 : right hand comma] = studentID
	// record [left hand comma+1:right hand comma] = firstName and so on
    // Note - All index are mapped directly to `comma` index, not first char of next field!
    // meaning increment the substr index by 1!

    // test string: A1,Bob,Loblaw,bob@bob.com,1,2,3,4,SECURITY

    // studentID
    size_t rhComma = record.find(','); // [2]
    string studentID = record.substr(0, rhComma); // [0:2]

    // firstName
    size_t lhComma = rhComma; // [2]
    rhComma = record.find(',', lhComma + 1); // [6]
    string firstName = record.substr(lhComma + 1, rhComma - (lhComma + 1)); // substring from ind: 3, length: 6 - (2+1) = 3 == Bob 

    // lastName 
    lhComma = rhComma; 
    rhComma = record.find(',', lhComma + 1); //  [13
    string lastName = record.substr(lhComma + 1, rhComma - (lhComma + 1)); 

    // email
    lhComma = rhComma;
    rhComma = record.find(',', lhComma + 1); // [25]
    string email = record.substr(lhComma + 1, rhComma - (lhComma + 1));

    // age
    lhComma = rhComma;
    rhComma = record.find(',', lhComma + 1); // [27]
    // use stoi to convert int
    int age = stoi(record.substr(lhComma + 1, rhComma - (lhComma + 1)));

    // daysInCourse[0]
    lhComma = rhComma;
    rhComma = record.find(',', lhComma + 1); // [29]
    // we have this array set up to accept doubles
    // so we need to use stod() to convert to double
    // stoi, stod == "s to d", "s to i"
    double daysInCourse1 = stod(record.substr(lhComma + 1, rhComma - (lhComma + 1)));

    // daysInCourse[1]
    lhComma = rhComma;
    rhComma = record.find(',', lhComma + 1); // [31]
    double daysInCourse2 = stod(record.substr(lhComma + 1, rhComma - (lhComma + 1)));

    // daysInCourse[2]
    lhComma = rhComma;
    rhComma = record.find(',', lhComma + 1); // [33]
    double daysInCourse3 = stod(record.substr(lhComma + 1, rhComma - (lhComma + 1)));

    // degreeProgram
    lhComma = rhComma;
    rhComma = record.find(',', lhComma + 1); // npos = -1 [34: -1] end of string; overflow of an unsigned int results in 1111... ~ signed int `minimum` value 
    string degreeType = record.substr(lhComma + 1, rhComma - (lhComma + 1));
    // use the parallel strings array in degree.h to assign the enum based on the parallel index value 
    DegreeProgram degreeProgram;
    for (int i = 0; i < 3; i++) {
        if (degreeType == degreeProgramStrings[i]) {
			degreeProgram = static_cast<DegreeProgram>(i);
		}
    }

	// call Roster::Add() to make them an object of Student
	Add(studentID, firstName, lastName, email, age, daysInCourse1, daysInCourse2, daysInCourse3, degreeProgram);
}

// instanciate a New Student object and add it to the classRosterArray
void Roster::Add(string studentID, string firstName, string lastName, string email, int age, double daysInCourse1, double daysInCourse2, double daysInCourse3, DegreeProgram degreeProgram) {
    // create temp array for numDays requirement for Student object
    double daysInCourse[3] = { daysInCourse1, daysInCourse2, daysInCourse3 };
    // rosterIndex incrementred FIRST, then becomes the index for Student object
    classRosterArray[++rosterIndex] = new Student(studentID, firstName, lastName, email, age, daysInCourse, degreeProgram);
    // classRosterArray[rosterIndex] is a pointer to the Student object in heap
    // as each object gets allocated you can see that the addresses are not contiguous!
    LOG("DEBUG: Student " << studentID << " object @ " << classRosterArray[rosterIndex]);
    LOG("Adding student: " << studentID << " Roster index: " << rosterIndex);
}

// remove Student by shifting the elements left and decrementing lastIndex
void Roster::Remove(string studentID) {
    // flag if student is not found
    bool check = false;
   
    for (int i = 0; i <= rosterIndex; i++) {
        if (studentID == classRosterArray[i]->GetId()) {
            cout << "Removing student: " << studentID;
            cout << " @ Roster index: " << i << endl;

            // preserve the object with a LOCAL instance of Student
            // whats cool here is that when you DON'T use New, you dont allocate something to heap
            // Student newStudent = *classRosterArray[i]; will get popped off stack when function exits
            // memory address for newStudent in the stack is drastically higher than heap!
            Student newStudent = *classRosterArray[i];
            LOG("DEBUG: Student " << studentID << " object @ " << classRosterArray[i]);
            LOG("DEBUG: Temp Student object @ " << &newStudent);

            // deallocate the object from the heap
            delete classRosterArray[i];
            // this index of the array still points to heap address
            // remove this reference by overwriting the entire pointer with 0 
            classRosterArray[i] = nullptr;

            // if i=j then object is already last item
            for (int j = i; j < rosterIndex; j++) {
                // else the object is replaced with the next object in the array until last index is reached
				classRosterArray[j] = classRosterArray[j + 1];
			}

            // decrement lastIndex and set bool
			rosterIndex--;
			check = true;

            // so now here's the cool part
            // still have data from the object that was removed so we can use its helper functions after i nuked it from the array
			cout << "\n\t\t" << "---removed---" << "\t\t" << endl;
            newStudent.PrintStudent();
            cout << "\t\t" << "---removed---" << "\t\t" << endl << endl; 
        }
    }
    if (check == false) {
		cout << "\t\t--" << studentID << " not found--\t\t" << endl;
	}
}

// implement printall using the student's method PrintStudent()
void Roster::PrintAll() {
    for (int i = 0; i <= rosterIndex; i++) {
		// class roster array holds objects of student
        // object->method() syntax
        classRosterArray[i]->PrintStudent();
	}
}

// printall or print by studentId
void Roster::PrintAverageDaysInCourse(string studentID) {
    if (studentID == "") {
        // no studentID passed, print all
        for (int i = 0; i <= rosterIndex; i++) {
            // these have to be within loop to get data for each student
            double sum = 0, average = 0;
            for (int j = 0; j < 3; j++) {
                sum += classRosterArray[i]->GetNumDays()[j];
            }
            average = sum / 3.0;
            cout << "SID " << classRosterArray[i]->GetId() << " average days: ";
            cout << average << endl;
        }
    }
    else {
        double sum = 0, average = 0;
        for (int i = 0; i <= rosterIndex; i++) {
            // this means the pointer to the student object accesses its member function GetId()
            if (classRosterArray[i]->GetId() == studentID) {
                for (int j = 0; j < 3; j++) {
                    // using a loop increment sum instead of summing by index
                    sum += classRosterArray[i]->GetNumDays()[j];
                }
                average = sum / 3.0;
                cout << "SID " << studentID << " average days: " << average << endl;
            }
        }
    }
}

// simple email validator totally legit enterprise level logic 
void Roster::PrintInvalidEmails() {
    bool check = false;
    for (int i = 0; i <= rosterIndex; i++) {
		string email = classRosterArray[i]->GetEmail();
        // it needs an "@" and a "." and cant contain spaces, any single violation will trip invalid email conditional ||
        // npos, "no position" is a c++ism that essentially sets all possible bits in unsigned int size_t to 1, ~~ max value == not found
        if (email.find('@') == string::npos || email.find('.') == string::npos || email.find(' ') != string::npos) {
			cout << "SID " << classRosterArray[i]->GetId() << " Invalid email: " << email << endl;
            // should set a flag that indicates if any were found, it'll still loop through after it finds an invalid email
            check = true;
		}
	}
    if (check == false) {
		cout << "No invalid emails found" << endl;
    }
}

// matches the type DegreeProgram in the enum with the same type of degreeProgram in theory
void Roster::PrintByDegreeProgram(DegreeProgram degreeProgram) {
    for (int i = 0; i <= rosterIndex; i++) {
        // both have type DegreeProgram so essentially we are just comparing ints
        if ( degreeProgram == classRosterArray[i]->GetDegreeProgram()) {
            classRosterArray[i]->PrintStudent();
        }
    }
}

Roster::~Roster() {
    for (int i = 0; i <= rosterIndex; i++) {
        // free the object nullify the pointer
		delete classRosterArray[i];
        classRosterArray[i] = nullptr;
	}
}