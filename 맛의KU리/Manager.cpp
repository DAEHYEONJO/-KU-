#include "Manager.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


int Manager::signUp()
{
   //id 입력받기 -> 제대로입력, 중복검사 -> pw 입력받기 -> 4자리숫자 입력 조건 충족 -> text파일에 저장하기
   //id, pw 입력 받을 때 quit 입력시 메인메뉴로 돌아가기
   /**/
   string test_id="", test_pw="";
   regex idChecker1("[a-zA-Z0-9]+");//알파벳/숫자인경우
   //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//숫자먼저시작하는경우

   while (true) {//id roof
      test_id.clear();
      test_pw.clear();
      cout << "id는 숫자와 영문자 조합이며, 6자리~10자리로 입력하세요\nid : ";
      getline(cin, test_id);
      if (!isin0to128(test_id)) {
          cout << "한국어 입력 금지" << endl;
          continue;
      }

      if (isSpace(test_id)) continue;
      else {
         if (!isQuit(test_id)) {//quit 아니면
            if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
               if (regex_match(test_id, idChecker1)) {
                  cout << "조건맞음\n" << endl;
                  readInfoTextFile();//저장되어있는거 읽어오기.
                  int count = 0;
                  for (count = 0; count < user.size(); count++) {//text file 중복검사
                     cout << "저장값 : " << user[count].id.c_str() << "입력값 : " << test_id << endl;
                     if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
                  }
                  if (count == user.size()) {
                     cout << "중복되는 id 없음\n" << endl;
                     while (true) {//pw roof
                        cout << "pw는 숫자만으로 이루어져 있으며, 4자리로 입력하세요\npw : ";
                        regex pwChecker("^[0-9]{4}$");
                        getline(cin, test_pw);//pw입력받기
                        if (!isin0to128(test_pw)) {
                            cout << "한국어 입력 금지" << endl;
                            continue;
                        }
                        if (regex_match(test_pw, pwChecker)) {
                           cout << "아이디 패스워드 모두 완료\n" << endl;
                           //info.txt에 해당 아이디 패스워드 추가하기.
                           ofstream writeFile;
                           writeFile.open("info.txt", std::ofstream::out | std::ofstream::app);//쓰기모드, 이어서 추가하기
                           if (writeFile.is_open()) {
                              string merge = test_id + "/" + test_pw + "\n";
                              writeFile.write(merge.c_str(), merge.size());
                           }
                           else {
                              cout << "파일 오픈 오류\n" << endl;
                           }
                           writeFile.close();
                           readInfoTextFile();//새로 추가되었으니 user벡터에 추가해주기
                           return 1;
                        }
                        else {
                           cout << "pw 조건 오류\n" << endl;
                        }
                     }
                  }
                  else {
                     cout << "id 중복\n" << endl;
                  }
               }
               else {
                  cout << "영문자와 숫자를 포함하여 주세요\n" << endl;
               }
            }
            else {
               cout << "id 길이 조건 오류\n" << endl;
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
   cout << "로그인이다\n" << endl;
   regex idChecker1("[a-zA-Z0-9]+");//영어먼저시작하는경우
   //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//숫자먼저시작하겹치다는경우

   while (true) {//로그인 성공하면 current_user에 로그인한 유저 정보 저장됨
      cout << "id : ";
      string test_id, test_pw;
      getline(cin, test_id);
      if (!isin0to128(test_pw)) {
          cout << "한국어 입력 금지" << endl;
          continue;
      }
      if (isSpace(test_id)) continue;
      else {
         if (!isQuit(test_id)) {
            if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
               if (regex_match(test_id, idChecker1)) {
                  readInfoTextFile();//저장되어있는거 읽어오기.
                  readRestTextFile();
                  int count = 0;
                  for (count = 0; count < user.size(); count++) {//text file 중복검사
                     cout << "아이디저장값 : " << user[count].id.c_str() << "입력값 : " << test_id << endl;
                     if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
                  }
                  if (count == user.size()) {//중복된 아이디 없으면 다시입력받기
                     cout << "중복된 아이디 없음.\n" << endl;
                  }
                  else {
                     while (true) {
                        cout << "pw : ";
                        regex pwChecker("^[0-9]{4}$");
                        getline(cin, test_pw);//pw입력받기
                        if (!isin0to128(test_pw)) {
                            cout << "한국어 입력 금지" << endl;
                            continue;
                        }
                        if (regex_match(test_pw, pwChecker)) {//pw형식 옳바름
                           if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
                              //로그인성공
                              current_user = new User(user[count].id, user[count].pw);
                                for (int i = 0; i < user[count].restaurant.size();i++) {
                                    current_user->restaurant.push_back(Restaurant(user[count].restaurant[i].category,
                                        user[count].restaurant[i].name,
                                        user[count].restaurant[i].address));
                                    cout << "현재유져 : " << current_user->restaurant[i].category
                                        << current_user->restaurant[i].name
                                        << current_user->restaurant[i].address << endl;
                                }
                              
                              //로그인 성공한 계정 접속
                              cout << "로그인 성공!\n id: " << user[count].id << endl;
                              return 1;
                           }
                           else {
                              cout << "비밀번호가 일치하지 않습니다.\n" << endl;
                           }

                        }
                        else {
                           cout << "옳바르지 않은 pw형식\n" << endl;
                        }
                     }


                  }
               }
            }
            else {
            cout << "id 길이 조건 오류\n" << endl;
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
      cout << "1. 로그인\t2. 회원가입\n>>보기선택 : ";
      
      regex menuChecker("^(1|2){1}$");

      getline(cin, test_menu);
      if (!isin0to128(test_menu)) {
          cout << "한국어 입력 금지" << endl;
          continue;
      }
      if (regex_match(test_menu, menuChecker)) {//입력값이 1 또는 2이면 진행
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
            cout << "이 문장 절대나오면 안됨 나오면 말해줘.\n" << endl;
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
          cout << "한국어 입력 금지" << endl;
          continue;
      }
      trim(c);
      if (regex_match(c, ynCheck)) {
         if (!strcmp(c.c_str(), "y")) return 1;
         return 0;
      }
      //y 또는 n 입력 안했을때 다시 위로가서 입력받기
   }
   return false;
}

int Manager::mainMenu()
{
   while (true) {
      cout << "1. 식당등록\t2.식당관리\t3. 식당검색\t4. 종료 : ";
      regex menuChecker("^([1-4]){1}$");
      string test_menu = "";
      getline(cin, test_menu);
      if (!isin0to128(test_menu)) {
          cout << "한국어 입력 금지" << endl;
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
               break;
            default:
               cout << "이 말 절대나오면안됨" << endl;
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
      cout << "카테고리/식당이름/식당주소" << endl << "입력하세요<<";
   //   data = "";
      getline(cin,data);
      if (!isin0to128(data)) {
          cout << "한국어 입력 금지" << endl;
          continue;
      }
      trim(data);//앞뒤공백은 자르기
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

          if (scount != 2) continue;//슬래시 2개 아니면 다시입력받기
      
          trim(data);//앞뒤공백은 자르기
      
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
                cout << "카테고리 영문자만 입력하세요" << endl;
                continue;
             }
             else {
                if (!((strcmp(category.c_str(), "japanese") == 0) || (strcmp(category.c_str(), "chinese") == 0) || (strcmp(category.c_str(), "korean") == 0) || (strcmp(category.c_str(), "western") == 0)))
                {//카테고리 검사
                   cout << "2??" << endl;
                   cout << "카테고리 4중에 한개만 입력해주세요ㅅㅂ" << endl;
                   continue;
                }
             }
         
             //이름검사
             regex nameChecker("[a-zA-Z[:space:]]+");
             if (!regex_match(R_name, nameChecker)) {
                cout << "식당 이름 영문자 또는 영문자와 공백 조합으로 입력하세요" << endl;
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
                char* ptr = strtok(buf, " \t");//공백+탭 조합도 판별하기위함
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
                    cout << "길이 1~15" << endl;
                    continue;
                }
                //텍스트파일에 식당이름 있나 없나 검사하기
                bool check = false;
                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].name.c_str(), R_name.c_str())) {
                            cout << "중복된 식당 이름이 있습니다\n" << endl;
                            check = true;
                            break;
                        }
                    }
                }
                if (check) continue;
             }
             regex adrChecker("[a-zA-Z0-9]+");//알파벳+숫자만입력
             if (!regex_match(R_address, adrChecker)) {
                cout << "영문자만 입력하세요" << endl;
                continue;
             }
             else {
                bool check = false;
                for (int i = 0; i < 10; i++) {//주소검사
                   if (strcmp(R_address.c_str(), V_address[i].c_str()) == 0) {
                      check = true;
                      break;
                   }
                   else {
                      check = false;
                   }
                }
                if (!(check)) {
                   cout << "주소 규칙위반" << endl;
                   continue;
                }
             }
         
             //모든항목 검사완료시 카테고리: *** 이름: *** 주소: *** 출력 후 y_n 받아야함 
             cout << "카테고리: " << category << "\n이름: " << R_name << "\n주소: " << R_address << endl;
             if (yesorno()) {//current_user의 레스토랑객체벡터에 레스토랑 만들어서 pushback
                 ofstream writeRestaurant;

                 writeRestaurant.open("Restaurant.txt", std::ofstream::out | std::ofstream::app);//쓰기모드, 이어서 추가하기
                 if (writeRestaurant.is_open()) {
                     string merge = current_user->id + "/" + category + "/" + R_name + "/" + R_address + "\n";
                     writeRestaurant.write(merge.c_str(), merge.size());
                 }
                 else {
                     cout << "파일 오픈 오류\n" << endl;
                 }
                 writeRestaurant.close();
                 readRestTextFile();

                current_user->restaurant.push_back(Restaurant(category, R_name, R_address));
                current_user->print();

                cout << "등록완료" << endl;
                return;
             }
             else {
                 cout << "추가안해\n" << endl;
                 continue;
             }
      }
      else return;
   }

}

