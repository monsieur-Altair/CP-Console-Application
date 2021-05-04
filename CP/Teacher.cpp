#include "Teacher.h"


Teacher::Teacher() :User()
{
	this->subject = "";
	this->ptrGroupList = nullptr;
	cout << "\n����������� TEACHER " << this;
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
	cout << "\n����������� TEACHER " << this;
}

Teacher::~Teacher()
{
	//if(this)
	//delete ptrGroupList;
	cout << "\n���������� TEACHER " << this;
}

void Teacher::Menu(list<Test*>** ptrFilteredTestList, list<Student*>* ptrFilteredStudentList)
{
	while (true)
	{
		short choice;
		system("cls");
		cout << "\n�� ����� ��� �������������\n�������� �������� ��������:\n1 - ������� ����";
		cout << "\n2 - ������� ����\n3 - ����������� ���������� � ����\n4 - ������������� ���������� ����";
		cout << "\n5 - ����������� ��� ��������� �����\n6 - ����������� ���� ��������� ����� �����";
		cout << "\n7 - ����������� ����������� ��������\n8 - ����������� ������� ������ �����";
		cout << "\n9 - ������������� ��������� �� ������� (�� �����������)\n10 - ������������� ��������� �� ���\n0 - �����\n\n";
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
			//cout << "\n������� ID ����� (1 �������)\n";
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
			cout << "\n������� ����� ����� (1 �������)\n";
			cin >> number;
			auto iter = (*ptrFilteredTestList)->begin();
			advance(iter, number - 1);
			delete* iter;
			(*ptrFilteredTestList)->erase(iter);
			break;
		}
		case VIEW_OWN_INF:
			cout << "\t���\t\t\t\t������\t\tID\t\t�������\t������\n";
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
						cout << "\n\n���� ���� ������ � ��� �������� �������\n";
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
			//cout << "\n������� ID ��������: ";
			//cin >> ID;
			//Check(&ID, 1, 100000000);
			//for (auto ptrStudent : *ptrFilteredStudentList)
			//	if (ptrStudent->GetID() == ID)
			//	{
			//		cout << "\n�������� ����� �������� " << ptrStudent->GetName();
			//		ptrStudent->PrintAllSolvedTestBriefly();
			//		break;
			//	}
			PrintOwnStudents(ptrFilteredStudentList);
			int number;
			cout << "\n������� ����� ��������: ";
			cin >> number;
			Check(&number, 1, ptrFilteredStudentList->size());
			auto ptrStudentIter = ptrFilteredStudentList->begin();
			advance(ptrStudentIter, number - 1);
			cout << "\n�������� ����� �������� " << (*ptrStudentIter)->GetName()<<"\n";
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
				cout << "\n������ ������������\n";
			}
			else
				cout << "\n������ ����\n";
			break;
		case SORT_STUDENT_ALPHABETICAL:
			if (ptrFilteredStudentList->size())
			{
				ptrFilteredStudentList->sort(sort::SortStudentAlphabetic);
				cout << "\n������ ������������\n";
			}
			else
				cout << "\n������ ����\n";
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
	//cout << "\n������� ���������� ID �����: ";
	cin.ignore();
	//getline(cin, uniqueID);
	uniqueID = hashFunction(Test::GetEntityCount());
	cout << "\n������� ������� �������� �����: ";
	getline(cin, shortDiscription);
	cout << "\n������� ����: ";
	cin >> course;
	Check(&course, 1, 6);
	cout << "\n������� ���������� ������� �� ������ (��� ������� ������� ����� ����������� ��� �������� ���������� �������): ";
	cin >> answersNumber;
	Check(&answersNumber, 1, 5);
	int isContinue = 1;
	do
	{
		ptrQuestionList->push_back(CreateQuestion(answersNumber));
		system("cls");
		cout << "\n������� ������ ��� ���� ������? 1 - ��, 0 - ���\n";
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
	Check(&correctAnswerOption, 1, answersNumber);
	cout << "\n������� ���������� ������ �� ������: ";
	cin >> pointsPerQuestion;
	Check(&pointsPerQuestion, 1, 1000);
	return new Question(question, answers, correctAnswerOption, pointsPerQuestion, answersNumber);
}

bool Teacher::PrintAvailableTest(list<Test*>** ptrFilteredTestList)
{
	if (!(*ptrFilteredTestList)->size())
	{
		cout << "\n������ ��������� ������ ����\n";
		return false;
	}
	int i = 1;
	cout << "�\tID\t\t�������\t����\t������� ��������\n";
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
		cout << "\n������ ��������� ����\n";
		return;
	}
	int i = 1;
	cout << "�\t���\t\t\t\t������\t\tID\t\t�-���\t����\t������\t��������\n";
	for (auto ptrStudent : *ptrFilteredStudentList)
	{
		cout << "\n" << i++ << ") ";
		ptrStudent->PrintInformation();
	}
}

