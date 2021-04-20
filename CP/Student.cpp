#include "Student.h"

Student::Student() :User()
{
	this->faculty = "���������";
	this->group = 0;
	this->ptrSubjectList = nullptr;
	cout << "\n����������� STUDENT " << this;
}

Student::Student
(
	string name, 
	string password, 
	string faculty, 
	int id, 
	int group, 
	int course, 
	list<string>* listPtr, 
	list<SolvedTest*>* ptrSolvedTest
) 
	:User(name, password, id)
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

void Student::Menu(list<Test*>* ptrFilteredTestList)
{
	//list<Test*>* ptrFilteredTestList = ptrFilteredTestList;
	while (true)
	{
		short choice;
		system("cls");
		cout << "\n�� ����� ��� �������\n�������� �������� ��������:\n1 - ������ ����";
		cout << "\n2 - ����������� ��������� �����\n3 - ����������� ���������� � ����";
		cout << "\n4 - ����������� �������� �����\n5 - ���������� ���� �������� ���� ���������\n0 - �����\n\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case SOLVE_TEST:
		{
			if(PrintAvailableAndNoSolvedTest(ptrFilteredTestList))
			{
				string testID;
				cout << "\n\n������� ID ��������� ����� (1 �������)\n";
				cin >> testID;
				Test* currentTest = nullptr;
				for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
					if (testID == (*iter)->GetID())
					{
						currentTest = (*iter);
						ptrSolvedTestList->push_back(currentTest->Solving());
						break;
					}
			}
			break;
		}
		case VIEW_ALL_AVAIBLE_TEST:
			this->PrintAvailableAndNoSolvedTest(ptrFilteredTestList);
			break;
		case VIEW_OWN_INF:
			this->PrintInformation();
			break;
		case VIEW_ALL_SOLVED_TESTS_BRIEFLY:
			this->PrintAllSolvedTestBriefly();
			break;
		case VIEW_ONE_SOLVED_TEST_FULLY:
		{
			if (!this->PrintAllSolvedTestBriefly())
				break;
			string testID;
			cout << "\n\n������� ID ��������� ����� (1 �������)\n";
			cin >> testID;
			system("cls");
			SolvedTest* ptrSolvedTest = this->SearchSolvedTestWithID(testID);
			if (!ptrSolvedTest)
			{
				cout << "\n��������� ���� �� ������\n";
				break;
			}
			Test* ptrOriginalTest = SearchTestWithID(ptrFilteredTestList, testID);
			ViewQuestionAndUserAnswer(ptrSolvedTest, ptrOriginalTest);
			break;
		}
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

int Student::GetGroup()
{
	return this->group;
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

list<SolvedTest*>* Student::GetPtrSolvedTestList()
{
	return this->ptrSolvedTestList;
}

bool Student::CheckSolvedTestList(Test* somePtrTest)
{
	for (auto somePtrSolvedTestIter = this->ptrSolvedTestList->begin(); somePtrSolvedTestIter != this->ptrSolvedTestList->end(); somePtrSolvedTestIter++)
	{
		if (somePtrTest->GetID() == (*somePtrSolvedTestIter)->GetID())
			return false;
	}
	return true;
}

bool Student::PrintAvailableAndNoSolvedTest(list<Test*>* ptrFilteredTestList)
{
	if (!ptrFilteredTestList->size())
	{
		cout << "\n��������� ������ ���\n";
		return false;
	}
	int countPrintedTets = 0;
	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
	{
		if (!CheckSolvedTestList(*iter))
			continue;
		(*iter)->PrintTestBriefly();
		countPrintedTets++;
	}
	if (!countPrintedTets)
	{
		cout << "\n\n�� ������ ��� ��������� �����\n";
		return false;
	}
	return true;
}

bool Student::PrintAllSolvedTestBriefly()
{
	if (!ptrSolvedTestList->size())
	{
		cout << "\n�������� ������ ���\n";
		return false;
	}
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		(*iter)->PrintBriefly();
	return true;
}

bool Student::PrintAllSolvedTestBriefly(string subject)
{
	return false;
}

SolvedTest* Student::SearchSolvedTestWithID(string testID)
{
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		if (testID == (*iter)->GetID())
			return (*iter);
	return nullptr;
}

void Student::DeleteEditedSolvedTest(string uniqueID)
{
	for(auto iter=this->ptrSolvedTestList->begin();iter!=this->ptrSolvedTestList->end();iter++)
		if (uniqueID == (*iter)->GetID())
		{
			delete (*iter);
			this->ptrSolvedTestList->erase(iter);
			break;
		}
}

Test* SearchTestWithID(list<Test*>* ptrFilteredTestList, string testID)
{
	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
		if (testID == (*iter)->GetID())
			return (*iter);
	return nullptr;
}
