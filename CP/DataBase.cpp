#include "DataBase.h"

DataBase::DataBase()
{
	cout << "\n����������� DATABASE " << this;
}

DataBase::DataBase(string dataBaseFilePath)//����� ������� �� ��������� �������
{
	string allTestFilePath, allStudentFilePath, allTeacherFilePath;
	string someTestFilePath, someStudentFilePath, someTeacherFilePath;
	ifstream dataBaseFile, allTestFile, studentFile, teacherFile;
	int size;

	dataBaseFile.open(dataBaseFilePath);
	if (!dataBaseFile.is_open())
		exit(-10);
	getline(dataBaseFile, allTestFilePath);
	getline(dataBaseFile, allStudentFilePath);
	getline(dataBaseFile, allTeacherFilePath);
	dataBaseFile.close();


	allTestFile.open(allTestFilePath);
	allTestFile.seekg(0, ios::end);
	size = allTestFile.tellg();
	allTestFile.seekg(0, ios::beg);

	if (!allTestFile.is_open())
		exit(-10);
	while (allTestFile.tellg() < (size))//-sizeof("\n")))
	{
		getline(allTestFile, someTestFilePath);
		//testFile >> someTestFilePath;
		//testFile.seekg(sizeof("\n"), ios::cur);
		listOfTests.push_back(new Test(someTestFilePath));
	}
	allTestFile.close();


	studentFile.open(allStudentFilePath);
	if (!studentFile.is_open())
		exit(-10);
	while (!studentFile.eof())
	{
		getline(studentFile, someStudentFilePath);
		listOfStudents.push_back(CreateStudentFromFile(someStudentFilePath));
	}
	studentFile.close();


	teacherFile.open(allTeacherFilePath);
	teacherFile.seekg(0, ios::end);
	size = teacherFile.tellg();
	teacherFile.seekg(0, ios::beg);
	if (!teacherFile.is_open())
		exit(-10);
	while (teacherFile.tellg() < (size))
	{
		getline(teacherFile, someTeacherFilePath);
		listOfTeachers.push_back(CreateTeacherFromFile(someTeacherFilePath));
	}
	teacherFile.close();


	cout << "\n����������� DATABASE " << this;
}

DataBase::~DataBase()
{
	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
		delete (*iter);
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
		delete (*iter);
	for (auto iter = listOfTeachers.begin(); iter != listOfTeachers.end(); iter++)
		delete (*iter);
	cout << "\n���������� DATABASE " << this;
}

void DataBase::AuthorizationMenu()
{
	short userChoice;
	Student** currentStudent = nullptr;
	Teacher** currentTeacher = nullptr;
	cout << "\n\n������������ � ������������������ ������� ��������� ������������ �� ��������� �����?\n��� �� ������� �������?\n1 - ������������������\n2 - �����\n0 - ����\n\n";
	cin >> userChoice;
	switch (userChoice)
	{
	case EXIT:
		*currentStudent = nullptr;
		*currentTeacher = nullptr;
		return;
	case REGISTRATION:
		Registration(currentStudent, currentTeacher);//overload
		if (*currentStudent)
		{
			(*currentStudent)->Menu(LoadTestsWithFilter((*currentStudent)->GetCourse(), (*currentStudent)->GetPtrSubjectList()));
		}
		else
		{
			(*currentTeacher)->Menu();
		}
		break;
	case LOGIN:
		while (!Login(currentStudent, currentTeacher))
			cout << "\n������������ �� ������, ���������, ��� �� ����� ������ ������ � ��������� ������������������\n";
		if (*currentStudent)
		{
			(*currentStudent)->Menu(LoadTestsWithFilter((*currentStudent)->GetCourse(), (*currentStudent)->GetPtrSubjectList()));
		}
		else
		{
			(*currentTeacher)->Menu();
		}
		break;
	default:
		*currentStudent = nullptr;
		*currentTeacher = nullptr;
		cout << "\n�������� ����\n";
		return;
	}
}

void DataBase::PrintAllTests()
{
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
	{
		cout << "\n";
		(*iter)->PrintTest();
		cout << "\n";
	}
}

void DataBase::PrintAllStudents()
{
	cout << "\n��� ��������\n";
	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
	{
		(*iter)->PrintInformation();
		cout << "\n";
	}
}

void DataBase::PrintAllTeachers()
{
	cout << "\n��� �������������\n";
	for (auto iter = listOfTeachers.begin(); iter != listOfTeachers.end(); iter++)
	{
		(*iter)->PrintInformation();
		cout << "\n";
	}
}

