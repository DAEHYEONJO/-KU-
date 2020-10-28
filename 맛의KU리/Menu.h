#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cstdlib>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

class Menu
{
public:
	string m_price;
	string m_name;
	Menu(string name, string price);
	~Menu();
};

