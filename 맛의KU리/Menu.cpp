#include "Menu.h"

Menu::Menu(int price, string name)
	:m_price(price),m_name(name)
{
	
}

bool isQuit(string str)
{
	if (!strcmp(str.c_str(), "quit")) return true;
	return false;
}
void Menu::inputTest()
{
	//�ѱ۰˻�
	//����˻�
	//�Ĵ�˻�� ������ �˻�
	string M_name, M_price,temp;
	string input;
	regex M_name_Checker("[a-zA-Z\\s]*");
	regex M_price_Checker("^[1-9]+[0-9]+,[0-9]*");
	while (true) {
		cout << "�޴�/��������: ";
		getline(cin, input);		
		char* data_buff = new char[input.size() + 1];
		strcpy(data_buff, input.c_str());
		//trim(input);//�յڰ����� �ڸ���
		if (!isQuit(input)) 
		{
			M_name = string(strtok(data_buff, "/"));
			M_price = string(strtok(NULL, "/"));
			trim(M_name);
			trim(M_price);
			if (regex_match(M_name, M_name_Checker))
			{
				for (int i = 0; i < M_name.size(); i++) {
					M_name[i] = tolower(M_name[i]);
				}
				cout << M_name << endl;
				cout << M_price << endl;
				if (!regex_match(M_price, M_price_Checker)) {
					cout << "���� ���� Ȯ��" << endl;
					continue;
				}

			}
			else if (regex_match(M_price, M_name_Checker))
			{
				temp = M_price;
				M_price = M_name;
				M_name = temp;
				cout << M_name << endl;
				cout << M_price << endl;
				if (!regex_match(M_price, M_price_Checker)) {
					cout << "���� ���� Ȯ��" << endl;
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

Menu::~Menu()
{
}

static void ltrim(string& s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !isspace(ch);
	}));
}


static void rtrim(string& s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !isspace(ch);
	}).base(), s.end());
}

static void trim(string& s) {
	ltrim(s);
	rtrim(s);
}
