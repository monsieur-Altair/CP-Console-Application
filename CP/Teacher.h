#pragma once
#include "User.h"

class Teacher : public User
{
    string subject;
    list<int>* ptrGroupList;//������ ����� �������, �� ������ ������ 
public:
    Teacher();
    Teacher
    (
        string,     //name
        string,     //password
        int,        //id
        string,     //subject
        list<int>*  //list of groups
    );

    ~Teacher();
    void Menu();
    void PrintInformation() override;
    void Unload(string);
};

