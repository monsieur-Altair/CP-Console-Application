#include "User.h"

User::User()
{
	this->fullName = "имя";
	this->password = "пароль";
	this->id = 0;
	cout << "\nКонструктор USER " << this;
}

User::User(string name, string password, int id)
{
	this->fullName = name;
	this->password = password;
	this->id = id;
	cout << "\nКонструктор USER " << this;
}

User::~User()
{
	cout << "\nДеструктор USER " << this;
}

void User::PrintUserInformation()
{
	cout << "\t" << fullName << "\t" << password << "\t" << id;
}

void User::Unload(ofstream& file)
{
	file << this->fullName << "\n" << this->password << "\n" << this->id << "\n";
}

bool User::Searching(int id, string password)
{
	return ((this->id == id) && (this->password == password));
}

int User::GetID()
{
	return this->id;
}

string User::GetPassword()
{
	return this->password;
}

