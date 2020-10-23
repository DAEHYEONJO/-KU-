#include "Manager.h"

int Manager::signUp()
{
	//id �Է¹ޱ� -> ������Է�, �ߺ��˻� -> pw �Է¹ޱ� -> 4�ڸ����� �Է� ���� ���� -> text���Ͽ� �����ϱ�
	//id, pw �Է� ���� �� quit �Է½� ���θ޴��� ���ư���
	/**/
	string test_id, test_pw;
	regex idChecker1("^([a-zA-Z]+[0-9]).*$");//������������ϴ°��
	regex idChecker2("^([0-9]+[a-zA-Z]).*$");//���ڸ��������ϴ°��

	while (true) {//id roof
		cout << "id�� ���ڿ� ������ �����̸�, 6�ڸ�~10�ڸ��� �Է��ϼ���\nid : ";
		getline(cin, test_id);
		if (!isQuit(test_id)) {//quit �ƴϸ�
			if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
				if (regex_match(test_id, idChecker1) || regex_match(test_id, idChecker2)) {
					cout << "���Ǹ���\n" << endl;
					readInfoTextFile();//����Ǿ��ִ°� �о����.
					int count = 0;
					for (count = 0; count < user.size(); count++) {//text file �ߺ��˻�
						cout << "���尪 : " << user[count].id.c_str() << "�Է°� : " << test_id << endl;
						if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
					}
					if (count == user.size()) {
						cout << "�ߺ��Ǵ� id ����\n" << endl;
						while (true){//pw roof
							cout << "pw�� ���ڸ����� �̷���� ������, 4�ڸ��� �Է��ϼ���\npw : ";
							regex pwChecker("^[0-9]{4}$");
							getline(cin, test_pw);//pw�Է¹ޱ�

							if (regex_match(test_pw, pwChecker)) {
								cout << "���̵� �н����� ��� �Ϸ�\n" << endl;
								//info.txt�� �ش� ���̵� �н����� �߰��ϱ�.
								ofstream writeFile;
								writeFile.open("info.txt",std::ofstream::out| std::ofstream::app);//������, �̾ �߰��ϱ�
								if (writeFile.is_open()) {
									string merge = test_id + "/" + test_pw+"\n";
									writeFile.write(merge.c_str(),merge.size());
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
			break;
		}
	}
	return 0;
}

int Manager::logIn()
{
	cout << "�α����̴�\n" << endl;
	regex idChecker1("^([a-zA-Z]+[0-9]).*$");//������������ϴ°��
	regex idChecker2("^([0-9]+[a-zA-Z]).*$");//���ڸ��������ϰ�ġ�ٴ°��

	while (true) {//id roof
		cout << "id : ";
		string test_id, test_pw;
		getline(cin, test_id);
		if (!isQuit(test_id)) {
			if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
				if (regex_match(test_id, idChecker1) || regex_match(test_id, idChecker2)) {
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
									cout << "�α��� ����!\n" << endl;
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
	return 0;
}

void Manager::loginMenu()
{
	int c = 0;
	while (c!=4) {
		
		cout << "1. �α���\t2. ȸ������\n>>���⼱�� : ";
		string test_menu = "";
		regex menuChecker("^(1|2){1}$");

		getline(cin, test_menu);
	
		if (regex_match(test_menu, menuChecker)){//�Է°��� 1 �Ǵ� 2�̸� ����
			const char* buf=test_menu.c_str();//char* buf
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

bool Manager::isQuit(string str)
{
	if (!strcmp(str.c_str(), "quit")) return true;
	return false;
}


Manager::Manager()
{
}

Manager::~Manager()
{
}
