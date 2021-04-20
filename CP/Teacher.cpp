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
			cout << "\nВведите ID теста (1 колонка)\n";
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
		{
			//
			ПРОВЕРКА
			PrintAvailableTest(ptrFilteredTestList);
			Test* test = SearchAvailableTest(ptrFilteredTestList);
			EditTest(this, test);
			for (auto ptrStudent : *ptrFilteredStudentList)
				ptrStudent->DeleteEditedSolvedTest(test->GetID());
			if (test->GetNumberOfQuestions() == 0)
				for (auto iter = (*ptrFilteredTestList)->begin(); iter != (*ptrFilteredTestList)->end(); iter++)
					if (test->GetID() == (*iter)->GetID())
						(*ptrFilteredTestList)->erase(iter);
			delete test;
			break;
		}
		case VIEW_ALL_AVAIBLE_TEST:
			PrintAvailableTest(ptrFilteredTestList);
			break;
		case VIEW_ALL_STUDENTS:
			PrintOwnStudents(ptrFilteredStudentList);
			break;
		case VIEW_ONE_STUDENT:
		{
			PrintOwnStudents(ptrFilteredStudentList);
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
			Test* test = SearchAvailableTest(ptrFilteredTestList);
			if (test)
				test->PrintTest();
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
	bool isContinue = true;
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

Test* Teacher::SearchAvailableTest(list<Test*>** ptrFilteredTestList)
{
	string uniqueID;
	cout << "\nВведите ID теста (1 колонка)\n";
	cin >> uniqueID;
	for (auto test : **ptrFilteredTestList)
		if (test->GetID() == uniqueID)
			return test;
	cout << "\nТест не найден\n";
	return nullptr;
}

void EditTest(Teacher* ptrTeacher, Test* ptrTest)
{
	while (true)
	{
		system("cls");
		string password;
		cout << "\nВведите ваш пароль: ";
		cin >> password;
		if (password != ptrTeacher->GetPassword())
		{
			cout << "\nВ доступе отказано\n";
			return;
		}
		int value;
		cout << "\nВыберите поле изменения:\n1 - Краткое описание\n2 - Вопрос\n0 - Выйти\n";
		cin >> value;
		system("cls");
		switch (value)
		{
		case 1:
			cout << "\nВведите новое краткое описание\n";
			cin >> ptrTest->shortDescription;
			break;
		case 2:
		{
			while (true)
			{
				system("cls");
				int i = 1, number;
				for (auto q : *(ptrTest->ptrQuestionList))
					cout << "\nВопрос № " << i++ << ": " << q->question;
				cout << "\n\nВведите номер вопроса (0 - выйти): ";
				cin >> number;
				if (!number)
					break;
				auto iter = ptrTest->ptrQuestionList->begin();
				advance(iter, number - 1);
				do
				{
					system("cls");
					cout << "\nЧто вы хотите сделать с вопросом?\n1 - удалить\n2 - изменить вопрос\n3 - изменить вариант ответа";
					cout << "\n4 - изменить правильный вариант ответа\n5 - изменить количество баллов за вопрос\n6 - Добавить новый вопрос\n0 - Выйти\n\n";
					cin >> value;
					switch (value)
					{
					case 1:
						delete * iter;
						ptrTest->ptrQuestionList->erase(iter);
						break;
					case 2:
						cout << "\nВведите новый вопрос: ";
						cin.ignore();
						getline(cin, (*iter)->question);
						break;
					case 3:
						for (int i = 0; i < (*iter)->numberOfAnswers; i++)
							cout << "\nОтвет №" << i + 1 << " :" << (*iter)->answerOptions[i];
						cout << "\n\nВведите номер ответа для изменения: ";
						cin >> number;
						cin.ignore();
						cout << "\nВведите новый ответ: ";
						getline(cin, (*iter)->answerOptions[number - 1]);
						break;
					case 4:
						cout << "\n" << (*iter)->question;
						for (int i = 0; i < (*iter)->numberOfAnswers; i++)
							cout << "\nОтвет №" << i + 1 << " :" << (*iter)->answerOptions[i];
						cout << "\nВведите новый правильный вариант ответа: ";
						cin >> (*iter)->correctAnswerOption;
						break;
					case 5:
						cout << "\nВведите новое количество баллов за вопрос: ";
						cin >> (*iter)->pointsPerQuestion;
						break;
					case 6:
						ptrTest->ptrQuestionList->push_back(ptrTeacher->CreateQuestion((*iter)->numberOfAnswers));
						break;
					default:
						break;
					}
				} while (!value);
			}
			break;
		}
		default:
			return;
		}
	}
}

string Teacher::GetPassword()
{
	return User::GetPassword();
}


