
#include "User_timetable.h"
#include <fstream>
#include<algorithm>
#include <iostream>
#include <memory>  // for allocator, __shared_ptr_access, shared_ptr
#include <string>  // for string, basic_string
#include <vector>  // for vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Radiobox, Horizontal, Menu, Renderer, Tab
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, separator, hbox, operator|, border


User_timetable::User_timetable(string file_path, string password)
{
    user_password = password;
    user_file_path = file_path;
    string command = "0";
    while (command != "ext")
    {
        string user_input = print_user_timetable(user_file_path);
        command = user_input.substr(0, user_input.find('-'));
        if (command == "add")
        {
            string content = user_input.substr(user_input.find('-') + 1);
            add_new_event(content);
        }
        else if (command == "del")
        {
            string content = user_input.substr(user_input.find('-') + 1);
            delete_event(content);
        }
        else if (command == "ext")
        {
            exit(0);
        }
        else
        {
            cout << "\n\n\nBad command\n\n\n";
        }
    }

}

map<Date_struct, vector<string>> User_timetable::get_planned_events(string file_path)
{
	ifstream user_file;
	user_file.open(user_file_path, std::fstream::app);
	string file_content;
	getline(user_file, file_content, '@');
	pair<Date_struct, vector<string>> date_and_events;
	vector< pair<Date_struct, vector<string>>> all_dates_and_events_vec;
	while (!user_file.eof())
	{
		getline(user_file, file_content, ':');
        if (file_content.length() > 4)
        {
            Date_struct current_event_date = get_date(file_content);
            getline(user_file, file_content);
            vector<string> events_in_current_date = get_events(file_content);
            date_and_events.first = current_event_date;
            date_and_events.second = events_in_current_date;

            all_dates_and_events_vec.push_back(date_and_events);
        }
	}

	sort(all_dates_and_events_vec.begin(), all_dates_and_events_vec.end());

	map<Date_struct, vector<string>> all_detes_and_events;
	for (auto i : all_dates_and_events_vec)
	{
		all_detes_and_events[i.first] = i.second;
	}
    user_file.close();
	return 	all_detes_and_events;
}

string User_timetable::print_user_timetable(string file_path)
{
    system("CLS");

	planned_events = get_planned_events(user_file_path);
    cout << "\nYOUR TIMETABLE\n";
    for (auto i : planned_events)
    {
        cout << "\n" << i.first.day << '/' << i.first.month << '/' << i.first.year << ":\n";
        for (auto j : i.second)
        {
            cout << "\t" << j << "\n";
        }
    }

    using namespace ftxui;

    // The data:
    std::string input;


    // The basic input components:
    Component user_input = Input(&input, "...");


    // The phone number input component:
    // We are using `CatchEvent` to filter out non-digit characters
   // auto on_click = [&] {screen.ExitLoopClosure(); };
   // auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
      //  Color::Default, Color::White);

    //auto button = Button("Login", on_click, style);

    // The component tree:
    auto component = Container::Vertical({
        user_input,
        });

    // Tweak how the component tree is rendered:
    auto renderer = Renderer(component, [&] {
        return vbox({
                   hbox(text("|add new event: add-DD/MM/YYYY:*your note*|  |delete event: del-DD/MM/YYYY|  |quit: ext-|")),
                   hbox(text("\n")),
                   hbox(text(" Input : "), user_input->Render()),
            }) |
            border;
        });

    auto screen = ScreenInteractive::TerminalOutput();
    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Return)
        {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
        });

    screen.Loop(renderer);

    return input;
}

void User_timetable::add_new_event(string new_event_data)
{
    ofstream user_file;
    user_file.open(user_file_path, std::fstream::app);
    bool good_input = check_date_format(new_event_data);
    if (new_event_data.find(':') != 10)
    {
        good_input = false;
    }
    if (good_input == false)
    {
        cout << "\n\n\nBad syntax\n\n\n";
    }
    else if (good_input == true)
    {
        Date_struct new_event_date = get_date(new_event_data.substr(0,new_event_data.find(':')));
        std::map<Date_struct, vector<string>>::iterator it = planned_events.find(new_event_date);
        if (it != planned_events.end())
        {
            planned_events[new_event_date].push_back(new_event_data.substr(new_event_data.find(':')+1));
            //
            ofstream user_file;
            user_file.open(user_file_path);
            user_file << user_password << "\n\n\n@\n";
            for (auto i : planned_events)
            {
                user_file << i.first.day << '/' << i.first.month << '/' << i.first.year << ":;";
                for (auto j : i.second)
                {
                    user_file << j << ';';
                }
                user_file << "\n";
            }
            user_file.close();
        }
        else
        {
            user_file << '\n' + new_event_data;
        }
    }
    user_file.close();
}
void User_timetable::delete_event(string date_to_delete_raw)
{
    bool good_input = check_date_format(date_to_delete_raw);
    if (good_input == false)
    {
        cout << "\n\n\nBad syntax\n\n\n";
    }
    else if (good_input == true)
    {
        Date_struct date_to_delete = get_date(date_to_delete_raw);
        std::map<Date_struct, vector<string>>::iterator it = planned_events.find(date_to_delete);
        if (it != planned_events.end())
        {
            planned_events.erase(it);

            ofstream user_file;
            user_file.open(user_file_path);
            user_file << user_password << "\n\n\n@\n";
            for (auto i : planned_events)
            {
                user_file << i.first.day << '/' << i.first.month << '/' << i.first.year << ":;";
                for (auto j : i.second)
                {
                    user_file << j << ';';
                }
                user_file << "\n";
            }
            user_file.close();
        }
        else
        {
            cout << "\n\n\nNo event on this date\n\n\n";
        }

    }


}


User_timetable::~User_timetable()
{
}