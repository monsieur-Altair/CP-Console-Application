#pragma once
#include "Test.h"
using namespace std;


class User
{
	string fullName; 
	int id;
	float hashedPassword;
	static int entityCount;
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
	bool Searching(int, float);
	int GetID();
	string GetName();
	//float GetHashedPassword();
	static int GetEntityCount();
};

