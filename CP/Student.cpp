#include "Student.h"

Student::Student() :User()
{
	this->faculty = "���������";
	this->group = 0;
	this->ptrSubjectList = nullptr;
	cout << "\n����������� STUDENT " << this;
}

Student::Student(string name, string password, string faculty, int id, int group, int course, list<string>* listPtr, list<SolvedTest*>* ptrSolvedTest) :User(name, password, id)
{
	this->group = group;
	this->faculty = faculty;
	this->course = course;
	this->ptrSubjectList = listPtr;
	this->ptrSolvedTestList = ptrSolvedTest;
	cout << "\n����������� STUDENT " << this;
}

Student::~Student()
{
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		delete* iter;
	delete ptrSolvedTestList;
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
		system("cls");
		cout << "\n�� ����� ��� �������\n�������� �������� ��������:\n1 - ������ ����";
		cout << "\n2 - ����������� ��������� �����\n3 - ����������� ���������� � ����\n4 - ����������� �������� �����\n0 - �����\n\n";
		cin >> choice;
		switch (choice)
		{
		case SOLVE_TEST:
		{
			string testID;
			if (!ptrFilteredTestList->size())
			{
				cout << "\n��������� ������ ���\n";
				break;
			}
			for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				(*iter)->PrintTestBriefly();
			cout << "\n\n������� ID ��������� ����� (1 �������)\n";
			cin >> testID;
			Test* currentTest=nullptr;
			for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				if (testID == (*iter)->GetID())
				{
					currentTest = (*iter);
					ptrSolvedTestList->push_back(currentTest->Solving());
					break;
				}
			break;
		}
		case VIEW_ALL_AVAIBLE_TEST:
			if (!ptrFilteredTestList->size())
			{
				cout << "\n��������� ������ ���\n";
				break;
			}
			for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				(*iter)->PrintTestBriefly();
			break;
		case VIEW_OWN_INF:
			this->PrintInformation();
			break;
		case VIEW_SOLVED_TESTS:
			if (!ptrSolvedTestList->size())
			{
				cout << "\n�������� ������ ���\n";
				break;
			}
			for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
				(*iter)->PrintBriefly();
			break;
		default:
			delete ptrFilteredTestList;
			return;
		}
		cout << "\n\n";
		system("pause");
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

void Student::Unload(string path)
{
	ofstream file;
	file.open(path);
	if (!file.is_open())
		exit(-11);
	User::Unload(file);
	file << this->faculty <<"\n"<<this->group << " " << this->course << " " << ptrSubjectList->size()<<"\n";
	for (auto iter=ptrSubjectList->begin(); iter!=ptrSubjectList->end(); iter++)
	{
		file << (*iter)<<"\n";
	}
	file << ptrSolvedTestList->size();
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		file << "\n" << *(*iter) ;
}