void Manager::searchRestaurant()
{
    cout << "현재 내 지역/시간/요일 :" << endl;
    string data="";
    getline(cin, data);


}

void Manager::readInfoTextFile()
{
   user.clear();//user 초기화
   char readline[16];//한 줄 최대 16글자 id->10, /->1, pw->4, \n->1
   char** temp_info = new char* [2];
   for (int i = 0; i < 2; i++) {
      temp_info[i] = new char[10];//그냥 크게 10으로 잡음
   }
   ifstream readFile;
   readFile.open("info.txt");
   if (readFile.is_open()) {
      
      while (!readFile.eof()) {
         readFile.getline(readline, 16);
         if (!readFile.eof()) {//eof일때 strtok안해줄라고
            cout << readline << endl;
            
            temp_info[0] = strtok(readline, "/");//id
            temp_info[1] = strtok(NULL, "/");//pw

            user.push_back(User(temp_info[0], temp_info[1]));
         }
      }
      for (int i = 0; i < user.size(); i++) {
          cout << "readinfo에서 user에 저장된값" << user[i].id << "/" << user[i].pw << endl;
      }
   }
   else {
      cout << "파일이 오픈되지 않음\n" << endl;
   }
   readFile.close();

  
}

void Manager::readRestTextFile()
{
    for (int i = 0; i < user.size(); i++) user[i].restaurant.clear();

    ifstream readRestaurant;
    char** temp_info_R = new char* [4];
    for (int i = 0; i < 4; i++) {
        temp_info_R[i] = new char[16];//그냥 크게 10으로 잡음
    }
    char* ptr = nullptr;
    char readlineR[50];//한 줄 최대 50글자 id->10, /->3, 카테고리->8, 식당이름->15, 주소->13\n->1
    readRestaurant.open("Restaurant.txt");
    if (readRestaurant.is_open()) {
        while (!readRestaurant.eof()) {
            readRestaurant.getline(readlineR, 50);
            if (!readRestaurant.eof()) {//eof일때 strtok안해줄라고
                //cout << "textfile : "<<readlineR << endl;

                temp_info_R[0] = strtok(readlineR, "/");//id
                temp_info_R[1] = strtok(NULL, "/");//category
                temp_info_R[2] = strtok(NULL, "/");//식당이름
                temp_info_R[3] = strtok(NULL, "/");//식당주소
                
                for (int i = 0; i < user.size(); i++) {//회원가입은 했지만 식당 안등록한새끼들은 user객체에 식당없음
                   
                    if (!strcmp(user[i].id.c_str(), temp_info_R[0])) {
                        user[i].restaurant.push_back(Restaurant(temp_info_R[1], temp_info_R[2], temp_info_R[3]));
                  
                    }
                    //cout << "i : " << i << endl;
                   // user[i].print();
                }
            }
        }
    }
    else {
        cout << "Restaurant.txt not open\n\n" << endl;
    }
    readRestaurant.close();
}

