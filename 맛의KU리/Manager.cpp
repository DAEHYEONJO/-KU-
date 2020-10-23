#include "Manager.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int Manager::signUp()
{
	//id 입력받기 -> 제대로입력, 중복검사 -> pw 입력받기 -> 4자리숫자 입력 조건 충족 -> text파일에 저장하기
	//id, pw 입력 받을 때 quit 입력시 메인메뉴로 돌아가기
	/**/
	string test_id, test_pw;
	regex idChecker1("^[a-zA-Z0-9].*$");//알파벳/숫자인경우
	//regex idChecker2("^([0-9]+[a-zA-Z]).*$");//숫자먼저시작하는경우

	while (true) {//id roof
		cout << "id는 숫자와 영문자 조합이며, 6자리~10자리로 입력하세요\nid : ";
		getline(cin, test_id);
		if (isSpace(test_id)) {
			continue;
		}
		else {
			if (!isQuit(test_id)) {//quit 아니면
				if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
					if (regex_match(test_id, idChecker1)) {
						cout << "조건맞음\n" << endl;
						readInfoTextFile();//저장되어있는거 읽어오기.
						int count = 0;
						for (count = 0; count < user.size(); count++) {//text file 중복검사
							cout << "저장값 : " << user[count].id.c_str() << "입력값 : " << test_id << endl;
							if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
						}
						if (count == user.size()) {
							cout << "중복되는 id 없음\n" << endl;
							while (true) {//pw roof
								cout << "pw는 숫자만으로 이루어져 있으며, 4자리로 입력하세요\npw : ";
								regex pwChecker("^[0-9]{4}$");
								getline(cin, test_pw);//pw입력받기

								if (regex_match(test_pw, pwChecker)) {
									cout << "아이디 패스워드 모두 완료\n" << endl;
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
									cout << "pw 조건 오류\n" << endl;
								}
							}
						}
						else {
							cout << "id 중복\n" << endl;
						}
					}
					else {
						cout << "영문자와 숫자를 포함하여 주세요\n" << endl;
					}
				}
				else {
					cout << "id 길이 조건 오류\n" << endl;
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
	cout << "로그인이다\n" << endl;
	regex idChecker1("^[a-zA-Z0-9].*$");//영어먼저시작하는경우
	//regex idChecker2("^([0-9]+[a-zA-Z]).*$");//숫자먼저시작하겹치다는경우

	while (true) {//id roof
		cout << "id : ";
		string test_id, test_pw;
		getline(cin, test_id);
		if (isSpace(test_id)) {
			continue;
		}
		else {
			if (!isQuit(test_id)) {
				if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
					if (regex_match(test_id, idChecker1)) {
						readInfoTextFile();//저장되어있는거 읽어오기.
						int count = 0;
						for (count = 0; count < user.size(); count++) {//text file 중복검사
							cout << "저장값 : " << user[count].id.c_str() << "입력값 : " << test_id << endl;
							if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
						}
						if (count == user.size()) {//중복된 아이디 없으면 다시입력받기
							cout << "중복된 아이디 없음.\n" << endl;
						}
						else {
							while (true) {
								cout << "pw : ";
								regex pwChecker("^[0-9]{4}$");
								getline(cin, test_pw);//pw입력받기

								if (regex_match(test_pw, pwChecker)) {//pw형식 옳바름
									if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
										//로그인성공
										current_user = User(user[count].id, user[count].pw);
										//로그인 성공한 계정 접속
										cout << "로그인 성공!\n id: " << user[count].id << endl;
										return 1;
									}
									else {
										cout << "비밀번호가 일치하지 않습니다.\n" << endl;
									}

								}
								else {
									cout << "옳바르지 않은 pw형식\n" << endl;
								}
							}


						}
					}
				}
				else {
					cout << "id 길이 조건 오류\n" << endl;
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
	while (c!=4) {
		
		cout << "1. 로그인\t2. 회원가입\n>>보기선택 : ";
		string test_menu = "";
		regex menuChecker("^(1|2){1}$");

		getline(cin, test_menu);
	
		if (regex_match(test_menu, menuChecker)){//입력값이 1 또는 2이면 진행
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
				cout << "이 문장 절대나오면 안됨 나오면 말해줘.\n" << endl;
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
		cout << "1. 식당등록\t2.식당관리\t3. 식당검색\t4. 종료 : ";
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
					registerRestaurant();
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					cout << "이 말 절대나오면안됨" << endl;
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
	cout << "카테고리/식당이름/식당주소" << endl << "입력하세요<<";
	string data;
	getline(cin, data);

}

void Manager::searchRestaurant()
{
}

void Manager::readInfoTextFile()
{
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
				cout << readline << endl;
				
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
			cout << "공백없이 입력해주세요" << endl;
			return true;
		}
	}
	return false;
}


Manager::Manager()
{
}

Manager::~Manager()
{
}
