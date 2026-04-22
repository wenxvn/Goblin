#pragma once
#include<iostream>
#include<string>
using namespace std;
#ifndef MY_CLASS_H
#define MY_CLASS_H
extern int flag ;//计数器，记载此时地图的编号
extern int map[13][13]  ;//地图信息，在init（）时具体赋值
//map[][]={0空地，1门，2技能导师重合，3冒险协会重合，4铁匠铺，5酒馆，6有boss}
extern int rw[2] ;//角色位置信息，在init（）赋值
extern int dqjszb[6] ;//当前角色装备的数组
extern int dqjsjn[3] ;//当前角色技能的数组
extern int dqjssx[7] ;//存储当前角色属性
extern int guai1[13][13] ;

//怪物在地图的位置init赋值
//（生命值，生命上限，攻击，防御，暴击率，爆伤，闪避）
// 进阶方案（吸血，反击，减伤（每次受到伤害均减少固定数值），格挡（盾），回复（每次交战固定回复））
class zhuangb {
public:
	std::string s;
	int sx[7];
	int price;

	// 确保只有一个构造函数，或者调用时使用了正确的构造函数
	zhuangb(const std::string& init_s = "",
		int sx0 = 0, int sx1 = 0, int sx2 = 0, int sx3 = 0,
		int sx4 = 0, int sx5 = 0, int sx6 = 0, int pr = 0)
		: s(init_s), price(pr) {
		sx[0] = sx0;
		sx[1] = sx1;
		sx[2] = sx2;
		sx[3] = sx3;
		sx[4] = sx4;
		sx[5] = sx5;
		sx[6] = sx6;
	}
};
zhuangb zhuangbei(int i);
class guaiw {
public:
	//名称
	string ming;
	//属性
	int sx[7];
	//技能
	int jn[3];
	guaiw(const string& init_ming = "",
		int sx0 = 0, int sx1 = 0, int sx2 = 0, int sx3 = 0,
		int sx4 = 0, int sx5 = 0, int sx6 = 0, int jn0 = 0,
		int jn1 = 0, int jn2 = 0)
		:ming(init_ming) {
		sx[0] = sx0;
		sx[1] = sx1;
		sx[2] = sx2;
		sx[3] = sx3;
		sx[4] = sx4;
		sx[5] = sx5;
		sx[6] = sx6;
		jn[0] = jn0;
		jn[1] = jn1;
		jn[2] = jn2;
	}
};
extern guaiw guai2[13][13];
guaiw guaiwu(int i);
class Skill {
public:
	std::string name;
	int sx[7]; // 技能属性加成，与装备属性对应
	int price;

	Skill(const std::string& init_name = "",
		int sx0 = 0, int sx1 = 0, int sx2 = 0, int sx3 = 0,
		int sx4 = 0, int sx5 = 0, int sx6 = 0, int pr = 0)
		: name(init_name), price(pr) {
		sx[0] = sx0;
		sx[1] = sx1;
		sx[2] = sx2;
		sx[3] = sx3;
		sx[4] = sx4;
		sx[5] = sx5;
		sx[6] = sx6;
		std::cout << "创建技能，价格输入: " << pr << ", 实际价格: " << price << std::endl;
	}
};

Skill skill(int i); // 声明获取技能的函数

// 声明技能数组

class shij {
public:
	string s[4];
	shij(const string& s0 = "",
		const string& s1 = "",
		const string& s2 = "",
		const string& s3 = "") {
		s[0] = s0;
		s[1] = s1;
		s[2] = s2;
		s[3] = s3;
	}
	shij(int i)
	{
		for (int i = 0;i < 4;i++)s[i] = "";
	}
};
shij shijian1(int i);
shij shijian2(int i, int j);
string jineng1(int i);
void jineng2(int i,int x, int y);
int jineng3(int i);
void jineng4(int i, int x, int y);
#endif