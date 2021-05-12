#pragma once
#include "Question.h"
#include <conio.h>
template <class T>
class AdditionalFunctions
{
public:
	static void Check(T*, double, double);
};

template<class T>
void AdditionalFunctions<T>::Check(T* value, double min , double max )
{
	if (cin.good() && (*value) >= min && (*value) <= max)
		return;
	cin.clear();
	cin.ignore(500, '\n');
	do
	{
		cout << "\nНеверный ввод!Вводить можно только цифры и в разумных пределах!\nВведите новое значение: ";
		char x = 0;
		*value = 0;
		bool isMinus = false, isAppear = false;
		do
		{
			x = _getch();
			if (x == '-' && !isAppear)
			{
				cout << x;
				isMinus = true;
				isAppear = true;
			}
			if (x >= '0' && x <= '9')
			{
				isAppear = true;
				cout << x;
				*value *= 10;
				if (!isMinus) *value += (x - 48);
				else *value -= (x - 48);
			}
			if (x == 8)
			{
				cout << "\b \b";
				*value /= 10;
			}
		} while (x != 13);
	} while (*value < min || *value > max);
}
