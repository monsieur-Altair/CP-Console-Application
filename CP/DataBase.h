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

	Teacher* Registration(Teacher*);
	Teacher* Login(Teacher*);
	//Teacher* SearchUser(Teacher*);

	Student* Registration(Student*);
	Student* Login(Student*);
	//Student* SearchUser(Student*);
	//bool Login(Student**, Teacher**);
	//bool SearchUser(int, string, Student**, Teacher**);
	void Unload(string);
	list<Test*>* LoadTestsWithFilter(int, list<string>*);
	list<Test*>* LoadTestsWithFilter(string);
	list<Student*>* LoadStudentsFilter(string, list<int>*);
};

Teacher* CreateTeacherFromFile(string);
Student* CreateStudentFromFile(string);

enum MenuChoice
{
	EXIT, REGISTRATION, LOGIN
};

enum UserType
{
	STUDENT = 1, TEACHER
};




