#pragma once
#include "Misc_functions.h"
#include <vector>
#include <map>
using namespace std;

class User_timetable
{
	map<Date_struct, vector<string>> planned_events;
	string user_file_path;
	string user_password;
	
public:
	map<Date_struct, vector<string>> get_planned_events(string user_file_path);
	string print_user_timetable(string user_file_path);
	void add_new_event(string new_event_data);
	void delete_event(string date_to_delete);

	User_timetable(string user_file_path, string passwort);
	~User_timetable();
	
};


