#include "student.h"
#include <iostream>
using namespace std;

// you can have both parameterized and parameterless
// this allows you to have flexible options to instanciate an object
// if Student is instanciated with no parameters, the default constructor is called
Student::Student() {
	this->studentId = "";
	this->firstName = "";
	this->lastName = "";
	this->email = "";
	this->age = 0;
	for (int i = 0; i < 3; i++) { this->numDays[i] = 0;};
	this->degreeProgram = DegreeProgram::SECURITY;
}	

// this->memberData = memberData is the alternative to using the setters
// for the sake of the assignment, use the setters
Student::Student(string studentId, string firstName, string lastName, string email, int age, double numDays[3], DegreeProgram degreeProgram) {
	Student::SetId(studentId);
	Student::SetFirstName(firstName);
	Student::SetLastName(lastName);
	Student::SetEmail(email);
	Student::setAge(age);
	// passing the array straight up seems to work
	// setter will loop through 3 indexes and assign the pointers to numDays[]
	Student::SetNumDays(numDays);
	Student::SetDegreeProgram(degreeProgram);
}

// since student itself does not allocate memory for any of its members, we dont need to delete anything
Student::~Student() {}

// 7 getters
string Student::GetId() const { return this->studentId; }
string Student::GetFirstName() const { return this->firstName; }
string Student::GetLastName() const { return this->lastName; }
string Student::GetEmail() const { return this->email; }
int Student::GetAge() const { return this->age; }
//explicitly hint that the return type is a pointer to a double (64 bit pointer for 64 bit data numDays[0])
double* Student::GetNumDays() const { return (double*)numDays; }
DegreeProgram Student::GetDegreeProgram() const { return this->degreeProgram; }

// 7 setters 
void Student::SetId(string studentId) { this->studentId = studentId; }
void Student::SetFirstName(string firstName) { this->firstName = firstName; }
void Student::SetLastName(string lastName) { this->lastName = lastName; }
void Student::SetEmail(string email) { this->email = email; }
void Student::setAge(int age) { this->age = age; }
// phenomon called "pointer decay" happens which means array passed translates to a pointer to the first element
// therefore numDays[] lives within pointer +- 24 bytes
void Student::SetNumDays(double numDays[]) {
	for (int i = 0; i < 3; i++) { this->numDays[i] = numDays[i]; }
}
void Student::SetDegreeProgram(DegreeProgram degreeProgram) { this->degreeProgram = degreeProgram; }

// use the getters to print the private data assigned to student object
void Student::PrintStudent() const {
	cout << this->GetId() << "\t "; // why do i have to do this to make the tab spacing work......
	cout << "First Name: " << this->GetFirstName() << "\t";
	cout << "Last Name: " << this->GetLastName() << "\t";
	cout << "Email: " << this->GetEmail() << "\t ";
	cout << "Age: " << this->GetAge() << "\t";
	cout << "daysInCourse: {" << this->GetNumDays()[0] << ", " << this->GetNumDays()[1] << ", " << this->GetNumDays()[2] << "}" << "\t";
	cout << "Degree Program: " << degreeProgramStrings[this->degreeProgram] << endl;
}	

