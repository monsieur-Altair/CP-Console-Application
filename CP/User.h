#pragma once
#include "Test.h"
using namespace std;


class User
{
	string fullName, password;
	int id;
public:
	User();
	User
	(
		string, //name
		string, //password
		int		//id
	);
	virtual	~User();
	//virtual void Menu() = 0;
	virtual void PrintInformation() = 0;
	void PrintUserInformation();
	void Unload(ofstream&);
	bool Searching(int, string);
	int GetID();
	string GetPassword();
};

