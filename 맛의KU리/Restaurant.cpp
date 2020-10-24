#include "Restaurant.h"

Restaurant::Restaurant(string category, string name, string address)
	:category(category),name(name),address(address)
{
}
Restaurant::Restaurant()
{
}
//add는 등록함수 set은 수정함수 레스토랑 멤버변수들의 입력/검사/저장할 예정
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
	cout << "부가정보 수정" << endl;
	cout << "1. 메뉴/가격 등록 \n2. 시간/휴무일 등록 \n3. 이전메뉴" << endl;
	while (true) {
		cout << "보기 선택: ";
		int select;
		cin >> select;
		cin.ignore();//버퍼 제거 
		if (select <= 3 && select >= 1) {
			if (select == 3) return;
			else if (select == 1) setMenu();
			else if (select == 2) setMore_info();
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
void Restaurant::more_info()
{
	cout << "부가정보 등록" << endl;
	cout << "1. 메뉴/가격 등록 \n2. 시간/휴무일 등록 \n3. 이전메뉴" << endl;
	while (true) {
		cout << "보기 선택: ";
		int select;
		cin >> select;
		cin.ignore();//버퍼 제거 
		if (select <= 3 && select >= 1) {
			if (select == 3) return;
			else if (select == 1) addMenu();
			else if (select == 2) addMore_info();
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

bool Restaurant::register_Status()
{
	char readline[50];//한 줄 최대 글자 
	char** temp_info = new char* [4];
	for (int i = 0; i < 2; i++) {
		temp_info[i] = new char[30];//그냥 크게 10으로 잡음
	}
	ifstream readFile;
	readFile.open("Restaurant_Info.txt");
	if (readFile.is_open()) {

		while (!readFile.eof()) {
			readFile.getline(readline, 50);
			if (!readFile.eof()) {//eof일때 strtok안해줄라고
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
		cout << "파일이 오픈되지 않음\n" << endl;
	}
	readFile.close();
}
Restaurant::~Restaurant()
{
}
