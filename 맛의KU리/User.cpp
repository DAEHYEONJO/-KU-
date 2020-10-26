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
	int i;
	if (restaurant.size() == 0) {
		cout << "등록된 식당이 없습니다" << endl;
		return;
	}
	for (i = 0; i < restaurant.size(); i++) {
		cout << i + 1 << ". " << restaurant.at(i).name;
		if (!(restaurant[i].open_hour.empty())) {
			//등록이 완료되어있다면 true 반환
			if (!restaurant[i].menu.empty())
				cout << "(full info)" << endl;
			else
				cout << "(need menu info)" << endl;
		}
		else {
			if (!restaurant[i].menu.empty())
				cout << "(need time/day info)" << endl;
			else
				cout << "(need both info)" << endl;
		}
	}
	cout << i + 1 << ". 메인메뉴 돌아가기" << endl;
}

void User::print()
{
	if (restaurant.size() == 0) {
		cout << id << "의 식당 등록되어있지 않음" << endl;
	}
	else {
		cout << "id : " << id << "님의 식당 상세 정보" << endl;
		for (int i = 0; i < restaurant.size(); i++) {
			cout <<"==============="<< i + 1 << "번째 식당정보" << "===============" << endl;
			restaurant[i].print_info();
			restaurant[i].print_menu();
			restaurant[i].print_open_hour();
			restaurant[i].print_close_day();
		}
	}
}

void User::readRestTxtFIle()
{
	restaurant.clear();//user 초기화
	char readline[50];//한 줄 최대 16글자 id->10, /->1, pw->4, \n->1
	char** temp_info = new char* [4];
	for (int i = 0; i < 2; i++) {
		temp_info[i] = new char[30];//그냥 크게 10으로 잡음
	}
	ifstream readFile;
	readFile.open("Restaurant.txt");
	if (readFile.is_open()) {

		while (!readFile.eof()) {
			readFile.getline(readline, 50);
			if (!readFile.eof()) {//eof일때 strtok안해줄라고
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
		cout << "파일이 오픈되지 않음\n" << endl;
	}
	readFile.close();
}

User::~User()
{
}