Test* Teacher::SearchAvailableTest(list<Test*>** ptrFilteredTestList)
{
	//string uniqueID;
	//cout << "\n������� ID ����� (1 �������)\n";
	//cin >> uniqueID;
	//for (auto test : **ptrFilteredTestList)
	//	if (test->GetID() == uniqueID)
	//		return test;
	//cout << "\n���� �� ������\n";
	int number;
	cout << "\n������� ����� ����� (1 �������)\n";
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
		cout << "\n������� ��� ������: ";
		cin >> password;
		int hashedPassword = hashFunction(password);
		if (hashedPassword != ptrTeacher->GetHashedPassword())
		{
			cout << "\n� ������� ��������\n";
			return;
		}
		int value;
		cout << "\n�������� ���� ���������:\n1 - ������� ��������\n2 - ������\n0 - �����\n";
		cin >> value;
		Check(&value, 0, 2);
		system("cls");
		switch (value)
		{
		case 1:
			cout << "\n������� ����� ������� ��������\n";
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
					cout << "\n������ � " << i++ << ": " << q->question;
				cout << "\n\n������� ����� ������� (0 - �����): ";
				cin >> number;
				Check(&number, 0, ptrTest->ptrQuestionList->size());
				if (!number)
					break;
				auto iter = ptrTest->ptrQuestionList->begin();
				advance(iter, number - 1);
				//do
				//{
				//	system("cls");
				//	cout << "\n��� �� ������ ������� � ��������?\n1 - �������\n2 - �������� ������\n3 - �������� ������� ������";
				//	cout << "\n4 - �������� ���������� ������� ������\n5 - �������� ���������� ������ �� ������\n6 - �������� ����� ������\n0 - �����\n\n";
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
				//		cout << "\n������� ����� ������: ";
				//		cin.ignore();
				//		getline(cin, (*iter)->question);
				//		break;
				//	case Teacher::CHANGE_ANSWER_OPTION:
				//		for (int i = 0; i < (*iter)->numberOfAnswers; i++)
				//			cout << "\n����� �" << i + 1 << " :" << (*iter)->answerOptions[i];
				//		cout << "\n\n������� ����� ������ ��� ���������: ";
				//		cin >> number;
				//		cin.ignore();
				//		cout << "\n������� ����� �����: ";
				//		getline(cin, (*iter)->answerOptions[number - 1]);
				//		break;
				//	case Teacher::CHANGE_CORRECT_ANSWER:
				//		cout << "\n" << (*iter)->question;
				//		for (int i = 0; i < (*iter)->numberOfAnswers; i++)
				//			cout << "\n����� �" << i + 1 << " :" << (*iter)->answerOptions[i];
				//		cout << "\n������� ����� ���������� ������� ������: ";
				//		cin >> (*iter)->correctAnswerOption;
				//		break;
				//	case Teacher::CHANGE_POINTS:
				//		cout << "\n������� ����� ���������� ������ �� ������: ";
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
				cout << "\n��� �� ������ ������� � ��������?\n1 - �������\n2 - �������� ������\n3 - �������� ������� ������";
				cout << "\n4 - �������� ���������� ������� ������\n5 - �������� ���������� ������ �� ������\n6 - �������� ����� ������\n0 - �����\n\n";
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
					cout << "\n������� ����� ������: ";
					cin.ignore();
					getline(cin, (*iter)->question);
					break;
				case Teacher::CHANGE_ANSWER_OPTION:
					for (int i = 0; i < (*iter)->numberOfAnswers; i++)
						cout << "\n����� �" << i + 1 << " :" << (*iter)->answerOptions[i];
					cout << "\n\n������� ����� ������ ��� ���������: ";
					cin >> number;
					cin.ignore();
					cout << "\n������� ����� �����: ";
					getline(cin, (*iter)->answerOptions[number - 1]);
					break;
				case Teacher::CHANGE_CORRECT_ANSWER:
					cout << "\n" << (*iter)->question;
					for (int i = 0; i < (*iter)->numberOfAnswers; i++)
						cout << "\n����� �" << i + 1 << " :" << (*iter)->answerOptions[i];
					cout << "\n������� ����� ���������� ������� ������: ";
					cin >> (*iter)->correctAnswerOption;
					break;
				case Teacher::CHANGE_POINTS:
					cout << "\n������� ����� ���������� ������ �� ������: ";
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