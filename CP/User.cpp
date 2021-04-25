#include "User.h"

User::User()
{
	this->fullName = "���";
	this->hashedPassword = 0;
	this->id = 0;
	cout << "\n����������� USER " << this;
}

User::User(string name, int hashedPassword, int id)
{
	this->fullName = name;
	this->hashedPassword = hashedPassword;
	this->id = id;
	cout << "\n����������� USER " << this;
}

User::~User()
{
	cout << "\n���������� USER " << this;
}

void User::PrintUserInformation()
{
	cout << "\t" << fullName << "\t" << hashedPassword << "\t" << id;
}

void User::Unload(ofstream& file)
{
	file << this->fullName << "\n" << this->hashedPassword << "\n" << this->id << "\n";
}

bool User::Searching(int id, int hashedPassword)
{
	return ((this->id == id) && (this->hashedPassword == hashedPassword));
}

int User::GetID()
{
	return this->id;
}

string User::GetName()
{
	return this->fullName;
}

int User::GetHashedPassword()
{
	return this->hashedPassword;
}

