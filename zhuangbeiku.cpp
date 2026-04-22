#include"head.h"
#include<iostream>
#include<string>
using namespace std;
class cj {
public:
    static zhuangb z1() {
        return zhuangb("普通护甲", 100, 150, 10, 5, 5, 3,110, 50); // 价格50
    }
    static zhuangb z2() {
        return zhuangb("精良护甲", 150, 200, 15, 8, 8, 5,115, 100); // 价格100
        
    }
    static zhuangb z3() {
        return zhuangb("稀有护甲", 200, 250, 20, 12, 10, 7,120, 200); // 价格200
    }
    static zhuangb z4() {
        return zhuangb("史诗护甲", 250, 300, 25, 15, 12, 9,125, 300); // 价格300
    }
    static zhuangb z5() {
        return zhuangb("传说护甲", 300, 350, 30, 18, 15, 11,130, 500); // 价格500
    }
    static zhuangb z6() {
        return zhuangb("普通武器", 50, 80, 30, 3, 10, 2,135, 80); // 价格80
    }
    static zhuangb z7() {
        return zhuangb("精良武器", 80, 120, 40, 5, 15, 3,140, 150); // 价格150
    }
    static zhuangb z8() {
        return zhuangb("稀有武器", 120, 180, 50, 8, 20, 4,145, 300); // 价格300
    }
    static zhuangb z9() {
        return zhuangb("史诗武器", 180, 250, 60, 12, 25, 5,150, 500); // 价格500
    }
};

// 获取装备
zhuangb zhuangbei(int i) {
    zhuangb a;
    switch (i) {
    case 1:a = cj::z1(); break;
    case 2:a = cj::z2(); break;
    case 3:a = cj::z3(); break;
    case 4:a = cj::z4(); break;
    case 5:a = cj::z5(); break;
    case 6:a = cj::z6(); break;
    case 7:a = cj::z7(); break;
    case 8:a = cj::z8(); break;
    case 9:a = cj::z9(); break;
    default:
        std::cerr << "Invalid equipment number: " << i << std::endl;
        break;
    }
    return a;
}