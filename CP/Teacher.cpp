#include "Teacher.h"

Teacher::Teacher() :User()
{
	this->subject = "";
	this->ptrGroupList = nullptr;
	cout << "\nКонструктор TEACHER " << this;
}

Teacher::Teacher(string name, string password, int id, string subject, list<int>* ptrList) : User(name, password, id)
{
	this->subject = subject;
	this->ptrGroupList = ptrList;
	cout << "\nКонструктор TEACHER " << this;
}

Teacher::~Teacher()
{
	//if(this)
	delete ptrGroupList;
	cout << "\nДеструктор TEACHER " << this;
}

void Teacher::Menu(list<Test*>** ptrFilteredTestList, list<Student*>* ptrFilteredStudentList)
{
	//list<Test*>* ptrFilteredTestList;
	while (true)
	{
		short choice;
		system("cls");
		cout << "\nВы вошли как преподаватель\nВыберите желаемое действие:\n1 - создать тест";
		cout << "\n2 - удалить тест\n3 - просмотреть информацию о себе\n4 - редактировать конкретный тест";
		cout << "\n5 - просмотреть все доступные тесты\n6 - просмотреть всех студентов своих групп";
		cout << "\n7 - просмотреть конкретного студента\n8 - просмотреть вопросы одного теста\n0 - Выйти\n\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case CREATE_TEST:
		{
			(*ptrFilteredTestList)->push_back(CreateTest());
			break;
		}
		case DELETE_TEST:
		{
			string uniqueID;
			PrintAvailableTest(ptrFilteredTestList);
			cout << "\nВведите ID теста, которого хотите удалить (1 колонка)\n";
			cin >> uniqueID;
			for (auto iter = (*ptrFilteredTestList)->begin(); iter != (*ptrFilteredTestList)->end(); iter++)
			{
				if ((*iter)->GetID() == uniqueID)
				{
					delete* iter;
					(*ptrFilteredTestList)->erase(iter);
					break;
				}
			}
			break;
		}
		case VIEW_OWN_INF:
			this->PrintInformation();
			break;
		case EDIT_TEST:
			PrintAvailableTest(ptrFilteredTestList);

			break;
		case VIEW_ALL_AVAIBLE_TEST:
			PrintAvailableTest(ptrFilteredTestList);
			break;
		case VIEW_ALL_STUDENTS:
			PrintOwnStudents(ptrFilteredStudentList);
			break;
		case VIEW_ONE_STUDENT:
		{
			PrintAvailableTest(ptrFilteredTestList);
			int ID;
			cout << "\nВведите ID студента: ";
			cin >> ID;
			for (auto ptrStudent : *ptrFilteredStudentList)
				if (ptrStudent->GetID() == ID)
				{
					ptrStudent->PrintAllSolvedTestBriefly();
					break;
				}
			break;
		}
		case VIEW_ONE_TEST_FULLY:
		{
			PrintAvailableTest(ptrFilteredTestList);
			string uniqueID;
			cout << "\nВведите ID теста, которого хотите удалить (1 колонка)\n";
			cin >> uniqueID;
			for (auto test : **ptrFilteredTestList)
			{
				if (test->GetID() == uniqueID)
				{
					test->PrintTest();
					break;
				}
			}
			cout << "\nТест не найден\n";
			break;
		}
		default:
			return;
		}
		cout << "\n\n";
		system("pause");
	}
}

void Teacher::PrintInformation()
{
	User::PrintUserInformation();
	cout << "\t" << this->subject << "\t";
	for (auto iter = ptrGroupList->begin(); iter != ptrGroupList->end(); iter++)
		cout << (*iter) << ", ";
}

void Teacher::Unload(string path)
{
	ofstream file;
	file.open(path);
	if (!file.is_open())
		exit(-11);
	User::Unload(file);
	file << this->subject << "\n" << this->ptrGroupList->size();
	for (auto iter = ptrGroupList->begin(); iter != ptrGroupList->end(); iter++)
		file << " " << (*iter);
	file.close();
}

string Teacher::GetSubject()
{
	return this->subject;
}

list<int>* Teacher::ptrGetGroupList()
{
	return this->ptrGroupList;
}

Test* Teacher::CreateTest()
{
	string uniqueID, shortDiscription, subject = this->subject;
	int course, answersNumber;
	list<Question*>* ptrQuestionList = new list<Question*>;
	cout << "\nВведите уникальный ID теста: ";
	cin.ignore();
	getline(cin, uniqueID);
	cout << "\nВведите короткое описание теста: ";
	getline(cin, shortDiscription);
	cout << "\nВведите курс: ";
	cin >> course;
	cout << "\nВведите количество ответов на вопрос (для каждого вопроса будет установлено это значение количества ответов): ";
	cin >> answersNumber;
	bool isContinue=true;
	do
	{
		ptrQuestionList->push_back(CreateQuestion(answersNumber));
		system("cls");
		cout << "\nЖелаете ввести еще один вопрос? 1 - да, 0 - нет\n";
		cin >> isContinue;
	} while (isContinue);
	return new Test(uniqueID, shortDiscription, subject, course, ptrQuestionList);
}

Question* Teacher::CreateQuestion(int answersNumber)
{
	string question;
	string* answers = new string[answersNumber];
	int correctAnswerOption, pointsPerQuestion;
	system("cls");
	cout << "\nВведите вопрос: ";
	cin.ignore();
	getline(cin, question);
	cout << "\nВведите " << answersNumber << " ответа(ов)\n";
	for (int i = 0; i < answersNumber; i++)
	{
		cout << "Ответ №" << i + 1 << ": ";
		getline(cin, answers[i]);
	}
	cout << "\nВведите номер правильного ответа: ";
	cin >> correctAnswerOption;
	cout << "\nВведите количество баллов за вопрос: ";
	cin >> pointsPerQuestion;
	return new Question(question, answers, correctAnswerOption, pointsPerQuestion, answersNumber);
}

void Teacher::PrintAvailableTest(list<Test*>** ptrFilteredTestList)
{
	if (!(*ptrFilteredTestList)->size())
	{
		cout << "\nСписок доступных тестов пуст\n";
		return;
	}
	for (auto ptrTest : **ptrFilteredTestList)
	{
		ptrTest->PrintTestBriefly();
		cout << "\n";
	}
}

void Teacher::PrintOwnStudents(list<Student*>* ptrFilteredStudentList)
{
	if (!ptrFilteredStudentList->size())
	{
		cout << "\nСписок доступных тестов пуст\n";
		return;
	}
	for (auto ptrStudent : *ptrFilteredStudentList)
	{
		ptrStudent->PrintInformation();
		cout << "\n";
	}
}

Test* Teacher::SearchAvailableTest(list<Test*>**)
{
}

