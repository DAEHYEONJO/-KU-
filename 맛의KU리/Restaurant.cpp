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
		cout <<"ī�װ� : " <<category<<" �Ĵ��̸� : " << name << endl;
		for (int i = 0; i < menu.size(); i++)
			cout<< "�޴��̸� : " << menu[i].m_name << " �޴�����  :" << menu[i].m_price <<"won"<<endl;
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

	//cout << "�����ð� : " << this->open_hour.at(0) << ":" << this->open_hour.at(1) << " ~ " << this->open_hour.at(open_hour.size() - 3) << ":" << this->open_hour.at(open_hour.size() - 2) << endl;
	cout << "open_hour size : " << open_hour.size() << endl;
	if(!open_hour.empty())
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
