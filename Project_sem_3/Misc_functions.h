#pragma once
#include "Date_struct.h"
#include <vector>

Date_struct get_date(string raw_date);
vector<string> get_events(string raw_events);
bool check_date_format(string raw_date);
