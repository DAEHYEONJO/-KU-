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
    char* ptr = strtok(buf, " \t");//����+�� ���յ� �Ǻ��ϱ�����
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
        cout << "���� 1~15 �� �Է��ϼ���\n" << endl;
        return false;
    }
    return true;
}

int Manager::signUp()
{
    //id �Է¹ޱ� -> ������Է�, �ߺ��˻� -> pw �Է¹ޱ� -> 4�ڸ����� �Է� ���� ���� -> text���Ͽ� �����ϱ�
    //id, pw �Է� ���� �� quit �Է½� ���θ޴��� ���ư���
    /**/
    string test_id = "", test_pw = "";
    regex idChecker1("[a-zA-Z0-9]+");//���ĺ�/�����ΰ��
    //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//���ڸ��������ϴ°��

    while (true) {//id roof
        cout << "\nȸ������ �Դϴ�." << endl;
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
                        //cout << "���Ǹ���\n" << endl;
                        readInfoTextFile();//����Ǿ��ִ°� �о����.
                        int count = 0;
                        for (count = 0; count < user.size(); count++) {//text file �ߺ��˻�
                            //cout << "���尪 : " << user[count].id.c_str() << "�Է°� : " << test_id << endl;
                            if (!strcmp(user[count].id.c_str(), test_id.c_str())) {
                              
                                break;
                            }
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
                                    cout << "ȸ������ �Ϸ�\n" << endl;
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
                                    cout << "�߸��� �����Դϴ�.\n" << endl;
                                }
                            }
                        }
                        else {
                            cout << "�ߺ��� �����Դϴ�.\n" << endl;
                        }
                    }
                    else {
                        cout << "�߸��� �����Դϴ�.\n" << endl;
                    }
                }
                else {
                    cout << "���� 6~10 ���� �Է��ϼ���.\n" << endl;
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
    regex idChecker1("[a-zA-Z0-9]+");//������������ϴ°��
    //regex idChecker2("^([0-9]+[a-zA-Z]).*$");//���ڸ��������ϰ�ġ�ٴ°��

    while (true) {//�α��� �����ϸ� current_user�� �α����� ���� ���� �����
        cout << "\n�α����Դϴ�." << endl;
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
                            //cout << "���̵����尪 : " << user[count].id.c_str() << "�Է°� : " << test_id << endl;
                            if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
                        }
                        if (count == user.size()) {//�ߺ��� ���̵� ������ �ٽ��Է¹ޱ�
                            cout << "���̵� ��ġ���� �ʽ��ϴ�.\n" << endl;
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
                                if (isQuit(test_pw)) break;
                                if (regex_match(test_pw, pwChecker)) {//pw���� �ǹٸ�
                                    if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
                                        //�α��μ���
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
                                        //cout << "���� �α��� �� ������ ���� " << endl;
                                        //current_user->print();


                                        //�α��� ������ ���� ����
                                        cout << "�α��� ����! id: " << user[count].id << endl;
                                        return 1;
                                    }
                                    else {
                                        cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n" << endl;
                                    }

                                }
                                else {
                                    cout << "�߸��� �����Դϴ�.\n" << endl;
                                }
                            }


                        }
                    }
                }
                else {
                    cout << "���� 6~10���� �Է��ϼ���.\n" << endl;
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
        cout << "\n1. �α���\t2. ȸ������\n>>���⼱�� : ";

        regex menuChecker("^(1|2){1}$");

        getline(cin, test_menu);
        if (!isin0to128(test_menu)) {
            cout << "�ѱ��� �Է� ����\n" << endl;
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
                //cout << "�� ���� ���볪���� �ȵ� ������ ������.\n" << endl;
                break;
            }
        }
        else {
            cout << "�߸��� �����Դϴ�.\n" << endl;
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
        if (i != (str.size() - 1)) {//�޸����ӵΰ�����
            return false;
        }
        else {
            //cout << "str : " << str.size() << "cc : " << cc << endl;
            //cout << str.size() - cc << endl;
            if (((str.size() - cc) > 5) || ((str.size() - cc) < 3)) {
                //cout << "���� 3�� �̻� 5�� ���� �Է� ����" << endl;
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
            cout << "�ѱ��� �Է� ����\n" << endl;
            continue;
        }
        trim(c);
        if (regex_match(c, ynCheck)) {
            if (!strcmp(c.c_str(), "y")) {
                cout << "����Ϸ�!\n" << endl;
                return 1;
            }
            cout << "������ �������� �ʽ��ϴ�.\n" << endl;
            return 0;
        }
        cout << "�߸��� �����Դϴ�.\n" << endl;
        //y �Ǵ� n �Է� �������� �ٽ� ���ΰ��� �Է¹ޱ�
    }
    //cout << "������ �������� �ʽ��ϴ�." << endl;
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
                    // cout << "���ϸ���" << endl;
                    return true;
                }
            }
            if (i == 7) {
                cout << "monday ~ sunday �� �Է¹ٶ��ϴ�.\n" << endl;
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
                // cout << "�ð�����" << endl;
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
    regex adrChecker("^[a-zA-Z0-9]+(dong)$");//���ĺ�+���ڸ��Է�
    if (regex_match(str, adrChecker)) {
        if ((str.size() >= 12) && (str.size() <= 13)) {
            int i = 0;
            for (i = 0; i < 10; i++) {
                if (!strcmp(V_address[i].c_str(), str.c_str())) {
                    // cout << "�ּ� ����" << endl;
                    return true;
                }
            }
            if (i == 10) {
                cout << "hwayang1dong~hwayang10dong �� �Է� �ٶ��ϴ�.\n" << endl;
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
                //cout << "���Ͽ� ���ٛ���" << str_wfr << endl;
                //cout << user.at(i).restaurant.at(k).menu.size() << endl;
            }
            else {
                cout << "���� ���� ����\n" << endl;
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
                //cout << "���Ͽ� ���ٛ���" << str << endl;
                //cout << user.at(i).restaurant.at(k).menu.size() << endl;
            }
            else {
                cout << "���� ���� ����\n" << endl;
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
                //cout << "���Ͽ� ���ٛ���" << str_info << endl;
                // cout << user.at(i).restaurant.at(k).menu.size() << endl;
            }
            else {
                cout << "���� ���� ����\n" << endl;
            }
        }
    }


    writeFile.close();

}

