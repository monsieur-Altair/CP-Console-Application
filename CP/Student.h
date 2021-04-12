#pragma once
#include "User.h"

class Student : public User
{
    string faculty;
    int group, course;
    list<string>* ptrSubjectList;
    list<SolvedTest*> SolvedTestList;
    enum MenuChoice
    {
        SOLVE_TEST = 1,
        VIEW_ALL_AVAIBLE_TEST,
        VIEW_OWN_INF,
        VIEW_SOLVED_TESTS
    };
public:
    Student();
    Student
    (
        string, //name
        string, //password
        string, //faculty
        int,    //id
        int,    //group
        int,    //course
        list<string>* //strings for list
    );
    ~Student();
    void Menu(list<Test*>*);
    void PrintInformation() override;
    list<string>* GetPtrSubjectList();
    int GetCourse();
};

