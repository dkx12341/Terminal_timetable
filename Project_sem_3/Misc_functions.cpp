
#include "Misc_functions.h"

Date_struct get_date(string raw_date)
{
	int separator_pos = 0;

	int beginning = 0;
	while (!isdigit(raw_date[beginning]))
	{
		beginning++;
	}
	separator_pos = raw_date.find('/', separator_pos + 1);
	string days_string = raw_date.substr(beginning, separator_pos - beginning);
	if (days_string.length() == 1)
	{
		days_string = '0' + days_string;
	}
	int old_separator = separator_pos;
	separator_pos = raw_date.find('/', separator_pos + 1);
	string months_string = raw_date.substr(old_separator + 1, separator_pos - old_separator - 1);
	if (months_string.length() == 1)
	{
		months_string = '0' + months_string;
	}
	string years_string = raw_date.substr(separator_pos + 1, raw_date.length() - separator_pos - 1);
	string date_weight_string = years_string + months_string + days_string;

	Date_struct good_date;

	good_date.year = stoi(years_string);
	good_date.month = stoi(months_string);
	good_date.day = stoi(days_string);
	good_date.date_weight = stoi(date_weight_string);

	return good_date;
}

vector<string> get_events(string raw_events)
{
	int separator_begin = 0;
	int separator_end = 0;
	vector<string> current_events;

	while (separator_end < raw_events.length() - 1)
	{
		separator_begin = raw_events.find(';', separator_end);
		separator_end = raw_events.find(';', separator_begin + 1);
		int event_lenght = separator_end - separator_begin;

		string single_event = raw_events.substr(separator_begin + 1, event_lenght - 1);
		current_events.push_back(single_event);
	}
	return current_events;
}

bool check_date_format(string raw_date)
{
	bool good_date = true;
	int separator_pos = 0;
	separator_pos = raw_date.find('/', separator_pos + 1);
	string days_string = raw_date.substr(separator_pos - 2, 2);
	string months_string = raw_date.substr(separator_pos + 1, 2);
	string years_string = raw_date.substr(separator_pos + 4, 4);

	for (auto i : days_string)
	{
		if (isdigit(i) == false)
		{
			good_date = false;
		}
	}
	for (auto i : months_string)
	{
		if (isdigit(i) == false)
		{
			good_date = false;
		}
	}
	for (auto i : years_string)
	{
		if (isdigit(i) == false)
		{
			good_date = false;
		}
	}
	
	return good_date;
}