#pragma once
#include <string>
#include "degree.h"
using namespace std;

class Student {

public:
	// constructor with no parameters, if you want to instanciate a student with no data
	Student(); 
	// constrcutor WITH parameters, this corresponds to the constructor in student.cpp that uses the setters to set private data
	Student(string studentId, string firstName, string lastName, string email, int age, double numDays[], DegreeProgram degreeProgram); 
	// destructor takes no arguments and contains cleanup code = delete[] arrayName;
	~Student();

	// 7 getters
	// `const` constraint to prevent modification of the object
	// id should be string ex "A1"
	string GetId() const;
	string GetFirstName() const;	
	string GetLastName() const;
    string GetEmail() const;	
	int GetAge() const;
	// pointer to double in the array (64 bit pointer for 64 bit double) 
	double* GetNumDays() const;
	DegreeProgram GetDegreeProgram() const;

	// 7 setters
	//void because they dont return anything,set private data
	void SetId(string ID);
	void SetFirstName(string firstName);
	void SetLastName(string lastName);
	void SetEmail(string email);
	void setAge(int age);
	void SetNumDays(double numDays[]);
	void SetDegreeProgram(DegreeProgram degreeProgram);

	//general purpose function
	void PrintStudent() const;
	
private:
	// only instances of Student can access these via getters and setters
	string studentId;
	string firstName;
	string lastName;
	string email;
	int age;
	double numDays[3];
	DegreeProgram degreeProgram;
};
