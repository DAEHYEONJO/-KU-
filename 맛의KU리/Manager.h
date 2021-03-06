﻿#pragma once
#include "User.h"
#include <Windows.h>
#include <tchar.h>
class Manager
{
public:
	string* humooil;
   vector<User> user;
   User* current_user;
   string* V_address;
   int signUp();
   int logIn();
   void loginMenu();
   string save_Openhour(int index, smatch match, string humoo);
   bool isMoney(string str);
   void writeRestTextFile();
   void writeR_MenuTextFile();
   void writeR_InfoTextFile();
   bool yesorno();
   bool isDay(string str);
   bool	oneSpaceLength(string& str);
   bool isTime(string str, vector<string>& v);
   bool isAddress(string str);
   int mainMenu();
   void registerRestaurant();
   void searchRestaurant();
   void readInfoTextFile();
   void readRestTextFile();
   void readR_InfoTextFile();
   void readR_MenuTextFile();
   void ManageRestaurant();
   string getDayIndex(string str);
   bool isin0to128(string str);
   bool isQuit(string str);
   bool isSpace(string str);
   bool isTwoSlash(string s);
   static void ltrim(string& s);
   static void rtrim(string& s);
   static void trim(string& s);
   Manager();
   ~Manager();
};
