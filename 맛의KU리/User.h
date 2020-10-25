#pragma once
#include <iostream>
#include <cstring>
#include <ctype.h>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include "Restaurant.h"
using namespace std;

class User
{
public:
	string id;
	string pw;
	vector<Restaurant> restaurant;
	User();
	User(string id, string pw);
	~User();
	void printMyRest();
	void print();
	void readRestTxtFIle();
};

