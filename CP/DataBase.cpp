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
	dataBaseFile.exceptions(ifstream::badbit | ifstream::failbit);
	allTestFile.exceptions(ifstream::badbit | ifstream::failbit);
	studentFile.exceptions(ifstream::badbit | ifstream::failbit);
	teacherFile.exceptions(ifstream::badbit | ifstream::failbit);
	int size;

	try
	{
		dataBaseFile.open(dataBaseFilePath);
		getline(dataBaseFile, allTestFilePath);
		getline(dataBaseFile, allStudentFilePath);
		getline(dataBaseFile, allTeacherFilePath);
		dataBaseFile.close();
	}
	catch (const ifstream::failure&)
	{
		cout << "\n������ �������� �����: " << dataBaseFilePath << "\n������������� ��������� ������� ����� � ��� ����\n";
		exit(-1);
	}

	try
	{
		allTestFile.open(allTestFilePath);
		allTestFile.seekg(0, ios::end);
		size = allTestFile.tellg();
		allTestFile.seekg(0, ios::beg);

		while (allTestFile.tellg() < (size))
		{
			try
			{
				getline(allTestFile, someTestFilePath);
				listOfTests.push_back(new Test(someTestFilePath));
			}
			catch (const ifstream::failure&)
			{
				cout << "\n������ �������� �����: " << someTestFilePath;
				cout << "\n������������� ��������� ������� ����� � ��� ����\n���� �� ��� ��������\n";
			}
			catch (const runtime_error& ex)
			{
				cout << ex.what();
			}
		}

		allTestFile.close();
	}
	catch (const ifstream::failure&)
	{
		cout << "\n������ �������� �����: " << allTestFilePath;
		cout << "\n������������� ��������� ������� ����� � ��� ����\n����� �� ���� ���������\n";
	}

	try
	{
		studentFile.open(allStudentFilePath);

		studentFile.seekg(0, ios::end);
		size = studentFile.tellg();
		studentFile.seekg(0, ios::beg);

		while (studentFile.tellg() < size)
		{
			try
			{
				getline(studentFile, someStudentFilePath);
				listOfStudents.push_back(CreateStudentFromFile(someStudentFilePath));
			}
			catch (const ifstream::failure&)
			{
				cout << "\n������ �������� �����: " << someStudentFilePath;
				cout << "\n������������� ��������� ������� ����� � ��� ����\n������� �� ��� ��������\n";
			}
			catch (const runtime_error& ex)
			{
				cout<<ex.what();
			}
		}
		studentFile.close();
	}
	catch (const ifstream::failure&)
	{
		cout << "\n������ �������� �����: " << allStudentFilePath;
		cout << "\n������������� ��������� ������� ����� � ��� ����\n�������� �� ���� ���������\n";
	}


	try
	{
		teacherFile.open(allTeacherFilePath);
		if (!teacherFile.is_open())
			exit(-10);
		teacherFile.seekg(0, ios::end);
		size = teacherFile.tellg();
		teacherFile.seekg(0, ios::beg);

		while (teacherFile.tellg() < (size))
		{
			try
			{
				getline(teacherFile, someTeacherFilePath);
				listOfTeachers.push_back(CreateTeacherFromFile(someTeacherFilePath));
			}
			catch (const ifstream::failure&)
			{
				cout << "\n������ �������� �����: " << someStudentFilePath;
				cout << "\n������������� ��������� ������� ����� � ��� ����\n������������� �� ��� ��������\n";
			}
			catch (const runtime_error& ex)
			{
				cout << ex.what();
			}
		}

		teacherFile.close();
	}
	catch (const ifstream::failure&)
	{
		cout << "\n������ �������� �����: " << allTeacherFilePath;
		cout << "\n������������� ��������� ������� ����� � ��� ����\n������������� �� ���� ���������\n";
	}

#ifdef DEBUG
	cout << "\n����������� DATABASE " << this;
#endif // DEBUG

}

