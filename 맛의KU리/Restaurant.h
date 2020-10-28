#pragma once
#include "Menu.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

class Restaurant
{
public:
	string name;
	string address;
	string category;
	vector<Menu> menu;
	vector<string> open_hour;
	vector<string> close_day;
	
	Restaurant();
	Restaurant(string category, string name, string address);
	void print_menu();
	void print_open_hour();
	void print_info();
	void print_info2();
	void print_close_day();
	bool set_open_hour(string time);
	bool register_Status();
	~Restaurant();
};

