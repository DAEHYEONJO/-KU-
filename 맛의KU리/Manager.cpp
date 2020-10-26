#include "Manager.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


int Manager::signUp()
{
   //id �Է¹ޱ� -> ������Է�, �ߺ��˻� -> pw �Է¹ޱ� -> 4�ڸ����� �Է� ���� ���� -> text���Ͽ� �����ϱ�
   //id, pw �Է� ���� �� quit �Է½� ���θ޴��� ���ư���
   /**/
   string test_id="", test_pw="";
   regex idChecker1("[a-zA-Z0-9]+");//���ĺ�/�����ΰ��
   //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//���ڸ��������ϴ°��

   while (true) {//id roof
      test_id.clear();
      test_pw.clear();
      cout << "id�� ���ڿ� ������ �����̸�, 6�ڸ�~10�ڸ��� �Է��ϼ���\nid : ";
      getline(cin, test_id);
      if (!isin0to128(test_id)) {
          cout << "�ѱ��� �Է� ����" << endl;
          continue;
      }

      if (isSpace(test_id)) continue;
      else {
         if (!isQuit(test_id)) {//quit �ƴϸ�
            if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
               if (regex_match(test_id, idChecker1)) {
                  cout << "���Ǹ���\n" << endl;
                  readInfoTextFile();//����Ǿ��ִ°� �о����.
                  int count = 0;
                  for (count = 0; count < user.size(); count++) {//text file �ߺ��˻�
                     cout << "���尪 : " << user[count].id.c_str() << "�Է°� : " << test_id << endl;
                     if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
                  }
                  if (count == user.size()) {
                     cout << "�ߺ��Ǵ� id ����\n" << endl;
                     while (true) {//pw roof
                        cout << "pw�� ���ڸ����� �̷���� ������, 4�ڸ��� �Է��ϼ���\npw : ";
                        regex pwChecker("^[0-9]{4}$");
                        getline(cin, test_pw);//pw�Է¹ޱ�
                        if (!isin0to128(test_pw)) {
                            cout << "�ѱ��� �Է� ����" << endl;
                            continue;
                        }
                        if (regex_match(test_pw, pwChecker)) {
                           cout << "���̵� �н����� ��� �Ϸ�\n" << endl;
                           //info.txt�� �ش� ���̵� �н����� �߰��ϱ�.
                           ofstream writeFile;
                           writeFile.open("info.txt", std::ofstream::out | std::ofstream::app);//������, �̾ �߰��ϱ�
                           if (writeFile.is_open()) {
                              string merge = test_id + "/" + test_pw + "\n";
                              writeFile.write(merge.c_str(), merge.size());
                           }
                           else {
                              cout << "���� ���� ����\n" << endl;
                           }
                           writeFile.close();
                           readInfoTextFile();//���� �߰��Ǿ����� user���Ϳ� �߰����ֱ�
                           return 1;
                        }
                        else {
                           cout << "pw ���� ����\n" << endl;
                        }
                     }
                  }
                  else {
                     cout << "id �ߺ�\n" << endl;
                  }
               }
               else {
                  cout << "�����ڿ� ���ڸ� �����Ͽ� �ּ���\n" << endl;
               }
            }
            else {
               cout << "id ���� ���� ����\n" << endl;
            }
         }
         else {
            return 0;
         }
      }
   }
}

int Manager::logIn()
{
   cout << "�α����̴�\n" << endl;
   regex idChecker1("[a-zA-Z0-9]+");//������������ϴ°��
   //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//���ڸ��������ϰ�ġ�ٴ°��

   while (true) {//�α��� �����ϸ� current_user�� �α����� ���� ���� �����
      cout << "id : ";
      string test_id, test_pw;
      getline(cin, test_id);
      if (!isin0to128(test_pw)) {
          cout << "�ѱ��� �Է� ����" << endl;
          continue;
      }
      if (isSpace(test_id)) continue;
      else {
         if (!isQuit(test_id)) {
            if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
               if (regex_match(test_id, idChecker1)) {
                  readInfoTextFile();//����Ǿ��ִ°� �о����.
                  readRestTextFile();
                  readR_InfoTextFile();
                  readR_MenuTextFile();
                  int count = 0;
                  for (count = 0; count < user.size(); count++) {//text file �ߺ��˻�
                     cout << "���̵����尪 : " << user[count].id.c_str() << "�Է°� : " << test_id << endl;
                     if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
                  }
                  if (count == user.size()) {//�ߺ��� ���̵� ������ �ٽ��Է¹ޱ�
                     cout << "�ߺ��� ���̵� ����.\n" << endl;
                  }
                  else {
                     while (true) {
                        cout << "pw : ";
                        regex pwChecker("^[0-9]{4}$");
                        getline(cin, test_pw);//pw�Է¹ޱ�
                        if (!isin0to128(test_pw)) {
                            cout << "�ѱ��� �Է� ����" << endl;
                            continue;
                        }
                        if (regex_match(test_pw, pwChecker)) {//pw���� �ǹٸ�
                           if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
                              //�α��μ���
                              current_user = new User(user[count].id, user[count].pw);
                                for (int i = 0; i < user[count].restaurant.size();i++) {
                                    current_user->restaurant.push_back(Restaurant(user[count].restaurant[i].category,
                                        user[count].restaurant[i].name,
                                        user[count].restaurant[i].address));
                                    current_user->restaurant[i].address = user[count].restaurant[i].address;
                                    current_user->restaurant[i].close_day = user[count].restaurant[i].close_day;
                                    current_user->restaurant[i].open_hour = user[count].restaurant[i].open_hour;
                                    for (int j = 0; j < user[count].restaurant[i].menu.size(); j++) {
                                        current_user->restaurant[i].menu.push_back(Menu(user[count].restaurant[i].menu[j].m_name,
                                            user[count].restaurant[i].menu[j].m_price));
                                    }
                                }
                                cout << "���� �α��� �� ������ ���� " << endl;
                                current_user->print();

                              
                              //�α��� ������ ���� ����
                              cout << "�α��� ����!\n id: " << user[count].id << endl;
                              return 1;
                           }
                           else {
                              cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n" << endl;
                           }

                        }
                        else {
                           cout << "�ǹٸ��� ���� pw����\n" << endl;
                        }
                     }


                  }
               }
            }
            else {
            cout << "id ���� ���� ����\n" << endl;
            }
         }
         else {
         break;
         }
      }
   }
   return 0;
}

void Manager::loginMenu()
{
   int c = 0;
   string test_menu = "";
   while (c != 4) {
      test_menu.clear();
      cout << "1. �α���\t2. ȸ������\n>>���⼱�� : ";
      
      regex menuChecker("^(1|2){1}$");

      getline(cin, test_menu);
      if (!isin0to128(test_menu)) {
          cout << "�ѱ��� �Է� ����" << endl;
          continue;
      }
      if (regex_match(test_menu, menuChecker)) {//�Է°��� 1 �Ǵ� 2�̸� ����
         const char* buf = test_menu.c_str();//char* buf
         int menu = atoi(buf);//char* to int
         switch (menu) {
         case 1: {
            if (logIn()) c = mainMenu();
         }
              break;
         case 2: {
            if (signUp())
               if (logIn()) c = mainMenu();
         }
              break;
         default:
            cout << "�� ���� ���볪���� �ȵ� ������ ������.\n" << endl;
            break;
         }
      }
      else {
         cout << "ERROR : input 1 or 2\n" << endl;
      }
   }
}