DataBase::~DataBase()
{
	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
		delete (*iter);
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
		delete (*iter);
	for (auto iter = listOfTeachers.begin(); iter != listOfTeachers.end(); iter++)
		delete (*iter);

#ifdef DEBUG
	cout << "\n���������� DATABASE " << this;
#endif // DEBUG
}

//void DataBase::AuthorizationMenu()
//{
//	short userChoice;
//	Student* currentStudent = nullptr;
//	Teacher* currentTeacher = nullptr;
//	system("cls");
//	cout << "\n\n������������ � ������������������ ������� ��������� ������������ �� ��������� �����?\n��� �� ������� �������?\n1 - ������������������\n2 - �����\n0 - ����\n\n";
//	cin >> userChoice;
//	switch (userChoice)
//	{
//	case EXIT:
//		currentStudent = nullptr;
//		currentTeacher = nullptr;
//		return;
//	case REGISTRATION:
//		Registration(&currentStudent, &currentTeacher);
//		if (currentStudent)
//			//��������� ����� � ���� �������� ������ ������;
//			currentStudent->Menu
//			(
//				LoadTestsWithFilter(currentStudent->GetCourse(), currentStudent->GetPtrSubjectList())
//			);
//		else
//		{
//			string teacherSubject = currentTeacher->GetSubject();
//			list<Test*>* ptrFilteredTest = LoadTestsWithFilter(teacherSubject);
//			currentTeacher->Menu(&ptrFilteredTest, LoadStudentsFilter(teacherSubject, currentTeacher->ptrGetGroupList()));
//			this->listOfTests.splice(listOfTests.end(), *ptrFilteredTest);//������� ���������� ������������� ������ ��������� � ��
//		}
//		break;
//	case LOGIN:
//		while (!Login(&currentStudent, &currentTeacher))
//			cout << "\n������������ �� ������, ���������, ��� �� ����� ������ ������ � ��������� ������������������\n";
//		if (currentStudent)
//			(currentStudent)->Menu(LoadTestsWithFilter(currentStudent->GetCourse(), currentStudent->GetPtrSubjectList()));
//		else
//		{
//			string teacherSubject = currentTeacher->GetSubject();
//			list<Test*>* ptrFilteredTest = LoadTestsWithFilter(teacherSubject);
//			currentTeacher->Menu(&ptrFilteredTest, LoadStudentsFilter(teacherSubject, currentTeacher->ptrGetGroupList()));
//			this->listOfTests.splice(listOfTests.end(), *ptrFilteredTest);//������� ���������� ������������� ������ ��������� � ��
//		}
//		break;
//	default:
//		currentStudent = nullptr;
//		currentTeacher = nullptr;
//		cout << "\n�������� ����\n";
//		return;
//	}
//}

