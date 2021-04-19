#include "Teacher.h"


Teacher::Teacher() :User()
{
	this->subject = "";
	this->ptrGroupList = nullptr;
	cout << "\n����������� TEACHER " << this;
}

Teacher::Teacher(string name, string password, int id, string subject, list<int>* ptrList) : User(name, password, id)
{
	this->subject = subject;
	this->ptrGroupList = ptrList;
	cout << "\n����������� TEACHER " << this;
}

Teacher::~Teacher()
{
	//if(this)
	delete ptrGroupList;
	cout << "\n���������� TEACHER " << this;
}

void Teacher::Menu(list<Test*>** ptrFilteredTestList, list<Student*>* ptrFilteredStudentList)
{
	//list<Test*>* ptrFilteredTestList;
	while (true)
	{
		short choice;
		system("cls");
		cout << "\n�� ����� ��� �������������\n�������� �������� ��������:\n1 - ������� ����";
		cout << "\n2 - ������� ����\n3 - ����������� ���������� � ����\n4 - ������������� ���������� ����";
		cout << "\n5 - ����������� ��� ��������� �����\n6 - ����������� ���� ��������� ����� �����";
		cout << "\n7 - ����������� ����������� ��������\n8 - ����������� ������� ������ �����\n0 - �����\n\n";
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
			cout << "\n������� ID ����� (1 �������)\n";
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
			PrintAvailableTest(ptrFilteredTestList);
			Test* test = SearchAvailableTest(ptrFilteredTestList);
			EditTest(this, test);
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
			PrintAvailableTest(ptrFilteredTestList);
			int ID;
			cout << "\n������� ID ��������: ";
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
	cout << "\n������� ���������� ID �����: ";
	cin.ignore();
	getline(cin, uniqueID);
	cout << "\n������� �������� �������� �����: ";
	getline(cin, shortDiscription);
	cout << "\n������� ����: ";
	cin >> course;
	cout << "\n������� ���������� ������� �� ������ (��� ������� ������� ����� ����������� ��� �������� ���������� �������): ";
	cin >> answersNumber;
	bool isContinue = true;
	do
	{
		ptrQuestionList->push_back(CreateQuestion(answersNumber));
		system("cls");
		cout << "\n������� ������ ��� ���� ������? 1 - ��, 0 - ���\n";
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
	cout << "\n������� ������: ";
	cin.ignore();
	getline(cin, question);
	cout << "\n������� " << answersNumber << " ������(��)\n";
	for (int i = 0; i < answersNumber; i++)
	{
		cout << "����� �" << i + 1 << ": ";
		getline(cin, answers[i]);
	}
	cout << "\n������� ����� ����������� ������: ";
	cin >> correctAnswerOption;
	cout << "\n������� ���������� ������ �� ������: ";
	cin >> pointsPerQuestion;
	return new Question(question, answers, correctAnswerOption, pointsPerQuestion, answersNumber);
}

void Teacher::PrintAvailableTest(list<Test*>** ptrFilteredTestList)
{
	if (!(*ptrFilteredTestList)->size())
	{
		cout << "\n������ ��������� ������ ����\n";
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
		cout << "\n������ ��������� ������ ����\n";
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
	cout << "\n������� ID ����� (1 �������)\n";
	cin >> uniqueID;
	for (auto test : **ptrFilteredTestList)
		if (test->GetID() == uniqueID)
			return test;
	cout << "\n���� �� ������\n";
	return nullptr;
}

void EditTest(Teacher* ptrTeacher, Test* ptrTest)
{
	string password;
	cout << "\n\n";
	cin >> password;
	if (password != ptrTeacher->GetPassword())
	{
		cout << "\n� ������� ��������\n";
		return;
	}
	int value;
	cout << "\n�������� ���� ���������:\n1 - ������� ��������\n2 - ������\n0 - �����\n";
	cin >> value;
	system("cls");
	switch (value)
	{
	case 1:
		cout << "\n������� ����� ������� ��������\n";
		cin >> ptrTest->shortDescription;
		break;
	case 2:
	{
		int i = 1, number;
		for (auto q : *(ptrTest->ptrQuestionList))
			cout << "\n������ � " << i << ": " << q->question;
		cout << "\n\n������� ����� �������: ";
		cin >> number;
		auto iter = ptrTest->ptrQuestionList->begin();
		advance(iter, number - 1);
		cout << "\n��� �� ������ ������� � ��������?\n1 - �������\n2 - �������� ������\n3 - �������� ������� ������";
		cout << "\n4 - �������� ���������� ������� ������\n5 - �������� ���������� ������ �� ������\n0 - �����\n\n";
		cin >> value;
		switch (value)
		{
		case 1:
			delete * iter;
			ptrTest->ptrQuestionList->erase(iter);
			break;
		case 2:
			cout << "\n������� ����� ������: ";
			cin >> (*iter)->question;
			break;
		case 3:
			for (int i = 0; i < (*iter)->numberOfAnswers; i++)
				cout << "\n����� �" << i + 1 << (*iter)->answerOptions[i];
			cout << "\n\n������� ����� ������ ��� ���������: ";
			cin >> number;
			cin.ignore();
			cout << "\n������� ����� �����: ";
			getline(cin, (*iter)->answerOptions[number - 1]);
			break;
		case 4:
			cout << "\n������� ����� ���������� ������� ������: ";
			cin >> (*iter)->correctAnswerOption;
			break;
		case 5:
			cout << "\n������� ����� ���������� ������ �� ������: ";
			cin >> (*iter)->pointsPerQuestion;
			break;
		default:
			return;
		}
	}
	default:
		return;
	}
}

string Teacher::GetPassword()
{
	return User::GetPassword();
}


