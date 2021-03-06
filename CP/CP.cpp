#include "DataBase.h"
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
	const string dataBaseFilePath = "D:\\OOP\\CP\\DataBaseFile.txt";
	DataBase db0(dataBaseFilePath);
#ifdef DEBUG
	db0.PrintAllTests();
	db0.PrintAllStudents();
	db0.PrintAllTeachers();
	system("pause");
#endif // DEBUG
	db0.AuthorizationMenu();
	db0.Unload(dataBaseFilePath);
	return 0;
}

//2069 строк 07.05