#pragma once
#include <string>

using namespace std;

struct Date_struct
{
	int year;
	int month;
	int day;
	int date_weight;


	bool operator<(const Date_struct& a) const
	{
		return date_weight < a.date_weight;
	}
};


