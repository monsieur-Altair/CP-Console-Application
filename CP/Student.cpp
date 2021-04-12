#include "Student.h"

Student::Student() :User()
{
	this->faculty = "���������";
	this->group = 0;
	this->ptrSubjectList = nullptr;
	cout << "\n����������� STUDENT " << this;
}

Student::Student(string name, string password, string faculty, int id, int group, int course, list<string>* listPtr) :User(name, password, id)
{
	this->group = group;
	this->faculty = faculty;
	this->course = course;
	this->ptrSubjectList = listPtr;
	cout << "\n����������� STUDENT " << this;
}

Student::~Student()
{
	for (auto iter = SolvedTestList.begin(); iter != SolvedTestList.end(); iter++)
		delete* iter;
	ptrSubjectList->clear();
	delete ptrSubjectList;
	cout << "\n���������� STUDENT " << this;
}

void Student::Menu(list<Test*>* ptr)
{
	list<Test*>* ptrFilteredTestList = ptr;
	while (true)
	{
		short choice;
		cout << "\n�� ����� ��� �������\n�������� �������� ��������:\n1 - ������ ����";
		cout << "\n2 - ����������� ��������� �����\n3 - ����������� ���������� � ����\n4 - ����������� �������� �����\n\n";
		cin >> choice;
		switch (choice)
		{
		case SOLVE_TEST:
		{
			string testID;
			for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				(*iter)->PrintTestBriefly();
			cout << "\n\n������� ID ��������� ����� (1 �������)\n";
			cin >> testID;
			Test* currentTest=nullptr;
			for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				if (testID == (*iter)->GetID())
				{
					currentTest = (*iter);
					SolvedTestList.push_back(currentTest->Solving());
					break;
				}
			break;
		}
		case VIEW_ALL_AVAIBLE_TEST:
			for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				(*iter)->PrintTestBriefly();
			break;
		case VIEW_OWN_INF:
			this->PrintInformation();
			break;
		case VIEW_SOLVED_TESTS:
			for (auto iter = SolvedTestList.begin(); iter != SolvedTestList.end(); iter++)
				(*iter)->PrintBriefly();
			break;
		default:
			delete ptrFilteredTestList;
			return;
		}
	}

}

void Student::PrintInformation()
{
	User::PrintUserInformation();
	cout << "\t" << this->faculty << "\t" << this->course << "\t" << this->group << "\t";
	for (auto iter = ptrSubjectList->begin(); iter != ptrSubjectList->end(); iter++)
		cout << (*iter) << ", ";
}

list<string>* Student::GetPtrSubjectList()
{
	return this->ptrSubjectList;
}

int Student::GetCourse()
{
	return this->course;
}