void DataBase::Registration(Student** userStudent, Teacher** userTeacher)
{
	//create BOOL
	short userChoice;
	string fullName, password;
	int id;
	cout << "\n������� ��� ������������\n1 - �������\t2 - �������������\n";
	cin >> userChoice;
	//check value
	cout << "\n������� ���\n";
	cin >> fullName;
	cout << "\n������� ������\n";
	cin >> password;
	cout << "\n������� ID\n";
	cin >> id;

	if (userChoice == STUDENT)
	{
		string faculty;
		list<string>* ptrList = new list<string>;
		int group, course;//CHECK
		cout << "\n������� ���������\n";
		cin >> faculty;
		cout << "\n������� ������\n";
		cin >> group;
		cout << "\n������� ����\n";
		cin >> course;
		cout << "\n������� ���� ������� �����������\n����� - 0\n";
		while (true)
		{
			string subject;
			cout << "\n�������: ";
			cin >> subject;
			if (subject == "0")
				break;
			ptrList->push_back(subject);
		}
		*userStudent = new Student(fullName, password, faculty, id, group, course, ptrList);
		listOfStudents.push_back(*userStudent);
	}
	if (userChoice == TEACHER)
	{
		string subject;
		list<int>* ptrGroupList = new list<int>;
		cout << "\n������� ������������� ����������: \n";
		cin >> subject;
		cout << "\n������� ������, � ������� ����������\n����� - 0\n";
		while (true)
		{
			int group;
			cout << "\n������: ";
			cin >> group;
			if (!group)
				break;
			ptrGroupList->push_back(group);
		}
		*userTeacher = new Teacher(fullName, password, id, subject, ptrGroupList);
		listOfTeachers.push_back(*userTeacher);
	}
}

bool DataBase::Login(Student** userStudent, Teacher** userTeacher)
{
	int id;
	string password;
	cout << "\n������� ���� ID ";
	cin >> id;
	cout << "\n������� ���� ������ ";
	cin >> password;
	return SearchUser(id, password, userStudent, userTeacher);
}

bool DataBase::SearchUser(int id, string password, Student** userStudent, Teacher** userTeacher)
{
	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
	{
		if ((*iter)->Searching(id, password))
		{
			userStudent = &(*iter);
			cout << "\n������������ ������\n";
			return true;
		}
	}
	for (auto iter = listOfTeachers.begin(); iter != listOfTeachers.end(); iter++)
	{
		if ((*iter)->Searching(id, password))
		{
			userTeacher = &(*iter);
			cout << "\n������������ ������\n";
			return true;
		}
	}
	cout << "\n������������ �� ������\n";
	return false;
}

void DataBase::Unload(string dataBaseFilePath)
{
	string allTestFilePath, allStudentFilePath, allTeacherFilePath;
	string someTestFilePath, someStudentFilePath, someTeacherFilePath;
	ifstream dataBaseFile;
	ofstream allTestFile, studentFile, allTeacherFile;
	int i = 1;
	string currPath;

	dataBaseFile.open(dataBaseFilePath);
	if (!dataBaseFile.is_open())
		exit(-10);
	getline(dataBaseFile, allTestFilePath);
	getline(dataBaseFile, allStudentFilePath);
	getline(dataBaseFile, allTeacherFilePath);
	dataBaseFile.close();

	allTestFile.open(allTestFilePath);
	if (!allTestFile.is_open())
		exit(-10);
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
	{
		currPath = "D:\\OOP\\CP\\������" + to_string(i++) + ".txt";
		allTestFile << currPath << "\n";
		(*iter)->UnloadTest(currPath);
	}

	i = 1;

	allTeacherFile.open(allTeacherFilePath);
	if (!allTeacherFile.is_open())
		exit(-10);
	for (auto iter = listOfTeachers.begin(); iter != listOfTeachers.end(); iter++)
	{
		currPath = "D:\\OOP\\CP\\�������������" + to_string(i++) + ".txt";
		allTeacherFile << currPath << "\n";
		(*iter)->Unload(currPath);
	}
	allTestFile.close();
}

list<Test*>* DataBase::LoadTestsWithFilter(int course, list<string>* ptrSubjList)
{
	list<Test*>* ptrFilterTestList = new list<Test*>;
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
	{
		if (course != (*iter)->GetCourse())
			continue;
		else
		{
			string subject = (*iter)->GetSubject();
			for (auto iter2 = ptrSubjList->begin(); iter2 != ptrSubjList->end(); iter2++)
				if (*iter2 == subject)
				{
					ptrFilterTestList->push_back(*iter);
					break;
				}
		}
	}
	return ptrFilterTestList;
}

Teacher* CreateTeacherFromFile(string filePath)
{
	ifstream file;
	string name, password, subject;
	int id, listSize;
	list<int>* ptrGroupList = new list<int>;
	file.open(filePath);
	if (!file.is_open())
		exit(-9);
	getline(file, name);
	getline(file, password);
	file >> id;
	file.seekg(sizeof("\n"), ios::cur);
	getline(file, subject);
	file >> listSize;
	for (int i = 0; i < listSize; i++)
	{
		int group;
		file >> group;
		ptrGroupList->push_back(group);
	}
	file.close();
	return new Teacher(name, password, id, subject, ptrGroupList);
}

Student* CreateStudentFromFile(string filePath)
{
	ifstream file;
	string name, password, faculty;
	list<string>* ptrList = new list<string>;
	int id, group, course, listSize;
	file.open(filePath);
	if (!file.is_open())
		exit(-9);
	getline(file, name);
	getline(file, password);
	getline(file, faculty);
	file >> id >> group >> course >> listSize;
	file.seekg(sizeof("\n"), ios::cur);
	for (int i = 0; i < listSize; i++)
	{
		string subject;
		getline(file, subject);
		ptrList->push_back(subject);
	}
	file.close();
	return new Student(name, password, faculty, id, group, course, ptrList);
}

