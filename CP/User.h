#pragma once
#include "Test.h"
using namespace std;


class User
{
	string fullName; 
	int id, hashedPassword;
public:
	User();
	User
	(
		string, //name
		int, //password
		int		//id
	);
	virtual	~User();
	virtual void PrintInformation() = 0;
	void PrintUserInformation();
	void Unload(ofstream&);
	bool Searching(int, int);
	int GetID();
	string GetName();
	int GetHashedPassword();
};

