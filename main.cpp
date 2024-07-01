#include "roster.h"
#include <iostream>
using namespace std;


void PrintBanner() {
	string line(50, '-');
	std::cout << line << std::endl;
	std::cout << "Scripting and Programming - Applications - C867" << std::endl;
	cout << "C++" << endl;
	cout << "Flavor: [x86_64, ARM64]" << endl;
	cout << "SID: 011007860 " << "First name: Ben " << "Last name: Robbins" << endl;
	std::cout << line << std::endl;
}

int main() {
	Roster classRoster;
	const std::string studentData[] = {
	"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
	"A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
	"A3,Jack,Napoli,The_lawyer99@yahoo.com,19,20,40,33,SOFTWARE",
	"A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
	"A5,Bob,Loblaw,bob.bob@bobloblaw.law,52,57,13,33,SOFTWARE"
	};

	// perform requirements
	PrintBanner();
	cout << "\n\t\t--Parsing student data--\t\t" << endl;
	for (int i = 0; i < 5; i++) { classRoster.Parse(studentData[i]); }
	cout << "\n\t\t--All students--\t\t" << endl;
	classRoster.PrintAll();
	cout << "\n\t\t--Invalid emails--\t\t" << endl;
	classRoster.PrintInvalidEmails();
	cout << "\n\t\t--Averaged days by SID:--\t\t" << endl;
	classRoster.PrintAverageDaysInCourse(); // called with no arguments defaults to print all
	cout << "\n\t\t--Averaged days SID: A5--\t\t" << endl;
	classRoster.PrintAverageDaysInCourse("A5"); // called with studentID
	cout << "\n\t\t--Students by program: SOFTWARE--\t\t" << endl;
	classRoster.PrintByDegreeProgram(DegreeProgram::SOFTWARE);
	cout << "\n\t\t--Remove A3--\t\t" << endl;
	classRoster.Remove("A3");
	cout << "\n\t\t--All students--\t\t" << endl;
	classRoster.PrintAll();
	cout << "\n\t\t--Remove A3--\t\t" << endl;
	classRoster.Remove("A3");

	// clean exit roster
	classRoster.~Roster();

	// basically api to user's executable capabilites like bash -c or cmd /C
	// pauses the console process before returning 0 to terminate the process
	system("pause");
	return 0;
}