void DataBase::AuthorizationMenu()
{
	short userChoice, userType;
	system("cls");
	cout << "\n\n������������ � ������������������ ������� ��������� ������������ �� ��������� �����!";
	cout << "\n��� �� ������� �������?\n1 - ������������������\n2 - �����\n0 - ����\n";
	cin >> userChoice;
	Check(&userChoice, 0, 2);
	if (!userChoice)
		return;
	cout << "\n�������� ��� ������������:\n1 - �������\n2 - �������������\n";
	Check(&userType, 0, 1);
	system("cls");

	switch (userType)
	{
	case STUDENT:
	{
		Student* ptrCurrentStudent = nullptr;
		if (userChoice == REGISTRATION)
			ptrCurrentStudent = Registration(ptrCurrentStudent);
		else if (userChoice == LOGIN)
			ptrCurrentStudent = Login(ptrCurrentStudent);
		if(ptrCurrentStudent)
			ptrCurrentStudent->Menu(LoadTestsWithFilter(ptrCurrentStudent->GetCourse(), ptrCurrentStudent->GetPtrSubjectList()));

		ptrCurrentStudent = nullptr;
		break;
	}
	case TEACHER:
	{
		Teacher* ptrCurrentTeacher = nullptr;
		if (userChoice == REGISTRATION)
			ptrCurrentTeacher = Registration(ptrCurrentTeacher);
		else if (userChoice == LOGIN)
			ptrCurrentTeacher = Login(ptrCurrentTeacher);
		if (ptrCurrentTeacher)
		{
			string teacherSubject = ptrCurrentTeacher->GetSubject();
			//shared_ptr<list<Test*>> ptrFilteredTest(LoadTestsWithFilter(teacherSubject));
			list<Test*>* ptrFilteredTest = LoadTestsWithFilter(teacherSubject);
			ptrCurrentTeacher->Menu(&ptrFilteredTest, LoadStudentsFilter(teacherSubject, ptrCurrentTeacher->ptrGetGroupList()));
			if (ptrFilteredTest->size())
				this->listOfTests.splice(listOfTests.end(), *ptrFilteredTest);//������� ���������� ������������� ������ ��������� � ��
			delete ptrFilteredTest;//smart pointer
		}
		ptrCurrentTeacher = nullptr;
		break;
	}
	default:
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

//void DataBase::Registration(Student** userStudent, Teacher** userTeacher)
//{
//	//create BOOL
//	short userChoice;
//	string fullName, password;
//	int id;
//	cout << "\n������� ��� ������������\n1 - �������\t2 - �������������\n";
//	cin >> userChoice;
//	//check value
//	cout << "\n������� ���\n";
//	cin >> fullName;
//	cout << "\n������� ������\n";
//	cin >> password;
//	cout << "\n������� ID\n";
//	cin >> id;
//
//	if (userChoice == STUDENT)
//	{
//		string faculty;
//		list<string>* ptrList = new list<string>;
//		list<SolvedTest*>* ptrSolvedTestList = new list<SolvedTest*>;
//		int group, course;//CHECK
//		cout << "\n������� ���������\n";
//		cin >> faculty;
//		cout << "\n������� ������\n";
//		cin >> group;
//		cout << "\n������� ����\n";
//		cin >> course;
//		cout << "\n������� ���� ������� �����������\n����� - 0\n";
//		while (true)
//		{
//			string subject;
//			cout << "\n�������: ";
//			cin >> subject;
//			if (subject == "0")
//				break;
//			ptrList->push_back(subject);
//		}
//		*userStudent = new Student(fullName, password, faculty, id, group, course, ptrList, ptrSolvedTestList);
//		listOfStudents.push_back(*userStudent);
//	}
//	if (userChoice == TEACHER)
//	{
//		string subject;
//		list<int>* ptrGroupList = new list<int>;
//		cout << "\n������� ������������� ����������: \n";
//		cin >> subject;
//		cout << "\n������� ������, � ������� ����������\n����� - 0\n";
//		while (true)
//		{
//			int group;
//			cout << "\n������: ";
//			cin >> group;
//			if (!group)
//				break;
//			ptrGroupList->push_back(group);
//		}
//		*userTeacher = new Teacher(fullName, password, id, subject, ptrGroupList);
//		listOfTeachers.push_back(*userTeacher);
//	}
//}

Student* DataBase::Registration(Student* ptrStudent)
{
	hash<string> hashFunction;
	string fullName,password;
	int id;
	hash<int> hashFunctionInt;
	id = hashFunctionInt(User::GetEntityCount());
	cout << "\n��� ���������� ID = " << id << " ����������, ��������� ���!";

	cout << "\n������� ���\n";
	cin.ignore();
	getline(cin, fullName);
	cout << "\n������� ������\n";
	getline(cin, password);
	int  hashedPassword = hashFunction(password);

	string faculty;
	shared_ptr<list<string>> ptrList(new list<string>);
	list<SolvedTest*>* ptrSolvedTestList = new list<SolvedTest*>;
	int group, course;
	cout << "\n������� ���������\n";
	cin.ignore();
	getline(cin, faculty);
	cout << "\n������� ������\n";
	cin >> group;
	Check(&group, 100000, 999999);
	cout << "\n������� ����\n";
	cin >> course;
	Check(&course, 1, 5);
	cout << "\n������� ���� ������� �����������\n����� - 0\n";
	cin.ignore();
	while (true)
	{
		string subject;
		cout << "\n�������: ";
		getline(cin, subject);
		if (subject == "0")
			break;
		ptrList->push_back(subject);
	}
	ptrStudent = new Student(fullName, hashedPassword, faculty, id, group, course, ptrList, ptrSolvedTestList);
	listOfStudents.push_back(ptrStudent);
	return ptrStudent;
}

Teacher* DataBase::Registration(Teacher* ptrTeacher)
{
	string fullName, password;
	int id;
	hash<int> hashFunctionInt;
	cin.ignore();
	id = hashFunctionInt(User::GetEntityCount());
	cout << "\n��� ���������� ID = " << id << " ����������, ��������� ���!";
	cout << "\n������� ���\n";
	getline(cin, fullName);
	cout << "\n������� ������\n";
	getline(cin, password);

	hash<string> hashFunction;
	int  hashedPassword = hashFunction(password);

	string subject;
	shared_ptr<list<int>> ptrGroupList ( new list<int>);
	cout << "\n������� ������������� ����������: \n";
	cin.ignore();
	getline(cin, subject);
	cout << "\n������� ������, � ������� ����������\n����� - 0\n";
	while (true)
	{
		int group;
		cout << "\n������: ";
		cin >> group;
		Check(&group, 0, 999999);
		if (!group)
			break;
		ptrGroupList->push_back(group);
	}
	ptrTeacher = new Teacher(fullName, hashedPassword, id, subject, ptrGroupList);
	listOfTeachers.push_back(ptrTeacher);
	return ptrTeacher;
}

//bool DataBase::Login(Student** userStudent, Teacher** userTeacher)
//{
//	int id;
//	string password;
//	cout << "\n������� ���� ID ";
//	cin >> id;
//	cout << "\n������� ���� ������ ";
//	cin >> password;
//	return SearchUser(id, password, userStudent, userTeacher);
//}
//
//bool DataBase::SearchUser(int id, string password, Student** userStudent, Teacher** userTeacher)
//{
//	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
//	{
//		if ((*iter)->Searching(id, password))
//		{
//			*userStudent = (*iter);
//			cout << "\n������������ ������\n";
//			return true;
//		}
//	}
//	for (auto iter = listOfTeachers.begin(); iter != listOfTeachers.end(); iter++)
//	{
//		if ((*iter)->Searching(id, password))
//		{
//			*userTeacher = (*iter);
//			cout << "\n������������ ������\n";
//			return true;
//		}
//	}
//	cout << "\n������������ �� ������\n";
//	return false;
//}

Student* DataBase::Login(Student* userStudent)
{
	int id;
	string password;
	hash<string> hashFunction;
	cout << "\n������� ���� ID ";
	cin >> id;
	Check(&id, 0, 999999999999);
	cout << "\n������� ���� ������ ";
	cin >> password;
	int hashedPassword = hashFunction(password);
	for (auto ptrStudent : listOfStudents)
	{
		if (ptrStudent->Searching(id, hashedPassword))
		{
			cout << "\n������������ ������\n";
			return ptrStudent;
		}
	}
	cout << "\n������������ �� ������\n";
	return nullptr;
}

Teacher* DataBase::Login(Teacher* userTeacher)
{
	int id;
	string password;
	hash<string> hashFunction;
	cout << "\n������� ���� ID ";
	cin >> id;
	Check(&id, 0, 99999999999);
	cout << "\n������� ���� ������ ";
	cin >> password;
	int hashedPassword = hashFunction(password);
	for (auto ptrTeacher : listOfTeachers)
	{
		if (ptrTeacher->Searching(id, hashedPassword))
		{
			cout << "\n������������ ������\n";
			return ptrTeacher;
		}
	}
	cout << "\n������������ �� ������\n";
	return nullptr;
}

void DataBase::Unload(string dataBaseFilePath)
{
	string allTestFilePath, allStudentFilePath, allTeacherFilePath;
	string someTestFilePath, someStudentFilePath, someTeacherFilePath;
	ifstream dataBaseFile;
	ofstream allTestFile, allStudentFile, allTeacherFile;
	int i = 1;
	string currPath;

	dataBaseFile.exceptions(ifstream::badbit | ifstream::failbit);

	try
	{
		dataBaseFile.open(dataBaseFilePath);
		getline(dataBaseFile, allTestFilePath);
		getline(dataBaseFile, allStudentFilePath);
		getline(dataBaseFile, allTeacherFilePath);
		dataBaseFile.close();
	}
	catch (const ifstream::failure&)
	{
		cout << "\n������ �������� �����: " << dataBaseFilePath;
		cout << "\n������������� ��������� ������� ����� � ��� ����\n���� �� ��� ��������\n";
	}

	allTestFile.open(allTestFilePath);
	if (!allTestFile.is_open())
		exit(-10);
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
	{
		currPath = "D:\\OOP\\CP\\����" + to_string(i++) + ".txt";
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
	allTeacherFile.close();

	i = 1;

	allStudentFile.open(allStudentFilePath);
	if (!allStudentFile.is_open())
		exit(-10);
	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
	{
		currPath = "D:\\OOP\\CP\\�������" + to_string(i++) + ".txt";
		allStudentFile << currPath << "\n";
		(*iter)->Unload(currPath);
	}
	allStudentFile.close();
}

//list<Test*>* DataBase::LoadTestsWithFilter(int course, list<string>* ptrSubjList)
//{
//	list<Test*>* ptrFilterTestList = new list<Test*>;
//	for (auto someTestIter = listOfTests.begin(); someTestIter != listOfTests.end(); someTestIter++)
//	{
//		if (course != (*someTestIter)->GetCourse())
//			continue;
//		else
//		{
//			string subject = (*someTestIter)->GetSubject();
//			for (auto someSubjectIter = ptrSubjList->begin(); someSubjectIter != ptrSubjList->end(); someSubjectIter++)
//				if (*someSubjectIter == subject)
//				{
//					ptrFilterTestList->push_back(*someTestIter);
//					break;
//				}
//		}
//	}
//	return ptrFilterTestList;
//}

list<Test*>* DataBase::LoadTestsWithFilter(int course, shared_ptr<list<string>> ptrSubjList)
{
	list<Test*>* ptrFilterTestList = new list<Test*>;
	for (auto somePtrTestIter = listOfTests.begin(); somePtrTestIter != listOfTests.end(); somePtrTestIter++)
	{
		if (course != (*somePtrTestIter)->GetCourse())
			continue;
		else
		{
			string subject = (*somePtrTestIter)->GetSubject();
			for (auto someSubjectIter = ptrSubjList->begin(); someSubjectIter != ptrSubjList->end(); someSubjectIter++)
				if (*someSubjectIter == subject)
				{
					ptrFilterTestList->push_back(*somePtrTestIter);
					break;
				}
		}
	}
	return ptrFilterTestList;
}

list<Test*>* DataBase::LoadTestsWithFilter(string subject)
{
	list<Test*>* ptrFilteredTestList = new list<Test*>;
	for (auto iter = listOfTests.begin(); iter != listOfTests.end(); iter++)
		if ((*iter)->GetSubject() == subject)
		{
			auto iter1 = iter;
			advance(iter, -1);
			ptrFilteredTestList->splice(ptrFilteredTestList->end(), listOfTests, iter1);
		}
	return ptrFilteredTestList;
}

list<Student*>* DataBase::LoadStudentsFilter(string subject, shared_ptr<list<int>> ptrGroupList)
{
	bool isFindGroup;
	bool isFindSubject;
	list<Student*>* ptrFilteredStudentList = new list<Student*>;
	for (auto iter = listOfStudents.begin(); iter != listOfStudents.end(); iter++)
	{
		isFindGroup = false;
		isFindSubject = false;

		int group = (*iter)->GetGroup();
		for (auto gr : *ptrGroupList)
			if (group == gr)
			{
				isFindGroup = true;
				break;
			}
		if (!isFindGroup)
			continue;

		shared_ptr<list<string>> ptrSubjectList = (*iter)->GetPtrSubjectList();
		for (auto subj : *ptrSubjectList)
			if (subject == subj)
			{
				isFindSubject = true;
				break;
			}
		if (!isFindSubject)
			continue;

		ptrFilteredStudentList->push_back((*iter));
	}

	return ptrFilteredStudentList;
}

Teacher* CreateTeacherFromFile(string filePath)
{
	ifstream file;
	string name, subject;
	int id, listSize, hashedPassword;
	shared_ptr<list<int>> ptrGroupList (new list<int>);
	file.open(filePath);
	if (!file.is_open())
		exit(-9);
	getline(file, name);
	//getline(file, hashedPassword);
	file >> hashedPassword;
	file.seekg(sizeof("\n"), ios::cur);
	file >> id;
	file.seekg(sizeof("\n"), ios::cur);
	getline(file, subject);
	file >> listSize;
	if(listSize<0)
		throw runtime_error("\n������������ ������ ��� ����������\n");

	for (int i = 0; i < listSize; i++)
	{
		int group;
		file >> group;
		if(group<0)
			throw runtime_error("\n������������ ������ ��� ����������\n");

		ptrGroupList->push_back(group);
	}
	file.close();
	return new Teacher(name, hashedPassword, id, subject, ptrGroupList);
}

Student* CreateStudentFromFile(string filePath)
{
	ifstream file;
	string name, faculty;
	shared_ptr<list<string>> ptrSubjectList(new list<string>);
	int id, group, course, listSize, hashedPassword;

	string shortDiscription;
	list<SolvedTest*>* ptrSolvedTestList = new list<SolvedTest*>;
	int uniqueID, maxPoints, receivedPoints;

	file.open(filePath);
	getline(file, name);
	file >> hashedPassword;
	file.seekg(sizeof("\n"), ios::cur);
	file >> id;
	file.seekg(sizeof("\n"), ios::cur);
	getline(file, faculty);
	file >> group >> course >> listSize;
	file.seekg(sizeof("\n"), ios::cur);
	for (int i = 0; i < listSize; i++)
	{
		string subject;
		getline(file, subject);
		ptrSubjectList->push_back(subject);
	}
	file >> listSize;

	if (id < 0 || group < 0 || course <= 0 || listSize <= 0)
		throw runtime_error("\n������������ ������ ��� ����������\n");

	for (int i = 0; i < listSize; i++)
	{
		string subject;
		shared_ptr<list<int>> answers (new list<int>);
		file.seekg(sizeof("\n"), ios::cur);
		//getline(file, uniqueID);
		file >> uniqueID;
		file.seekg(sizeof("\n"), ios::cur);
		getline(file, subject);
		getline(file, shortDiscription);
		file >> receivedPoints >> maxPoints;
		file.seekg(sizeof("\n"), ios::cur);
		int sizeAnswers, oneAnswer;
		file >> sizeAnswers;
		for (int j = 0; j < sizeAnswers; j++)
		{
			file >> oneAnswer;
			answers->push_back(oneAnswer);
			if (oneAnswer < 0)
				throw runtime_error("\n������������ ������ ��� ����������\n");
		}
		if (receivedPoints < 0 || maxPoints < 0)
			throw runtime_error("\n������������ ������ ��� ����������\n");

		ptrSolvedTestList->push_back(new SolvedTest(answers, shortDiscription, uniqueID, subject, receivedPoints, maxPoints));
	}
	file.close();

	return new Student(name, hashedPassword, faculty, id, group, course, ptrSubjectList, ptrSolvedTestList);
}

