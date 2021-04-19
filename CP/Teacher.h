#pragma once
#include "Student.h"

class Teacher : public User
{
    string subject;
    list<int>* ptrGroupList;//список групп препода, мб список спецух 
    enum MenuChoice
    {
        CREATE_TEST = 1,
        DELETE_TEST,
        VIEW_OWN_INF,
        EDIT_TEST,
        VIEW_ALL_AVAIBLE_TEST,
        VIEW_ALL_STUDENTS,
        VIEW_ONE_STUDENT,
        VIEW_ONE_TEST_FULLY
    };
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
    void Menu(list<Test*>**,list<Student*>*);
    void PrintInformation() override;
    void Unload(string);

    list<int>* ptrGetGroupList();
    Test* CreateTest();
    Question* CreateQuestion(int);
    void PrintAvailableTest(list<Test*>**);
    void PrintOwnStudents(list<Student*>*);
    Test* SearchAvailableTest(list<Test*>**);
    friend void EditTest(Teacher*, Test*);
    string GetSubject();
    string GetPassword();
};

