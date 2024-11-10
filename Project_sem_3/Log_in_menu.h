#pragma once
#include"User_timetable.h"
#include <string>

using namespace std;

class Log_in_menu
{

	string user_filepath;
	string user_password;
public:
	pair<string,string> print_log_in_menu();
	bool check_user_data(pair<string, string> data);
	string get_user_filepath();

	Log_in_menu();
	~Log_in_menu();

};

