#pragma once
#include "Menu.h"
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
	~Restaurant();
};

