#pragma once
#include "User.h"

class Manager
{
public:
   vector<User> user;
   User* current_user;
   string* V_address;
   int signUp();
   int logIn();
   void loginMenu();
   bool yesorno();
   int mainMenu();
   void registerRestaurant();
   void searchRestaurant();
   void readInfoTextFile();
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
