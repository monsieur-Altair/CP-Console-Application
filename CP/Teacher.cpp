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

void Teacher::Menu(list<Test*>* ptrFilterdTestList, list<Student*>* ptrFilteredStudentList)
{
	//list<Test*>* ptrFilteredTestList;
	while (true)
	{
		short choice;
		system("cls");
		cout << "\n�� ����� ��� �������������\n�������� �������� ��������:\n1 - ������� ����";
		cout << "\n2 - ������� ����\n3 - ����������� ���������� � ����\n4 - ������������� ���������� ����";
		cout << "\n5 - ����������� ��������� �����\n6 - ����������� ��������� ����� �����";
		cout << "\n7 - ����������� ����������� ��������\n0 - �����\n\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case CREATE_TEST:
		{

			break;
		}
		case DELETE_TEST:
			break;
		case VIEW_OWN_INF:
			break;
		case EDIT_TEST:
			break;
		case VIEW_ALL_AVAIBLE_TEST:
			break;
		case VIEW_ALL_STUDENTS:
			break;
		case VIEW_ONE_STUDENT:
			break;
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

