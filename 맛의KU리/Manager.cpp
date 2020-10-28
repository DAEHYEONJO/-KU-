#include "Manager.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


bool Manager::oneSpaceLength(string& str)
{
    for (int i = 0; i < str.size(); i++) {
        str[i] = tolower(str[i]);
    }
    //cout << "R_name : " << str << endl;
    vector<char*>v;
    char* buf = new char[str.size() + 1];
    strcpy(buf, str.c_str());
    char* ptr = strtok(buf, " \t");//공백+탭 조합도 판별하기위함
    while (ptr != nullptr) {
        //cout << "3??" << endl;
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
    str = result;
    if (str.size() < 1 || str.size() > 15) {
        cout << "길이 1~15 로 입력하세요\n" << endl;
        return false;
    }
    return true;
}

int Manager::signUp()
{
    //id 입력받기 -> 제대로입력, 중복검사 -> pw 입력받기 -> 4자리숫자 입력 조건 충족 -> text파일에 저장하기
    //id, pw 입력 받을 때 quit 입력시 메인메뉴로 돌아가기
    /**/
    string test_id = "", test_pw = "";
    regex idChecker1("[a-zA-Z0-9]+");//알파벳/숫자인경우
    //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//숫자먼저시작하는경우

    while (true) {//id roof
        cout << "\n회원가입 입니다." << endl;
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
                        //cout << "조건맞음\n" << endl;
                        readInfoTextFile();//저장되어있는거 읽어오기.
                        int count = 0;
                        for (count = 0; count < user.size(); count++) {//text file 중복검사
                            //cout << "저장값 : " << user[count].id.c_str() << "입력값 : " << test_id << endl;
                            if (!strcmp(user[count].id.c_str(), test_id.c_str())) {
                              
                                break;
                            }
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
                                    cout << "회원가입 완료\n" << endl;
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
                                    cout << "잘못된 형식입니다.\n" << endl;
                                }
                            }
                        }
                        else {
                            cout << "중복된 정보입니다.\n" << endl;
                        }
                    }
                    else {
                        cout << "잘못된 형식입니다.\n" << endl;
                    }
                }
                else {
                    cout << "길이 6~10 으로 입력하세요.\n" << endl;
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
    regex idChecker1("[a-zA-Z0-9]+");//영어먼저시작하는경우
    //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//숫자먼저시작하겹치다는경우

    while (true) {//로그인 성공하면 current_user에 로그인한 유저 정보 저장됨
        cout << "\n로그인입니다." << endl;
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
                        readR_InfoTextFile();
                        readR_MenuTextFile();
                        int count = 0;
                        for (count = 0; count < user.size(); count++) {//text file 중복검사
                            //cout << "아이디저장값 : " << user[count].id.c_str() << "입력값 : " << test_id << endl;
                            if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
                        }
                        if (count == user.size()) {//중복된 아이디 없으면 다시입력받기
                            cout << "아이디가 일치하지 않습니다.\n" << endl;
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
                                if (isQuit(test_pw)) break;
                                if (regex_match(test_pw, pwChecker)) {//pw형식 옳바름
                                    if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
                                        //로그인성공
                                        current_user = new User(user[count].id, user[count].pw);
                                        for (int i = 0; i < user[count].restaurant.size(); i++) {
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
                                        //cout << "현재 로그인 한 유저의 정보 " << endl;
                                        //current_user->print();


                                        //로그인 성공한 계정 접속
                                        cout << "로그인 성공! id: " << user[count].id << endl;
                                        return 1;
                                    }
                                    else {
                                        cout << "비밀번호가 일치하지 않습니다.\n" << endl;
                                    }

                                }
                                else {
                                    cout << "잘못된 형식입니다.\n" << endl;
                                }
                            }


                        }
                    }
                }
                else {
                    cout << "길이 6~10으로 입력하세요.\n" << endl;
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
        cout << "\n1. 로그인\t2. 회원가입\n>>보기선택 : ";

        regex menuChecker("^(1|2){1}$");

        getline(cin, test_menu);
        if (!isin0to128(test_menu)) {
            cout << "한국어 입력 금지\n" << endl;
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
                //cout << "이 문장 절대나오면 안됨 나오면 말해줘.\n" << endl;
                break;
            }
        }
        else {
            cout << "잘못된 형식입니다.\n" << endl;
        }
    }
}

bool Manager::isMoney(string str)
{
    regex money("^[1-9]+[0-9,].*$");
    if (regex_match(str, money)) {
        int i = 0;
        int cc = 0;
        for (i = 0; i < str.size() - 1; i++) {
            if ((str.at(i) == ',') && (str.at(i + 1) == ',')) {
                break;
            }
        }
        for (int j = 0; j < str.size(); j++) {
            if ((str.at(j) == ',')) { cc++; }
        }
        if (i != (str.size() - 1)) {//콤마연속두개등장
            return false;
        }
        else {
            //cout << "str : " << str.size() << "cc : " << cc << endl;
            //cout << str.size() - cc << endl;
            if (((str.size() - cc) > 5) || ((str.size() - cc) < 3)) {
                //cout << "숫자 3개 이상 5개 이하 입력 가능" << endl;
                return false;
            }
            else {
                return true;
            }
        }
    }
    else {
        return false;
    }
    return false;
}

bool Manager::yesorno()
{
    string c = "";
    regex ynCheck("(y)|(n){1}$");
    while (true) {
        cout << "input y or n : ";
        getline(cin, c);
        if (!isin0to128(c)) {
            cout << "한국어 입력 금지\n" << endl;
            continue;
        }
        trim(c);
        if (regex_match(c, ynCheck)) {
            if (!strcmp(c.c_str(), "y")) {
                cout << "저장완료!\n" << endl;
                return 1;
            }
            cout << "정보를 저장하지 않습니다.\n" << endl;
            return 0;
        }
        cout << "잘못된 형식입니다.\n" << endl;
        //y 또는 n 입력 안했을때 다시 위로가서 입력받기
    }
    //cout << "정보를 저장하지 않습니다." << endl;
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
                    // cout << "요일맞음" << endl;
                    return true;
                }
            }
            if (i == 7) {
                cout << "monday ~ sunday 중 입력바랍니다.\n" << endl;
                return false;
            }
        }
        else {
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
                // cout << "시간맞음" << endl;
                return true;
            }
            else {
                return false;
            }
        }
        else { return false; }
    }
    return false;

}

bool Manager::isAddress(string str)
{
    regex adrChecker("^[a-zA-Z0-9]+(dong)$");//알파벳+숫자만입력
    if (regex_match(str, adrChecker)) {
        if ((str.size() >= 12) && (str.size() <= 13)) {
            int i = 0;
            for (i = 0; i < 10; i++) {
                if (!strcmp(V_address[i].c_str(), str.c_str())) {
                    // cout << "주소 맞음" << endl;
                    return true;
                }
            }
            if (i == 10) {
                cout << "hwayang1dong~hwayang10dong 중 입력 바랍니다.\n" << endl;
                return false;
            }
        }
        else {
            return false;
        }
    }
    return false;
}


