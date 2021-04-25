#include "Student.h"

Student::Student() :User()
{
	this->faculty = "факультет";
	this->group = 0;
	this->ptrSubjectList = nullptr;
	cout << "\nКонструктор STUDENT " << this;
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
	cout << "\nКонструктор STUDENT " << this;
}

Student::~Student()
{
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		delete* iter;
	delete ptrSolvedTestList;
	ptrSubjectList->clear();
	//delete ptrSubjectList;
	cout << "\nДеструктор STUDENT " << this;
}

void Student::Menu(list<Test*>* ptrFilteredTestList)
{
	while (true)
	{
		short choice;
		system("cls");
		cout << "\nВы вошли как студент\nВыберите желаемое действие:\n1 - решить тест";
		cout << "\n2 - просмотреть доступные тесты\n3 - просмотреть информацию о себе";
		cout << "\n4 - просмотреть решенные тесты\n5 - посмотреть один решенный тест полностью";
		cout << "\n6 - Отсортировать список решенных тестов по предметам";
		cout << "\n7 - Отсортировать список решенных тестов по проценту правильных ответов";
		cout << "\n8 - Отсортировать список доступх по предметам (А-Я)\n0 - Выйти\n\n";
		cin >> choice;
		Check(&choice, 0, SORT_AVAILABLE_BY_SUBJECTS);
		system("cls");
		switch (choice)
		{
		case SOLVE_TEST:
		{
			int countPrintedTests = 0;
			if (PrintAvailableAndNoSolvedTest(ptrFilteredTestList,&countPrintedTests))
			{
				int number;
				cout << "\n\nВведите номер желаемого теста (1 колонка)\n";
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
			this->PrintInformation();
			break;
		case VIEW_ALL_SOLVED_TESTS_BRIEFLY:
			this->PrintAllSolvedTestBriefly();
			break;
		case VIEW_ONE_SOLVED_TEST_FULLY:
		{
			if (!this->PrintAllSolvedTestBriefly())
				break;
			//string testID;
			int number;
			cout << "\n\nВведите номер желаемого теста (1 колонка)\n";
			//cout << "\n\nВведите ID желаемого теста (1 колонка)\n";
			//cin >> testID;			
			//system("cls");
			//SolvedTest* ptrSolvedTest = this->SearchSolvedTestWithID(testID);
			//if (!ptrSolvedTest)
			//{
			//	cout << "\nУказанный тест не найден\n";
			//	break;
			//}
			cin >> number;
			Check(&number, 1, ptrSolvedTestList->size());
			auto iter = ptrSolvedTestList->begin();
			advance(iter, number - 1);
			SolvedTest* ptrSolvedTest = (*iter);
			Test* ptrOriginalTest = SearchTestWithID(ptrFilteredTestList, ptrSolvedTest->GetID());
			ViewQuestionAndUserAnswer(ptrSolvedTest, ptrOriginalTest);
			break;
		}
		case SORT_SOLVED_BY_SUBJECTS:
			if (ptrSolvedTestList->size())
			{
				ptrSolvedTestList->sort(sort::SortSolvedBySubject);
				cout << "\nСписок осортирован\n";
			}
			else
				cout << "\nСписок пуст\n";
			break;
		case SORT_SOLVED_BY_PERCENTAGE:
			if (ptrSolvedTestList->size())
			{
				ptrSolvedTestList->sort(sort::SortByAnswerPercentage);
				cout << "\nСписок отсортирован\n";
			}
			else
				cout << "\nСписок пуст\n";
			break;
		case SORT_AVAILABLE_BY_SUBJECTS:
			if (ptrFilteredTestList->size())
			{
				ptrFilteredTestList->sort(sort::SortTestBySubject);
				cout << "\nСписок отсортирован\n";
			}
			else
				cout << "\nСписок пуст\n";
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
	if (!ptrFilteredTestList->size())
	{
		cout << "\nДоступных тестов нет\n";
		return false;
	}
	int i = 1;
	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
	{
		if (!CheckSolvedTestList(*iter))
			continue;
		cout << "\n " << i++ << ") ";
		(*iter)->PrintTestBriefly();
		(*countPrintedTests)++;
	}
	if (!(*countPrintedTests))
	{
		cout << "\n\nВы решили все доступные тесты\n";
		return false;
	}
	return true;
}

bool Student::PrintAllSolvedTestBriefly()
{
	if (!ptrSolvedTestList->size())
	{
		cout << "\nРешенных тестов нет\n";
		return false;
	}
	int i = 1;
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