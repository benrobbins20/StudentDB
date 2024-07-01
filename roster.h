#pragma once
#include "student.h"

class Roster {
public:

	// destructor
	~Roster();
	
	void Parse(string record);
	void Add(
		string studentID, 
		string firstName, 
		string lastName, 
		string emailAddress, 
		int age, 
		double daysInCourse1, 
		double daysInCourse2, 
		double daysInCourse3, 
		DegreeProgram degreeprogram);
	void Remove(string studentID);
	void PrintAll();
	void PrintAverageDaysInCourse(string studentID = "");
	void PrintInvalidEmails();
	void PrintByDegreeProgram(DegreeProgram degreeProgram);

private:
	// array of pointers to Student objects 
	Student* classRosterArray[5];
	//used with array[++lastIndex] = object index
	int rosterIndex = -1;
	
};