void Manager::writeRestTextFile()
{
    ofstream writeFile;

    writeFile.open("Restaurant.txt", std::ofstream::out);
    //cout << "write Restaurant txt" << endl;
    string id_wfr;
    string category_wfr;
    string name_wfr;
    string adr_wfr;

    string str_wfr;
    for (int i = 0; i < user.size(); i++) {
        id_wfr = user.at(i).id;
        if (user.at(i).restaurant.empty()) continue;
        for (int k = 0; k < user.at(i).restaurant.size(); k++) {
            category_wfr = user.at(i).restaurant.at(k).category;
            name_wfr = user.at(i).restaurant.at(k).name;
            adr_wfr = user.at(i).restaurant.at(k).address;
            str_wfr = id_wfr + "/" + category_wfr + "/" + name_wfr + "/" + adr_wfr + "\n";
            if (writeFile.is_open()) {
                writeFile.write(str_wfr.c_str(), str_wfr.size());
                //cout << "파일에 한줄썻음" << str_wfr << endl;
                //cout << user.at(i).restaurant.at(k).menu.size() << endl;
            }
            else {
                cout << "파일 오픈 오류\n" << endl;
            }
        }
    }


    writeFile.close();
}
void Manager::writeR_MenuTextFile()
{

    ofstream writeFile;

    writeFile.open("Restaurant_Menu.txt", std::ofstream::out);
    //cout << "write R_menu txt" << endl;
    string name;
    string menu;

    string str;
    for (int i = 0; i < user.size(); i++) {
        name = "";
        for (int k = 0; k < user.at(i).restaurant.size(); k++) {
            name = user.at(i).restaurant.at(k).name;
            menu = "";
            if (user.at(i).restaurant.at(k).menu.size() == 0) continue;
            for (int j = 0; j < user.at(i).restaurant.at(k).menu.size(); j++) {
                menu += "/" + user.at(i).restaurant.at(k).menu.at(j).m_name + "/" + user.at(i).restaurant.at(k).menu.at(j).m_price;
            }
            str = name + menu + "\n";
            if (writeFile.is_open()) {
                writeFile.write(str.c_str(), str.size());
                //cout << "파일에 한줄썻음" << str << endl;
                //cout << user.at(i).restaurant.at(k).menu.size() << endl;
            }
            else {
                cout << "파일 오픈 오류\n" << endl;
            }
        }
    }


    writeFile.close();
}
void Manager::writeR_InfoTextFile()
{
    ofstream writeFile;

    writeFile.open("Restaurant_Info.txt", std::ofstream::out);
    //cout << "write R_Info txt" << endl;
    string name_info;
    string adr_info;
    string time_info;
    string day_info;

    string str_info;
    for (int i = 0; i < user.size(); i++) {
        name_info = "";
        adr_info = "";
        if (user.at(i).restaurant.empty()) continue;
        for (int k = 0; k < user.at(i).restaurant.size(); k++) {
            name_info = user.at(i).restaurant.at(k).name;
            adr_info = user.at(i).restaurant.at(k).address;

            if (user.at(i).restaurant.at(k).open_hour.empty()) continue;

            if (user.at(i).restaurant.at(k).close_day.at(0) == "\0")
                day_info = "";
            else
                day_info = "/" + user.at(i).restaurant.at(k).close_day.at(0);
            time_info = "";
            for (int j = 0; j < user.at(i).restaurant.at(k).open_hour.size() - 1; j++) {
                if (user.at(i).restaurant.at(k).open_hour.size() <= 5) {
                    if (j == 1 || j == 3) time_info += ":";
                    if (j == 2) time_info += "~";
                    time_info += user.at(i).restaurant.at(k).open_hour.at(j);
                }
                else {
                    if (j == 1 || j == 3 || j == 6 || j == 8) time_info += ":";
                    if (j == 2 || j == 7) time_info += "~";
                    if (j == 5) time_info += ",";
                    if (j == 4) continue;
                    time_info += user.at(i).restaurant.at(k).open_hour.at(j);
                }
            }

            str_info = name_info + "/" + adr_info + "/" + time_info + day_info + "\n";
            if (writeFile.is_open()) {
                writeFile.write(str_info.c_str(), str_info.size());
                //cout << "파일에 한줄썻음" << str_info << endl;
                // cout << user.at(i).restaurant.at(k).menu.size() << endl;
            }
            else {
                cout << "파일 오픈 오류\n" << endl;
            }
        }
    }


    writeFile.close();

}

int Manager::mainMenu()
{
    while (true) {
        cout << "\n1. 식당등록\t2.식당관리\t3. 식당검색\t4. 종료 : ";
        regex menuChecker("^([1-4]){1}$");
        string test_menu = "";
        getline(cin, test_menu);
        if (!isin0to128(test_menu)) {
            cout << "한국어 입력 금지\n" << endl;
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
                    searchRestaurant();
                    break;
                default:
                    cout << "이 말 절대나오면안됨" << endl;
                    break;
                }
            }
        }
        else {
            cout << "잘못된 형식입니다.\n" << endl;
        }
    }
}

void Manager::registerRestaurant()
{
    vector<User>temp_user;
    int scount = 0;//slash count
    string data = "", category = "", R_name = "", R_address = "";
    char* data_buff = nullptr;
    while (true) {
        scount = 0;
        cout << "\n\n카테고리는 korean, japanese, chinese, western 중 한개 입력하세요" << endl;
        cout << "식당이름은 영문자 또는 영문자,공백문자 조합이며\n 공백개수 제외 1자리 ~ 15자리 사이로 입력하세요." << endl;
        cout << "식당이름 입력시 문자들 사이 2개 이상의 공백은 1개로 간주합니다." << endl;
        cout << "식당주소는 hwayang1dong ~ hwayang10dong 중 한개의 동만 입력하세요." << endl;
        cout << "카테고리/식당이름/식당주소" << endl << "입력하세요<<";
        //   data = "";
        getline(cin, data);
        if (!isin0to128(data)) {
            cout << "한국어 입력 금지\n" << endl;
            continue;
        }
        trim(data);//앞뒤공백은 자르기
        if (!isQuit(data)) {
            //cout << "data : " << data << endl;
            //cout << "datasize : " << data.size() << endl;
            data_buff = new char[data.size() + 1];
            strcpy(data_buff, data.c_str());
            for (int i = 0; i < data.size(); i++) {
                if ((int)data[i] == 47)
                    scount++;
            }
            //cout << "scount : " << scount << endl;

            if (scount != 2) {
                cout << "잘못된 형식입니다.\n" << endl;
                continue;//슬래시 2개 아니면 다시입력받기
            }

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

            //cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;
            trim(category);
            trim(R_name);
            trim(R_address);
            //cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;

            regex categoryChecker("^[a-z].*$");
            if (!regex_match(category, categoryChecker)) {
                cout << "잘못된 형식입니다.\n" << endl;
                continue;
            }
            else {
                if (!((strcmp(category.c_str(), "japanese") == 0) || (strcmp(category.c_str(), "chinese") == 0) || (strcmp(category.c_str(), "korean") == 0) || (strcmp(category.c_str(), "western") == 0)))
                {//카테고리 검사
                    //cout << "2??" << endl;
                    cout << "잘못된 형식입니다.\n" << endl;
                    continue;
                }
            }

            //이름검사
            regex nameChecker("[a-zA-Z[:space:]]+");
            if (!regex_match(R_name, nameChecker)) {
                cout << "잘못된 형식입니다.\n" << endl;
                continue;
            }
            else {
                for (int i = 0; i < R_name.size(); i++) {
                    R_name[i] = tolower(R_name[i]);
                }
                //cout << "R_name : " << R_name << endl;
                vector<char*>v;
                char* buf = new char[R_name.size() + 1];
                strcpy(buf, R_name.c_str());
                char* ptr = strtok(buf, " \t");//공백+탭 조합도 판별하기위함
                while (ptr != nullptr) {
                    //cout << "3??" << endl;
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
                    cout << "길이 1~15으로 입력하세요\n" << endl;
                    continue;
                }
                //텍스트파일에 식당이름 있나 없나 검사하기
                bool check = false;
                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].name.c_str(), R_name.c_str())) {
                            cout <<"중복된 정보입니다.\n" << endl;
                            check = true;
                            break;
                        }
                    }
                }
                if (check) continue;
            }
            regex adrChecker("[a-zA-Z0-9]+");//알파벳+숫자만입력
            if (!regex_match(R_address, adrChecker)) {
                cout << "잘못된 형식입니다.\n" << endl;
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
                    cout << "잘못된 형식입니다.\n" << endl;
                    continue;
                }
            }

            //모든항목 검사완료시 카테고리: *** 이름: *** 주소: *** 출력 후 y_n 받아야함 
           // cout << "카테고리: " << category << "\n이름: " << R_name << "\n주소: " << R_address << endl;
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
                current_user->restaurant.push_back(Restaurant(category, R_name, R_address));
                readRestTextFile();
                //current_user->print();

                //cout << "등록완료" << endl;
                return;
            }
            else {
               // cout << "추가안해\n" << endl;
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
    vector<string> timeV;
    while (true) {
        temp.clear();
        find_R_list.clear();
        timeV.clear();
        data.clear();
        adr.clear();
        time.clear();
        day.clear();
        int scount = 0;
        cout << "\n\n순서 무관하게 3개의 데이터를 / 로 구분하여 입력하세요." << endl;
        cout << "지역은 hwayang1dong ~ hwayang10dong 중 한개만 입력하세요." << endl;
        cout << "시간은 : 를 기준으로 시:분을 입력하세요." << endl;
        cout << "시 : 0~23, 분 : 0~59" << endl;
        cout << "요일은 monday ~ sunday 중 한개를 입력하세요." << endl;
        cout << "지역/시간/요일 :";
        getline(cin, data);
        if (isin0to128(data)) {
            trim(data);
            if (!isQuit(data)) {
                for (int i = 0; i < data.size(); i++) {
                    if ((int)data[i] == 47)
                        scount++;
                }
                if (scount != 2) {
                    cout << "잘못된 형식입니다.\n" << endl;
                    continue;//슬래시 2개 아니면 다시입력받기
                }
                buf = new char[data.size() + 1];
                strcpy(buf, data.c_str());
                ptr = strtok(buf, "/");
                while (ptr != nullptr) {
                    temp.push_back(ptr);
                    ptr = strtok(NULL, "/");
                }
                if (temp.size() != 3) {
                    cout << "잘못된 형식입니다.\n" << endl;
                    continue;
                }

                for (int i = 0; i < temp.size(); i++) {
                    string str = (string)temp[i];
                    trim(str);
                    if (isTime(str, timeV)) time = str;
                    if (isDay(str)) day = str;
                    if (isAddress(str)) adr = str;
                }
                if ((time.empty()) || (day.empty()) || (adr.empty())) {
                    cout << "잘못된 형식입니다.\n" << endl;
                    continue;
                }
               // cout << "time : " << time << "/day : " << day << "/adr : " << adr << endl;

                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].address.c_str(), adr.c_str())) {
                            if (!user[i].restaurant[j].open_hour.empty()) {
                                //입력한 지역과 식당 주소가 일치하는 식당 발견, 시간 검사 시작

                               // cout << " 쥬소 일치 식당 찾음!!!!!!" << endl;
                                //cout << "일치한 식당 : " << user[i].restaurant[j].name << endl;
                                if (user[i].restaurant[j].open_hour.size() == 5) {
                                    //식당 마감시간이 자정 안넘은경우 timeV[0]:입력 시간,timeV[1]:입력 분
                                    if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].close_day[1].c_str())) {
                                        //입력요일이 저장된 휴무일이랑 다를때만 비교하기
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[0])) {
                                            if (stoi(timeV[1]) >= stoi(user[i].restaurant[j].open_hour[1])) {//1
                                               // cout << "1번임" << endl;
                                                find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[0])) {
                                            if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[2])) {
                                                if (stoi(timeV[1]) < stoi(user[i].restaurant[j].open_hour[3])) {//2
                                                 //   cout << "2번임" << endl;
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                                }
                                            }
                                            if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[2])) {//3
                                              //  cout << "3번임" << endl;
                                                find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                    }
                                }
                                else {//식당 마감시간이 자정을 넘은 경우
                                    if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[0])) {//h==h1
                                        //앞범위인경우
                                        if (stoi(timeV[1]) >= stoi(user[i].restaurant[j].open_hour[1])) {//m>=m1
                                          //  cout << "앞 1번임" << endl;
                                            if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[4].c_str()) != 0)//내가 입력한 요일이랑 휴무일이랑 다를 경우
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }
                                    if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[0])) {//h>h1
                                        // 앞범위인경우
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[2])) {//h==23
                                            if (stoi(timeV[1]) <= stoi(user[i].restaurant[j].open_hour[3])) {//m<=59
                                            //    cout << "앞 2번임" << endl;
                                                if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[4].c_str()) != 0)//내가 입력한 요일이랑 휴무일이랑 다를 경우
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[2])) {//h<23
                                           // cout << "앞 3번임" << endl;
                                            if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[4].c_str()) != 0)//내가 입력한 요일이랑 휴무일이랑 다를 경우
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }

                                    if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[5])) {//h==00
                                        //뒷범위인경우
                                       // cout << "뒤 1번임" << endl;
                                        if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[9].c_str()) != 0)//내가 입력한 요일이랑 휴무일이랑 다를 경우
                                            find_R_list.push_back(user[i].restaurant[j]);
                                    }
                                    if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[5])) {//h>00
                                        //뒷범위인경우
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[7])) {//h==h2
                                            if (stoi(timeV[1]) < stoi(user[i].restaurant[j].open_hour[8])) {//m<m2
                                          //      cout << "뒤 2번임" << endl;
                                                if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[9].c_str()) != 0)//내가 입력한 요일이랑 휴무일이랑 다를 경우
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[7])) {//h<h2
                                         //   cout << "뒤 3번임" << endl;
                                            if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[9].c_str()) != 0)//내가 입력한 요일이랑 휴무일이랑 다를 경우
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
                while (true) {
                    if (find_R_list.size() == 0) {
                        cout << "일치하는 식당정보 없습니다.\n" << endl;
                        break;
                    }
                    cout << "\n\n*************************************식당목록*************************************" << endl;
                    for (int i = 0; i < find_R_list.size(); i++) {
                        cout << i + 1 << ". ";
                        find_R_list[i].print_info();
                    }
                    cout << find_R_list.size() + 1 << ". " << "메인메뉴로 가기\n" << ">> ";
                    string menu = "";
                    regex menuChecker("^([0-9]){1}$");
                    getline(cin, menu);
                    if (regex_match(menu, menuChecker)) {
                        if (!((stoi(menu) >= 1) && (stoi(menu) <= find_R_list.size() + 1))) {
                            cout << "잘못된 형식입니다.\n" << endl;
                            continue;
                        }
                        else {
                            if (stoi(menu) == find_R_list.size() + 1) {
                                return;
                            }
                            else {
                                find_R_list[stoi(menu) - 1].print_menu();
                                while (true) {
                                    cout << "뒤로 가려면 quit을 입력해주세요\n" << ">> ";
                                    menu.clear();
                                    getline(cin, menu);
                                    trim(menu);
                                    if (isQuit(menu)) break;
                                    else continue;
                                }
                            }
                        }
                    }
                    else {
                        continue;
                    }
                }


            }
            else {
                return;
            }
        }
        else {
            cout << "한글 입력 금지\n" << endl;
            continue;
        }
    }




}