bool Manager::yesorno()
{
   string c = "";
   regex ynCheck("(y)|(n){1}$");
   while (true) {
      cout << "yes or no?: ";
      getline(cin, c);
      if (!isin0to128(c)) {
          cout << "�ѱ��� �Է� ����" << endl;
          continue;
      }
      trim(c);
      if (regex_match(c, ynCheck)) {
         if (!strcmp(c.c_str(), "y")) return 1;
         return 0;
      }
      //y �Ǵ� n �Է� �������� �ٽ� ���ΰ��� �Է¹ޱ�
   }
   return false;
}

bool Manager::isDay(string str)
{
    regex Day_Checker("^[a-zA-Z]+(day)$");
    if (regex_match(str, Day_Checker)) {
        if ((str.size() >= 6) && (str.size() <= 9)) {
            int i = 0;
            for (i = 0; i < 7; i++) {
                if (!strcmp(humooil[i].c_str(), str.c_str())) {
                    cout << "���ϸ���" << endl;
                    return true;
                }
            }
            if (i == 7) {
                cout << "monday~sunday �Է¹ٶ�" << endl;
            }
        }
        else {
            cout << "day ���� 6~9 �� �Է��ϼ���" << endl;
            return false;
        }
    }
    return false;
}

bool Manager::isTime(string str, vector<string>& v)
{
    regex Time_Checker("([0-9]{1,2})\:([0-9]{1,2})*$");
    smatch sm;
    if (regex_match(str, sm, Time_Checker)) {
        for (int i = 1; i <= 2; i++)
            v.push_back(sm.str(i));

        if ((stoi(sm.str(1)) >= 0) && (stoi(sm.str(1)) <= 23)) {
            if ((stoi(sm.str(2)) >= 0) && (stoi(sm.str(2)) <= 59)) {
                return true;
            }
            else {
                cout << "�� ���� ����" << endl;
                return false;
            }
        }
        else {
            cout << "�ð� ���� ����" << endl;
            return false;
        }
    }
    else cout << "�ð� ���Ŀ� �°� �Է��ϼ���" << endl;
    return false;

}

bool Manager::isAddress(string str)
{
    regex adrChecker("^[a-zA-Z0-9]+(dong)$");//���ĺ�+���ڸ��Է�
    if (regex_match(str, adrChecker)) {
        if ((str.size() >= 12) && (str.size() <= 13)) {
            int i = 0;
            for (i = 0; i < 10; i++) {
                if (!strcmp(V_address[i].c_str(), str.c_str())) {
                    return true;
                }
            }
            if (i == 10) {
                cout << "hwayang1dong~10dong �Է��ϼ���" << endl;
                return false;
            }
        }
        else {
            cout << "day ���� 12~13 ���� �Է��ϼ���" << endl;
            return false;
        }
    }
    return false;
}

int Manager::mainMenu()
{
   while (true) {
      cout << "1. �Ĵ���\t2.�Ĵ����\t3. �Ĵ�˻�\t4. ���� : ";
      regex menuChecker("^([1-4]){1}$");
      string test_menu = "";
      getline(cin, test_menu);
      if (!isin0to128(test_menu)) {
          cout << "�ѱ��� �Է� ����" << endl;
          continue;
      }
      if (regex_match(test_menu, menuChecker)) {
         const char* buf = test_menu.c_str();//char* buf
         int menu = atoi(buf);//char* to int
         if (menu == 4) return menu;
         else {
            switch (menu) {
            case 1:
               registerRestaurant();
               break;
            case 2:
                ManageRestaurant();
               break;
            case 3:
                //searchRestaurant();
               break;
            default:
               cout << "�� �� ���볪����ȵ�" << endl;
               break;
            }
         }
      }
      else {
         cout << "ERROR : input 1 ~ 4\n" << endl;
      }
   }
}

void Manager::registerRestaurant()
{
   vector<User>temp_user;
   int scount = 0;//slash count
   string data="", category="", R_name="", R_address="";
   char* data_buff = nullptr;
   while (true) {
      scount = 0;
      cout << "ī�װ�/�Ĵ��̸�/�Ĵ��ּ�" << endl << "�Է��ϼ���<<";
   //   data = "";
      getline(cin,data);
      if (!isin0to128(data)) {
          cout << "�ѱ��� �Է� ����" << endl;
          continue;
      }
      trim(data);//�յڰ����� �ڸ���
      if (!isQuit(data)) {
          cout << "data : " << data << endl;
          cout << "datasize : " << data.size() << endl;
          data_buff = new char[data.size() + 1];
          strcpy(data_buff, data.c_str());
          for (int i = 0; i < data.size(); i++) {
             if ((int)data[i] == 47)
                scount++;
          }
          cout << "scount : "<<scount << endl;

          if (scount != 2) continue;//������ 2�� �ƴϸ� �ٽ��Է¹ޱ�
      
          trim(data);//�յڰ����� �ڸ���
      
             vector<char*>stv;
             char* ptr1 = strtok(data_buff, "/");
             while (ptr1 != nullptr) {
                stv.push_back(ptr1);
                ptr1 = strtok(NULL, "/");
             }
             if (stv.size() == 3) {
                category = (string)stv[0];
                R_name = (string)stv[1];
                R_address = (string)stv[2];
             }
             else {
                continue;
             }
         
             cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;
             trim(category);
             trim(R_name);
             trim(R_address);
             cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;

             regex categoryChecker("^[a-z].*$");
             if (!regex_match(category, categoryChecker)) {
                cout << "ī�װ� �����ڸ� �Է��ϼ���" << endl;
                continue;
             }
             else {
                if (!((strcmp(category.c_str(), "japanese") == 0) || (strcmp(category.c_str(), "chinese") == 0) || (strcmp(category.c_str(), "korean") == 0) || (strcmp(category.c_str(), "western") == 0)))
                {//ī�װ� �˻�
                   cout << "2??" << endl;
                   cout << "ī�װ� 4�߿� �Ѱ��� �Է����ּ��䤵��" << endl;
                   continue;
                }
             }
         
             //�̸��˻�
             regex nameChecker("[a-zA-Z[:space:]]+");
             if (!regex_match(R_name, nameChecker)) {
                cout << "�Ĵ� �̸� ������ �Ǵ� �����ڿ� ���� �������� �Է��ϼ���" << endl;
                continue;
             }
             else {
                for (int i = 0; i < R_name.size(); i++) {
                   R_name[i] = tolower(R_name[i]);
                }
                cout << "R_name : " << R_name << endl;
                vector<char*>v;
                char* buf = new char[R_name.size() + 1];
                strcpy(buf, R_name.c_str());
                char* ptr = strtok(buf, " \t");//����+�� ���յ� �Ǻ��ϱ�����
                while (ptr != nullptr) {
                   cout << "3??" << endl;
                   v.push_back(ptr);
                   ptr = strtok(NULL, " \t");
                }
                string result = "";
                if (v.size() == 1) {
                   result = (string)v[0];
                }
                else {
                   for (int i = 0; i < v.size(); i++) {
                      if (i != v.size() - 1) {
                         result += (string)v[i] + " ";
                      }
                      else {
                         result += (string)v[i];
                      }
                   }
                }
                R_name = result;
                if (R_name.size() < 1 || R_name.size() > 15) {
                    cout << "���� 1~15" << endl;
                    continue;
                }
                //�ؽ�Ʈ���Ͽ� �Ĵ��̸� �ֳ� ���� �˻��ϱ�
                bool check = false;
                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].name.c_str(), R_name.c_str())) {
                            cout << "�ߺ��� �Ĵ� �̸��� �ֽ��ϴ�\n" << endl;
                            check = true;
                            break;
                        }
                    }
                }
                if (check) continue;
             }
             regex adrChecker("[a-zA-Z0-9]+");//���ĺ�+���ڸ��Է�
             if (!regex_match(R_address, adrChecker)) {
                cout << "�����ڸ� �Է��ϼ���" << endl;
                continue;
             }
             else {
             bool check = false;
             for (int i = 0; i < 10; i++) {//�ּҰ˻�
                 if (strcmp(R_address.c_str(), V_address[i].c_str()) == 0) {
                     check = true;
                     break;
                 }
                 else {
                     check = false;
                 }
             }
             if (!(check)) {
                 cout << "�ּ� ��Ģ����" << endl;
                 continue;
             }
             }

             //����׸� �˻�Ϸ�� ī�װ�: *** �̸�: *** �ּ�: *** ��� �� y_n �޾ƾ��� 
             cout << "ī�װ�: " << category << "\n�̸�: " << R_name << "\n�ּ�: " << R_address << endl;
             if (yesorno()) {//current_user�� ���������ü���Ϳ� ������� ���� pushback
                 ofstream writeRestaurant;

                 writeRestaurant.open("Restaurant.txt", std::ofstream::out | std::ofstream::app);//������, �̾ �߰��ϱ�
                 if (writeRestaurant.is_open()) {
                     string merge = current_user->id + "/" + category + "/" + R_name + "/" + R_address + "\n";
                     writeRestaurant.write(merge.c_str(), merge.size());
                 }
                 else {
                     cout << "���� ���� ����\n" << endl;
                 }
                 writeRestaurant.close();
                 readRestTextFile();

                 current_user->restaurant.push_back(Restaurant(category, R_name, R_address));
                 current_user->print();

                 cout << "��ϿϷ�" << endl;
                 return;
             }
             else {
                 cout << "�߰�����\n" << endl;
                 continue;
             }
      }
      else return;
   }

}

