#pragma once

#include "Student.h"
#include "Teacher.h"
#include <memory>

class DataBase
{
	list<Test*>		listOfTests;
	list<Student*>	listOfStudents;
	list<Teacher*>	listOfTeachers;

	

	enum MenuChoice
	{
		EXIT, REGISTRATION, LOGIN
	};
	enum UserType
	{
		STUDENT = 1, TEACHER
	};
public:
	DataBase();
	DataBase(string);
	~DataBase();
	void Unload(string);
	void AuthorizationMenu();
	void PrintAllTests();
	void PrintAllStudents();
	void PrintAllTeachers();
	Teacher* Registration(Teacher*);
	Teacher* Login(Teacher*);
	Student* Registration(Student*);
	Student* Login(Student*);
	list<Test*>*	LoadTestsWithFilter(int, shared_ptr<list<string>>);
	list<Test*>*	LoadTestsWithFilter(string);
	list<Student*>* LoadStudentsFilter(string, shared_ptr<list<int>>);
};


Teacher* CreateTeacherFromFile(string);
Student* CreateStudentFromFile(string);






