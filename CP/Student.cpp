#include "Student.h"

Student::Student() :User()
{
	this->faculty = "";
	this->group = 0;
	this->ptrSubjectList = nullptr;
#ifdef DEBUG
	cout << "\nКонструктор STUDENT " << this;
#endif
}

Student::Student
(
	string	name,
	int		hashedPassword,
	string	faculty,
	int		id,
	int		group,
	int		course,
	shared_ptr<list<string>> listPtr,
	list<SolvedTest*>*		 ptrSolvedTest
):User(name, hashedPassword, id)
{
	this->group = group;
	this->faculty = faculty;
	this->course = course;
	this->ptrSubjectList = listPtr;
	this->ptrSolvedTestList = ptrSolvedTest;
#ifdef DEBUG
	cout << "\nКонструктор STUDENT " << this;
#endif
}

Student::~Student()
{
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
		delete* iter;
	delete ptrSolvedTestList;
	ptrSubjectList->clear();
#ifdef DEBUG
	cout << "\nДеструктор STUDENT " << this;
#endif
}

void Student::Menu(list<Test*>* ptrFilteredTestList)
{
	list<Test*>* ptrSolvedFullTest = new list<Test*>;
	this->DeleteSolvedFromFilteredList(ptrFilteredTestList, ptrSolvedFullTest);

	while (true)
	{
		short choice;
		system("cls");
		cout << "\nВы вошли как студент\nВыберите желаемое действие:\n1 - решить тест";
		cout << "\n2 - просмотреть доступные тесты\n3 - просмотреть информацию о себе";
		cout << "\n4 - просмотреть решенные тесты\n5 - посмотреть один решенный тест полностью";
		cout << "\n6 - Отсортировать список решенных тестов по предметам";
		cout << "\n7 - Отсортировать список решенных тестов по проценту правильных ответов";
		cout << "\n8 - Отсортировать список доступных по предметам (А-Я)\n0 - Выйти\n\n";
		cin >> choice;
		Check(&choice, 0, SORT_AVAILABLE_BY_SUBJECTS);
		system("cls");
		switch (choice)
		{
		case SOLVE_TEST:
		{
			if (PrintAvailableAndNoSolvedTest(ptrFilteredTestList))
			{
				int number;
				cout << "\n\nВведите номер желаемого теста (1 колонка)\n";
				cin >> number;
				Check(&number, 1, ptrFilteredTestList->size());
				auto iter = ptrFilteredTestList->begin();
				advance(iter, number - 1);
				Test* currentTest = *iter;
				ptrSolvedTestList->push_back(currentTest->Solving());
				
				ptrSolvedFullTest->splice(ptrSolvedFullTest->end(), *ptrFilteredTestList, iter);
			}
			break;
		}
		case VIEW_ALL_AVAIBLE_TEST:
			this->PrintAvailableAndNoSolvedTest(ptrFilteredTestList);
			break;
		case VIEW_OWN_INF:
			cout << "\tФИО\t\t\t\tПароль\t\tID\t\tФ-тет\tКурс\tГруппа\tПредметы\n";
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
			cout << "\n\nВведите номер желаемого теста (1 колонка)\n";
			cin >> number;
			Check(&number, 1, ptrSolvedTestList->size());
			auto iter = ptrSolvedTestList->begin();
			advance(iter, number - 1);
			SolvedTest* ptrSolvedTest = (*iter);
			Test* ptrOriginalTest = SearchTestWithID(ptrSolvedFullTest, ptrSolvedTest->GetID());
			system("cls");
			if (!ptrOriginalTest)
			{
				cout << "\nТест не найден\n";
				break;
			}
			ViewQuestionAndUserAnswer(ptrSolvedTest, ptrOriginalTest);
			break;
		}
		case SORT_SOLVED_BY_SUBJECTS:
		{
			int size = ptrSolvedTestList->size();
			if (size == 0)
				cout << "\nСписок пуст\n";
			else if (size == 1)
				cout << "\nВ списке один элемент\n";
			else
			{
				ptrSolvedTestList->sort(sort::SortSolvedBySubject);
				cout << "\nСписок отсортирован\n";
			}
			break;
		}
		case SORT_SOLVED_BY_PERCENTAGE:
		{
			int size = ptrSolvedTestList->size();
			if (size == 0)
				cout << "\nСписок пуст\n";
			else if (size == 1)
				cout << "\nВ списке один элемент\n";
			else
			{
				ptrSolvedTestList->sort(sort::SortByAnswerPercentage);
				cout << "\nСписок отсортирован\n";
			}
			break;
		}
		case SORT_AVAILABLE_BY_SUBJECTS:
		{
			int size = ptrFilteredTestList->size();
			if (size == 0)
				cout << "\nСписок пуст\n";
			else if (size == 1)
				cout << "\nВ списке один элемент\n";
			else
			{
				ptrFilteredTestList->sort(sort::SortTestBySubject);
				cout << "\nСписок отсортирован\n";
			}
			break;
		}
		default:
			delete ptrFilteredTestList;
			delete ptrSolvedFullTest;
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
		file << (*iter) << "\n";
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
	for (auto somePtrSolvedTestIter = ptrSolvedTestList->begin(); somePtrSolvedTestIter != ptrSolvedTestList->end(); somePtrSolvedTestIter++)
		if (somePtrTest->GetID() == (*somePtrSolvedTestIter)->GetID())
			return false;
	return true;
}

bool Student::PrintAvailableAndNoSolvedTest(list<Test*>* ptrFilteredTestList)
{
	if (!ptrFilteredTestList->size())
	{
		cout << "\nДоступных тестов нет или вы решили все доступные тесты\n";
		return false;
	}
	int i = 1;
	cout << "№\tID\t\tПредмет\tКурс\tКраткое описание\n";
	for (auto iter = ptrFilteredTestList->begin(); iter != ptrFilteredTestList->end(); iter++)
	{
		cout << "\n " << i++ << ") ";
		(*iter)->PrintTestBriefly();
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
	cout << "№\tID\t\tПредмет\tБаллы\tКраткое описание\n";
	for (auto iter = ptrSolvedTestList->begin(); iter != ptrSolvedTestList->end(); iter++)
	{
		cout << "\n" << i++ << ") ";
		(*iter)->PrintBriefly();
	}
	return true;
}

void Student::DeleteSolvedFromFilteredList(list<Test*>* ptrFilteredTestList , list<Test*>* ptrSolvedFullTest)
{
	if (ptrFilteredTestList->size() == 0)
		return;
	ptrFilteredTestList->push_front(new Test());

	for (auto iterOrigTest = ptrFilteredTestList->begin(); iterOrigTest != ptrFilteredTestList->end(); iterOrigTest++)
	{
		for(auto iterSolvedTest=ptrSolvedTestList->begin();iterSolvedTest!=ptrSolvedTestList->end();iterSolvedTest++)
			if ((*iterOrigTest)->GetID() == (*iterSolvedTest)->GetID())
			{
				auto iterCopy = iterOrigTest;
				advance(iterOrigTest, -1);
				ptrSolvedFullTest->splice(ptrSolvedFullTest->end(), *ptrFilteredTestList, iterCopy);
				break;
			}
	}

	auto iter = ptrFilteredTestList->begin();
	delete* iter;
	ptrFilteredTestList->erase(iter);
}




string Student::GetName()
{
	return User::GetName();
}

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

Test* SearchTestWithID(list<Test*>* ptrTestList, int testID)
{
	for (auto iter = ptrTestList->begin(); iter != ptrTestList->end(); iter++)
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