void Manager::searchRestaurant()
{
    vector<char*>temp;
    char* ptr = nullptr;
    char* buf = nullptr;
    string data = "", adr = "", time = "", day = "";
    vector<Restaurant>find_R_list;
    while (true) {
        temp.clear();
        int scount = 0;
        cout << "���� �����ϰ� 3���� �����͸� / �� �����Ͽ� �Է��ϼ���" << endl;
        cout << "���� �� ����/�ð�/���� :";
        getline(cin, data);
        if (isin0to128(data)) {
            trim(data);
            if (!isQuit(data)) {
                for (int i = 0; i < data.size(); i++) {
                    if ((int)data[i] == 47)
                        scount++;
                }
                if (scount != 2) {
                    cout << "������ 2�� �Է����� ������ �ȵ˴ϴ�." << endl;
                    continue;//������ 2�� �ƴϸ� �ٽ��Է¹ޱ�
                }
                buf = new char[data.size() + 1];
                strcpy(buf, data.c_str());
                ptr = strtok(buf, "/");
                while (ptr != nullptr) {
                    temp.push_back(ptr);
                    ptr = strtok(NULL, "/");
                }
                if (temp.size() != 3) {
                    cout << "������ �� �� �� /�� �����Ͽ� 3�� �Է��ϼ���" << endl;
                    continue;
                }
                vector<string> timeV;
                for (int i = 0; i < temp.size(); i++) {
                    string str = (string)temp[i];
                    trim(str);
                    if (isTime(str, timeV)) time = str;
                    if (isDay(str)) day = str;
                    if (isAddress(str)) adr = str;
                }
                cout << "time : " << time << "/day : " << day << "/adr : " << adr << endl;

                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); i++) {
                        if (!strcmp(user[i].restaurant[j].address.c_str(), adr.c_str())) {
                            //�Է��� ������ �Ĵ� �ּҰ� ��ġ�ϴ� �Ĵ� �߰�, �ð� �˻� ����
                            //�Ĵ� �����ð��� ���� �ȳ������ timeV[0]:�Է½ð�,timeV[1]:�Էº�
                            
                            if (user[i].restaurant[j].open_hour.size() == 5) {
                                if (strcmp(getDayIndex(adr).c_str(), user[i].restaurant[j].close_day[1].c_str())){
                                    //�Է¿����� ����� �޹����̶� �ٸ����� ���ϱ�
                                    if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[0])) {
                                        if (stoi(timeV[1]) >= stoi(user[i].restaurant[j].open_hour[1])) {//1
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }
                                    if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[0])) {
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[2])) {
                                            if (stoi(timeV[1]) < stoi(user[i].restaurant[j].open_hour[3])) {//2
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[2])) {//3
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }
                                }
                            }
                            else {//�����ð��� ������ ���� ���
                                //�� �Է½ð��� �չ�������, �� �������� Ȯ��
                                

                            }

                        }
                    }
                }
            }
            else {
                return;
            }
        }
        else {
            cout << "�ѱ� �Է� ����" << endl;
            continue;
        }
    }
    



}

void Manager::readInfoTextFile()
{
   cout << "readInfoTextFile" << endl;
   user.clear();//user �ʱ�ȭ
   char readline[16];//�� �� �ִ� 16���� id->10, /->1, pw->4, \n->1
   char** temp_info = new char* [2];
   for (int i = 0; i < 2; i++) {
      temp_info[i] = new char[10];//�׳� ũ�� 10���� ����
   }
   ifstream readFile;
   readFile.open("info.txt");
   if (readFile.is_open()) {
      
      while (!readFile.eof()) {
         readFile.getline(readline, 16);
         if (!readFile.eof()) {//eof�϶� strtok�����ٶ��
            temp_info[0] = strtok(readline, "/");//id
            temp_info[1] = strtok(NULL, "/");//pw

            user.push_back(User(temp_info[0], temp_info[1]));
         }
      }
   }
   else {
      cout << "������ ���µ��� ����\n" << endl;
   }
   readFile.close();

  
}

