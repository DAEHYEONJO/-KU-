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
      if (isin0to128(test_id)) cout << "�ѱ� �Է� ����" << endl;
      else continue;
      cout << (int)test_id[0] << endl;
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
      if (isSpace(test_id)) continue;
      else {
         if (!isQuit(test_id)) {
            if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
               if (regex_match(test_id, idChecker1)) {
                  readInfoTextFile();//����Ǿ��ִ°� �о����.
                  int count = 0;
                  for (count = 0; count < user.size(); count++) {//text file �ߺ��˻�
                     cout << "���尪 : " << user[count].id.c_str() << "�Է°� : " << test_id << endl;
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

                        if (regex_match(test_pw, pwChecker)) {//pw���� �ǹٸ�
                           if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
                              //�α��μ���
                              current_user = new User(user[count].id, user[count].pw);
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
      trim(c);
      if (regex_match(c, ynCheck)) {
         if (!strcmp(c.c_str(), "y")) return 1;
         return 0;
      }
      //y �Ǵ� n �Է� �������� �ٽ� ���ΰ��� �Է¹ޱ�
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
               break;
            case 3:
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
      if (!isQuit(data)) {
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
            regex upperChecker("[A-Z]");
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
            //�ؽ�Ʈ���Ͽ� �Ĵ��̸� �ֳ� ���� �˻��ϱ�
         }
         regex adrChecker("[a-zA-Z0-9]+");//���ĺ�+���ڸ��Է�
         if (!regex_match(R_address, adrChecker)) {
            cout << "�����ڸ� �Է��ϼ���" << endl;
            continue;
         }
         else {
            bool check = false;
            for (int i = 0; i < 10; i++) {//�ּҰ˻�
               cout << "4??" << endl;
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
         if (yesorno()) {
            //current_user�� ���������ü���Ϳ� ������� ���� pushback
            current_user->restaurant.push_back(Restaurant(category, R_name, R_address));
            for (int i = 0; i < current_user->restaurant.size(); i++) {
               cout << "ī�װ� : " << current_user->restaurant[i].category << "/�̸� : " << current_user->restaurant[i].name << "/�ּ� : " << current_user->restaurant[i].address << endl;
            }

            cout << "��ϿϷ�" << endl;
            return;
         }
         cout << "5??" << endl;
      }
      else return;
   }

}

void Manager::searchRestaurant()
{
}

void Manager::readInfoTextFile()
{
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
            cout << readline << endl;
            
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
      cout << V_address[i] << endl;
   }

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