int Manager::mainMenu()
{
    while (true) {
        cout << "\n1. �Ĵ���\t2.�Ĵ����\t3. �Ĵ�˻�\t4. ���� : ";
        regex menuChecker("^([1-4]){1}$");
        string test_menu = "";
        getline(cin, test_menu);
        if (!isin0to128(test_menu)) {
            cout << "�ѱ��� �Է� ����\n" << endl;
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
                    cout << "�� �� ���볪����ȵ�" << endl;
                    break;
                }
            }
        }
        else {
            cout << "�߸��� �����Դϴ�.\n" << endl;
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
        cout << "\n\nī�װ��� korean, japanese, chinese, western �� �Ѱ� �Է��ϼ���" << endl;
        cout << "�Ĵ��̸��� ������ �Ǵ� ������,���鹮�� �����̸�\n ���鰳�� ���� 1�ڸ� ~ 15�ڸ� ���̷� �Է��ϼ���." << endl;
        cout << "�Ĵ��̸� �Է½� ���ڵ� ���� 2�� �̻��� ������ 1���� �����մϴ�." << endl;
        cout << "�Ĵ��ּҴ� hwayang1dong ~ hwayang10dong �� �Ѱ��� ���� �Է��ϼ���." << endl;
        cout << "ī�װ�/�Ĵ��̸�/�Ĵ��ּ�" << endl << "�Է��ϼ���<<";
        //   data = "";
        getline(cin, data);
        if (!isin0to128(data)) {
            cout << "�ѱ��� �Է� ����\n" << endl;
            continue;
        }
        trim(data);//�յڰ����� �ڸ���
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
                cout << "�߸��� �����Դϴ�.\n" << endl;
                continue;//������ 2�� �ƴϸ� �ٽ��Է¹ޱ�
            }

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

            //cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;
            trim(category);
            trim(R_name);
            trim(R_address);
            //cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;

            regex categoryChecker("^[a-z].*$");
            if (!regex_match(category, categoryChecker)) {
                cout << "�߸��� �����Դϴ�.\n" << endl;
                continue;
            }
            else {
                if (!((strcmp(category.c_str(), "japanese") == 0) || (strcmp(category.c_str(), "chinese") == 0) || (strcmp(category.c_str(), "korean") == 0) || (strcmp(category.c_str(), "western") == 0)))
                {//ī�װ� �˻�
                    //cout << "2??" << endl;
                    cout << "�߸��� �����Դϴ�.\n" << endl;
                    continue;
                }
            }

            //�̸��˻�
            regex nameChecker("[a-zA-Z[:space:]]+");
            if (!regex_match(R_name, nameChecker)) {
                cout << "�߸��� �����Դϴ�.\n" << endl;
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
                char* ptr = strtok(buf, " \t");//����+�� ���յ� �Ǻ��ϱ�����
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
                    cout << "���� 1~15���� �Է��ϼ���\n" << endl;
                    continue;
                }
                //�ؽ�Ʈ���Ͽ� �Ĵ��̸� �ֳ� ���� �˻��ϱ�
                bool check = false;
                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].name.c_str(), R_name.c_str())) {
                            cout <<"�ߺ��� �����Դϴ�.\n" << endl;
                            check = true;
                            break;
                        }
                    }
                }
                if (check) continue;
            }
            regex adrChecker("[a-zA-Z0-9]+");//���ĺ�+���ڸ��Է�
            if (!regex_match(R_address, adrChecker)) {
                cout << "�߸��� �����Դϴ�.\n" << endl;
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
                    cout << "�߸��� �����Դϴ�.\n" << endl;
                    continue;
                }
            }

            //����׸� �˻�Ϸ�� ī�װ�: *** �̸�: *** �ּ�: *** ��� �� y_n �޾ƾ��� 
           // cout << "ī�װ�: " << category << "\n�̸�: " << R_name << "\n�ּ�: " << R_address << endl;
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
                current_user->restaurant.push_back(Restaurant(category, R_name, R_address));
                readRestTextFile();
                //current_user->print();

                //cout << "��ϿϷ�" << endl;
                return;
            }
            else {
               // cout << "�߰�����\n" << endl;
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
        cout << "\n\n���� �����ϰ� 3���� �����͸� / �� �����Ͽ� �Է��ϼ���." << endl;
        cout << "������ hwayang1dong ~ hwayang10dong �� �Ѱ��� �Է��ϼ���." << endl;
        cout << "�ð��� : �� �������� ��:���� �Է��ϼ���." << endl;
        cout << "�� : 0~23, �� : 0~59" << endl;
        cout << "������ monday ~ sunday �� �Ѱ��� �Է��ϼ���." << endl;
        cout << "����/�ð�/���� :";
        getline(cin, data);
        if (isin0to128(data)) {
            trim(data);
            if (!isQuit(data)) {
                for (int i = 0; i < data.size(); i++) {
                    if ((int)data[i] == 47)
                        scount++;
                }
                if (scount != 2) {
                    cout << "�߸��� �����Դϴ�.\n" << endl;
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
                    cout << "�߸��� �����Դϴ�.\n" << endl;
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
                    cout << "�߸��� �����Դϴ�.\n" << endl;
                    continue;
                }
               // cout << "time : " << time << "/day : " << day << "/adr : " << adr << endl;

                for (int i = 0; i < user.size(); i++) {
                    for (int j = 0; j < user[i].restaurant.size(); j++) {
                        if (!strcmp(user[i].restaurant[j].address.c_str(), adr.c_str())) {
                            if (!user[i].restaurant[j].open_hour.empty()) {
                                //�Է��� ������ �Ĵ� �ּҰ� ��ġ�ϴ� �Ĵ� �߰�, �ð� �˻� ����

                               // cout << " ��� ��ġ �Ĵ� ã��!!!!!!" << endl;
                                //cout << "��ġ�� �Ĵ� : " << user[i].restaurant[j].name << endl;
                                if (user[i].restaurant[j].open_hour.size() == 5) {
                                    //�Ĵ� �����ð��� ���� �ȳ������ timeV[0]:�Է� �ð�,timeV[1]:�Է� ��
                                    if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].close_day[1].c_str())) {
                                        //�Է¿����� ����� �޹����̶� �ٸ����� ���ϱ�
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[0])) {
                                            if (stoi(timeV[1]) >= stoi(user[i].restaurant[j].open_hour[1])) {//1
                                               // cout << "1����" << endl;
                                                find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[0])) {
                                            if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[2])) {
                                                if (stoi(timeV[1]) < stoi(user[i].restaurant[j].open_hour[3])) {//2
                                                 //   cout << "2����" << endl;
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                                }
                                            }
                                            if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[2])) {//3
                                              //  cout << "3����" << endl;
                                                find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                    }
                                }
                                else {//�Ĵ� �����ð��� ������ ���� ���
                                    if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[0])) {//h==h1
                                        //�չ����ΰ��
                                        if (stoi(timeV[1]) >= stoi(user[i].restaurant[j].open_hour[1])) {//m>=m1
                                          //  cout << "�� 1����" << endl;
                                            if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[4].c_str()) != 0)//���� �Է��� �����̶� �޹����̶� �ٸ� ���
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }
                                    if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[0])) {//h>h1
                                        // �չ����ΰ��
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[2])) {//h==23
                                            if (stoi(timeV[1]) <= stoi(user[i].restaurant[j].open_hour[3])) {//m<=59
                                            //    cout << "�� 2����" << endl;
                                                if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[4].c_str()) != 0)//���� �Է��� �����̶� �޹����̶� �ٸ� ���
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[2])) {//h<23
                                           // cout << "�� 3����" << endl;
                                            if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[4].c_str()) != 0)//���� �Է��� �����̶� �޹����̶� �ٸ� ���
                                                find_R_list.push_back(user[i].restaurant[j]);
                                        }
                                    }

                                    if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[5])) {//h==00
                                        //�޹����ΰ��
                                       // cout << "�� 1����" << endl;
                                        if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[9].c_str()) != 0)//���� �Է��� �����̶� �޹����̶� �ٸ� ���
                                            find_R_list.push_back(user[i].restaurant[j]);
                                    }
                                    if (stoi(timeV[0]) > stoi(user[i].restaurant[j].open_hour[5])) {//h>00
                                        //�޹����ΰ��
                                        if (stoi(timeV[0]) == stoi(user[i].restaurant[j].open_hour[7])) {//h==h2
                                            if (stoi(timeV[1]) < stoi(user[i].restaurant[j].open_hour[8])) {//m<m2
                                          //      cout << "�� 2����" << endl;
                                                if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[9].c_str()) != 0)//���� �Է��� �����̶� �޹����̶� �ٸ� ���
                                                    find_R_list.push_back(user[i].restaurant[j]);
                                            }
                                        }
                                        if (stoi(timeV[0]) < stoi(user[i].restaurant[j].open_hour[7])) {//h<h2
                                         //   cout << "�� 3����" << endl;
                                            if (strcmp(getDayIndex(day).c_str(), user[i].restaurant[j].open_hour[9].c_str()) != 0)//���� �Է��� �����̶� �޹����̶� �ٸ� ���
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
                        cout << "��ġ�ϴ� �Ĵ����� �����ϴ�.\n" << endl;
                        break;
                    }
                    cout << "\n\n*************************************�Ĵ���*************************************" << endl;
                    for (int i = 0; i < find_R_list.size(); i++) {
                        cout << i + 1 << ". ";
                        find_R_list[i].print_info();
                    }
                    cout << find_R_list.size() + 1 << ". " << "���θ޴��� ����\n" << ">> ";
                    string menu = "";
                    regex menuChecker("^([0-9]){1}$");
                    getline(cin, menu);
                    if (regex_match(menu, menuChecker)) {
                        if (!((stoi(menu) >= 1) && (stoi(menu) <= find_R_list.size() + 1))) {
                            cout << "�߸��� �����Դϴ�.\n" << endl;
                            continue;
                        }
                        else {
                            if (stoi(menu) == find_R_list.size() + 1) {
                                return;
                            }
                            else {
                                find_R_list[stoi(menu) - 1].print_menu();
                                while (true) {
                                    cout << "�ڷ� ������ quit�� �Է����ּ���\n" << ">> ";
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
            cout << "�ѱ� �Է� ����\n" << endl;
            continue;
        }
    }




}

void Manager::readInfoTextFile()
{
    //cout << "readInfoTextFile" << endl;
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
    //cout << "readRestTextFile" << endl;
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
                // "/"�������� 4�� �Ǵ� 3�� ©���ֱ�
                //1��° : �Ĵ��̸�
                //2��° : �ּ�
                //3��° : �����ð�-> �޸��� �ִ��� ������ �˻��ϱ�.������ �޸� �������� ¥����.
                //                   �޸� ������ : ~ �������� ¥����, ¥���� : �������� ¥���� �����ϱ�.
                //4��° : �޹���
                ptr = strtok(readlineR_I, "/");
                while (ptr != nullptr) {
                    v.push_back(ptr);
                    ptr = strtok(NULL, "/");
                }

                if (v.size() == 3) {//�޹��� ���°��ù�
                    dayflag = false;
                    humoo = "";
                }
                else { humoo = v[3]; }
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
                            user[i].restaurant[j].open_hour.assign(temp.begin(), temp.end());//�����ð�
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
            cout << "��ϵ� �Ĵ��� �����ϴ� �Ĵ��� ����� �ּ���" << endl;
            return;
        }
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
                   // cin.ignore();
                    cout << "�ΰ����� ����" << endl;
                    cout << "1. �޴�/���� ���� \n2. �ּ�/�ð�/�޹��� ���� \n3. �����޴�" << endl;
                    cout << "���� ����: ";
                    int select_menu2;
                    cin >> select_menu2;
                    if (isQuit(to_string(select_menu2))) continue;
                    cin.ignore();//���� ����
                    if (select_menu2 == 3) break;
                    if (select_menu2 < 3 && select_menu2 >= 1) {
                        if (select_menu2 == 1)
                        {
                            //�޴�����
                            string M_name, M_price, temp;
                            string input;
                            regex M_name_Checker("[a-zA-Z\\s]*");
                            //regex M_price_Checker("^[1-9]?(,|[0-9])[\\S]*");
                            while (true) {
                                // writeR_MenuTextFile();
                                vector<Menu>::iterator iter = current_user->restaurant.at(select - 1).menu.begin();
                                if (current_user->restaurant.at(select - 1).menu.size() == 3) {
                                    cout << "�޴��� ���̻� �߰��� �� �����ϴ�." << endl;
                                }
                                current_user->restaurant.at(select - 1).print_menu();
                                cout << "�޴�/(����) �Է�: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "�ѱ��� �Է� ����" << endl;
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
                                trim(input);//�յڰ����� �ڸ���

                                if (scount == 0 && !isQuit(input)) {
                                    //�޴��� �Էµ� 
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
                                            cout << "������ �޴�: " << M_name << endl;
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

                                                cout << "���� �Ϸ�" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "�߸��� �����Դϴ�." << endl;
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
                                            cout << "�߸��� �����Դϴ�." << endl;
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
                                            cout << "�߸��� �����Դϴ�." << endl;
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
                                                cout << "���̻� �߰��� �� �����ϴ�(�ִ� �޴� 3��)" << endl;
                                                continue;
                                            }
                                            cout << "�߰��� �޴��̸�: " << M_name << endl;
                                            cout << "�߰��� �޴�����: " << M_price << endl;
                                            if (yesorno()) {

                                                current_user->restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                                for (int j = 0; j < user.size(); j++) {
                                                    if (user.at(j).id == current_user->id)
                                                        user.at(j).restaurant.at(select - 1).menu.push_back(Menu(M_name, M_price));
                                                }
                                                writeR_MenuTextFile();
                                                cout << "�߰� �Ϸ�!" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }

                                        }
                                        cout << "�޴��̸�: " << M_name << endl;
                                        cout << "������ �޴�����: " << M_price << endl;
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
                                            cout << "���� �Ϸ�!" << endl;
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
                                            cout << "�����Ϸ�!" << endl;
                                            continue;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//�Ѵ� ���Խ� �ȸ���->���Է�
                                        cout << "�߸��� �����Դϴ�." << endl;
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
                                cout << "�ּ�/�ð�/�޹�����: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "�ѱ��� �Է� ����" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//�յڰ����� �ڸ���
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                // cout << "scount : " << scount << endl;
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
                                            cout << "�޹��� " << input << " ����" << endl;
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
                                                cout << "���� �Ϸ�" << endl;
                                            }
                                            else continue;
                                        }
                                        else {
                                            cout << "�޹��� " << input << " ����" << endl;
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
                                                cout << "���� �Ϸ�" << endl;
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
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }

                                        if (!(stoi(match_one.str(1)) < 24 && stoi(match_one.str(3)) < 24 && stoi(match_one.str(2)) < 60 && stoi(match_one.str(4)) < 60))
                                        {
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }
                                        cout << "�����ð� " << input << " ����" << endl;
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
                                                //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                //������ �������� �ʴ� �ð�
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
                                            cout << "���� �Ϸ�" << endl;
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
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }
                                        else {
                                            cout << "�ּ� " << input << " ����" << endl;
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
                                                cout << "���� �Ϸ�" << endl;
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
                                        cout << "�߸��� �����Դϴ�." << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str1 << " ����" << endl;
                                                cout << "�����ð�: " << str2 << " ����" << endl;
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
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                        //������ �������� �ʴ� �ð�
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
                                                    cout << "���� �Ϸ�" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str1 << " ����" << endl;
                                                    cout << "�ּ� " << str2 << " ����" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str1 << " ����" << endl;
                                                cout << "�����ð�: " << str2 << " ����" << endl;
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
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                        //������ �������� �ʴ� �ð�
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
                                                    cout << "���� �Ϸ�" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str1 << " ����" << endl;
                                                    cout << "�ּ� " << str2 << " ����" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str2 << " ����" << endl;
                                                cout << "�����ð�: " << str1 << " ����" << endl;
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
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                        //������ �������� �ʴ� �ð�
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
                                                    cout << "���� �Ϸ�" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str2 << " ����" << endl;
                                                    cout << "�ּ� " << str1 << " ����" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }

                                                if (!(stoi(match2_2.str(1)) < 24 && stoi(match2_2.str(3)) < 24 && stoi(match2_2.str(2)) < 60 && stoi(match2_2.str(4)) < 60))
                                                {
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                cout << "�޹��� " << str2 << " ����" << endl;
                                                cout << "�����ð�: " << str1 << " ����" << endl;
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
                                                        //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                        //������ �������� �ʴ� �ð�
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
                                                    cout << "���� �Ϸ�" << endl;
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
                                                    cout << "�߸��� �����Դϴ�." << endl;
                                                    continue;
                                                }
                                                else {
                                                    cout << "�޹��� " << str2 << " ����" << endl;
                                                    cout << "�ּ� " << str1 << " ����" << endl;
                                                    if (yesorno()) {
                                                        current_user->restaurant.at(select - 1).close_day.at(0) = str2;
                                                        for (k = 0; k < 7; k++) {
                                                            if (humooil[k] == str2) {
                                                                current_user->restaurant.at(select - 1).close_day.at(1) = to_string(k);
                                                                break;
                                                            }
                                                        }
                                                        current_user->restaurant.at(select - 1).address = str1;
                                                        //cout << "���� �Ϸ�" << endl;
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
                                                        cout << "���� �Ϸ�" << endl;
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
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }
                                            else {//�ּ� �˻� ��� 
                                                smatch match3;



                                                if (regex_match(str2, match3, Time_Checker))
                                                {
                                                    if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                                    {
                                                        cout << "�߸��� �����Դϴ�." << endl;
                                                        continue;
                                                    }

                                                    cout << "�ּ� " << str1 << " ����" << endl;
                                                    cout << "���� �ð� " << str2 << " ����" << endl;
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
                                                            //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                            //������ �������� �ʴ� �ð�
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
                                                        cout << "���� �Ϸ�" << endl;
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
                                    {//�ּ�(str1)or�ð�(str2)�� ����

                                        {
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
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }
                                            else {//�ּ� �˻� ��� 
                                                smatch match3;



                                                if (regex_match(str2, match3, Time_Checker))
                                                {
                                                    if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                                    {
                                                        cout << "�߸��� �����Դϴ�.." << endl;
                                                        continue;
                                                    }

                                                    cout << "�ּ� " << str1 << " ����" << endl;
                                                    cout << "���� �ð� " << str2 << " ����" << endl;
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
                                                            //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                            //������ �������� �ʴ� �ð�
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
                                                        cout << "���� �Ϸ�" << endl;
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
                                {//������ ����
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
                                        cout << "�߸��� �����Դϴ�." << endl;
                                        continue;
                                    }
                                    cout << strd.at(0) << "/" << strd.at(1) << "/" << strd.at(2) << endl;

                                    //������ str.[0]
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
                                        //�޹�����
                                            //�ð� �ּ� �Ǻ�
                                        if (regex_match(time, match3, Time_Checker))
                                        {//�ð�

                                            current_user->restaurant.at(select - 1).open_hour.clear();
                                            if (stoi(match3.str(1)) == stoi(match3.str(3)) && stoi(match3.str(2)) == stoi(match3.str(4)))
                                            {
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match3.str(1)) < 24 && stoi(match3.str(3)) < 24 && stoi(match3.str(2)) < 60 && stoi(match3.str(4)) < 60))
                                            {
                                                cout << "�߸��� �����Դϴ�." << endl;
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
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }
                                            cout << "�޹��� " << day << " ����" << endl;
                                            cout << "�����ð�: " << time << " ����" << endl;
                                            cout << "�ּ�: " << adr << " ����" << endl;
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
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                    //������ �������� �ʴ� �ð�
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
                                                cout << "���� �Ϸ�" << endl;
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
                                                cout << "�߸��� �����Դϴ�.." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match3.str(1)) < 24 && stoi(match3.str(3)) < 24 && stoi(match3.str(2)) < 60 && stoi(match3.str(4)) < 60))
                                            {
                                                cout << "�߸��� �����Դϴ�." << endl;
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
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }
                                            cout << "�޹��� " << day << " ����" << endl;
                                            cout << "�����ð�: " << time << " ����" << endl;
                                            cout << "�ּ�: " << adr << " ����" << endl;
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
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                    //������ �������� �ʴ� �ð�
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
                                                cout << "���� �Ϸ�" << endl;
                                                continue;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else
                                        {
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }

                                    }






                                    continue;
                                }

                            }
                        }
                        else {
                            cout << "�߸��� �����Դϴ�." << endl;
                            cin.clear();
                        }
                    }
                    else if (cin.fail()) {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "�߸��� �����Դϴ�." << endl;
                    }
                    else {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "�߸��� �����Դϴ�." << endl;
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
                            // regex M_price_Checker("^[1-9]?(,|[0-9])[\\S]*");
                            while (true) {
                                cout << "�޴��� ���� �ҹ��ڿ� �������� 1~15�� �̳��� �Է����ּ���" << endl;
                                cout << "2���̻��� ������ 1���� ġȯ�Ǹ� �� ��, �� �� ������ ���ŵ˴ϴ�." << endl;
                                cout << "������ 100~99999 �� ������ ���� �մϴ�." << endl;
                                cout << "��ǥ�� �� ���� �ƴ� ���� ������ �� �ְ�, �ΰ��� �������� ����� �� �����ϴ�." << endl;
                                cout << "�� �����ʹ� (/)�� �����ؼ� �Է����ּ���" << endl;
                                cout << "�޴�/��������: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "�ѱ��� �Է� ����" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//�յڰ����� �ڸ���
                                int scount = 0;
                                for (int i = 0; i < input.size(); i++) {
                                    if ((int)input[i] == 47)
                                        scount++;
                                }
                                //cout << "scount : " << scount << endl;

                                if (scount != 1) {
                                    if (isQuit(input)) break;
                                    cout << "�߸��� �����Դϴ�." << endl;
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
                                        cout << "�߸��� �����Դϴ�." << endl;
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
                                            cout << "�߸��� �����Դϴ�." << endl;
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
                                            ofstream writeFile;

                                            writeFile.open("Restaurant_Menu.txt", std::ofstream::out | std::ofstream::app);
                                            if (writeFile.is_open()) {
                                                string str = current_user->restaurant.at(select - 1).name + "/" + M_name + "/" + M_price + "\n";
                                                writeFile.write(str.c_str(), str.size());
                                            }
                                            else {
                                                cout << "���� ���� ����\n" << endl;
                                            }
                                            writeFile.close();
                                            readR_MenuTextFile();
                                            //menu.push_back(Menu(price, M_name));
                                            cout << "��� �Ϸ�" << endl;
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
                                            cout << "�߸��� �����Դϴ�." << endl;
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
                                            ofstream writeFile;

                                            writeFile.open("Restaurant_Menu.txt", std::ofstream::out | std::ofstream::app);
                                            if (writeFile.is_open()) {
                                                string str = current_user->restaurant.at(select - 1).name + "/" + M_name + "/" + M_price + "\n";
                                                writeFile.write(str.c_str(), str.size());
                                            }
                                            else {
                                                cout << "���� ���� ����\n" << endl;
                                            }
                                            writeFile.close();
                                            readR_MenuTextFile();
                                            cout << "��� �Ϸ�" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {//�Ѵ� ���Խ� �ȸ���->���Է�
                                        cout << "�߸��� �����Դϴ�." << endl;
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
                                cout << "�����ð��� 24�ð� �������� ����Ͽ� �ֽð� 00�ÿ� 24���� ȥ���� ���ֱ� ���� 24�ô� �Է¹��� �ʽ��ϴ�." << endl;
                                cout << "���� �ð��� ���� �ð��� Ư������(~)�� ���еǸ� �� �ð��� �ÿ� ���� (:)�� ���е˴ϴ�." << endl;
                                cout << "���� �Է��� �����˴ϴ�." << endl;
                                cout << "�޹����� ���� �ҹ��ڷ� monday, tuesday, wednesday thursday friday saturday sunday �� �ϳ��� �Է¹޽��ϴ�." << endl;
                                cout << "�����ð��� �ʼ��� ����ؾ� ������ �޹����� ������� �ʾƵ� �˴ϴ�." << endl;
                                cout << "�� �����ʹ� (/)�� �����ؼ� �Է����ּ���" << endl;
                                cout << "�ð�/�޹�����: ";
                                getline(cin, input);
                                if (!isin0to128(input)) {
                                    cout << "�ѱ��� �Է� ����" << endl;
                                    continue;
                                }
                                char* data_buff = new char[input.size() + 1];
                                strcpy(data_buff, input.c_str());
                                //trim(input);//�յڰ����� �ڸ���
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
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }

                                        if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                        {
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }
                                        cout << "�����ð�: " << input << endl;
                                        cout << "�޹��� ����" << endl;
                                        if (yesorno()) { //match ��� temp�� �ٲ㼭 ���� �ٲ㼭 �־���� 
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
                                            //�޹����̶� �ε��� ����
                                            if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                    cout << "���� ���� ����\n" << endl;
                                                }
                                                writeFile.close();
                                            }
                                            else {
                                                //������ �������� �ʴ� �ð�
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
                                                    cout << "���� ���� ����\n" << endl;
                                                }
                                                writeFile.close();
                                            }
                                            readR_InfoTextFile();
                                            cout << "��� �Ϸ�" << endl;
                                            break;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                    else {
                                        cout << "�߸��� �����Դϴ�." << endl;
                                        continue;
                                    }
                                    cout << "�߸��� �����Դϴ�." << endl;
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
                                        cout << "�߸��� �����Դϴ�." << endl;
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
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                            {
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }
                                            cout << "�����ð�: " << hour << endl;
                                            cout << "�޹���: " << close_day << endl;
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
                                                } //�޹����̶� �ε��� ����
                                                if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                        cout << "���� ���� ����\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
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
                                                        cout << "���� ���� ����\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                readR_InfoTextFile();
                                                cout << "��� �Ϸ�" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "�߸��� �����Դϴ�." << endl;
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
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }

                                            if (!(stoi(match.str(1)) < 24 && stoi(match.str(3)) < 24 && stoi(match.str(2)) < 60 && stoi(match.str(4)) < 60))
                                            {
                                                cout << "�߸��� �����Դϴ�." << endl;
                                                continue;
                                            }
                                            cout << "�����ð�: " << hour << endl;
                                            cout << "�޹���: " << close_day << endl;
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
                                                } //�޹����̶� �ε��� ����
                                                if (stoi(match.str(1)) >= stoi(match.str(3)) && stoi(match.str(2)) >= stoi(match.str(4))) {
                                                    //�սð��� �޽ð� ���� ũ�鳪���� ����
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
                                                        cout << "���� ���� ����\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                else {
                                                    //������ �������� �ʴ� �ð�
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
                                                        cout << "���� ���� ����\n" << endl;
                                                    }
                                                    writeFile.close();
                                                }
                                                readR_InfoTextFile();
                                                cout << "��� �Ϸ�" << endl;
                                                break;
                                            }
                                            else {
                                                continue;
                                            }
                                        }
                                        else {
                                            cout << "�߸��� �����Դϴ�." << endl;
                                            continue;
                                        }
                                    }
                                    else {//�Ѵ� ���Խ� �ȸ���->���Է�
                                        cout << "�߸��� �����Դϴ�." << endl;
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
                        cout << "�߸��� �����Դϴ�." << endl;
                    }
                        
                }
            }
        }
        else {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "�߸��� �����Դϴ�." << endl;

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
            cout << "������� �Է����ּ���\n" << endl;
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
