#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cstdlib>
#include <fstream>

using namespace std;
class Menu
{
public:
	int m_price;
	string m_name;

	Menu(int price, string name);
	~Menu();
};

