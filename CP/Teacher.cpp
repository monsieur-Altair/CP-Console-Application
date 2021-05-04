#include "Teacher.h"


Teacher::Teacher() :User()
{
	this->subject = "";
	this->ptrGroupList = nullptr;
	cout << "\nКонструктор TEACHER " << this;
}

Teacher::Teacher
(
	string	name,
	int		hashedPassword,
	int		id,
	string	subject,
	shared_ptr<list<int>>	ptrList
) : User(name, hashedPassword, id)
{
	this->subject = subject;
	this->ptrGroupList = ptrList;
	cout << "\nКонструктор TEACHER " << this;
}

Teacher::~Teacher()
{
	//if(this)
	//delete ptrGroupList;
	cout << "\nДеструктор TEACHER " << this;
}

void Teacher::Menu(list<Test*>** ptrFilteredTestList, list<Student*>* ptrFilteredStudentList)
{
	while (true)
	{
		short choice;
		system("cls");
		cout << "\nВы вошли как преподаватель\nВыберите желаемое действие:\n1 - создать тест";
		cout << "\n2 - удалить тест\n3 - просмотреть информацию о себе\n4 - редактировать конкретный тест";
		cout << "\n5 - просмотреть все доступные тесты\n6 - просмотреть всех студентов своих групп";
		cout << "\n7 - просмотреть конкретного студента\n8 - просмотреть вопросы одного теста";
		cout << "\n9 - Отсортировать студентов по группам (по возрастанию)\n10 - Отсортировать студентов по ФИО\n0 - Выйти\n\n";
		cin >> choice;
		Check(&choice, 0, SORT_STUDENT_ALPHABETICAL);
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
			//string uniqueID;
			//PrintAvailableTest(ptrFilteredTestList);
			//cout << "\nВведите ID теста (1 колонка)\n";
			//cin >> uniqueID;
			//for (auto iter = (*ptrFilteredTestList)->begin(); iter != (*ptrFilteredTestList)->end(); iter++)
			//{
			//	if ((*iter)->GetID() == uniqueID)
			//	{
			//		delete* iter;
			//		(*ptrFilteredTestList)->erase(iter);
			//		break;
			//	}
			//}
			int number;
			if (!PrintAvailableTest(ptrFilteredTestList))
				break;
			cout << "\nВведите номер теста (1 колонка)\n";
			cin >> number;
			auto iter = (*ptrFilteredTestList)->begin();
			advance(iter, number - 1);
			delete* iter;
			(*ptrFilteredTestList)->erase(iter);
			break;
		}
		case VIEW_OWN_INF:
			cout << "\tФИО\t\t\t\tПароль\t\tID\t\tПредмет\tГруппы\n";
			this->PrintInformation();
			break;
		case EDIT_TEST:
		{
			if (!PrintAvailableTest(ptrFilteredTestList))
				break;
			Test* test = SearchAvailableTest(ptrFilteredTestList);
			bool isEdit = false;
			EditTest(this, test, &isEdit);
			if (isEdit)
				for (auto ptrStudent : *ptrFilteredStudentList)
					ptrStudent->DeleteEditedSolvedTest(test->GetID());

			if (test->GetNumberOfQuestions() == 0)
				for (auto iter = (*ptrFilteredTestList)->begin(); iter != (*ptrFilteredTestList)->end(); iter++)
					if (test->GetID() == (*iter)->GetID())
					{
						cout << "\n\nТест стал пустым и его пришлось удалить\n";
						(*ptrFilteredTestList)->erase(iter);
						delete test;
					}
			test = nullptr;
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
			//PrintOwnStudents(ptrFilteredStudentList);
			//int ID;
			//cout << "\nВведите ID студента: ";
			//cin >> ID;
			//Check(&ID, 1, 100000000);
			//for (auto ptrStudent : *ptrFilteredStudentList)
			//	if (ptrStudent->GetID() == ID)
			//	{
			//		cout << "\nРешенные тесты студента " << ptrStudent->GetName();
			//		ptrStudent->PrintAllSolvedTestBriefly();
			//		break;
			//	}
			PrintOwnStudents(ptrFilteredStudentList);
			int number;
			cout << "\nВведите номер студента: ";
			cin >> number;
			Check(&number, 1, ptrFilteredStudentList->size());
			auto ptrStudentIter = ptrFilteredStudentList->begin();
			advance(ptrStudentIter, number - 1);
			cout << "\nРешенные тесты студента " << (*ptrStudentIter)->GetName()<<"\n";
			(*ptrStudentIter)->PrintAllSolvedTestBriefly();
			break;
		}
		case VIEW_ONE_TEST_FULLY:
		{
			if (!PrintAvailableTest(ptrFilteredTestList))
				break;
			Test* test = SearchAvailableTest(ptrFilteredTestList);
			test->PrintTest();
			break;
		}
		case SORT_STUDENTS_BY_GROUPS:
			if (ptrFilteredStudentList->size())
			{
				ptrFilteredStudentList->sort(sort::SortStudentByGroups);
				cout << "\nСписок отсортирован\n";
			}
			else
				cout << "\nСписок пуст\n";
			break;
		case SORT_STUDENT_ALPHABETICAL:
			if (ptrFilteredStudentList->size())
			{
				ptrFilteredStudentList->sort(sort::SortStudentAlphabetic);
				cout << "\nСписок отсортирован\n";
			}
			else
				cout << "\nСписок пуст\n";
			break;
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

shared_ptr<list<int>> Teacher::ptrGetGroupList()
{
	return this->ptrGroupList;
}

Test* Teacher::CreateTest()
{
	string shortDiscription, subject = this->subject;
	int course, uniqueID, answersNumber;
	hash<int> hashFunction;
	list<Question*>* ptrQuestionList = new list<Question*>;
	//cout << "\nВведите уникальный ID теста: ";
	cin.ignore();
	//getline(cin, uniqueID);
	uniqueID = hashFunction(Test::GetEntityCount());
	cout << "\nВведите краткое описание теста: ";
	getline(cin, shortDiscription);
	cout << "\nВведите курс: ";
	cin >> course;
	Check(&course, 1, 6);
	cout << "\nВведите количество ответов на вопрос (для каждого вопроса будет установлено это значение количества ответов): ";
	cin >> answersNumber;
	Check(&answersNumber, 1, 5);
	int isContinue = 1;
	do
	{
		ptrQuestionList->push_back(CreateQuestion(answersNumber));
		system("cls");
		cout << "\nЖелаете ввести еще один вопрос? 1 - да, 0 - нет\n";
		cin >> isContinue;
		Check(&isContinue, 0, 1);
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
	Check(&correctAnswerOption, 1, answersNumber);
	cout << "\nВведите количество баллов за вопрос: ";
	cin >> pointsPerQuestion;
	Check(&pointsPerQuestion, 1, 1000);
	return new Question(question, answers, correctAnswerOption, pointsPerQuestion, answersNumber);
}

bool Teacher::PrintAvailableTest(list<Test*>** ptrFilteredTestList)
{
	if (!(*ptrFilteredTestList)->size())
	{
		cout << "\nСписок доступных тестов пуст\n";
		return false;
	}
	int i = 1;
	cout << "№\tID\t\tПредмет\tКурс\tКраткое описание\n";
	for (auto ptrTest : **ptrFilteredTestList)
	{
		cout << "\n" << i++ << ") ";
		ptrTest->PrintTestBriefly();
	}
	return true;
}

void Teacher::PrintOwnStudents(list<Student*>* ptrFilteredStudentList)
{
	if (!ptrFilteredStudentList->size())
	{
		cout << "\nСписок студентов пуст\n";
		return;
	}
	int i = 1;
	cout << "№\tФИО\t\t\t\tПароль\t\tID\t\tФ-тет\tКурс\tГруппа\tПредметы\n";
	for (auto ptrStudent : *ptrFilteredStudentList)
	{
		cout << "\n" << i++ << ") ";
		ptrStudent->PrintInformation();
	}
}

Test* Teacher::SearchAvailableTest(list<Test*>** ptrFilteredTestList)
{
	//string uniqueID;
	//cout << "\nВведите ID теста (1 колонка)\n";
	//cin >> uniqueID;
	//for (auto test : **ptrFilteredTestList)
	//	if (test->GetID() == uniqueID)
	//		return test;
	//cout << "\nТест не найден\n";
	int number;
	cout << "\nВведите номер теста (1 колонка)\n";
	cin >> number;
	Check(&number, 1, (*ptrFilteredTestList)->size());
	auto iter = (*ptrFilteredTestList)->begin();
	advance(iter, number - 1);
	return *iter;
	//return nullptr;
}

void EditTest(Teacher* ptrTeacher, Test* ptrTest, bool* isEdit)
{
	while (true)
	{
		system("cls");
		string password;
		hash<string> hashFunction;
		cout << "\nВведите ваш пароль: ";
		cin >> password;
		int hashedPassword = hashFunction(password);
		if (hashedPassword != ptrTeacher->GetHashedPassword())
		{
			cout << "\nВ доступе отказано\n";
			return;
		}
		int value;
		cout << "\nВыберите поле изменения:\n1 - Краткое описание\n2 - Вопрос\n0 - Выйти\n";
		cin >> value;
		Check(&value, 0, 2);
		system("cls");
		switch (value)
		{
		case 1:
			cout << "\nВведите новое краткое описание\n";
			cin >> ptrTest->shortDescription;
			*isEdit = true;
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
				Check(&number, 0, ptrTest->ptrQuestionList->size());
				if (!number)
					break;
				auto iter = ptrTest->ptrQuestionList->begin();
				advance(iter, number - 1);
				//do
				//{
				//	system("cls");
				//	cout << "\nЧто вы хотите сделать с вопросом?\n1 - удалить\n2 - изменить вопрос\n3 - изменить вариант ответа";
				//	cout << "\n4 - изменить правильный вариант ответа\n5 - изменить количество баллов за вопрос\n6 - Добавить новый вопрос\n0 - Выйти\n\n";
				//	cin >> value;
				//	Check(&value, 0, Teacher::ADD_NEW_QUESTION);
				//	if (value)
				//		*isEdit = true;
				//	switch (value)
				//	{
				//	case Teacher::DELETE:
				//		delete * iter;
				//		ptrTest->ptrQuestionList->erase(iter);
				//		break;
				//	case Teacher::CHANGE_QUESTION:
				//		cout << "\nВведите новый вопрос: ";
				//		cin.ignore();
				//		getline(cin, (*iter)->question);
				//		break;
				//	case Teacher::CHANGE_ANSWER_OPTION:
				//		for (int i = 0; i < (*iter)->numberOfAnswers; i++)
				//			cout << "\nОтвет №" << i + 1 << " :" << (*iter)->answerOptions[i];
				//		cout << "\n\nВведите номер ответа для изменения: ";
				//		cin >> number;
				//		cin.ignore();
				//		cout << "\nВведите новый ответ: ";
				//		getline(cin, (*iter)->answerOptions[number - 1]);
				//		break;
				//	case Teacher::CHANGE_CORRECT_ANSWER:
				//		cout << "\n" << (*iter)->question;
				//		for (int i = 0; i < (*iter)->numberOfAnswers; i++)
				//			cout << "\nОтвет №" << i + 1 << " :" << (*iter)->answerOptions[i];
				//		cout << "\nВведите новый правильный вариант ответа: ";
				//		cin >> (*iter)->correctAnswerOption;
				//		break;
				//	case Teacher::CHANGE_POINTS:
				//		cout << "\nВведите новое количество баллов за вопрос: ";
				//		cin >> (*iter)->pointsPerQuestion;
				//		break;
				//	case Teacher::ADD_NEW_QUESTION:
				//		ptrTest->ptrQuestionList->push_back(ptrTeacher->CreateQuestion((*iter)->numberOfAnswers));
				//		break;
				//	default:
				//		break;
				//	}
				//} while (!value);
				system("cls");
				cout << "\nЧто вы хотите сделать с вопросом?\n1 - удалить\n2 - изменить вопрос\n3 - изменить вариант ответа";
				cout << "\n4 - изменить правильный вариант ответа\n5 - изменить количество баллов за вопрос\n6 - Добавить новый вопрос\n0 - Выйти\n\n";
				cin >> value;
				Check(&value, 0, Teacher::ADD_NEW_QUESTION);
				if (value)
					*isEdit = true;
				switch (value)
				{
				case Teacher::DELETE:
					delete* iter;
					ptrTest->ptrQuestionList->erase(iter);
					break;
				case Teacher::CHANGE_QUESTION:
					cout << "\nВведите новый вопрос: ";
					cin.ignore();
					getline(cin, (*iter)->question);
					break;
				case Teacher::CHANGE_ANSWER_OPTION:
					for (int i = 0; i < (*iter)->numberOfAnswers; i++)
						cout << "\nОтвет №" << i + 1 << " :" << (*iter)->answerOptions[i];
					cout << "\n\nВведите номер ответа для изменения: ";
					cin >> number;
					cin.ignore();
					cout << "\nВведите новый ответ: ";
					getline(cin, (*iter)->answerOptions[number - 1]);
					break;
				case Teacher::CHANGE_CORRECT_ANSWER:
					cout << "\n" << (*iter)->question;
					for (int i = 0; i < (*iter)->numberOfAnswers; i++)
						cout << "\nОтвет №" << i + 1 << " :" << (*iter)->answerOptions[i];
					cout << "\nВведите новый правильный вариант ответа: ";
					cin >> (*iter)->correctAnswerOption;
					break;
				case Teacher::CHANGE_POINTS:
					cout << "\nВведите новое количество баллов за вопрос: ";
					cin >> (*iter)->pointsPerQuestion;
					break;
				case Teacher::ADD_NEW_QUESTION:
					ptrTest->ptrQuestionList->push_back(ptrTeacher->CreateQuestion((*iter)->numberOfAnswers));
					break;
				default:
					break;
				}

			}
			break;
		}
		default:
			return;
		}
	}
}

int Teacher::GetHashedPassword()
{
	return User::GetHashedPassword();
}