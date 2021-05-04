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
	int hashedPassword,
	string faculty,
	int id,
	int group,
	int course,
	shared_ptr<list<string>> listPtr,
	list<SolvedTest*>* ptrSolvedTest
):User(name, hashedPassword, id)
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
	//delete ptrSubjectList;
	cout << "\n���������� STUDENT " << this;
}

//void Student::DeleteSolvedFromFilteredList(list<Test*>* ptrFilteredTestList, list<Test*>* ptrSolvedFullTest)
//{
//	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
//	{
//		for (auto iter2 = this->ptrSolvedTestList->begin(); iter2 != ptrSolvedTestList->end(); iter2++)
//			if ((*iter)->GetID() == (*iter2)->GetID())
//			{
//				////ptrFilteredTestList->erase(iter);
//				//auto it = iter;
//				//if (it != ptrFilteredTestList->begin())
//				//	iter--;
//				//else iter++;
//				//ptrSolvedFullTest->splice(ptrSolvedFullTest->end(), *ptrFilteredTestList, it);
//				auto it = iter;
//				ptrFilteredTestList->push_back(*it);
//				ptrFilteredTestList->erase(iter);
//
//				break;
//			}
//	}
//}

void Student::Menu(list<Test*>* ptrFilteredTestList)
{
	while (true)
	{
		short choice;
		system("cls");
		cout << "\n�� ����� ��� �������\n�������� �������� ��������:\n1 - ������ ����";
		cout << "\n2 - ����������� ��������� �����\n3 - ����������� ���������� � ����";
		cout << "\n4 - ����������� �������� �����\n5 - ���������� ���� �������� ���� ���������";
		cout << "\n6 - ������������� ������ �������� ������ �� ���������";
		cout << "\n7 - ������������� ������ �������� ������ �� �������� ���������� �������";
		cout << "\n8 - ������������� ������ ��������� �� ��������� (�-�)\n0 - �����\n\n";
		cin >> choice;
		Check(&choice, 0, SORT_AVAILABLE_BY_SUBJECTS);
		list<Test*>* ptrSolvedFullTest = new list<Test*>;
		//this->DeleteSolvedFromFilteredList(ptrFilteredTestList, ptrSolvedFullTest);
		system("cls");
		switch (choice)
		{
		case SOLVE_TEST:
		{
			int countPrintedTests = 0;
			if (PrintAvailableAndNoSolvedTest(ptrFilteredTestList,&countPrintedTests))
			{
				int number;
				cout << "\n\n������� ����� ��������� ����� (1 �������)\n";
				cin >> number;
				Check(&number, 1, countPrintedTests);
				auto iter = ptrFilteredTestList->begin();
				advance(iter, number - 1);
				Test* currentTest = *iter;
				ptrSolvedTestList->push_back(currentTest->Solving());

				//for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
				//	if (testID == (*iter)->GetID())
				//	{
				//		currentTest = (*iter);
				//		ptrSolvedTestList->push_back(currentTest->Solving());
				//		break;
				//	}
			}
			break;
		}
		case VIEW_ALL_AVAIBLE_TEST:
		{
			int i;
			this->PrintAvailableAndNoSolvedTest(ptrFilteredTestList,&i);
			break;
		}
		case VIEW_OWN_INF:
			cout << "\t���\t\t\t\t������\t\tID\t\t�-���\t����\t������\t��������\n";
			this->PrintInformation();
			break;
		case VIEW_ALL_SOLVED_TESTS_BRIEFLY:
			this->PrintAllSolvedTestBriefly();
			break;
		case VIEW_ONE_SOLVED_TEST_FULLY:
		{
			if (!this->PrintAllSolvedTestBriefly())
				break;
			int number;
			cout << "\n\n������� ����� ��������� ����� (1 �������)\n";
			cin >> number;
			Check(&number, 1, ptrSolvedTestList->size());
			auto iter = ptrSolvedTestList->begin();
			advance(iter, number - 1);
			SolvedTest* ptrSolvedTest = (*iter);
			Test* ptrOriginalTest = SearchTestWithID(ptrFilteredTestList, ptrSolvedTest->GetID());
			system("cls");
			ViewQuestionAndUserAnswer(ptrSolvedTest, ptrOriginalTest);
			break;
		}
		case SORT_SOLVED_BY_SUBJECTS:
			if (ptrSolvedTestList->size())
			{
				ptrSolvedTestList->sort(sort::SortSolvedBySubject);
				cout << "\n������ �����������\n";
			}
			else
				cout << "\n������ ����\n";
			break;
		case SORT_SOLVED_BY_PERCENTAGE:
			if (ptrSolvedTestList->size())
			{
				ptrSolvedTestList->sort(sort::SortByAnswerPercentage);
				cout << "\n������ ������������\n";
			}
			else
				cout << "\n������ ����\n";
			break;
		case SORT_AVAILABLE_BY_SUBJECTS:
			if (ptrFilteredTestList->size())
			{
				ptrFilteredTestList->sort(sort::SortTestBySubject);
				cout << "\n������ ������������\n";
			}
			else
				cout << "\n������ ����\n";
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

shared_ptr<list<string>> Student::GetPtrSubjectList()
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
	file << this->faculty << "\n" << this->group << " " << this->course << " " << ptrSubjectList->size() << "\n";
	for (auto iter = ptrSubjectList->begin(); iter != ptrSubjectList->end(); iter++)
	{
		file << (*iter) << "\n";
	}
	file << ptrSolvedTestList->size();
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		file << "\n" << *(*iter);
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

bool Student::PrintAvailableAndNoSolvedTest(list<Test*>* ptrFilteredTestList, int* countPrintedTests)
{
	*countPrintedTests = 0;
	if (!ptrFilteredTestList->size())
	{
		cout << "\n��������� ������ ���\n";
		return false;
	}
	int i = 1;
	cout << "�\tID\t\t�������\t����\t������� ��������\n";
	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++,i++)
	{
		if (!CheckSolvedTestList(*iter))
			continue;
		cout << "\n " << i << ") ";
		(*iter)->PrintTestBriefly();
		(*countPrintedTests)++;
	}
	if (!(*countPrintedTests))
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
	int i = 1;
	cout << "�\tID\t\t�������\t�����\t������� ��������\n";
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
	{
		cout << "\n" << i++ << ") ";
		(*iter)->PrintBriefly();
	}
	return true;
}




string Student::GetName()
{
	return User::GetName();
}

//SolvedTest* Student::SearchSolvedTestWithID(string testID)
//{
//	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
//		if (testID == (*iter)->GetID())
//			return (*iter);
//	return nullptr;
//}

void Student::DeleteEditedSolvedTest(int uniqueID)
{
	for (auto iter = this->ptrSolvedTestList->begin(); iter != this->ptrSolvedTestList->end(); iter++)
		if (uniqueID == (*iter)->GetID())
		{
			delete (*iter);
			this->ptrSolvedTestList->erase(iter);
			break;
		}
}

Test* SearchTestWithID(list<Test*>* ptrFilteredTestList, int testID)
{
	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
		if (testID == (*iter)->GetID())
			return (*iter);
	return nullptr;
}

bool sort::SortStudentByGroups(const Student* ptr1, const Student* ptr2)
{
	return (ptr1->group) < (ptr2->group);
}

bool sort::SortStudentAlphabetic(Student* ptr1, Student* ptr2)
{
	return (ptr1->GetName().compare(ptr2->GetName()) < 0);
}