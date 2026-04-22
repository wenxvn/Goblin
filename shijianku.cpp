#include"head.h"
#include<iostream>
#include<string>
using namespace std;
class cj {
public:
	static shij s1() {
		
		return shij("土坡中央的位置，是一个明显由\
		生物开凿而成的泥石洞穴，洞口有着大量生物活动的痕\
		迹。空气中隐隐能闻到丝缕臭气。",
			"深入探索",
			"我是胆小鬼，我先溜了");
	}
};
class cj2 {
public:
	static shij s1(int j) {
		if (j == 1) {
			//在该格生成boss大哥布林
			//修改全局变量
			return shij("你惊扰了大哥布林");
		}
		else if (j == 2) {
			return shij("你小心的离开了");
		};
	}
};
shij shijian1(int i) {
	shij a;
	switch (i) {
	case 1:a = cj::s1();break;
	case 2:
	default:
		break;
	}
	return a;
}
shij shijian2(int i, int j) {
	shij a;
	switch (i) {
	case 1:a = cj2::s1(j);break;
	//case 2:
	}
	return a;
}