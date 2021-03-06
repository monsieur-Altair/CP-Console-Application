#pragma once
#include "User.h"

class Student : public User
{
    string faculty;
    int group, course;
    shared_ptr<list<string>> ptrSubjectList;
    list<SolvedTest*>* ptrSolvedTestList;
    enum MenuChoice
    {
        SOLVE_TEST = 1,
        VIEW_ALL_AVAIBLE_TEST,
        VIEW_OWN_INF,
        VIEW_ALL_SOLVED_TESTS_BRIEFLY,
        VIEW_ONE_SOLVED_TEST_FULLY,
        SORT_SOLVED_BY_SUBJECTS,
        SORT_SOLVED_BY_PERCENTAGE,
        SORT_AVAILABLE_BY_SUBJECTS
    };
public:
    Student();
    Student
    (
        string, //name
        int,    //Hashed password
        string, //faculty
        int,    //id
        int,    //group
        int,    //course
        shared_ptr<list<string>>, //strings for list
        list<SolvedTest*>*        //list of solved test
    );
    ~Student();

    int  GetCourse();
    int  GetGroup();
    void Menu(list<Test*>*);
    void PrintInformation() override;
    void Unload(string)     override;
    bool CheckSolvedTestList(Test*);
    bool PrintAvailableAndNoSolvedTest(list<Test*>*);
    bool PrintAllSolvedTestBriefly();
    void DeleteSolvedFromFilteredList(list<Test*>*, list<Test*>*);
    string GetName();
    shared_ptr<list<string>>GetPtrSubjectList();
    list<SolvedTest*>*      GetPtrSolvedTestList();
    void DeleteEditedSolvedTest(int);
    friend bool sort::SortStudentByGroups(const Student*, const Student*);
    friend bool sort::SortStudentAlphabetic(Student*, Student*);
};

Test* SearchTestWithID(list<Test*>*,int);
