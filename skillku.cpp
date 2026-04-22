#include "head.h"

class SkillLibrary {
public:
    static Skill s1() {
        return Skill("普通技能", 10, 15, 5, 3, 2, 1, 1, 2); // 价格50
    }
    static Skill s2() {
        return Skill("高级技能", 20, 30, 10, 6, 4, 2, 2, 5); // 价格100
    }
    // 可以添加更多技能
};

Skill skill(int i) {
    Skill a;
    switch (i) {
    case 1: a = SkillLibrary::s1(); break;
    case 2: a = SkillLibrary::s2(); break;
        // 对应更多技能
    }
    return a;
}