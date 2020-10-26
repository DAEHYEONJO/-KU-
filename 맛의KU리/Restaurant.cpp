#include "Restaurant.h"

Restaurant::Restaurant(string category, string name, string address)
	:category(category),name(name),address(address)
{
	
}
void Restaurant::print_menu()
{
	if (menu.empty())
		cout << name << "�Ĵ��� �޴� ��� �ȵǾ�����" << endl;
	else {
		for (int i = 0; i < menu.size(); i++)
			cout << "�Ĵ��̸� : " << name << "�޴��̸� : " << menu[i].m_name << "�޴�����  :" << menu[i].m_price << endl;
	}
		
}
void Restaurant::print_open_hour()
{
	
	if (open_hour.size() == 0) {
		cout << name << "�Ĵ��� �����ð� ��� �ȵǾ�����" << endl;
	}
	else {
		for (int i = 0; i < open_hour.size(); i++) {
			cout << open_hour[i] << " | ";
		}
		cout << endl;
	}
}
void Restaurant::print_info()
{
	cout << "ī�װ� : " << category << " �Ĵ��̸� : " << name << " �Ĵ��ּ� : " << address << endl;
	
}
void Restaurant::print_info2()
{
	cout << this->name << " �� �ΰ�����" << endl;

	cout << "�ּ�: " << this->address << endl;
	if (this->close_day.at(0) == "\0")
		cout << "�޹��� ����" << endl;
	else
		cout << "�޹��� : " << this->close_day.at(0) << " index: " << this->close_day.at(1) << endl;

	cout << "�����ð� : " << this->open_hour.at(0) << ":" << this->open_hour.at(1) << " ~ " << this->open_hour.at(open_hour.size() - 3) << ":" << this->open_hour.at(open_hour.size() - 2) << endl;
}
void Restaurant::print_close_day()
{
	
	if (close_day.size() == 0) {
		cout << "�Ĵ��̸� : " << name << "�޹��� ��� �ȵǾ�����" << endl;
	}
	else {
		for (int i = 0; i < close_day.size(); i++) {
			cout<<close_day[i] << " | ";
		}
		cout << endl;
	}
}
bool Restaurant::set_open_hour(string time)
{
	/*if (���ĸ���) {
		���� ��
			return true;
	}
	return false;*/
	return false;
}
Restaurant::Restaurant()
{
}
//add�� ����Լ� set�� �����Լ� ������� ����������� �Է�/�˻�/������ ����
void Restaurant::addMenu()
{

	Menu::inputTest();


}
void Restaurant::addMore_info()
{

}

void Restaurant::setMenu()
{

}
void Restaurant::setMore_info()
{

}
void Restaurant::change_info()
{
	cout << "�ΰ����� ����" << endl;
	cout << "1. �޴�/���� ��� \n2. �ð�/�޹��� ��� \n3. �����޴�" << endl;
	while (true) {
		cout << "���� ����: ";
		int select;
		cin >> select;
		cin.ignore();//���� ���� 
		if (select <= 3 && select >= 1) {
			if (select == 3) return;
			else if (select == 1) setMenu();
			else if (select == 2) setMore_info();
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
void Restaurant::more_info()
{
	cout << "�ΰ����� ���" << endl;
	cout << "1. �޴�/���� ��� \n2. �ð�/�޹��� ��� \n3. �����޴�" << endl;
	while (true) {
		cout << "���� ����: ";
		int select;
		cin >> select;
		cin.ignore();//���� ���� 
		if (select <= 3 && select >= 1) {
			if (select == 3) return;
			else if (select == 1) addMenu();
			else if (select == 2) addMore_info();
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

bool Restaurant::register_Status()
{
	char readline[50];//�� �� �ִ� ���� 
	char** temp_info = new char* [4];
	for (int i = 0; i < 2; i++) {
		temp_info[i] = new char[30];//�׳� ũ�� 10���� ����
	}
	ifstream readFile;
	readFile.open("Restaurant_Info.txt");
	if (readFile.is_open()) {

		while (!readFile.eof()) {
			readFile.getline(readline, 50);
			if (!readFile.eof()) {//eof�϶� strtok�����ٶ��
				//cout << readline << endl;

				temp_info[0] = strtok(readline, "/");
				temp_info[1] = strtok(NULL, "/");
				temp_info[2] = strtok(NULL, "/");
				temp_info[3] = strtok(NULL, "/");
				if (temp_info[0] == this->name) {
					if (temp_info[2] == NULL || temp_info[3] == NULL) {
						return false;
					}
					else return true;
				}
			}
		}

	}
	else {
		cout << "������ ���µ��� ����\n" << endl;
	}
	readFile.close();
}
Restaurant::~Restaurant()
{

}