void Manager::readInfoTextFile()
{
    //cout << "readInfoTextFile" << endl;
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
                temp_info[0] = strtok(readline, "/");//id
                temp_info[1] = strtok(NULL, "/");//pw

                user.push_back(User(temp_info[0], temp_info[1]));
            }
        }
    }
    else {
        cout << "파일이 오픈되지 않음\n" << endl;
    }
    readFile.close();


}

void Manager::readRestTextFile()
{
    //cout << "readRestTextFile" << endl;
    for (int i = 0; i < user.size(); i++) {
        user[i].restaurant.clear();
    }


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
                temp_info_R[0] = strtok(readlineR, "/");//id
                temp_info_R[1] = strtok(NULL, "/");//category
                temp_info_R[2] = strtok(NULL, "/");//식당이름
                temp_info_R[3] = strtok(NULL, "/");//식당주소
                for (int i = 0; i < user.size(); i++) {//회원가입은 했지만 식당 안등록한새끼들은 user객체에 식당없음
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
    //cout << "readRestaurant close" << endl;
    readRestaurant.close();
}

void Manager::readR_InfoTextFile()
{
    //cout << "void Manager::readR_InfoTextFile()" << endl;
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
    smatch match, match2;
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
                // "/"기준으로 4개 또는 3개 짤라주기
                //1번째 : 식당이름
                //2번째 : 주소
                //3번째 : 영업시간-> 콤마가 있는지 없는지 검사하기.있으면 콤마 기준으로 짜르기.
                //                   콤마 없으면 : ~ 기준으로 짜르기, 짜른거 : 기준으로 짜르기 저장하기.
                //4번째 : 휴무일
                ptr = strtok(readlineR_I, "/");
                while (ptr != nullptr) {
                    v.push_back(ptr);
                    ptr = strtok(NULL, "/");
                }

                if (v.size() == 3) {//휴무일 없는경우시발
                    dayflag = false;
                    humoo = "";
                }
                else { humoo = v[3]; }
                string tlqkf = (string)v[2];
                if (regex_match(tlqkf, match, timeCheck)) {//콤마없는경우
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
                            user[i].restaurant[j].address = v[1];//주소
                            user[i].restaurant[j].open_hour.assign(temp.begin(), temp.end());//영업시간
                            user[i].restaurant[j].close_day.push_back(humoo);
                            user[i].restaurant[j].close_day.push_back(getDayIndex(humoo));
                        }
                    }
                }

            }
        }
    }
    else {
        cout << "Restaurant_Info.txt 안열림\n" << endl;
    }
    readR_Info.close();
}

