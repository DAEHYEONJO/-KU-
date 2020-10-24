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
	string open_hour;
	string close_day;
	Restaurant();
	Restaurant(string category, string name, string address);
	bool register_Status();
	void change_info();
	void more_info();
	void addMenu();
	void addMore_info();
	void setMenu();
	void setMore_info();
	~Restaurant();
};

