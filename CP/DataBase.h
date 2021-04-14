#pragma once

#include "Student.h"
#include "Teacher.h"

class DataBase
{
	list<Test*>		listOfTests;
	list<Student*>	listOfStudents;
	list<Teacher*>	listOfTeachers;
public:
	DataBase();
	DataBase(string);
	~DataBase();
	void AuthorizationMenu();
	void PrintAllTests();
	void PrintAllStudents();
	void PrintAllTeachers();
	void Registration(Student**, Teacher**);
	bool Login(Student**, Teacher**);
	bool SearchUser(int, string, Student**, Teacher**);
	void Unload(string);
	list<Test*>* LoadTestsWithFilter(int, list<string>*);

};

Teacher* CreateTeacherFromFile(string);
Student* CreateStudentFromFile(string);

enum MenuChoice
{
	EXIT, REGISTRATION, LOGIN
};

enum RoleChoice
{
	STUDENT = 1, TEACHER
};