void Manager::readRestTextFile()
{
    cout << "readRestTextFile" << endl;
    for (int i = 0; i < user.size(); i++) {
        user[i].restaurant.clear();
    }
        

    ifstream readRestaurant;
    char** temp_info_R = new char* [4];
    for (int i = 0; i < 4; i++) {
        temp_info_R[i] = new char[16];//�׳� ũ�� 10���� ����
    }
    char* ptr = nullptr;
    char readlineR[50];//�� �� �ִ� 50���� id->10, /->3, ī�װ�->8, �Ĵ��̸�->15, �ּ�->13\n->1
    readRestaurant.open("Restaurant.txt");
    if (readRestaurant.is_open()) {
        while (!readRestaurant.eof()) {
            readRestaurant.getline(readlineR, 50);
            if (!readRestaurant.eof()) {//eof�϶� strtok�����ٶ��
                temp_info_R[0] = strtok(readlineR, "/");//id
                temp_info_R[1] = strtok(NULL, "/");//category
                temp_info_R[2] = strtok(NULL, "/");//�Ĵ��̸�
                temp_info_R[3] = strtok(NULL, "/");//�Ĵ��ּ�
                for (int i = 0; i < user.size(); i++) {//ȸ�������� ������ �Ĵ� �ȵ���ѻ������� user��ü�� �Ĵ����
                    if (!strcmp(user[i].id.c_str(), temp_info_R[0])) {
                        user[i].restaurant.push_back(Restaurant(temp_info_R[1], temp_info_R[2], temp_info_R[3]));
                        break;
                    }
                }
            }
        }
    }
    else {
        cout << "Restaurant.txt not open\n\n" << endl;
    }
    cout << "readRestaurant close" << endl;
    readRestaurant.close();
}

void Manager::readR_InfoTextFile()
{
    cout << "void Manager::readR_InfoTextFile()" << endl;
    for (int i = 0; i < user.size(); i++) {
        for (int j = 0; j < user[i].restaurant.size(); j++) {
            user[i].restaurant[j].open_hour.clear();
            user[i].restaurant[j].close_day.clear();
        }
    }
    ifstream readR_Info;
    vector<char*>v;
    char* ptr = nullptr;
    char readlineR_I[60];
    readR_Info.open("Restaurant_Info.txt");
    regex timeCheck("([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})*$");
    regex timeCheck2("([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})\,([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})*$");
    smatch match,match2;
    vector<string> temp;
    bool dayflag = true;
    string humoo;
    if (readR_Info.is_open()) {
        while (!readR_Info.eof()) {
            v.clear();
            temp.clear();
            dayflag = true;
            humoo.clear();
            readR_Info.getline(readlineR_I, 60);
            if (!readR_Info.eof()) {
                // "/"�������� 4�� �Ǵ� 3�� ©���ֱ�
                //1��° : �Ĵ��̸�
                //2��° : �ּ�
                //3��° : �����ð�-> �޸��� �ִ��� ������ �˻��ϱ�.������ �޸� �������� ¥����.
                //                   �޸� ������ : ~ �������� ¥����, ¥���� : �������� ¥���� �����ϱ�.
                //4��° : �޹���
                ptr = strtok(readlineR_I, "/");
                while (ptr != nullptr) {
                    v.push_back(ptr);
                    ptr = strtok(NULL , "/");
                }
                
                if (v.size() == 3) {//�޹��� ���°��ù�
                    dayflag = false;
                    humoo = "";
                }
                else { humoo = v[3];}
                string tlqkf = (string)v[2];
                if (regex_match(tlqkf, match, timeCheck)) {//�޸����°��
                    temp.push_back(match.str(1));
                    temp.push_back(match.str(2));
                    temp.push_back(match.str(3));
                    temp.push_back(match.str(4));
                    temp.push_back(getDayIndex(humoo));
                }
                if (regex_match(tlqkf, match2, timeCheck2)) {
                    temp.push_back(match2.str(1));
                    temp.push_back(match2.str(2));
                    temp.push_back(match2.str(3));
                    temp.push_back(match2.str(4));
                    temp.push_back(getDayIndex(humoo));
                    temp.push_back(match2.str(5));
                    temp.push_back(match2.str(6));
                    temp.push_back(match2.str(7));
                    temp.push_back(match2.str(8));
                    if (!dayflag)
                        temp.push_back(getDayIndex(humoo));
                    else
                        temp.push_back(to_string((stoi(getDayIndex(humoo)) + 1) % 7));
                }
                
                
                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].name.c_str(), v[0])) {
                            user[i].restaurant[j].address = v[1];//�ּ�
                            user[i].restaurant[j].open_hour.assign(temp.begin(),temp.end());//�����ð�
                            user[i].restaurant[j].close_day.push_back(humoo);
                            user[i].restaurant[j].close_day.push_back(getDayIndex(humoo));
                        }
                    }
                }
                
            }
        }
    }
    else {
        cout << "Restaurant_Info.txt �ȿ���\n" << endl;
    }
    readR_Info.close();
}

