#pragma once
#include "Menu.h"
class Restaurant
{
public:
	vector<Menu> menu;
	string open_hour;
	string close_day;
	Restaurant();
	~Restaurant();
};

