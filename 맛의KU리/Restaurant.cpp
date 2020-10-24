#include "Restaurant.h"

Restaurant::Restaurant(string category, string name, string address)
	:category(category),name(name),address(address)
{
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
