<<<<<<< HEAD

#include "Manager.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

static void trim(string & s);
bool yesorno() {
	string c;
	regex ynCheck("(y)|(n){1}$");
	while (true) {
		cout << "yes or no?: ";
		getline(cin, c);

		trim(c);

		if (regex_match(c, ynCheck)) {
			if (!strcmp(c.c_str(), "y")) return true;
			else return false;//no인경우
		}
		//y 또는 n 입력 안했을때 다시 위로가서 입력받기
	}
	return false;
}

string V_address[10] = { "hwayang1dong", "hwayang2dong", "hwayang3dong", "hwayang4dong", "hwayang5dong", "hwayang6dong", "hwayang7dong", "hwayang8dong", "hwayang9dong", "hwayang10dong" };
=======
癤�#include "Manager.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

>>>>>>> first

int Manager::signUp()
{
	//id �엯�젰諛쏄린 -> �젣���濡쒖엯�젰, 以묐났寃��궗 -> pw �엯�젰諛쏄린 -> 4�옄由ъ닽�옄 �엯�젰 議곌굔 異⑹” -> text�뙆�씪�뿉 ����옣�븯湲�
	//id, pw �엯�젰 諛쏆쓣 �븣 quit �엯�젰�떆 硫붿씤硫붾돱濡� �룎�븘媛�湲�
	/**/
	string test_id="", test_pw="";
	regex idChecker1("[a-zA-Z0-9]+");//�븣�뙆踰�/�닽�옄�씤寃쎌슦
	//regex idChecker2("^([0-9]+[a-zA-Z]).*$");//�닽�옄癒쇱���떆�옉�븯�뒗寃쎌슦

	while (true) {//id roof
		test_id.clear();
		test_pw.clear();
		cout << "id�뒗 �닽�옄��� �쁺臾몄옄 議고빀�씠硫�, 6�옄由�~10�옄由щ줈 �엯�젰�븯�꽭�슂\nid : ";
		getline(cin, test_id);
		if (isin0to128(test_id)) cout << "�븳湲� �엯�젰 �꽩�꽩" << endl;
		else continue;
		cout << (int)test_id[0] << endl;
		if (isSpace(test_id)) continue;
		else {
			if (!isQuit(test_id)) {//quit �븘�땲硫�
				if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
					if (regex_match(test_id, idChecker1)) {
						cout << "議곌굔留욎쓬\n" << endl;
						readInfoTextFile();//����옣�릺�뼱�엳�뒗嫄� �씫�뼱�삤湲�.
						int count = 0;
						for (count = 0; count < user.size(); count++) {//text file 以묐났寃��궗
							cout << "����옣媛� : " << user[count].id.c_str() << "�엯�젰媛� : " << test_id << endl;
							if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
						}
						if (count == user.size()) {
							cout << "以묐났�릺�뒗 id �뾾�쓬\n" << endl;
							while (true) {//pw roof
								cout << "pw�뒗 �닽�옄留뚯쑝濡� �씠猷⑥뼱�졇 �엳�쑝硫�, 4�옄由щ줈 �엯�젰�븯�꽭�슂\npw : ";
								regex pwChecker("^[0-9]{4}$");
								getline(cin, test_pw);//pw�엯�젰諛쏄린

								if (regex_match(test_pw, pwChecker)) {
									cout << "�븘�씠�뵒 �뙣�뒪�썙�뱶 紐⑤몢 �셿猷�\n" << endl;
									//info.txt�뿉 �빐�떦 �븘�씠�뵒 �뙣�뒪�썙�뱶 異붽���븯湲�.
									ofstream writeFile;
									writeFile.open("info.txt", std::ofstream::out | std::ofstream::app);//�벐湲곕え�뱶, �씠�뼱�꽌 異붽���븯湲�
									if (writeFile.is_open()) {
										string merge = test_id + "/" + test_pw + "\n";
										writeFile.write(merge.c_str(), merge.size());
									}
									else {
										cout << "�뙆�씪 �삤�뵂 �삤瑜�\n" << endl;
									}
									writeFile.close();
									readInfoTextFile();//�깉濡� 異붽���릺�뿀�쑝�땲 user踰≫꽣�뿉 異붽���빐二쇨린
									return 1;
								}
								else {
									cout << "pw 議곌굔 �삤瑜�\n" << endl;
								}
							}
						}
						else {
							cout << "id 以묐났\n" << endl;
						}
					}
					else {
						cout << "�쁺臾몄옄��� �닽�옄瑜� �룷�븿�븯�뿬 二쇱꽭�슂\n" << endl;
					}
				}
				else {
					cout << "id 湲몄씠 議곌굔 �삤瑜�\n" << endl;
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
	cout << "濡쒓렇�씤�씠�떎\n" << endl;
	regex idChecker1("[a-zA-Z0-9]+");//�쁺�뼱癒쇱���떆�옉�븯�뒗寃쎌슦
	//regex idChecker2("^([0-9]+[a-zA-Z]).*$");//�닽�옄癒쇱���떆�옉�븯寃뱀튂�떎�뒗寃쎌슦

	while (true) {//濡쒓렇�씤 �꽦怨듯븯硫� current_user�뿉 濡쒓렇�씤�븳 �쑀��� �젙蹂� ����옣�맖
		cout << "id : ";
		string test_id, test_pw;
		getline(cin, test_id);
		if (isSpace(test_id)) continue;
		else {
			if (!isQuit(test_id)) {
				if ((test_id.size() >= 6) && (test_id.size() <= 10)) {
					if (regex_match(test_id, idChecker1)) {
						readInfoTextFile();//����옣�릺�뼱�엳�뒗嫄� �씫�뼱�삤湲�.
						int count = 0;
						for (count = 0; count < user.size(); count++) {//text file 以묐났寃��궗
							cout << "����옣媛� : " << user[count].id.c_str() << "�엯�젰媛� : " << test_id << endl;
							if (!strcmp(user[count].id.c_str(), test_id.c_str())) break;
						}
						if (count == user.size()) {//以묐났�맂 �븘�씠�뵒 �뾾�쑝硫� �떎�떆�엯�젰諛쏄린
							cout << "以묐났�맂 �븘�씠�뵒 �뾾�쓬.\n" << endl;
						}
						else {
							while (true) {
								cout << "pw : ";
								regex pwChecker("^[0-9]{4}$");
								getline(cin, test_pw);//pw�엯�젰諛쏄린

								if (regex_match(test_pw, pwChecker)) {//pw�삎�떇 �삾諛붾쫫
									if (!strcmp(user[count].pw.c_str(), test_pw.c_str())) {
										//濡쒓렇�씤�꽦怨�
										current_user = new User(user[count].id, user[count].pw);
										//濡쒓렇�씤 �꽦怨듯븳 怨꾩젙 �젒�냽
										cout << "濡쒓렇�씤 �꽦怨�!\n id: " << user[count].id << endl;
										return 1;
									}
									else {
										cout << "鍮꾨��踰덊샇媛� �씪移섑븯吏� �븡�뒿�땲�떎.\n" << endl;
									}

								}
								else {
									cout << "�삾諛붾Ⅴ吏� �븡��� pw�삎�떇\n" << endl;
								}
							}


						}
					}
				}
				else {
<<<<<<< HEAD
					cout << "id 길이 조건 오류\n" << endl;
=======
				cout << "id 湲몄씠 議곌굔 �삤瑜�\n" << endl;
>>>>>>> first
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
		cout << "1. 濡쒓렇�씤\t2. �쉶�썝媛��엯\n>>蹂닿린�꽑�깮 : ";
		
		regex menuChecker("^(1|2){1}$");

		getline(cin, test_menu);

		if (regex_match(test_menu, menuChecker)) {//�엯�젰媛믪씠 1 �삉�뒗 2�씠硫� 吏꾪뻾
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
				cout << "�씠 臾몄옣 �젅����굹�삤硫� �븞�맖 �굹�삤硫� 留먰빐以�.\n" << endl;
				break;
			}
		}
		else {
			cout << "ERROR : input 1 or 2\n" << endl;
		}
	}
}

bool Manager::yesorno()
{
	string c = "";
	regex ynCheck("(y)|(n){1}$");
	while (true) {
		cout << "yes or no?: ";
		getline(cin, c);
		trim(c);
		if (regex_match(c, ynCheck)) {
			if (!strcmp(c.c_str(), "y")) return 1;
			return 0;
		}
		//y �삉�뒗 n �엯�젰 �븞�뻽�쓣�븣 �떎�떆 �쐞濡쒓���꽌 �엯�젰諛쏄린
	}
	return false;
}

int Manager::mainMenu()
{
	while (true) {
		cout << "1. �떇�떦�벑濡�\t2.�떇�떦愿�由�\t3. �떇�떦寃��깋\t4. 醫낅즺 : ";
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
					cout << "�씠 留� �젅����굹�삤硫댁븞�맖" << endl;
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
<<<<<<< HEAD
	string data, category, R_name, R_address;
	char* data_buff = new char[15];
	while (true) {
		cout << "카테고리/식당이름/식당주소" << endl << "입력하세요<<";
		getline(cin, data);
		strcpy(data_buff, data.c_str());
		trim(data);//앞뒤공백은 자르기
		if (!isQuit(data)) {
			category = string(strtok(data_buff, "/"));
			R_name = string(strtok(NULL, "/"));
			R_address = string(strtok(NULL, "/"));
			trim(category);
			trim(R_name);
			trim(R_address);

			//카테고리검사
			if (!(strcmp(category.c_str(), "japanese") == 0 || strcmp(category.c_str(), "chinese") == 0 || strcmp(category.c_str(), "korean") == 0 || strcmp(category.c_str(), "western") == 0))
			{
				cout << "카테고리 규칙위반 " << endl;
				continue;
			}
			
			//이름검사
			vector<char*>v;
			char* buf = new char[R_name.size()];
			strcpy(buf, R_name.c_str());
			char* ptr = strtok(buf, " \t");
			while (ptr != nullptr) {
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
=======
	vector<User>temp_user;
	int scount = 0;//slash count
	string data="", category="", R_name="", R_address="";
	char* data_buff = nullptr;
	while (true) {
		scount = 0;
		cout << "移댄뀒怨좊━/�떇�떦�씠由�/�떇�떦二쇱냼" << endl << "�엯�젰�븯�꽭�슂<<";
	//	data = "";
		getline(cin,data);
		cout << "data : " << data << endl;
		cout << "datasize : " << data.size() << endl;
		data_buff = new char[data.size() + 1];
		strcpy(data_buff, data.c_str());
		for (int i = 0; i < data.size(); i++) {
			if ((int)data[i] == 47)
				scount++;
		}
		cout << "scount : "<<scount << endl;

		if (scount != 2) continue;//�뒳�옒�떆 2媛� �븘�땲硫� �떎�떆�엯�젰諛쏄린
		
		trim(data);//�븵�뮘怨듬갚��� �옄瑜닿린
		if (!isQuit(data)) {
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
			
			cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;
			trim(category);
			trim(R_name);
			trim(R_address);
			cout << "category/" << category << "/R_name/" << R_name << "/R_address/" << R_address << endl;

			regex categoryChecker("^[a-z].*$");
			if (!regex_match(category, categoryChecker)) {
				cout << "移댄뀒怨좊━ �쁺臾몄옄留� �엯�젰�븯�꽭�슂" << endl;
				continue;
			}
			else {
				if (!((strcmp(category.c_str(), "japanese") == 0) || (strcmp(category.c_str(), "chinese") == 0) || (strcmp(category.c_str(), "korean") == 0) || (strcmp(category.c_str(), "western") == 0)))
				{//移댄뀒怨좊━ 寃��궗
					cout << "2??" << endl;
					cout << "移댄뀒怨좊━ 4以묒뿉 �븳媛쒕쭔 �엯�젰�빐二쇱꽭�슂�뀉�뀆" << endl;
					continue;
				}
			}
			
			//�씠由꾧���궗
			regex nameChecker("[a-zA-Z[:space:]]+");
			if (!regex_match(R_name, nameChecker)) {
				cout << "�떇�떦 �씠由� �쁺臾몄옄 �삉�뒗 �쁺臾몄옄��� 怨듬갚 議고빀�쑝濡� �엯�젰�븯�꽭�슂" << endl;
				continue;
			}
			else {
				regex upperChecker("[A-Z]");
				for (int i = 0; i < R_name.size(); i++) {
					R_name[i] = tolower(R_name[i]);
				}
				cout << "R_name : " << R_name << endl;
				vector<char*>v;
				char* buf = new char[R_name.size() + 1];
				strcpy(buf, R_name.c_str());
				char* ptr = strtok(buf, " \t");//怨듬갚+�꺆 議고빀�룄 �뙋蹂꾪븯湲곗쐞�븿
				while (ptr != nullptr) {
					cout << "3??" << endl;
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
				//�뀓�뒪�듃�뙆�씪�뿉 �떇�떦�씠由� �엳�굹 �뾾�굹 寃��궗�븯湲�
			}
			regex adrChecker("[a-zA-Z0-9]+");//�븣�뙆踰�+�닽�옄留뚯엯�젰
			if (!regex_match(R_address, adrChecker)) {
				cout << "�쁺臾몄옄留� �엯�젰�븯�꽭�슂" << endl;
				continue;
			}
			else {
				bool check = false;
				for (int i = 0; i < 10; i++) {//二쇱냼寃��궗
					cout << "4??" << endl;
					if (strcmp(R_address.c_str(), V_address[i].c_str()) == 0) {
						check = true;
						break;
>>>>>>> first
					}
					else {
						result += (string)v[i];
					}
				}
<<<<<<< HEAD
			}
			R_name = result;


			//주소검사
			bool check = false;
			for (int i = 0; i < 10; i++) {
				if (strcmp(R_address.c_str(), V_address[i].c_str()) == 0) {
					check = true;
					break;
				}
				else {
					check = false;
				}
			}
			if (!(check)) {
				cout << "주소 규칙위반" << endl;
				continue;
			}

			//모든항목 검사완료시 카테고리: *** 이름: *** 주소: *** 출력 후 y_n 받아야함 
			cout << "카테고리: " << category << "\n이름: " << R_name << "\n주소: " << R_address << endl;
			if (yesorno()) {
				//current_user의 레스토랑객체벡터에 레스토랑 만들어서 pushback
				current_user.restaurant.push_back(Restaurant(category, R_name, R_address));
				cout << "등록완료" << endl;
				return;
			}
		}
		else { return; }
=======
				if (!(check)) {
					cout << "二쇱냼 洹쒖튃�쐞諛�" << endl;
					continue;
				}
			}
			
			//紐⑤뱺�빆紐� 寃��궗�셿猷뚯떆 移댄뀒怨좊━: *** �씠由�: *** 二쇱냼: *** 異쒕젰 �썑 y_n 諛쏆븘�빞�븿 
			cout << "移댄뀒怨좊━: " << category << "\n�씠由�: " << R_name << "\n二쇱냼: " << R_address << endl;
			if (yesorno()) {
				//current_user�쓽 �젅�뒪�넗�옉媛앹껜踰≫꽣�뿉 �젅�뒪�넗�옉 留뚮뱾�뼱�꽌 pushback
				current_user->restaurant.push_back(Restaurant(category, R_name, R_address));
				for (int i = 0; i < current_user->restaurant.size(); i++) {
					cout << "移댄뀒怨좊━ : " << current_user->restaurant[i].category << "/�씠由� : " << current_user->restaurant[i].name << "/二쇱냼 : " << current_user->restaurant[i].address << endl;
				}

				cout << "�벑濡앹셿猷�" << endl;
				return;
			}
			cout << "5??" << endl;
		}
		else return;
>>>>>>> first
	}
}

void Manager::searchRestaurant()
{
}

void Manager::readInfoTextFile()
{
	user.clear();//user 珥덇린�솕
	char readline[16];//�븳 以� 理쒕�� 16湲��옄 id->10, /->1, pw->4, \n->1
	char** temp_info = new char* [2];
	for (int i = 0; i < 2; i++) {
		temp_info[i] = new char[10];//洹몃깷 �겕寃� 10�쑝濡� �옟�쓬
	}
	ifstream readFile;
	readFile.open("info.txt");
	if (readFile.is_open()) {

		while (!readFile.eof()) {
			readFile.getline(readline, 16);
			if (!readFile.eof()) {//eof�씪�븣 strtok�븞�빐以꾨씪怨�
				cout << readline << endl;

				temp_info[0] = strtok(readline, "/");//id
				temp_info[1] = strtok(NULL, "/");//pw

				user.push_back(User(temp_info[0], temp_info[1]));
			}
		}

	}
	else {
		cout << "�뙆�씪�씠 �삤�뵂�릺吏� �븡�쓬\n" << endl;
	}
	readFile.close();
}

bool Manager::isin0to128(string str)
{
	int i = 0;
	cout << str << endl;
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
			cout << "怨듬갚�뾾�씠 �엯�젰�빐二쇱꽭�슂" << endl;
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
	V_address = new string [10];
	for (int i = 0; i < 10; i++) {
		V_address[i] = "hwayang" + to_string(i + 1) + "dong";
		cout << V_address[i] << endl;
	}

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
	cout << "�굹�뒗 trime" << endl;
	ltrim(s);
	rtrim(s);
}
<<<<<<< HEAD
=======

>>>>>>> first