void Manager::readR_MenuTextFile()
{
    //�޴� �ִ� 3��, ����ݾ� �ִ� 5�ڸ�
    cout << "readR_MenuTextFile()" << endl;
    for (int i = 0; i < user.size(); i++) {
        for (int j = 0; j < user[i].restaurant.size(); i++) {
            user[i].restaurant[j].menu.clear();
        }
    }
    ifstream readR_Menu;
    readR_Menu.open("Restaurant_Menu.txt");
    char* ptr = nullptr;
    vector<char*>v;
    char buf[85];
    if (readR_Menu.is_open()) {
        
        while (!readR_Menu.eof()) {
            readR_Menu.getline(buf, 85);
            v.clear();
            if (!readR_Menu.eof()) {
                ptr = strtok(buf, "/");
                while (ptr != nullptr) {
                    v.push_back(ptr);
                    ptr = strtok(NULL, "/");
                }
                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].name.c_str(), v[0])) {
                            for (int k = 1; k < v.size(); k += 2) {
                                user[i].restaurant[j].menu.push_back(Menu(v[k], v[k + 1]));
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        cout << "Restaurant_Menu.txt open error\n" << endl;
    }
}

void Manager::ManageRestaurant()
{

    while (true) {
        int select;
        cout << "<<�Ĵ� ����Ʈ>>" << endl;
        current_user->printMyRest();
        cout << "���⼱�� : ";
        cin >> select;
        cin.ignore();//���� ���� 
        if (select == current_user->restaurant.size() + 1) return;

        if (select < current_user->restaurant.size() + 1 && select >= 1) {
            if (!(current_user->restaurant.at(select - 1).menu.empty() || current_user->restaurant.at(select - 1).open_hour.empty())) {
                while (true) {
                    //full info
                    cout << "�ΰ����� ����" << endl;
                    cout << "1. �޴�/���� ���� \n2. �ּ�/�ð�/�޹��� ���� \n3. �����޴�" << endl;
                    cout << "���� ����: ";
                    int select_menu2;
                    cin >> select_menu2;
                    cin.ignore();//���� ����
                    if (select_menu2 == 3) break;
                    if (select_menu2 < 3 && select_menu2 >= 1) {
                        if (select_menu2 == 1)
                        {
                            //�޴�����
                            string M_name, M_price, temp;
                            string input;
                            regex M_name_Checker("[a-zA-Z\\s]*");
                            regex M_price_Checker("^[1-9]?(,|[0-9])[\\S]*");
                            while (true) {
                                vector<Menu>::iterator iter = current_user->restaurant.at(select - 1).menu.begin();
                                current_user->restaurant.at(select - 1).print_menu();
                                cout << "�޴�/(����) �Է�: ";
                                getline(cin, input);
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                cout << "scount : " << scount << endl;
                                trim(input);//�յڰ����� �ڸ���

                                if (scount == 0 && !isQuit(input)) {
                                    //�޴��� �Էµ� 
                                    M_name = input;
                                    for (int i = 0; i < M_name.size(); i++) {
                                        M_name[i] = tolower(M_name[i]);
                                    }
                                    if (regex_match(M_name, M_name_Checker))
                                    {
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        bool del_menu = false;
                                        for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size(); i++) {
                                            if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {
                                                del_menu = true;
                                                break;
                                            }
                                        }
                                        if (del_menu) {
                                            cout << "������ �޴�: " << M_name << endl;
                                            if (yesorno()) {

                                                for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size(); i++) {
                                                    if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {

                                                        current_user->restaurant.at(select - 1).menu.erase(iter + i);
                                                    }
                                                }

                                                cout << "�����Ϸ�!" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "�Է� �޴����� Ȯ���ϼ���" << endl;
                                        }
                                    }

                                }
                                if (!isQuit(input)) {
                                    vector<char*>stv;
                                    char* ptr1 = strtok(data_buff, "/");
                                    while (ptr1 != nullptr) {
                                        stv.push_back(ptr1);
                                        ptr1 = strtok(NULL, "/");
                                    }
                                    if (stv.size() == 2) {
                                        M_name = (string)stv[0];
                                        M_price = (string)stv[1];
                                    }
                                    else {
                                        if (M_price.empty())
                                            cout << "������ ���� ����" << endl;
                                        continue;
                                    }
                                    trim(M_name);
                                    trim(M_price);

                                    if (regex_match(M_name, M_name_Checker))
                                    {
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!regex_match(M_price, M_price_Checker)) {
                                            cout << "���� ���� Ȯ��" << endl;
                                            continue;
                                        }
                                        bool add = true;
                                        for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size() - 1; i++) {
                                            if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {
                                                add = false;
                                                break;
                                            }
                                        }
                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }
                                        if (add) {
                                            cout << "�߰��� �޴��̸�: " << M_name << endl;
                                            cout << "�߰��� �޴�����: " << M_price << endl;
                                            if (yesorno()) {

                                                current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                                cout << "�߰��Ϸ�!" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }

                                        }
                                        cout << "�޴��̸�: " << M_name << endl;
                                        cout << "������ �޴�����: " << M_price << endl;
                                        if (yesorno()) {
                                            for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size() - 1; i++) {
                                                if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {

                                                    current_user->restaurant.at(select - 1).menu.at(i).m_price = M_price;
                                                }
                                            }
                                            cout << "�����Ϸ�!" << endl;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else if (regex_match(M_price, M_name_Checker))
                                    {
                                        temp = M_price;
                                        M_price = M_name;
                                        M_name = temp;
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!regex_match(M_price, M_price_Checker)) {
                                            cout << "���� ���� Ȯ��" << endl;
                                            continue;
                                        }
                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }
                                        cout << "�޴��̸�: " << M_name << endl;
                                        cout << "������ �޴�����: " << M_price << endl;
                                        if (yesorno()) {
                                            for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size() - 1; i++) {
                                                if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {

                                                    current_user->restaurant.at(select - 1).menu.at(i).m_price = M_price;
                                                }
                                            }
                                            cout << "�����Ϸ�!" << endl;
                                            continue;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//�Ѵ� ���Խ� �ȸ���->���Է�
                                        cout << "�޴�/���� ���� Ȯ�ιٶ�" << endl;
                                        continue;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                            continue;
                        }
                        else if (select_menu2 == 2)
                        {//���� ����

                            string hour, close_day, temp;
                            string input;
                            regex Time_Checker("([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})*$");
                            regex Day_Checker("^[a-zA-Z]+(DAY|DAy|DaY|Day|day|daY|dAY|dAy)$");
                            regex adrChecker("[a-zA-Z0-9]+");//���ĺ�+���ڸ��Է�
                            while (true) {
                                current_user->restaurant.at(select - 1).print_info2();
                                cout << "�ð�/�޹�����: ";
                                getline(cin, input);
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//�յڰ����� �ڸ���
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                cout << "scount : " << scount << endl;
                                trim(input);
                                if (isQuit(input)) break;

                                if (scount == 0)
                                {//���� �ϳ��� ����
                                    //�޹��� �̶�� ���� or ����
                                    //�ð� �̶�� ����
                                    //�ּ� ��� ����
                                    smatch match_one;
                                    if (regex_match(input, Day_Checker))
                                    {//�޹�
                                        for (int i = 0; i < input.size(); i++) {
                                            input[i] = tolower(input[i]);
                                        }
                                        int k = 0;
                                        if (current_user->restaurant.at(select - 1).close_day.at(0) == input) {
                                            cout << "�޹��� " << input << " ����?" << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                            }
                                            else continue;
                                        }
                                        else {
                                            cout << "�޹��� " << input << " ����?" << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).close_day.at(0) = input;
                                                for (k = 0; k < 7; k++) {
                                                    if (humooil[k] == input) {
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                        cout << input << " " << k;
                                                        cout << "�޹��� �����Ϸ�" << endl;
                                                        break;
                                                    }
                                                }
                                            }
                                            else continue;
                                        }
                                    }
                                    else if (regex_match(input, match_one, Time_Checker))
                                    {//�ð�
                                        string humoo = current_user->restaurant.at(select - 1).open_hour.at(4);
                                        current_user->restaurant.at(select - 1).open_hour.clear();

                                        if (stoi(match_one.str(1)) == stoi(match_one.str(3)) && stoi(match_one.str(2)) == stoi(match_one.str(4)))
                                        {
                                            cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                            continue;
                                        }

                                        if (!(stoi(match_one.str(1)) < 24 && stoi(match_one.str(3)) < 24 && stoi(match_one.str(2)) < 60 && stoi(match_one.str(4)) < 60))
                                        {
                                            cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                            continue;
                                        }
                                        cout << "�����ð��� " << input << " �� �����" << endl;
                                        if (yesorno()) {
                                            if (stoi(match_one.str(1)) >= stoi(match_one.str(3)) && stoi(match_one.str(2)) >= stoi(match_one.str(4))) {
                                                //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(1));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(2));
                                                current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(humoo);
                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(3));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(4));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(humoo) + 1) % 7));
                                            }
                                            else {
                                                //������ �������� �ʴ� �ð�
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(1));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(2));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(3));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match_one.str(4));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(humoo);
                                            }
                                            cout << "�����ð������Ϸ�" << endl;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else
                                    {//�ּ�
                                        bool check = false;
                                        for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                            if (strcmp(input.c_str(), V_address[i].c_str()) == 0) {
                                                check = true;
                                                break;
                                            }
                                            else {
                                                check = false;
                                            }
                                        }
                                        if (!(check)) {
                                            cout << "�ּ� ��Ģ����" << endl;
                                            continue;
                                        }
                                        else {
                                            cout << "�ּ� " << input << " ���� �����" << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).address = input;
                                                cout << input << endl;
                                                cout << "�ּ� ���� �Ϸ�" << endl;
                                            }
                                            else continue;
                                        }
                                    }
                                    continue;
                                }
                                else if (scount == 1)
                                {//���� �ΰ��� ����
                                    string str1, str2;
                                    smatch match2_1, match2_2;
                                    vector<char*>stv;
                                    char* ptr1 = strtok(data_buff, "/");
                                    while (ptr1 != nullptr) {
                                        stv.push_back(ptr1);
                                        ptr1 = strtok(NULL, "/");
                                    }
                                    if (stv.size() == 2) {
                                        str1 = (string)stv[0];
                                        str2 = (string)stv[1];
                                        trim(str1);
                                        trim(str2);
                                    }
                                    else {
                                        cout << "������ ���� ����" << endl;
                                        continue;
                                    }
                                    cout << str1 << "/" << str2 << endl;

                                    if (regex_match(str1, Day_Checker))
                                    { //ù���ڿ��� �ð�
                                        for (int i = 0; i < str1.size(); i++) {
                                            str1[i] = tolower(str1[i]);
                                        }
                                        int k = 0;
                                        if (current_user->restaurant.at(select - 1).close_day.at(0) == str1) {
                                            //�޹�����
                                                //�ð� �ּ� �Ǻ�
                                            if (regex_match(str2, match2_2, Time_Checker))
                                            {//�ð�

                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str1 << "����" << endl;
                                                cout << "�����ð�: " << str2 << endl;
                                                if (yesorno()) {
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                    current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                    }
                                                    else {
                                                        //������ �������� �ʴ� �ð�
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    }
                                                    cout << "�����Ϸ�" << endl;
                                                    break;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//�ּ�
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                                    if (strcmp(str2.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "�ּ� ��Ģ����" << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str1 << "����" << endl;
                                                    cout << "�ּ� " << str2 << "����" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                        current_user->restaurant.at(select - 1).address = str2;
                                                        cout << "���� �Ϸ�" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                        else {
                                            //�޹�����

                                                //�ð� �ּ� �Ǻ� 
                                            if (regex_match(str2, match2_2, Time_Checker))
                                            {//�ð�
                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str1 << " ����" << endl;
                                                cout << "�����ð�: " << str2 << endl;
                                                if (yesorno()) {
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = str1;
                                                    for (k = 0; k < 7; k++) {
                                                        if (humooil[k] == str1) {
                                                            current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                            break;
                                                        }
                                                    }
                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                    }
                                                    else {
                                                        //������ �������� �ʴ� �ð�
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    }
                                                    cout << "�����Ϸ�" << endl;
                                                    continue;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//�ּ�
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                                    if (strcmp(str2.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "�ּ� ��Ģ����" << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str1 << "����" << endl;
                                                    cout << "�ּ� " << str2 << "����" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = str1;
                                                        for (k = 0; k < 7; k++) {
                                                            if (humooil[k] == str1) {
                                                                current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                                break;
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).address = str2;
                                                        cout << "���� �Ϸ�" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                    }
                                    else if (regex_match(str2, Day_Checker))
                                    {//�ι�° ���ڿ��� �ð�
                                        for (int i = 0; i < str2.size(); i++) {
                                            str2[i] = tolower(str2[i]);
                                        }
                                        int k = 0;
                                        if (current_user->restaurant.at(select - 1).close_day.at(0) == str2) {
                                            //�޹�����
                                                //�ð� �ּ� �Ǻ�
                                            if (regex_match(str1, match2_2, Time_Checker))
                                            {//�ð�

                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str2 << "����" << endl;
                                                cout << "�����ð�: " << str1 << endl;
                                                if (yesorno()) {
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                    current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                    }
                                                    else {
                                                        //������ �������� �ʴ� �ð�
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    }
                                                    cout << "�����Ϸ�" << endl;
                                                    break;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//�ּ�
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                                    if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "�ּ� ��Ģ����" << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str2 << "����" << endl;
                                                    cout << "�ּ� " << str1 << "����" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                        current_user->restaurant.at(select - 1).address = str1;
                                                        cout << "���� �Ϸ�" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                        else {
                                            //�޹�����

                                                //�ð� �ּ� �Ǻ� 
                                            if (regex_match(str1, match2_2, Time_Checker))
                                            {//�ð�
                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str2 << " ����" << endl;
                                                cout << "�����ð�: " << str1 << endl;
                                                if (yesorno()) {
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = str2;
                                                    for (k = 0; k < 7; k++) {
                                                        if (humooil[k] == str2) {
                                                            current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                            break;
                                                        }
                                                    }
                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                    }
                                                    else {
                                                        //������ �������� �ʴ� �ð�
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    }
                                                    cout << "�����Ϸ�" << endl;
                                                    continue;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//�ּ�
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                                    if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "�ּ� ��Ģ����" << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str2 << "����" << endl;
                                                    cout << "�ּ� " << str1 << "����" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = str2;
                                                        for (k = 0; k < 7; k++) {
                                                            if (humooil[k] == str2) {
                                                                current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                                break;
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).address = str1;
                                                        cout << "���� �Ϸ�" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                    }
                                    else
                                    {//�ּ�(str1)or�ð�(str2)�� ����
                                        string temp;
                                        if (regex_match(str1, Time_Checker)) {//str1�� �ð��̸� swap
                                            temp = str1;
                                            str1 = str2;
                                            str2 = str1;
                                        }
                                        bool check = false;
                                        for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                            if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                check = true;
                                                break;
                                            }
                                            else {
                                                check = false;
                                            }
                                        }
                                        if (!(check)) {
                                            cout << "�ּ� ��Ģ����" << endl;
                                            continue;
                                        }
                                        else {//�ּ� �˻� ���
                                            cout << "�ּ� ���� " << str1 << endl;
                                            cout << "���� �ð� " << str2 << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).address = str1;
                                                string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match2_2.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                }
                                                cout << "�����Ϸ�" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                    }
                                    continue;
                                }
                                else
                                {//������ ����
                                    vector<string> str;
                                    smatch match3;
                                    vector<char*>stv;
                                    char* ptr1 = strtok(data_buff, "/");
                                    while (ptr1 != nullptr) {
                                        stv.push_back(ptr1);
                                        ptr1 = strtok(NULL, "/");
                                    }
                                    if (stv.size() == 3) {
                                        str.push_back((string)stv[0]);
                                        str.push_back((string)stv[1]);
                                        str.push_back((string)stv[2]);
                                        trim(str.at(0));
                                        trim(str.at(1));
                                        trim(str.at(2));
                                    }
                                    else {
                                        cout << "������ ���� ����" << endl;
                                        continue;
                                    }
                                    cout << str.at(0) << "/" << str.at(1) << "/" << str.at(2) << endl;

                                    //������ str.[0]
                                    string day, adr, time;
                                    for (int i = 0; i < 3; i++) {
                                        if (regex_match(str.at(i), Day_Checker))
                                            day = str.at(i);
                                        else if (regex_match(str.at(i), Time_Checker))
                                            time = str.at(i);
                                        else
                                            adr = str.at(i);
                                    }

                                    cout << day << "/" << time << "/" << adr << endl;
                                    for (int i = 0; i < day.size(); i++) {
                                        day[i] = tolower(day[i]);
                                    }
                                    int k = 0;
                                    if (current_user->restaurant.at(select - 1).close_day.at(0) == day) {
                                        //�޹�����
                                            //�ð� �ּ� �Ǻ�
                                        if (regex_match(time, match3, Time_Checker))
                                        {//�ð�

                                            current_user->restaurant.at(select - 1).open_hour.clear();
                                            if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                            {
                                                cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match3.str(1)) < 24 && stoi(match3.str(3)) < 24 && stoi(match3.str(2)) < 60 && stoi(match3.str(4)) < 60))
                                            {
                                                cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                continue;
                                            }
                                            bool check = false;
                                            for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                                if (strcmp(adr.c_str(), V_address[i].c_str()) == 0) {
                                                    check = true;
                                                    break;
                                                }
                                                else {
                                                    check = false;
                                                }
                                            }
                                            if (!(check)) {
                                                cout << "�ּ� ��Ģ����" << endl;
                                                continue;
                                            }
                                            cout << "�޹��� " << day << "����" << endl;
                                            cout << "�����ð�: " << time << endl;
                                            cout << "�ּ�: " << adr << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).address = adr;
                                                current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                if (stoi(match3.str(1)) >= stoi(match3.str(3)) && stoi(match3.str(2)) >= stoi(match3.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                }
                                                cout << "�����Ϸ�" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else
                                        {//�ּ�
                                            continue;
                                        }

                                    }
                                    else {
                                        //�޹�����

                                            //�ð� �ּ� �Ǻ� 
                                        if (regex_match(time, match3, Time_Checker))
                                        {//�ð�
                                            current_user->restaurant.at(select - 1).open_hour.clear();
                                            if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                            {
                                                cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match3.str(1)) < 24 && stoi(match3.str(3)) < 24 && stoi(match3.str(2)) < 60 && stoi(match3.str(4)) < 60))
                                            {
                                                cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                continue;
                                            }
                                            bool check = false;
                                            for (int i = 0; i < 10; i++) {//�ּҰ˻�
                                                if (strcmp(adr.c_str(), V_address[i].c_str()) == 0) {
                                                    check = true;
                                                    break;
                                                }
                                                else {
                                                    check = false;
                                                }
                                            }
                                            if (!(check)) {
                                                cout << "�ּ� ��Ģ����" << endl;
                                                continue;
                                            }
                                            cout << "�޹��� " << day << " ����" << endl;
                                            cout << "�����ð�: " << time << endl;
                                            cout << "�ּ�: " << adr << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).address = adr;
                                                current_user->restaurant.at(select - 1).close_day.at(0) = day;
                                                for (k = 0; k < 7; k++) {
                                                    if (humooil[k] == day) {
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                        break;
                                                    }
                                                }
                                                string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                if (stoi(match3.str(1)) >= stoi(match3.str(3)) && stoi(match3.str(2)) >= stoi(match3.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match3.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                }
                                                cout << "�����Ϸ�" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else
                                        {
                                            continue;
                                        }

                                    }






                                    continue;
                                }

                            }
                        }
                        else
                            cout << "�ٽ� �Է��� �ּ���" << endl;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "�ٽ� �Է����ּ���" << endl;
                        }
                    }
                }
            }
            else {
                //need info
                while (true) {
                    cout << "�ΰ����� ���" << endl;
                    cout << "1. �޴�/���� ��� \n2. �ð�/�޹��� ��� \n3. �����޴�" << endl;
                    cout << "���� ����: ";
                    int select_menu;
                    cin >> select_menu;
                    cin.ignore();//���� ���� 
                    if (select_menu <= 3 && select_menu >= 1) {
                        if (select_menu == 3) break;
                        else if (select_menu == 1)
                        {
                            if (!current_user->restaurant.at(select - 1).menu.empty()) {
                                cout << "�̹� �޴��� ��ϵǾ� �ֽ��ϴ�" << endl;
                                continue;
                            }
                            string M_name, M_price, temp;
                            string input;
                            regex M_name_Checker("[a-zA-Z\\s]*");
                            regex M_price_Checker("^[1-9]?(,|[0-9])[\\S]*");
                            while (true) {
                                cout << "�޴�/��������: ";
                                getline(cin, input);
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//�յڰ����� �ڸ���
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                cout << "scount : " << scount << endl;

                                if (scount != 1) {
                                    if (isQuit(input)) break;
                                    cout << "������ ��������" << endl;
                                    continue;//������ 1�� �ƴϸ� �ٽ��Է¹ޱ�
                                }
                                trim(input);//�յڰ����� �ڸ���
                                if (!isQuit(input)) {
                                    vector<char*>stv;
                                    char* ptr1 = strtok(data_buff, "/");
                                    while (ptr1 != nullptr) {
                                        stv.push_back(ptr1);
                                        ptr1 = strtok(NULL, "/");
                                    }
                                    if (stv.size() == 2) {
                                        M_name = (string)stv[0];
                                        M_price = (string)stv[1];
                                    }
                                    else {
                                        cout << "������ ���� ����" << endl;
                                        continue;
                                    }
                                    trim(M_name);
                                    trim(M_price);
                                    if (regex_match(M_name, M_name_Checker))
                                    {
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!regex_match(M_price, M_price_Checker)) {
                                            cout << "���� ���� Ȯ��" << endl;
                                            continue;
                                        }

                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }

                                        cout << "�޴��̸�: " << M_name << endl;
                                        cout << "�޴�����: " << M_price << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                            //menu.push_back(Menu(price, M_name));
                                            cout << "��ϿϷ�!" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else if (regex_match(M_price, M_name_Checker))
                                    {
                                        temp = M_price;
                                        M_price = M_name;
                                        M_name = temp;
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!regex_match(M_price, M_price_Checker)) {
                                            cout << "���� ���� Ȯ��" << endl;
                                            continue;
                                        }
                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }
                                        cout << "�޴��̸�: " << M_name << endl;
                                        cout << "�޴�����: " << M_price << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                            cout << "��ϿϷ�!" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//�Ѵ� ���Խ� �ȸ���->���Է�
                                        cout << "�޴�/���� ���� Ȯ�ιٶ�" << endl;
                                        continue;
                                    }
                                }
                                else
                                {
                                    return;
                                }
                            }
                        }
                        else if (select_menu == 2)
                        {
                            if (!current_user->restaurant.at(select - 1).open_hour.empty()) {
                                cout << "�̹� �ΰ������� ��ϵǾ� �ֽ��ϴ�" << endl;
                                continue;
                            }
                            string hour, close_day, temp;
                            string input;
                            regex Time_Checker("([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})*$");
                            regex Day_Checker("^[a-zA-Z]+(DAY|DAy|DaY|Day|day|daY|dAY|dAy)$");
                            while (true) {
                                cout << "�ð�/�޹�����: ";
                                getline(cin, input);
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//�յڰ����� �ڸ���
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                cout << "scount : " << scount << endl;

                                if (scount != 1) {
                                    if (isQuit(input)) break;
                                    smatch match;
                                    if (regex_match(input, match, Time_Checker)) {
                                        if (stoi(match.str(1)) == stoi(match.str(3)) && stoi(match.str(2)) == stoi(match.str(4)))
                                        {
                                            cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                            continue;
                                        }

                                        if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                        {
                                            cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                            continue;
                                        }
                                        cout << "�����ð�: " << input << endl;
                                        cout << "�޹��� ����" << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).close_day.push_back("\0");
                                            current_user->restaurant.at(select - 1).close_day.push_back(to_string(-1));
                                            //�޹����̶� �ε��� ����
                                            if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(1));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(2));
                                                current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string(-1));

                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(3));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(4));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string(-1));
                                            }
                                            else {
                                                //������ �������� �ʴ� �ð�
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(1));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(2));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(3));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(match.str(4));
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string(-1));
                                            }
                                            cout << "��ϿϷ�" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {
                                        cout << "�ð� ���� Ȯ��" << endl;
                                        continue;
                                    }
                                    cout << "������ ��������" << endl;
                                    continue;//������ 1�� �ƴϸ� �ٽ��Է¹ޱ�
                                }
                                trim(input);//�յڰ����� �ڸ���
                                if (!isQuit(input)) {
                                    vector<char*>stv;
                                    char* ptr1 = strtok(data_buff, "/");
                                    while (ptr1 != nullptr) {
                                        stv.push_back(ptr1);
                                        ptr1 = strtok(NULL, "/");
                                    }
                                    if (stv.size() == 2) {
                                        hour = (string)stv[0];
                                        close_day = (string)stv[1];
                                    }
                                    else {
                                        cout << "������ ���� ����" << endl;
                                        continue;
                                    }
                                    trim(hour);
                                    trim(close_day);
                                    smatch match;
                                    if (regex_match(close_day, Day_Checker))
                                    {
                                        for (int i = 0; i < close_day.size(); i++) {
                                            close_day[i] = tolower(close_day[i]);
                                        }

                                        if (regex_match(hour, match, Time_Checker)) {
                                            if (stoi(match.str(1)) == stoi(match.str(3)) && stoi(match.str(2)) == stoi(match.str(4)))
                                            {
                                                cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                            {
                                                cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                continue;
                                            }
                                            cout << "�����ð�: " << hour << endl;
                                            cout << "�޹���: " << close_day << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).close_day.push_back(close_day);
                                                int i = 0;
                                                for (int i = 0; i < 7; i++) {
                                                    if (humooil[i] == close_day) {
                                                        current_user->restaurant.at(select - 1).close_day.push_back(to_string(i));
                                                        break;
                                                    }
                                                } //�޹����̶� �ε��� ����
                                                if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                    cout << to_string(i) << endl;
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((i + 1) % 7));
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                }
                                                cout << "��ϿϷ�" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "�ð� ���� Ȯ��" << endl;
                                            continue;
                                        }
                                    }
                                    else if (regex_match(hour, Day_Checker))
                                    {
                                        temp = hour;
                                        hour = close_day;
                                        close_day = temp;
                                        for (int i = 0; i < close_day.size(); i++) {
                                            close_day[i] = tolower(close_day[i]);
                                        }

                                        if (regex_match(hour, match, Time_Checker)) {
                                            if (stoi(match.str(1)) == stoi(match.str(3)) && stoi(match.str(2)) == stoi(match.str(4)))
                                            {
                                                cout << "����/���� �ð��� ������ �����ϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                            {
                                                cout << "24�ð� ���Ŀ� �����ּ���" << endl;
                                                continue;
                                            }
                                            cout << "�����ð�: " << hour << endl;
                                            cout << "�޹���: " << close_day << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).close_day.push_back(close_day);
                                                int i = 0;
                                                for (int i = 0; i < 7; i++) {
                                                    if (humooil[i] == close_day) {
                                                        current_user->restaurant.at(select - 1).close_day.push_back(to_string(i));
                                                        break;
                                                    }
                                                } //�޹����̶� �ε��� ����
                                                if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                    cout << to_string(i) << endl;
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((i + 1) % 7));
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(1));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(2));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(3));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(match.str(4));
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                }
                                                cout << "��ϿϷ�" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "�ð� ���� Ȯ��" << endl;
                                            continue;
                                        }
                                    }
                                    else {//�Ѵ� ���Խ� �ȸ���->���Է�
                                        cout << "�޹���/�ð� ���� Ȯ�ιٶ�" << endl;
                                        continue;
                                    }
                                }
                                else
                                {
                                    return;
                                }
                            }
                        }
                    }
                    else
                        cout << "�ٽ� �Է��� �ּ���" << endl;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "�ٽ� �Է����ּ���" << endl;
                    }
                }
            }
        }
        else {
            cout << "�ٽ� �Է��� �ּ���\n\n" << endl;
        }
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "�ٽ� �Է����ּ���" << endl;

        }
    }
}


