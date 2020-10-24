#include "User.h"

User::User()
{
}

User::User(string id, string pw)
	:id(id), pw(pw)
{
}
void User::printMyRest()
{
	readRestTxtFIle();
	int i;
	if (restaurant.size() == 0) {
		cout << "��ϵ� �Ĵ��� �����ϴ�" << endl;
		return;
	}
	for (i = 0; i < restaurant.size(); i++) {
		cout << i + 1 << ". " << restaurant.at(i).name;
		if (restaurant.at(i).register_Status())//����� �Ϸ�Ǿ��ִٸ� true ��ȯ
			cout << "(full info)" << endl;
		else
			cout << "(register more info)" << endl;
	}
	cout << i + 1 << ". ���θ޴� ���ư���" << endl;	
}

void User::readRestTxtFIle()
{
	restaurant.clear();//user �ʱ�ȭ
	char readline[50];//�� �� �ִ� 16���� id->10, /->1, pw->4, \n->1
	char** temp_info = new char* [4];
	for (int i = 0; i < 2; i++) {
		temp_info[i] = new char[30];//�׳� ũ�� 10���� ����
	}
	ifstream readFile;
	readFile.open("Restaurant.txt");
	if (readFile.is_open()) {

		while (!readFile.eof()) {
			readFile.getline(readline, 50);
			if (!readFile.eof()) {//eof�϶� strtok�����ٶ��
				cout << readline << endl;

				temp_info[0] = strtok(readline, "/");
				temp_info[1] = strtok(NULL, "/");
				temp_info[2] = strtok(NULL, "/");
				temp_info[3] = strtok(NULL, "/");
				if(temp_info[0]==this->id)
					restaurant.push_back(Restaurant(temp_info[1], temp_info[2],temp_info[3]));
			}
		}

	}
	else {
		cout << "������ ���µ��� ����\n" << endl;
	}
	readFile.close();
}

User::~User()
{
}

