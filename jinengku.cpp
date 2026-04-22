#include"head.h"
#include<iostream>
#include<string>
using namespace std;
class cj {
public:
	static string j1() {
		//详情
		string zong = "【旋斩】\n对敌方的伤害增加50%";
		return  zong;
	}
};
void shanghai1(int& kou) {
	int randomnumber = rand() % 100;
	if (dqjssx[4]<= randomnumber) {
		kou = dqjssx[2] * (100 - dqjssx[3]) / 100 * dqjssx[5];
	}//暴击
	else {
		kou = dqjssx[2] * (100 - dqjssx[3]) / 100;
	}//没暴
	
}
void shanghai2(int& kou,int x,int y) {
	int randomnumber = rand() % 100;
	if (guai2[x][y].sx[4]<= randomnumber) {
		kou = guai2[x][y].sx[2] * (100 - guai2[x][y].sx[3]) / 100 * guai2[x][y].sx[5];
	}//暴击
	else {
		kou = guai2[x][y].sx[2] * (100 - guai2[x][y].sx[3]) / 100;
	}//没暴
}
class cj2 {//主角
public:
	//读取全局变量当前属性
		//计算对方扣血
	static void j1(int x,int y) {
		int kou = 0;
		shanghai1(kou);
		kou = kou * 3 / 2;
		guai2[x][y].sx[0] -= kou;
	}

};
class cj3 {//概率
public:
	static int j1() {
		return 50;
	}
};
class cj4 { // 反击
public:
	static void j1(int x, int y) {
		int kou = 0;
		shanghai2(kou, x, y);
		kou = kou * 3 / 2; // 假设这里是反击伤害倍数
		std::cout << "怪物反击伤害: " << kou << std::endl;
		if (kou > 0) {
			dqjssx[0] -= kou;
			if (dqjssx[0] < 0) {
				dqjssx[0] = 0; // 确保角色血量不会为负数
			}
		}
	}
};
string jineng1(int i) {
	string a;
	switch (i) {
	case 1:a= cj::j1();break;
	//case 2:
	}
	return a;
}
void jineng2(int i,int x,int y) {
	switch (i) {
	case 1:cj2::j1(x, y);break;
	}
}
int jineng3(int i) {
	int j;
	switch (i) {
	case 1:j=cj3::j1();return j;
	}
}
void jineng4(int i, int x, int y) {
	switch (i) {
	case 1:
		cj4::j1(x, y);
		break;
	default:
		// 处理默认攻击逻辑
		int kou = 10;
		shanghai2(kou, x, y);
		std::cout << "怪物默认攻击伤害: " << kou << std::endl;
		if (kou > 0) {
			dqjssx[0] -= kou;
			if (dqjssx[0] < 0) {
				dqjssx[0] = 0; // 确保角色血量不会为负数
			}
		}
		break;
	}
}