string Manager::getDayIndex(string str)
{
    if (!strcmp(str.c_str(), "monday")) return "0";
    else if (!strcmp(str.c_str(), "tuesday")) return "1";
    else if (!strcmp(str.c_str(), "wednesday")) return "2";
    else if (!strcmp(str.c_str(), "thursday")) return "3";
    else if (!strcmp(str.c_str(), "friday")) return "4";
    else if (!strcmp(str.c_str(), "saturday")) return "5";
    else if (!strcmp(str.c_str(), "sunday")) return "6";
    else return "-1";
}



bool Manager::isin0to128(string str)
{
   int i = 0;
   cout << str << endl;
   for (i = 0; i < str.size(); i++) {
      if (!(((int)str[i] >= 0) && ((int)str[i] <= 127))) {
         return false;
      }
   }
   return true;
}


bool Manager::isQuit(string str)
{
   if (!strcmp(str.c_str(), "quit")) return true;
   return false;
}

bool Manager::isSpace(string str)
{
   for (int i = 0; i < str.length(); i++) {
      const char* check = str.c_str();
      if (isspace(check[i])) {
         cout << "������� �Է����ּ���" << endl;
         return true;
      }
   }
   return false;
}

bool Manager::isTwoSlash(string s)
{
   return false;
}


Manager::Manager()
{
   V_address = new string [10];
   for (int i = 0; i < 10; i++) {
      V_address[i] = "hwayang" + to_string(i + 1) + "dong";
   }
   humooil = new string[7];
   humooil[0] = "monday";
   humooil[1] = "tuesday";
   humooil[2] = "wednesday";
   humooil[3] = "thusday";
   humooil[4] = "friday";
   humooil[5] = "saturday";
   humooil[6] = "sunday";
}

Manager::~Manager()
{
}
void Manager::ltrim(string& s)
{
   s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
      return !isspace(ch);
      }));
}

void Manager::rtrim(string& s)
{
   s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
      return !isspace(ch);
      }).base(), s.end());
}

void Manager::trim(string& s)
{
   cout << "���� trime" << endl;
   ltrim(s);
   rtrim(s);
}
