#include"head.h"
#include<iostream>
#include<string>
using namespace std;
class cj {
public:
	static guaiw g1() {
		return guaiw("蓝色史莱姆", 50, 50, 3, 5, 5, 105, 9, 1, 0, 0);
	}
	static guaiw g2() {
		return guaiw("粉色史莱姆", 60, 60, 5, 3, 3, 110, 6, 1, 0, 0);
	}
	static guaiw g3() {
		return guaiw("史莱姆女王", 60, 60, 5, 3, 3, 110, 0, 1, 0, 0);
	}
	static guaiw g4() {
		return guaiw("哥布林", 60, 60, 5, 3, 3, 110, 0, 1, 0, 0);
	}
	static guaiw g5() {
		return guaiw("大哥布林", 60, 60, 5, 3, 3, 110, 0, 1, 0, 0);
	}
	static guaiw g6() {
		return guaiw("树妖", 60, 60, 5, 3, 3, 110, 0, 1, 0, 0);
	}
};

guaiw guaiwu(int i) {
	guaiw a;
	switch (i) {
	case 1:
		a = cj::g1();break;
	case 2:
		a = cj::g2();break;

	case 3:
		a = cj::g3();break;

	case 4:
		a = cj::g4();break;

	case 5:
		a = cj::g5();break;

	case 6:
		a = cj::g6();break;

		return a;
	}
}