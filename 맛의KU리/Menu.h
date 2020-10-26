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

static void trim(string& s);

class Menu
{
public:
	string m_price;
	string m_name;
	static void inputTest();
	Menu(string name, string price);
	~Menu();
};

