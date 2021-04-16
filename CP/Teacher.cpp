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
		cout << "\n5 - просмотреть доступные тесты\n6 - просмотреть студентов своих групп";
		cout << "\n7 - просмотреть конкретного студента\n0 - Выйти\n\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case CREATE_TEST:
		{
			string uniqueID, shortDiscription, subject = this->subject;
			int course, answersNumber;
			list<Question*>* ptrQuestionList = new list<Question*>;
			cout << "\nВведите уникальный ID теста:\n";
			cin >> uniqueID;
			cout << "\nВведите короткое описание теста:\n";
			cin >> shortDiscription;
			cout << "\nВведите курс: ";
			cin >> course;
			cout << "\nВведите количество ответов на вопрос (для каждого вопроса будет установлено это значение количества ответов: ";
			cin >> answersNumber;
			while (true)
			{
				string question;
				string* answers = new string[answersNumber];
				int correctAnswerOption, pointsPerQuestion;
				system("cls");
				cout << "\nВведите вопрос:\n";
				cin >> question;
				cout << "\nВведите " << answersNumber << " ответа(ов)\n";
				for (int i = 0; i < answersNumber; i++)
				{
					cout << "\nОтвет №" << i + 1 << ": ";
					cin >> answers[i];
				}
				cout << "\nВведите номер правильного ответа: ";
				cin >> correctAnswerOption;
				cout << "\nВведите количество баллов за вопрос: \n";
				cin >> pointsPerQuestion;
				ptrQuestionList->push_back(new Question(question, answers, correctAnswerOption, pointsPerQuestion, answersNumber));
				system("cls");
				cout << "\nЖелаете ввести еще один вопрос? 1 - да, 0 - нет\n";
				bool choice;
				cin >> choice;
				if (!choice)
					break;
			}
			(*ptrFilteredTestList)->push_back(new Test(uniqueID, shortDiscription, subject, course, ptrQuestionList));
			break;
		}
		case DELETE_TEST:
		{
			string uniqueID;
			for (auto ptrTest : **ptrFilteredTestList)
			{
				ptrTest->PrintTestBriefly();
				cout << "\n";
			}
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
			break;
		case VIEW_ALL_AVAIBLE_TEST:
			for (auto ptrTest : **ptrFilteredTestList)
			{
				ptrTest->PrintTestBriefly();
				cout << "\n";
			}
			break;
		case VIEW_ALL_STUDENTS:
			for (auto ptrStudent : *ptrFilteredStudentList)
			{
				ptrStudent->PrintInformation();
				cout << "\n";
			}
			break;
		case VIEW_ONE_STUDENT:
		{
			int ID;
			for (auto ptrStudent : *ptrFilteredStudentList)
			{
				ptrStudent->PrintInformation();
				cout << "\n";
			}
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
		default:
			break;
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