void Manager::ManageRestaurant()
{

    while (true) {
        int select;
        cout << "<<식당 리스트>>" << endl;
        current_user->printMyRest();
        cout << "보기선택 : ";
        cin >> select;
        cin.ignore();//버퍼 제거 
        if (select <= current_user->restaurant.size() + 1 && select >= 1) {
            if (select == current_user->restaurant.size() + 1) return;
            if (current_user->restaurant.at(select - 1).register_Status()) {
                cout << "부가정보 수정" << endl;
                cout << "1. 메뉴/가격 등록 \n2. 시간/휴무일 등록 \n3. 이전메뉴" << endl;
                while (true) {
                    cout << "보기 선택: ";
                    int select;
                    cin >> select;
                    cin.ignore();//버퍼 제거 
                    if (select <= 3 && select >= 1) {
                        if (select == 3) return;
                        else if (select == 1) cout << "setMenu()";
                        else if (select == 2) cout << "setMore_info()";
                    }
                    else
                        cout << "다시 입력해 주세요" << endl;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "다시 입력해주세요" << endl;
                    }
                }
            }
            else {
                while (true) {
                    cout << "부가정보 등록" << endl;
                    cout << "1. 메뉴/가격 등록 \n2. 시간/휴무일 등록 \n3. 이전메뉴" << endl;
                    cout << "보기 선택: ";
                    int select;
                    cin >> select;
                    cin.ignore();//버퍼 제거 
                    if (select <= 3 && select >= 1) {
                        if (select == 3) return;
                        else if (select == 1)
                        {
                            string M_name, M_price, temp;
                            string input;
                            regex M_name_Checker("[a-zA-Z\\s]*");
                            regex M_price_Checker("^[1-9]?(,|[0-9])*");
                            while (true) {
                                cout << "메뉴/가격정보: ";
                                getline(cin, input);
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//앞뒤공백은 자르기
                                if (!isQuit(input))
                                {
                                    M_name = string(strtok(data_buff, "/"));
                                    M_price = string(strtok(NULL, "/"));
                                    char* price = new char[M_price.size()];
                                    int count = 0;
                                    const char* m = M_price.c_str();
                                    trim(M_name);
                                    trim(M_price);
                                    if (regex_match(M_name, M_name_Checker))
                                    {
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!regex_match(M_price, M_price_Checker)) {
                                            cout << "가격 형식 확인" << endl;
                                            continue;
                                        }

                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }

                                        cout << "메뉴이름: " << M_name << endl;
                                        cout << "메뉴가격: " << M_price << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).menu.push_back(Menu(M_price, M_name));
                                            //menu.push_back(Menu(price, M_name));
                                            cout << "등록완료!" << endl;
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
                                            cout << "가격 형식 확인" << endl;
                                            continue;
                                        }
                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }
                                        cout << "메뉴이름: " << M_name << endl;
                                        cout << "메뉴가격: " << M_price << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).menu.push_back(Menu(M_price, M_name));
                                            cout << "등록완료!" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//둘다 정규식 안맞음->재입력
                                        cout << "메뉴/가격 형식 확인바람" << endl;
                                        continue;
                                    }
                                }
                                else
                                {
                                    return;
                                }
                            }
                            break;
                        }
                        else if (select == 2) cout << "addMore_info()" << endl;
                    }
                    else
                        cout << "다시 입력해 주세요" << endl;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "다시 입력해주세요" << endl;
                    }
                }
            }
        }
        else {
            cout << "다시 입력해 주세요\n\n" << endl;
        }
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "다시 입력해주세요" << endl;

        }
    }
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
         cout << "공백없이 입력해주세요" << endl;
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
   cout << "나는 trime" << endl;
   ltrim(s);
   rtrim(s);
}