void Manager::readR_MenuTextFile()
{
    //메뉴 최대 3개, 저장금액 최대 5자리
    //cout << "readR_MenuTextFile()" << endl;
    for (int i = 0; i < user.size(); i++) {
        for (int j = 0; j < user[i].restaurant.size(); j++) {
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
        if (current_user->restaurant.empty()) {
            cout << "등록된 식당이 없습니다 식당을 등록해 주세요" << endl;
            return;
        }
        int select;
        cout << "<<식당 리스트>>" << endl;
        current_user->printMyRest();
        cout << "보기선택 : ";
        cin >> select;
        cin.ignore();//버퍼 제거 
        if (select == current_user->restaurant.size() + 1) return;

        if (select < current_user->restaurant.size() + 1 && select >= 1) {
            if (!(current_user->restaurant.at(select - 1).menu.empty() || current_user->restaurant.at(select - 1).open_hour.empty())) {
                while (true) {
                    //full info
                   // cin.ignore();
                    cout << "부가정보 수정" << endl;
                    cout << "1. 메뉴/가격 수정 \n2. 주소/시간/휴무일 수정 \n3. 이전메뉴" << endl;
                    cout << "보기 선택: ";
                    int select_menu2;
                    cin >> select_menu2;
                    if (isQuit(to_string(select_menu2))) continue;
                    cin.ignore();//버퍼 제거
                    if (select_menu2 == 3) break;
                    if (select_menu2 < 3 && select_menu2 >= 1) {
                        if (select_menu2 == 1)
                        {
                            //메뉴수정
                            string M_name, M_price, temp;
                            string input;
                            regex M_name_Checker("[a-zA-Z\\s]*");
                            //regex M_price_Checker("^[1-9]?(,|[0-9])[\\S]*");
                            while (true) {
                                // writeR_MenuTextFile();
                                vector<Menu>::iterator iter = current_user->restaurant.at(select - 1).menu.begin();
                                if (current_user->restaurant.at(select - 1).menu.size() == 3) {
                                    cout << "메뉴를 더이상 추가할 수 없습니다." << endl;
                                }
                                current_user->restaurant.at(select - 1).print_menu();
                                cout << "메뉴/(가격) 입력: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "한국어 입력 금지" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                // cout << "scount : " << scount << endl;
                                trim(input);//앞뒤공백은 자르기

                                if (scount == 0 && !isQuit(input)) {
                                    //메뉴만 입력됨 
                                    M_name = input;
                                    if (!oneSpaceLength(M_name)) { continue; }
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
                                            cout << "삭제할 메뉴: " << M_name << endl;
                                            if (yesorno()) {
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        vector<Menu>::iterator iter2 = user.at(j).restaurant.at(select - 1).menu.begin();
                                                        for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size() - 1; i++) {
                                                            if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {
                                                                user.at(j).restaurant.at(select - 1).menu.erase(iter2 + i);
                                                                current_user->restaurant.at(select - 1).menu.erase(iter + i);
                                                            }
                                                        }
                                                    }
                                                }
                                                writeR_MenuTextFile();

                                                cout << "삭제 완료" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "잘못된 형식입니다." << endl;
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
                                            cout << "잘못된 형식입니다." << endl;
                                        continue;
                                    }
                                    trim(M_name);
                                    trim(M_price);

                                    if (regex_match(M_name, M_name_Checker))
                                    {
                                        if (!oneSpaceLength(M_name)) { continue; }
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!isMoney(M_price)) {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }
                                        bool add = true;
                                        for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size(); i++) {
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
                                            if (current_user->restaurant.at(select - 1).menu.size() == 3) {
                                                cout << "더이상 추가할 수 없습니다(최대 메뉴 3개)" << endl;
                                                continue;
                                            }
                                            cout << "추가할 메뉴이름: " << M_name << endl;
                                            cout << "추가할 메뉴가격: " << M_price << endl;
                                            if (yesorno()) {

                                                current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id)
                                                        user.at(j).restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                                }
                                                writeR_MenuTextFile();
                                                cout << "추가 완료!" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }

                                        }
                                        cout << "메뉴이름: " << M_name << endl;
                                        cout << "수정된 메뉴가격: " << M_price << endl;
                                        if (yesorno()) {

                                            for (int j = 0; j < user.size(); j++) {
                                                if (user.at(j).id == current_user->id) {
                                                    for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size(); i++) {
                                                        if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {
                                                            user.at(j).restaurant.at(select - 1).menu.at(i).m_price = M_price;
                                                            current_user->restaurant.at(select - 1).menu.at(i).m_price = M_price;
                                                        }
                                                    }
                                                }
                                            }
                                            writeR_MenuTextFile();
                                            cout << "수정 완료!" << endl;
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
                                        if (!oneSpaceLength(M_name)) { continue; }
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!isMoney(M_price)) {
                                            cout << "가격 형식 확인" << endl;
                                            continue;
                                        }
                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }
                                        cout << "메뉴이름: " << M_name << endl;
                                        cout << "수정된 메뉴가격: " << M_price << endl;
                                        if (yesorno()) {
                                            for (int j = 0; j < user.size(); j++) {
                                                if (user.at(j).id == current_user->id) {
                                                    for (int i = 0; i < current_user->restaurant.at(select - 1).menu.size() - 1; i++) {
                                                        if (current_user->restaurant.at(select - 1).menu.at(i).m_name == M_name) {
                                                            user.at(j).restaurant.at(select - 1).menu.at(i).m_price = M_price;
                                                            current_user->restaurant.at(select - 1).menu.at(i).m_price = M_price;
                                                        }
                                                    }
                                                }
                                            }
                                            writeR_MenuTextFile();
                                            cout << "수정완료!" << endl;
                                            continue;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//둘다 정규식 안맞음->재입력
                                        cout << "잘못된 형식입니다." << endl;
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
                        {//정보 수정

                            string hour, close_day, temp;
                            string input;
                            regex Time_Checker("([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})*$");
                            regex Day_Checker("^[a-zA-Z]+(DAY|DAy|DaY|Day|day|daY|dAY|dAy)$");
                            regex adrChecker("[a-zA-Z0-9]+");//알파벳+숫자만입력
                            while (true) {
                                current_user->restaurant.at(select - 1).print_info2();
                                cout << "주소/시간/휴무정보: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "한국어 입력 금지" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//앞뒤공백은 자르기
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                // cout << "scount : " << scount << endl;
                                trim(input);
                                if (isQuit(input)) break;

                                if (scount == 0)
                                {//셋중 하나의 정보
                                    //휴무일 이라면 삭제 or 수정
                                    //시간 이라면 수정
                                    //주소 라면 수정
                                    smatch match_one;
                                    if (regex_match(input, Day_Checker))
                                    {//휴무
                                        for (int i = 0; i < input.size(); i++) {
                                            input[i] = tolower(input[i]);
                                        }
                                        int k = 0;
                                        if (current_user->restaurant.at(select - 1).close_day.at(0) == input) {
                                            cout << "휴무일 " << input << " 삭제" << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).close_day.at(0) = "\0";
                                                        user.at(j).restaurant.at(select - 1).close_day.at(1) = "-1";
                                                    }
                                                }
                                                writeR_InfoTextFile();
                                                cout << "삭제 완료" << endl;
                                            }
                                            else continue;
                                        }
                                        else {
                                            cout << "휴무일 " << input << " 수정" << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).close_day.at(0) = input;
                                                for (k = 0; k < 7; k++) {
                                                    if (humooil[k] == input) {
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                        cout << input << " " << k;

                                                        break;
                                                    }
                                                }
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).close_day.at(0) = input;
                                                        user.at(j).restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                    }
                                                }
                                                writeR_InfoTextFile();
                                                cout << "수정 완료" << endl;
                                            }
                                            else continue;
                                        }
                                    }
                                    else if (regex_match(input, match_one, Time_Checker))
                                    {//시간
                                        string humoo = current_user->restaurant.at(select - 1).open_hour.at(4);
                                        current_user->restaurant.at(select - 1).open_hour.clear();

                                        if (stoi(match_one.str(1)) == stoi(match_one.str(3)) && stoi(match_one.str(2)) == stoi(match_one.str(4)))
                                        {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }

                                        if (!(stoi(match_one.str(1)) < 24 && stoi(match_one.str(3)) < 24 && stoi(match_one.str(2)) < 60 && stoi(match_one.str(4)) < 60))
                                        {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }
                                        cout << "영업시간 " << input << " 수정" << endl;
                                        if (yesorno()) {
                                            string temp[4];
                                            temp->clear();
                                            for (int i = 0; i < 4; i++) {
                                                temp[i] = match_one.str(i + 1);
                                                if (match_one.str(i + 1).size() == 1) {
                                                    temp[i] = "0" + match_one.str(i + 1);
                                                }
                                            }
                                            if (stoi(match_one.str(1)) >= stoi(match_one.str(3)) && stoi(match_one.str(2)) >= stoi(match_one.str(4))) {
                                                //앞시간이 뒷시간 보다 크면나누어 저장
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(humoo);
                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(humoo) + 1) % 7));
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                    }
                                                }
                                            }
                                            else {
                                                //자정을 포함하지 않는 시간
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(humoo);
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                    }
                                                }
                                            }
                                            writeR_InfoTextFile();
                                            cout << "수정 완료" << endl;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else
                                    {//주소
                                        bool check = false;
                                        for (int i = 0; i < 10; i++) {//주소검사
                                            if (strcmp(input.c_str(), V_address[i].c_str()) == 0) {
                                                check = true;
                                                break;
                                            }
                                            else {
                                                check = false;
                                            }
                                        }
                                        if (!(check)) {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }
                                        else {
                                            cout << "주소 " << input << " 수정" << endl;
                                            if (yesorno()) {
                                                current_user->restaurant.at(select - 1).address = input;
                                                cout << input << endl;
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).address = input;
                                                    }
                                                }
                                                writeR_InfoTextFile();
                                                writeRestTextFile();
                                                cout << "수정 완료" << endl;
                                            }
                                            else continue;
                                        }
                                    }
                                    continue;
                                }
                                else if (scount == 1)
                                {//셋중 두개의 정보
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
                                        cout << "잘못된 형식입니다." << endl;
                                        continue;
                                    }
                                    cout << str1 << "/" << str2 << endl;

                                    if (regex_match(str1, Day_Checker))
                                    { //첫문자열이 시간
                                        for (int i = 0; i < str1.size(); i++) {
                                            str1[i] = tolower(str1[i]);
                                        }
                                        int k = 0;
                                        if (current_user->restaurant.at(select - 1).close_day.at(0) == str1) {
                                            //휴무삭제
                                                //시간 주소 판별
                                            if (regex_match(str2, match2_2, Time_Checker))
                                            {//시간

                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                cout << "휴무일 " << str1 << " 삭제" << endl;
                                                cout << "영업시간: " << str2 << " 수정" << endl;
                                                if (yesorno()) {
                                                    string temp[4];
                                                    temp->clear();
                                                    for (int i = 0; i < 4; i++) {
                                                        temp[i] = match2_2.str(i + 1);
                                                        if (match2_2.str(i + 1).size() == 1) {
                                                            temp[i] = "0" + match2_2.str(i + 1);
                                                        }
                                                    }
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                    current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).close_day.at(0) = "\0";
                                                            user.at(j).restaurant.at(select - 1).close_day.at(1) = "-1";
                                                        }
                                                    }
                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //앞시간이 뒷시간 보다 크면나누어 저장
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);

                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }

                                                    }
                                                    else {
                                                        //자정을 포함하지 않는 시간
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);

                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    writeR_InfoTextFile();
                                                    cout << "수정 완료" << endl;
                                                    break;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//주소
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//주소검사
                                                    if (strcmp(str2.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "휴무일 " << str1 << " 삭제" << endl;
                                                    cout << "주소 " << str2 << " 수정" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                        current_user->restaurant.at(select - 1).address = str2;
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).close_day.at(0) = "\0";
                                                                user.at(j).restaurant.at(select - 1).close_day.at(1) = "-1";
                                                            }
                                                        }
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).address = str2;
                                                            }
                                                        }
                                                        writeR_InfoTextFile();
                                                        writeRestTextFile();
                                                        cout << "수정 완료" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                        else {
                                            //휴무변경

                                                //시간 주소 판별 
                                            if (regex_match(str2, match2_2, Time_Checker))
                                            {//시간
                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                cout << "휴무일 " << str1 << " 수정" << endl;
                                                cout << "영업시간: " << str2 << " 수정" << endl;
                                                if (yesorno()) {
                                                    string temp[4];
                                                    temp->clear();
                                                    for (int i = 0; i < 4; i++) {
                                                        temp[i] = match2_2.str(i + 1);
                                                        if (match2_2.str(i + 1).size() == 1) {
                                                            temp[i] = "0" + match2_2.str(i + 1);
                                                        }
                                                    }
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = str1;
                                                    for (k = 0; k < 7; k++) {
                                                        if (humooil[k] == str1) {
                                                            current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                            break;
                                                        }
                                                    }
                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).close_day.at(0) = str1;
                                                            user.at(j).restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                        }
                                                    }

                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //앞시간이 뒷시간 보다 크면나누어 저장
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    else {
                                                        //자정을 포함하지 않는 시간
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    writeR_InfoTextFile();
                                                    cout << "수정 완료" << endl;
                                                    continue;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//주소
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//주소검사
                                                    if (strcmp(str2.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "휴무일 " << str1 << " 수정" << endl;
                                                    cout << "주소 " << str2 << " 수정" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = str1;
                                                        for (k = 0; k < 7; k++) {
                                                            if (humooil[k] == str1) {
                                                                current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                                break;
                                                            }
                                                        }
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).close_day.at(0) = str1;
                                                                user.at(j).restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).address = str2;

                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).address = str2;
                                                            }
                                                        }
                                                        writeR_InfoTextFile();
                                                        writeRestTextFile();
                                                        cout << "수정 완료" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                    }
                                    else if (regex_match(str2, Day_Checker))
                                    {//두번째 문자열이 시간
                                        for (int i = 0; i < str2.size(); i++) {
                                            str2[i] = tolower(str2[i]);
                                        }
                                        int k = 0;
                                        if (current_user->restaurant.at(select - 1).close_day.at(0) == str2) {
                                            //휴무삭제
                                                //시간 주소 판별
                                            if (regex_match(str1, match2_2, Time_Checker))
                                            {//시간

                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                cout << "휴무일 " << str2 << " 삭제" << endl;
                                                cout << "영업시간: " << str1 << " 수정" << endl;
                                                if (yesorno()) {
                                                    string temp[4];
                                                    temp->clear();
                                                    for (int i = 0; i < 4; i++) {
                                                        temp[i] = match2_2.str(i + 1);
                                                        if (match2_2.str(i + 1).size() == 1) {
                                                            temp[i] = "0" + match2_2.str(i + 1);
                                                        }
                                                    }
                                                    current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                    current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).close_day.at(0) = "\0";
                                                            user.at(j).restaurant.at(select - 1).close_day.at(1) = "-1";
                                                        }
                                                    }
                                                    string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                    string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                    if (stoi(match2_2.str(1)) >= stoi(match2_2.str(3)) && stoi(match2_2.str(2)) >= stoi(match2_2.str(4))) {
                                                        //앞시간이 뒷시간 보다 크면나누어 저장
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    else {
                                                        //자정을 포함하지 않는 시간
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    writeR_InfoTextFile();
                                                    cout << "수정 완료" << endl;
                                                    break;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//주소
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//주소검사
                                                    if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "휴무일 " << str2 << " 삭제" << endl;
                                                    cout << "주소 " << str1 << " 수정" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                        current_user->restaurant.at(select - 1).address = str1;

                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).close_day.at(0) = "\0";
                                                                user.at(j).restaurant.at(select - 1).close_day.at(1) = "-1";
                                                            }
                                                        }
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).address = str1;
                                                            }
                                                        }
                                                        writeR_InfoTextFile();
                                                        writeRestTextFile();
                                                        cout << "수정 완료" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                        else {
                                            //휴무변경

                                                //시간 주소 판별 
                                            if (regex_match(str1, match2_2, Time_Checker))
                                            {//시간
                                                current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match2_2.str(1)) == stoi(match2_2.str(3)) && stoi(match2_2.str(2)) == stoi(match2_2.str(4)))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                cout << "휴무일 " << str2 << " 수정" << endl;
                                                cout << "영업시간: " << str1 << " 수정" << endl;
                                                if (yesorno()) {
                                                    string temp[4];
                                                    temp->clear();
                                                    for (int i = 0; i < 4; i++) {
                                                        temp[i] = match2_2.str(i + 1);
                                                        if (match2_2.str(i + 1).size() == 1) {
                                                            temp[i] = "0" + match2_2.str(i + 1);
                                                        }
                                                    }
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
                                                        //앞시간이 뒷시간 보다 크면나누어 저장
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    else {
                                                        //자정을 포함하지 않는 시간
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                        current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                            }
                                                        }
                                                    }
                                                    writeR_InfoTextFile();
                                                    cout << "수정 완료" << endl;
                                                    continue;
                                                }
                                                else {
                                                    continue;
                                                }
                                            }
                                            else
                                            {//주소
                                                bool check = false;
                                                for (int i = 0; i < 10; i++) {//주소검사
                                                    if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                        check = true;
                                                        break;
                                                    }
                                                    else {
                                                        check = false;
                                                    }
                                                }
                                                if (!(check)) {
                                                    cout << "잘못된 형식입니다." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "휴무일 " << str2 << " 수정" << endl;
                                                    cout << "주소 " << str1 << " 수정" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = str2;
                                                        for (k = 0; k < 7; k++) {
                                                            if (humooil[k] == str2) {
                                                                current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                                break;
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).address = str1;
                                                        //cout << "수정 완료" << endl;
                                                        //

                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).close_day.at(0) = str2;
                                                                user.at(j).restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                            }
                                                        }
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).address = str1;
                                                            }
                                                        }
                                                        writeR_InfoTextFile();
                                                        writeRestTextFile();
                                                        cout << "수정 완료" << endl;
                                                    }
                                                    else continue;
                                                }
                                            }

                                        }
                                    }
                                    else if (regex_match(str1, Time_Checker))
                                    {
                                        string temp;
                                        temp = str1;
                                        str1 = str2;
                                        str2 = temp;
                                        {
                                            bool check = false;
                                            for (int i = 0; i < 10; i++) {//주소검사
                                                if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                    check = true;
                                                    break;
                                                }
                                                else {
                                                    check = false;
                                                }
                                            }
                                            if (!(check)) {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            else {//주소 검사 통과 
                                                smatch match3;



                                                if (regex_match(str2, match3, Time_Checker))
                                                {
                                                    if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                                    {
                                                        cout << "잘못된 형식입니다." << endl;
                                                        continue;
                                                    }

                                                    cout << "주소 " << str1 << " 수정" << endl;
                                                    cout << "영업 시간 " << str2 << " 수정" << endl;
                                                    if (yesorno()) {
                                                        string temp[4];
                                                        temp->clear();
                                                        for (int i = 0; i < 4; i++) {
                                                            temp[i] = match3.str(i + 1);
                                                            if (match3.str(i + 1).size() == 1) {
                                                                temp[i] = "0" + match3.str(i + 1);
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).open_hour.clear();
                                                        current_user->restaurant.at(select - 1).address = str1;
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).address = str1;
                                                            }
                                                        }
                                                        string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                        string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                        if (stoi(match3.str(1)) >= stoi(match3.str(3)) && stoi(match3.str(2)) > stoi(match3.str(4))) {
                                                            //앞시간이 뒷시간 보다 크면나누어 저장
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                            if (index == "-1")
                                                                current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                            else
                                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));

                                                            for (int j = 0; j < user.size(); j++) {
                                                                if (user.at(j).id == current_user->id) {
                                                                    user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                                }
                                                            }
                                                        }
                                                        else {
                                                            //자정을 포함하지 않는 시간
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(index);

                                                            for (int j = 0; j < user.size(); j++) {
                                                                if (user.at(j).id == current_user->id) {
                                                                    user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                                }
                                                            }
                                                        }
                                                        writeR_InfoTextFile();
                                                        writeRestTextFile();
                                                        cout << "수정 완료" << endl;
                                                        continue;
                                                    }
                                                    else {
                                                        continue;
                                                    }



                                                }
                                            }
                                        }
                                    }
                                    else if (regex_match(str2, Time_Checker))
                                    {//주소(str1)or시간(str2)의 조합

                                        {
                                            bool check = false;
                                            for (int i = 0; i < 10; i++) {//주소검사
                                                if (strcmp(str1.c_str(), V_address[i].c_str()) == 0) {
                                                    check = true;
                                                    break;
                                                }
                                                else {
                                                    check = false;
                                                }
                                            }
                                            if (!(check)) {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            else {//주소 검사 통과 
                                                smatch match3;



                                                if (regex_match(str2, match3, Time_Checker))
                                                {
                                                    if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                                    {
                                                        cout << "잘못된 형식입니다.." << endl;
                                                        continue;
                                                    }

                                                    cout << "주소 " << str1 << " 수정" << endl;
                                                    cout << "영업 시간 " << str2 << " 수정" << endl;
                                                    if (yesorno()) {
                                                        string temp[4];
                                                        temp->clear();
                                                        for (int i = 0; i < 4; i++) {
                                                            temp[i] = match3.str(i + 1);
                                                            if (match3.str(i + 1).size() == 1) {
                                                                temp[i] = "0" + match3.str(i + 1);
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).open_hour.clear();
                                                        current_user->restaurant.at(select - 1).address = str1;
                                                        for (int j = 0; j < user.size(); j++) {
                                                            if (user.at(j).id == current_user->id) {
                                                                user.at(j).restaurant.at(select - 1).address = str1;
                                                            }
                                                        }
                                                        string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                        string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                        if (stoi(match3.str(1)) >= stoi(match3.str(3)) && stoi(match3.str(2)) > stoi(match3.str(4))) {
                                                            //앞시간이 뒷시간 보다 크면나누어 저장
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                            if (index == "-1")
                                                                current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                            else
                                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));

                                                            for (int j = 0; j < user.size(); j++) {
                                                                if (user.at(j).id == current_user->id) {
                                                                    user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                                }
                                                            }
                                                        }
                                                        else {
                                                            //자정을 포함하지 않는 시간
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                            current_user->restaurant.at(select - 1).open_hour.push_back(index);

                                                            for (int j = 0; j < user.size(); j++) {
                                                                if (user.at(j).id == current_user->id) {
                                                                    user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                                }
                                                            }
                                                        }
                                                        writeR_InfoTextFile();
                                                        writeRestTextFile();
                                                        cout << "수정 완료" << endl;
                                                        continue;
                                                    }
                                                    else {
                                                        continue;
                                                    }



                                                }
                                            }
                                        }

                                    }
                                    continue;
                                }
                                else if (scount == 2)
                                {//세개의 정보
                                    vector<string> strd;
                                    smatch match3;
                                    vector<char*>stv;
                                    char* ptr1 = strtok(data_buff, "/");
                                    while (ptr1 != nullptr) {
                                        stv.push_back(ptr1);
                                        ptr1 = strtok(NULL, "/");
                                    }
                                    if (stv.size() == 3) {
                                        strd.push_back((string)stv[0]);
                                        strd.push_back((string)stv[1]);
                                        strd.push_back((string)stv[2]);
                                        trim(strd.at(0));
                                        trim(strd.at(1));
                                        trim(strd.at(2));
                                    }
                                    else {
                                        cout << "잘못된 형식입니다." << endl;
                                        continue;
                                    }
                                    cout << strd.at(0) << "/" << strd.at(1) << "/" << strd.at(2) << endl;

                                    //요일을 str.[0]
                                    string day, adr, time;
                                    for (int i = 0; i < 3; i++) {
                                        if (regex_match(strd.at(i), Day_Checker))
                                            day = strd.at(i);
                                        else if (regex_match(strd.at(i), Time_Checker))
                                            time = strd.at(i);
                                        else
                                            adr = strd.at(i);
                                    }

                                    cout << day << "/" << time << "/" << adr << endl;
                                    for (int i = 0; i < day.size(); i++) {
                                        day[i] = tolower(day[i]);
                                    }
                                    int k = 0;
                                    if (current_user->restaurant.at(select - 1).close_day.at(0) == day) {
                                        //휴무삭제
                                            //시간 주소 판별
                                        if (regex_match(time, match3, Time_Checker))
                                        {//시간

                                            current_user->restaurant.at(select - 1).open_hour.clear();
                                            if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                            {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match3.str(1)) < 24 && stoi(match3.str(3)) < 24 && stoi(match3.str(2)) < 60 && stoi(match3.str(4)) < 60))
                                            {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            bool check = false;
                                            for (int i = 0; i < 10; i++) {//주소검사
                                                if (strcmp(adr.c_str(), V_address[i].c_str()) == 0) {
                                                    check = true;
                                                    break;
                                                }
                                                else {
                                                    check = false;
                                                }
                                            }
                                            if (!(check)) {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            cout << "휴무일 " << day << " 삭제" << endl;
                                            cout << "영업시간: " << time << " 수정" << endl;
                                            cout << "주소: " << adr << " 수정" << endl;
                                            if (yesorno()) {
                                                string temp[4];
                                                temp->clear();
                                                for (int i = 0; i < 4; i++) {
                                                    temp[i] = match3.str(i + 1);
                                                    if (match3.str(i + 1).size() == 1) {
                                                        temp[i] = "0" + match3.str(i + 1);
                                                    }
                                                }
                                                current_user->restaurant.at(select - 1).address = adr;

                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).address = adr;
                                                    }
                                                }
                                                current_user->restaurant.at(select - 1).close_day.at(0) = "\0";
                                                current_user->restaurant.at(select - 1).close_day.at(1) = "-1";
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).close_day.at(0) = "\0";
                                                        user.at(j).restaurant.at(select - 1).close_day.at(1) = "-1";
                                                    }
                                                }
                                                string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                if (stoi(match3.str(1)) >= stoi(match3.str(3)) && stoi(match3.str(2)) >= stoi(match3.str(4))) {
                                                    //앞시간이 뒷시간 보다 크면나누어 저장
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);


                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).open_hour.clear();
                                                            user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                        }
                                                    }
                                                }
                                                else {
                                                    //자정을 포함하지 않는 시간
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);


                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                        }
                                                    }
                                                }
                                                writeR_InfoTextFile();
                                                writeRestTextFile();
                                                cout << "수정 완료" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else
                                        {//주소
                                            continue;
                                        }

                                    }
                                    else {
                                        //휴무변경

                                            //시간 주소 판별 
                                        if (regex_match(time, match3, Time_Checker))
                                        {//시간
                                            current_user->restaurant.at(select - 1).open_hour.clear();
                                            if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                            {
                                                cout << "잘못된 형식입니다.." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match3.str(1)) < 24 && stoi(match3.str(3)) < 24 && stoi(match3.str(2)) < 60 && stoi(match3.str(4)) < 60))
                                            {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            bool check = false;
                                            for (int i = 0; i < 10; i++) {//주소검사
                                                if (strcmp(adr.c_str(), V_address[i].c_str()) == 0) {
                                                    check = true;
                                                    break;
                                                }
                                                else {
                                                    check = false;
                                                }
                                            }
                                            if (!(check)) {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            cout << "휴무일 " << day << " 수정" << endl;
                                            cout << "영업시간: " << time << " 수정" << endl;
                                            cout << "주소: " << adr << " 수정" << endl;
                                            if (yesorno()) {

                                                string temp[4];
                                                temp->clear();
                                                for (int i = 0; i < 4; i++) {
                                                    temp[i] = match3.str(i + 1);
                                                    if (match3.str(i + 1).size() == 1) {
                                                        temp[i] = "0" + match3.str(i + 1);
                                                    }
                                                }
                                                current_user->restaurant.at(select - 1).address = adr;


                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).address = adr;
                                                    }
                                                }
                                                current_user->restaurant.at(select - 1).close_day.at(0) = day;
                                                for (k = 0; k < 7; k++) {
                                                    if (humooil[k] == day) {
                                                        current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                        break;
                                                    }
                                                }
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id) {
                                                        user.at(j).restaurant.at(select - 1).close_day.at(0) = day;
                                                        user.at(j).restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                    }
                                                }
                                                string humoo = current_user->restaurant.at(select - 1).close_day.at(0);
                                                string index = current_user->restaurant.at(select - 1).close_day.at(1);
                                                //current_user->restaurant.at(select - 1).open_hour.clear();
                                                if (stoi(match3.str(1)) >= stoi(match3.str(3)) && stoi(match3.str(2)) >= stoi(match3.str(4))) {
                                                    //앞시간이 뒷시간 보다 크면나누어 저장
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((stoi(index) + 1) % 7));
                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).open_hour.clear();
                                                            user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                        }
                                                    }
                                                }
                                                else {
                                                    //자정을 포함하지 않는 시간
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(index);
                                                    for (int j = 0; j < user.size(); j++) {
                                                        if (user.at(j).id == current_user->id) {
                                                            user.at(j).restaurant.at(select - 1).open_hour.assign(current_user->restaurant.at(select - 1).open_hour.begin(), current_user->restaurant.at(select - 1).open_hour.end());
                                                        }
                                                    }
                                                }
                                                writeR_InfoTextFile();
                                                writeRestTextFile();
                                                cout << "수정 완료" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else
                                        {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }

                                    }






                                    continue;
                                }

                            }
                        }
                        else {
                            cout << "잘못된 형식입니다." << endl;
                            cin.clear();
                        }
                    }
                    else if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "잘못된 형식입니다." << endl;
                    }
                    else {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "잘못된 형식입니다." << endl;
                    }
                }
            }
            else {
                //need info
                while (true) {
                    cout << "부가정보 등록" << endl;
                    cout << "1. 메뉴/가격 등록 \n2. 시간/휴무일 등록 \n3. 이전메뉴" << endl;
                    cout << "보기 선택: ";
                    int select_menu;
                    cin >> select_menu;
                    cin.ignore();//버퍼 제거 
                    if (select_menu <= 3 && select_menu >= 1) {
                        if (select_menu == 3) break;
                        else if (select_menu == 1)
                        {
                            if (!current_user->restaurant.at(select - 1).menu.empty()) {
                                cout << "이미 메뉴가 등록되어 있습니다" << endl;
                                continue;
                            }
                            string M_name, M_price, temp;
                            string input;
                            regex M_name_Checker("[a-zA-Z\\s]*");
                            // regex M_price_Checker("^[1-9]?(,|[0-9])[\\S]*");
                            while (true) {
                                cout << "메뉴는 영어 소문자와 공백으로 1~15자 이내로 입력해주세요" << endl;
                                cout << "2개이상의 공백은 1개로 치환되며 맨 앞, 맨 뒤 공백은 제거됩니다." << endl;
                                cout << "가격은 100~99999 의 범위로 제한 합니다." << endl;
                                cout << "쉼표는 맨 앞이 아닌 어디든 등장할 수 있고, 두개를 연속으로 사용할 수 없습니다." << endl;
                                cout << "각 데이터는 (/)로 구분해서 입력해주세요" << endl;
                                cout << "메뉴/가격정보: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "한국어 입력 금지" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//앞뒤공백은 자르기
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                //cout << "scount : " << scount << endl;

                                if (scount != 1) {
                                    if (isQuit(input)) break;
                                    cout << "잘못된 형식입니다." << endl;
                                    continue;//슬래시 1개 아니면 다시입력받기
                                }
                                trim(input);//앞뒤공백은 자르기
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
                                        cout << "잘못된 형식입니다." << endl;
                                        continue;
                                    }
                                    trim(M_name);
                                    trim(M_price);
                                    if (regex_match(M_name, M_name_Checker))
                                    {
                                        if (!oneSpaceLength(M_name)) { continue; }
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!isMoney(M_price)) {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }

                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }

                                        cout << "메뉴이름: " << M_name << endl;
                                        cout << "메뉴가격: " << M_price << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                            ofstream writeFile;

                                            writeFile.open("Restaurant_Menu.txt", std::ofstream::out | std::ofstream::app);
                                            if (writeFile.is_open()) {
                                                string str = current_user->restaurant.at(select - 1).name + "/" + M_name + "/" + M_price + "\n";
                                                writeFile.write(str.c_str(), str.size());
                                            }
                                            else {
                                                cout << "파일 오픈 오류\n" << endl;
                                            }
                                            writeFile.close();
                                            readR_MenuTextFile();
                                            //menu.push_back(Menu(price, M_name));
                                            cout << "등록 완료" << endl;
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
                                        if (!oneSpaceLength(M_name)) { continue; }
                                        for (int i = 0; i < M_name.size(); i++) {
                                            M_name[i] = tolower(M_name[i]);
                                        }
                                        if (!isMoney(M_price)) {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }
                                        if (M_price.find(",") != -1) {
                                            while (M_price.find(",") != -1)
                                                M_price.replace(M_price.find(","), 1, "");
                                        }
                                        cout << "메뉴이름: " << M_name << endl;
                                        cout << "메뉴가격: " << M_price << endl;
                                        if (yesorno()) {
                                            current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                            ofstream writeFile;

                                            writeFile.open("Restaurant_Menu.txt", std::ofstream::out | std::ofstream::app);
                                            if (writeFile.is_open()) {
                                                string str = current_user->restaurant.at(select - 1).name + "/" + M_name + "/" + M_price + "\n";
                                                writeFile.write(str.c_str(), str.size());
                                            }
                                            else {
                                                cout << "파일 오픈 오류\n" << endl;
                                            }
                                            writeFile.close();
                                            readR_MenuTextFile();
                                            cout << "등록 완료" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//둘다 정규식 안맞음->재입력
                                        cout << "잘못된 형식입니다." << endl;
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
                                cout << "이미 부가정보가 등록되어 있습니다" << endl;
                                continue;
                            }
                            string hour, close_day, temp;
                            string input;
                            regex Time_Checker("([0-9]{1,2})\:([0-9]{1,2})\~([0-9]{1,2})\:([0-9]{1,2})*$");
                            regex Day_Checker("^[a-zA-Z]+(DAY|DAy|DaY|Day|day|daY|dAY|dAy)$");
                            while (true) {
                                cout << "영업시간은 24시간 형식으로 사용하여 주시고 00시와 24시의 혼동을 없애기 위해 24시는 입력받지 않습니다." << endl;
                                cout << "시작 시간과 종료 시간은 특수문자(~)로 구분되며 각 시간의 시와 분은 (:)로 구분됩니다." << endl;
                                cout << "공백 입력은 금지됩니다." << endl;
                                cout << "휴무일은 영문 소문자로 monday, tuesday, wednesday thursday friday saturday sunday 중 하나를 입력받습니다." << endl;
                                cout << "영업시간은 필수로 등록해야 하지만 휴무일은 등록하지 않아도 됩니다." << endl;
                                cout << "각 데이터는 (/)로 구분해서 입력해주세요" << endl;
                                cout << "시간/휴무정보: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "한국어 입력 금지" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//앞뒤공백은 자르기
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                //cout << "scount : " << scount << endl;

                                if (scount != 1) {
                                    if (isQuit(input)) break;
                                    smatch match;
                                    if (regex_match(input, match, Time_Checker)) {
                                        if (stoi(match.str(1)) == stoi(match.str(3)) && stoi(match.str(2)) == stoi(match.str(4)))
                                        {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }

                                        if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                        {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }
                                        cout << "영업시간: " << input << endl;
                                        cout << "휴무일 없음" << endl;
                                        if (yesorno()) { //match 대신 temp로 바꿔서 전부 바꿔서 넣어야함 
                                            string temp[4];
                                            temp->clear();
                                            for (int i = 0; i < 4; i++) {
                                                temp[i] = match.str(i + 1);
                                                if (match.str(i + 1).size() == 1) {
                                                    temp[i] = "0" + match.str(i + 1);
                                                }
                                            }
                                            current_user->restaurant.at(select - 1).close_day.push_back("\0");
                                            current_user->restaurant.at(select - 1).close_day.push_back(to_string(-1));
                                            //휴무일이랑 인덱스 저장
                                            if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                //앞시간이 뒷시간 보다 크면나누어 저장
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string(-1));

                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string(-1));

                                                string time = temp[0] + ":" + temp[1] + "~23:59,00:00~" + temp[2] + ":" + temp[3];
                                                string adr = current_user->restaurant.at(select - 1).address;
                                                string str = current_user->restaurant.at(select - 1).name + "/" + adr + "/" + time + "\n";
                                                ofstream writeFile;

                                                writeFile.open("Restaurant_Info.txt", std::ofstream::out | std::ofstream::app);
                                                if (writeFile.is_open()) {
                                                    writeFile.write(str.c_str(), str.size());
                                                }
                                                else {
                                                    cout << "파일 오픈 오류\n" << endl;
                                                }
                                                writeFile.close();
                                            }
                                            else {
                                                //자정을 포함하지 않는 시간
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                current_user->restaurant.at(select - 1).open_hour.push_back(to_string(-1));
                                                string time = temp[0] + ":" + temp[1] + "~23:59,00:00~" + temp[2] + ":" + temp[3];
                                                string adr = current_user->restaurant.at(select - 1).address;
                                                string str = current_user->restaurant.at(select - 1).name + "/" + adr + "/" + time + "\n";

                                                ofstream writeFile;

                                                writeFile.open("Restaurant_Info.txt", std::ofstream::out | std::ofstream::app);
                                                if (writeFile.is_open()) {
                                                    writeFile.write(str.c_str(), str.size());
                                                }
                                                else {
                                                    cout << "파일 오픈 오류\n" << endl;
                                                }
                                                writeFile.close();
                                            }
                                            readR_InfoTextFile();
                                            cout << "등록 완료" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {
                                        cout << "잘못된 형식입니다." << endl;
                                        continue;
                                    }
                                    cout << "잘못된 형식입니다." << endl;
                                    continue;//슬래시 1개 아니면 다시입력받기
                                }
                                trim(input);//앞뒤공백은 자르기
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
                                        cout << "잘못된 형식입니다." << endl;
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
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                            {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            cout << "영업시간: " << hour << endl;
                                            cout << "휴무일: " << close_day << endl;
                                            if (yesorno()) {
                                                string temp[4];
                                                temp->clear();
                                                for (int i = 0; i < 4; i++) {
                                                    temp[i] = match.str(i + 1);
                                                    if (match.str(i + 1).size() == 1) {
                                                        temp[i] = "0" + match.str(i + 1);
                                                    }
                                                }

                                                current_user->restaurant.at(select - 1).close_day.push_back(close_day);
                                                int i = 0;
                                                for (int i = 0; i < 7; i++) {
                                                    if (humooil[i] == close_day) {
                                                        current_user->restaurant.at(select - 1).close_day.push_back(to_string(i));
                                                        break;
                                                    }
                                                } //휴무일이랑 인덱스 저장
                                                if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                    //앞시간이 뒷시간 보다 크면나누어 저장
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                    cout << to_string(i) << endl;
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((i + 1) % 7));
                                                    string temp[4];
                                                    for (int i = 0; i < 4; i++) {
                                                        temp[i] = match.str(i + 1);
                                                        if (match.str(i + 1).size() == 1) {
                                                            temp[i] = "0" + match.str(i + 1);
                                                        }
                                                    }
                                                    string time = temp[0] + ":" + temp[1] + "~23:59,00:00~" + temp[2] + ":" + temp[3];
                                                    string adr = current_user->restaurant.at(select - 1).address;
                                                    string str = current_user->restaurant.at(select - 1).name + "/" + adr + "/" + time + "/" + close_day + "\n";
                                                    ofstream writeFile;

                                                    writeFile.open("Restaurant_Info.txt", std::ofstream::out | std::ofstream::app);
                                                    if (writeFile.is_open()) {
                                                        writeFile.write(str.c_str(), str.size());
                                                    }
                                                    else {
                                                        cout << "파일 오픈 오류\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                else {
                                                    //자정을 포함하지 않는 시간
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                    string time = temp[0] + ":" + temp[1] + "~23:59,00:00~" + temp[2] + ":" + temp[3];
                                                    string adr = current_user->restaurant.at(select - 1).address;
                                                    string str = current_user->restaurant.at(select - 1).name + "/" + adr + "/" + time + "/" + close_day + "\n";
                                                    ofstream writeFile;
                                                    writeFile.open("Restaurant_Info.txt", std::ofstream::out | std::ofstream::app);
                                                    if (writeFile.is_open()) {
                                                        writeFile.write(str.c_str(), str.size());
                                                    }
                                                    else {
                                                        cout << "파일 오픈 오류\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                readR_InfoTextFile();
                                                cout << "등록 완료" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "잘못된 형식입니다." << endl;
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
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                            {
                                                cout << "잘못된 형식입니다." << endl;
                                                continue;
                                            }
                                            cout << "영업시간: " << hour << endl;
                                            cout << "휴무일: " << close_day << endl;
                                            if (yesorno()) {
                                                string temp[4];
                                                temp->clear();
                                                for (int i = 0; i < 4; i++) {
                                                    temp[i] = match.str(i + 1);
                                                    if (match.str(i + 1).size() == 1) {
                                                        temp[i] = "0" + match.str(i + 1);
                                                    }
                                                }

                                                current_user->restaurant.at(select - 1).close_day.push_back(close_day);
                                                int i = 0;
                                                for (int i = 0; i < 7; i++) {
                                                    if (humooil[i] == close_day) {
                                                        current_user->restaurant.at(select - 1).close_day.push_back(to_string(i));
                                                        break;
                                                    }
                                                } //휴무일이랑 인덱스 저장
                                                if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                    //앞시간이 뒷시간 보다 크면나누어 저장
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("23");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("59");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                    cout << to_string(i) << endl;
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back("00");
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string((i + 1) % 7));
                                                    string time = temp[0] + ":" + temp[1] + "~23:59,00:00~" + temp[2] + ":" + temp[3];
                                                    string adr = current_user->restaurant.at(select - 1).address;
                                                    string str = current_user->restaurant.at(select - 1).name + "/" + adr + "/" + time + "/" + close_day + "\n";

                                                    ofstream writeFile;

                                                    writeFile.open("Restaurant_Info.txt", std::ofstream::out | std::ofstream::app);
                                                    if (writeFile.is_open()) {
                                                        writeFile.write(str.c_str(), str.size());
                                                    }
                                                    else {
                                                        cout << "파일 오픈 오류\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                else {
                                                    //자정을 포함하지 않는 시간
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[0]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[1]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[2]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(temp[3]);
                                                    current_user->restaurant.at(select - 1).open_hour.push_back(to_string(i));
                                                    string time = temp[0] + ":" + temp[1] + "~23:59,00:00~" + temp[2] + ":" + temp[3];
                                                    string adr = current_user->restaurant.at(select - 1).address;
                                                    string str = current_user->restaurant.at(select - 1).name + "/" + adr + "/" + time + "/" + close_day + "\n";

                                                    ofstream writeFile;

                                                    writeFile.open("Restaurant_Info.txt", std::ofstream::out | std::ofstream::app);
                                                    if (writeFile.is_open()) {
                                                        writeFile.write(str.c_str(), str.size());
                                                    }
                                                    else {
                                                        cout << "파일 오픈 오류\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                readR_InfoTextFile();
                                                cout << "등록 완료" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "잘못된 형식입니다." << endl;
                                            continue;
                                        }
                                    }
                                    else {//둘다 정규식 안맞음->재입력
                                        cout << "잘못된 형식입니다." << endl;
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
                    else{
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "잘못된 형식입니다." << endl;
                    }
                        
                }
            }
        }
        else {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "잘못된 형식입니다." << endl;

        }
    }
}


string Manager::getDayIndex(string str)
{
    // cout << "str : " << str << endl;
    for (int i = 0; i < 7; i++) {
        if (!strcmp(str.c_str(), humooil[i].c_str()))
            return to_string(i);
    }
    return to_string(-1);
}



bool Manager::isin0to128(string str)
{
    int i = 0;
    //cout << str << endl;
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
            cout << "공백없이 입력해주세요\n" << endl;
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
    V_address = new string[10];
    for (int i = 0; i < 10; i++) {
        V_address[i] = "hwayang" + to_string(i + 1) + "dong";
    }
    humooil = new string[7];
    humooil[0] = "monday";
    humooil[1] = "tuesday";
    humooil[2] = "wednesday";
    humooil[3] = "thursday";
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
    ltrim(s);
    rtrim(s);
}
