#include<iostream>
#include<easyx.h>
#include"head.h"
#include <Windows.h>
#include<mmsystem.h>
#include<fstream>
#include <vector>
#include <string> 
#include <random>
#pragma comment(lib,"winmm.lib")
using namespace std;

 int flag=0;//计数器，记载此时地图的编号
 int map[13][13] = { 0 };//地图信息，在init（）时具体赋值
//map[][]={0空地，1门，2技能导师重合，3冒险协会重合，4铁匠铺，5酒馆，6有boss}
 int rw[2] = { 0 };//角色位置信息，在init（）赋值
 int dqjszb[6] = { 0 };//当前角色装备的数组
 int dqjsjn[3] = { 0 };//当前角色技能的数组
 int dqjssx[7] = { 0 };//存储当前角色属性
 
 int guai1[13][13] = { 0 };
 guaiw guai2[13][13] = {};
void win();
void guide();
void fight(int,int);
void xianjin();
bool tjservice[18][2] = { 0 };
int cailiao = 0;//材料数量
int qian = 0;//银币数量
void guaiwuv();
void guaiwuxinxi(int , int );
void gouhuo();
void menu();
void creatbutton(int x, int y, int i, int j, const char* arr);
void g_save();
void g_jx();
void yuanbutton(int x, int y, int r, const char* arr);
void shz();
void yinyue(int i);
void yinxiao(int i);
void tuj();
void tuj_zb();
void tuj_jn();
void dutujian();
void xietujian();
void init();
void gouhuo();
void game();
void event();
void tiejiangpu();
void jinengdaoshi();
void jiuguan();
int a1 = 1, a2 = 1;


void creatbutton(int x, int y, int i, int j, const char* arr) {
    settextstyle(30, 0, "华文琥珀");
    settextcolor(RGB(30, 30, 30));
    setbkmode(TRANSPARENT);
    rectangle(x, y, i, j);
    int chang = i - x, kuan = j - y;
    int textWidth = textwidth(arr);
    int textHeight = textheight(arr);
    outtextxy(x +(chang- textWidth) / 2, y + (kuan-textHeight) / 2, arr);
}//ok!
void yuanbutton(int x, int y, int r, const char* arr)
{
    settextstyle(30, 0, "华文琥珀");
    settextcolor(RGB(30, 30, 30));
    setbkmode(TRANSPARENT);
    circle(x, y, r);
    int textWidth = textwidth(arr);
    int textHeight = textheight(arr);
    outtextxy(x - textWidth/2, y - textHeight/2, arr);
}//ok!
void menu() {
    cleardevice(); // 仅在进入菜单时清屏一次
    BeginBatchDraw();
    IMAGE img_beijing1;
    loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
    putimage(0, 0, &img_beijing1);
    settextstyle(100, 0, "华文琥珀");
    settextcolor(RGB(30, 30, 30));
    setbkmode(TRANSPARENT);
    outtextxy(350, 50, "哥布林重度依赖");
    creatbutton(300,200 ,450 ,300 , "开始新游戏");
    creatbutton(900,200,1050,300,"继续游戏");
    creatbutton(300,600 ,450 ,700 , "游戏设置");
    creatbutton(900,600 ,1050 ,700 , "游戏图鉴");
    creatbutton(650,400 ,800 ,500 , "退出游戏");
    FlushBatchDraw();
    ExMessage m;
    while (1) {
        peekmessage(&m, EX_MOUSE | EX_KEY);
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >=300 && m.x <=450 && m.y >=200 && m.y <=300 ) {
                a2 = 11;
                break;
            }
            if (m.x >= 900&& m.x <=1050 && m.y >=200 && m.y <= 300) {
                g_jx();
                a2 = 11;
                break;
            }
            if (m.x >= 300&& m.x <=450 && m.y >=600 && m.y <=700 ) {
                a2 = 2;
                break;
            }
            if (m.x >=900 && m.x <=1050 && m.y >=600 && m.y <=700 ) {
                a2 = 3;
                break;
            }
            if (m.x >=650 && m.x <=800 && m.y >= 400&& m.y <=500 ) {
                a2 = 0;
                break;
            }
        }
    }
}
void g_save() {
    //游戏，保存！
    std::ofstream outFile("wenjian/dang.txt", std::ios::binary);//问号处加上路径
    if (outFile) {
        outFile.write(reinterpret_cast<const char*>(&flag), sizeof(flag));
        outFile.write(reinterpret_cast<const char*>(map), sizeof(map));
        outFile.write(reinterpret_cast<const char*>(rw), sizeof(rw));
        outFile.write(reinterpret_cast<const char*>(dqjszb), sizeof(dqjszb));
        outFile.write(reinterpret_cast<const char*>(dqjsjn), sizeof(dqjsjn));
        outFile.write(reinterpret_cast<const char*>(dqjssx), sizeof(dqjssx));
        outFile.write(reinterpret_cast<const char*>(guai1), sizeof(guai1));
        outFile.write(reinterpret_cast<const char*>(tjservice), sizeof(tjservice));
        outFile.write(reinterpret_cast<const char*>(&cailiao), sizeof(cailiao));
        outFile.write(reinterpret_cast<const char*>(&qian), sizeof(qian));
        outFile.close();
    }
}
void g_jx() {
    //游戏，加载！
    //if有存档，那就把存档加载出来
    //else没有存档，初始化游戏
    std::ifstream inFile("wenjian/dang.txt", std::ios::binary);//问号处加上路径
    if (inFile) {
        inFile.read(reinterpret_cast<char*>(&flag), sizeof(flag));
        inFile.read(reinterpret_cast<char*>(map), sizeof(map));
        inFile.read(reinterpret_cast<char*>(rw), sizeof(rw));
        inFile.read(reinterpret_cast<char*>(dqjszb), sizeof(dqjszb));
        inFile.read(reinterpret_cast<char*>(dqjsjn), sizeof(dqjsjn));
        inFile.read(reinterpret_cast<char*>(dqjssx), sizeof(dqjssx));
        inFile.read(reinterpret_cast<char*>(guai1), sizeof(guai1));
        inFile.read(reinterpret_cast<char*>(tjservice), sizeof(tjservice));
        inFile.read(reinterpret_cast<char*>(&cailiao), sizeof(cailiao));
        inFile.read(reinterpret_cast<char*>(&qian), sizeof(qian));
        inFile.close();
    }
    else init();
}
void shz() {
    cleardevice();
    BeginBatchDraw();
    IMAGE img_beijing1;
    loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
    putimage(0, 0, &img_beijing1);
    yuanbutton(600, 225, 25, "-");
    yuanbutton(800, 225, 25, "+");
    yuanbutton(600, 625, 25, "-");
    yuanbutton(800, 625, 25, "+");
    creatbutton(650, 200, 750, 250, "音量");
    creatbutton(650, 600, 750, 650, "音效");
    FlushBatchDraw();
    static int yueliang = 300;
    static int xiaoliang = 300;
    while (1) {
        ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        if (m.message == WM_LBUTTONDOWN) {
            if ((m.x - 600) * (m.x - 600) + (m.y - 225) * (m.y - 225) <= 25 * 25) {
                yueliang = max(0, yueliang - 100);
                yinyue(yueliang);
            }
            else if ((m.x - 800) * (m.x - 800) + (m.y - 225) * (m.y - 225) <= 25 * 25) {
                yueliang = min(1000, yueliang + 100);
                yinyue(yueliang);
            }
            else if ((m.x - 600) * (m.x - 600) + (m.y - 625) * (m.y - 625) <= 25 * 25) {
                xiaoliang = max(0, xiaoliang - 100);
                yinxiao(xiaoliang);
            }
            else if ((m.x - 800) * (m.x - 800) + (m.y - 625) * (m.y - 625) <= 25 * 25) {
                xiaoliang = min(1000, xiaoliang + 100);
                yinxiao(xiaoliang);
            }
        }
        else if (m.message == WM_KEYDOWN) {
            if (m.vkcode == VK_ESCAPE) {
                a2 = 1;
                break;
            }
        }
        BeginBatchDraw();
        FlushBatchDraw();
    }
    cleardevice();
    menu();
 }//ok！
void yinyue(int i) {
    char a[30];
    snprintf(a, sizeof(a), "setaudio bgm volume to %d", i);
    mciSendString(a, NULL, 0, NULL);
}//ok!
void yinxiao(int i) {
    char a[35];
    snprintf(a, sizeof(a), "setaudio yinxiao volume to %d", i);
    mciSendString(a, NULL, 0, NULL);
}//ok!
void dutujian() {
    ifstream tujia;
    tujia.open("wenjian/tujia.txt", ios::in );
    char a[18][18] = { 0 };
    //读取文件，给tjservice全局变量赋值
    for (int i = 0;i < 18;i++) {
        for (int j = 0;j < 2;j++) {
            tujia >> a[i][j];
            tjservice[i][j] =a[i][j] ;//读文件，赋值
        }
    }
    tujia.close();
}//ok!
void xietujian() {
    ofstream tujia("wenjian/tujia.txt");
    if (tujia) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 2; j++) {
                tujia << tjservice[i][j] << " ";
            }
            tujia << "\n";
        }
        tujia.close();
    }
}
void tuj() {
    cleardevice();
    BeginBatchDraw();
    IMAGE img_beijing1;
    loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
    putimage(0, 0, &img_beijing1);
    creatbutton(0, 0, 100, 50, "返回");
    creatbutton(600, 200, 750, 300, "装备图鉴");
    creatbutton(600, 600, 750, 700, "技能图鉴");
    FlushBatchDraw();
    while (1) {
        ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >= 600 && m.y >= 200 && m.x <= 750 && m.y <= 300) {
                //装备图鉴
                a2 = 4;
                break;
            }
            else if (m.x >= 600 && m.y >= 600 && m.x <= 750 && m.y <= 700) {
                //技能图鉴
                a2 = 5;
                break;
            }
            else if (m.x >= 0 && m.y >= 0 && m.x <= 100 && m.y <= 50) {
                //点左上角的返回
                a2 = a1;
                break;
            }

        }
        else if (m.message == WM_KEYDOWN) {
            if (m.vkcode == VK_ESCAPE) {
                a2 = 1;
                break;
            }
        }
    }
}//ok!
void jnnn(int i, int j) {
   
        switch (i + 1) {
        case 1:
        {
            IMAGE img_jn1;
            loadimage(&img_jn1, "tupian/jn1.jpg", 200, 100);
            putimage(200, 100, &img_jn1);
            break;
        }

        case 2:
        {
            IMAGE img_jn2;
            loadimage(&img_jn2, "tupian/jn2.jpg", 200,100);
            putimage(600,100, &img_jn2);
            break;
        }

        case 3:
        {
            IMAGE img_jn3;
            loadimage(&img_jn3, "tupian/jn3.jpg", 200, 100);
            putimage(1000, 100, &img_jn3);
            break;
        }

        case 4:
        {
            IMAGE img_jn4;
            loadimage(&img_jn4, "tupian/jn4.jpg", 200, 100);
            putimage(200, 300, &img_jn4);
            break;
        }

        case 5:
        {
            IMAGE img_jn5;
            loadimage(&img_jn5, "tupian/jn5.jpg", 200, 100);
            putimage(600, 300, &img_jn5);
            break;
        }
        case 6:
        {
            IMAGE img_jn6;
            loadimage(&img_jn6, "tupian/jn6.jpg", 200,100);
            putimage(1000, 300, &img_jn6);
            break;
        }

        case 7:
        {
            IMAGE img_jn7;
            loadimage(&img_jn7, "tupian/jn7.jpg", 200, 100);
            putimage(200, 500, &img_jn7);
            break;
        }

        case 8:
        {
            IMAGE img_jn8;
            loadimage(&img_jn8, "tupian/jn8.jpg", 200, 100);
            putimage(400, 500, &img_jn8);
            break;
        }

        case 9:
        {
            IMAGE img_jn9;
            loadimage(&img_jn9, "tupian/jn9.jpg", 200, 100);
            putimage(1000,500, &img_jn9);
            break;
        }
        }
    
}
void zbbb(int i,int j) {
        switch (i + 1) {
        case 1:
        {
            IMAGE img_zb1;
            loadimage(&img_zb1, "tupian/zb1.jpg", 200, 100);
            putimage(200, 100, &img_zb1);
            break;
        }

        case 2:
        {
            IMAGE img_zb2;
            loadimage(&img_zb2, "tupian/zb2.jpg", 200, 100);
            putimage(600, 100, &img_zb2);
            break;
        }

        case 3:
        {
            IMAGE img_zb3;
            loadimage(&img_zb3, "tupian/zb3.jpg", 200, 100);
            putimage(1000, 100, &img_zb3);
            break;
        }

        case 4:
        {
            IMAGE img_zb4;
            loadimage(&img_zb4, "tupian/zb4.jpg", 200, 100);
            putimage(200, 300, &img_zb4);
            break;
        }

        case 5:
        {
            IMAGE img_zb5;
            loadimage(&img_zb5, "tupian/zb5.jpg", 200, 100);
            putimage(600, 300, &img_zb5);
            break;
        }
        case 6:
        {
            IMAGE img_zb6;
            loadimage(&img_zb6, "tupian/zb6.jpg", 200, 100);
            putimage(1000, 300, &img_zb6);
            break;
        }

        case 7:
        {
            IMAGE img_zb7;
            loadimage(&img_zb7, "tupian/zb7.jpg", 200, 100);
            putimage(200, 500, &img_zb7);
            break;
        }

        case 8:
        {
            IMAGE img_zb8;
            loadimage(&img_zb8, "tupian/zb8.jpg", 200, 100);
            putimage(400, 500, &img_zb8);
            break;
        }

        case 9:
        {
            IMAGE img_zb9;
            loadimage(&img_zb9, "tupian/zb9.jpg", 200, 100);
            putimage(1000, 500, &img_zb9);
            break;
        }
        }
    }
    void tuj_zb() {
    cleardevice(); // 仅在进入装备图鉴时清屏一次
    BeginBatchDraw();
    IMAGE img_beijing1;
    loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
    putimage(0, 0, &img_beijing1);
    creatbutton(0, 0, 100, 50, "返回");
    creatbutton(350, 700, 400, 720, "<");
    creatbutton(400, 700, 450, 720, ">");
    for (int i = 0; i < 9; i++) {
        int j = 0;
        if (tjservice[i][j]) {
            zbbb(i, j);
        }
    }
    FlushBatchDraw();
    while (1) {
        ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >= 0 && m.y >= 0 && m.x <= 100 && m.y <= 50) {
                // 左上角的返回
                a2 = a1;
                break;
            }
            else if (m.x > 400 && m.y > 700 && m.x < 450 && m.y < 720) { // 右箭头
                BeginBatchDraw();
                // 不进行清屏操作，直接绘制新内容
                for (int i = 9; i < 18; i++) {
                    int j = 0;
                    if (tjservice[i][j]) {
                        zbbb(i, j);
                    }
                }
                FlushBatchDraw();
            }
            else if (m.x > 350 && m.y > 700 && m.x < 400 && m.y < 720) { // 左箭头
                BeginBatchDraw();
                // 不进行清屏操作，直接绘制新内容
                for (int i = 0; i < 9; i++) {
                    int j = 0;
                    if (tjservice[i][j]) {
                        zbbb(i, j);
                    }
                }
                FlushBatchDraw();
            }
        }
        else if (m.message == WM_KEYDOWN) {
            if (m.vkcode == VK_ESCAPE) {
                a2 = 1;
                break;
            }
        }
    }
}

//ok!
void tuj_jn() {
    cleardevice();
    BeginBatchDraw();
    IMAGE img_beijing1;
    loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
    putimage(0, 0, &img_beijing1);
    creatbutton(0, 0, 100, 50, "返回");
    creatbutton(350, 700, 400, 720, "<");
    creatbutton(400, 700, 450, 720, ">");
    for (int i = 0;i < 9;i++) {
        int j = 1;
        if (tjservice[i][j]) {
            jnnn(i, j);
        }
    }
    FlushBatchDraw();
    while (1) {
       ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >= 0 && m.y >= 0 && m.x <= 100 && m.y <= 50) {
            //点左上角的返回
            a2 = a1;
            break;
        }
            else if (m.x > 400 && m.y > 700 && m.x < 450 && m.y < 720) {
                cleardevice();
                IMAGE img_beijing1;
                loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
                putimage(0, 0, &img_beijing1);
                for (int i = 9;i < 18;i++) {
                    int j = 1;
                    if (tjservice[i][j]) {
                        jnnn(i, j);
                    }
                }
               
            }
            else if(m.x > 350 && m.y > 700 && m.x < 400 && m.y < 720){
                cleardevice();
                IMAGE img_beijing1;
                loadimage(&img_beijing1, "tupian/beijing1.jpg", 1400, 800);
                putimage(0, 0, &img_beijing1);
                for (int i = 0;i < 9;i++) {
                    int j = 1;
                    if (tjservice[i][j]) {
                        jnnn(i, j);
                    }
                }
              
            }
        }
        else if (m.message == WM_KEYDOWN) {
            if (m.vkcode == VK_ESCAPE) {
                cleardevice();
                a2 = 1;
                break;
            }
           }
    }
    }//ok!
int b=0;
void dqjn(ExMessage m) // 技能展示
{
    // BeginBatchDraw();
    for (int i = 0; i < 3; i++) {
        yuanbutton(1100 + 50 * i, 50, 25, "");
        if (dqjsjn[i] != 0) {
            // 将技能编号转换为字符串
            char skillNumber[10];
            sprintf(skillNumber, "%d", dqjsjn[i]);
            // 在圈的中心位置显示技能编号
            settextstyle(20, 0, "华文琥珀");
            settextcolor(RGB(30, 30, 30));
            setbkmode(TRANSPARENT);
            int textWidth = textwidth(skillNumber);
            int textHeight = textheight(skillNumber);
            outtextxy(1100 + 50 * i - textWidth / 2, 50 - textHeight / 2, skillNumber);
        }
    }
    if (m.message == WM_LBUTTONDOWN) {
        for (int i = 0; i < 3; i++) {
            if (m.x > 1075 + 50 * i && m.x < 1125 + 50 * i && m.y > 25 && m.y < 75) {
                int z = i + 1;
                if (b != i) {
                    int k = dqjsjn[b];
                    dqjsjn[b] = dqjsjn[i];
                    dqjsjn[i] = k;
                }
                else b = i;
                switch (dqjsjn[z - 1]) { // 注意这里索引要减1
                case 1:
                {
                    IMAGE img_jn1;
                    loadimage(&img_jn1, "tupian/jn1.jpg", 300, 150);
                    putimage(1100, 100, &img_jn1);
                    break;
                }
                case 2:
                {
                    IMAGE img_jn2;
                    loadimage(&img_jn2, "tupian/jn2.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn2);                   // 位置改为 (1100, 100)
                    break;
                }
                case 3:
                {
                    IMAGE img_jn3;
                    loadimage(&img_jn3, "tupian/jn3.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn3);                   // 位置改为 (1100, 100)
                    break;
                }
                case 4:
                {
                    IMAGE img_jn4;
                    loadimage(&img_jn4, "tupian/jn4.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn4);                   // 位置改为 (1100, 100)
                    break;
                }
                case 5:
                {
                    IMAGE img_jn5;
                    loadimage(&img_jn5, "tupian/jn5.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn5);                   // 位置改为 (1100, 100)
                    break;
                }
                case 6:
                {
                    IMAGE img_jn6;
                    loadimage(&img_jn6, "tupian/jn6.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn6);                   // 位置改为 (1100, 100)
                    break;
                }
                case 7:
                {
                    IMAGE img_jn7;
                    loadimage(&img_jn7, "tupian/jn7.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn7);                   // 位置改为 (1100, 100)
                    break;
                }
                case 8:
                {
                    IMAGE img_jn8;
                    loadimage(&img_jn8, "tupian/jn8.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn8);                   // 位置改为 (1100, 100)
                    break;
                }
                case 9:
                {
                    IMAGE img_jn9;
                    loadimage(&img_jn9, "tupian/jn9.jpg", 300, 150); // 尺寸改为 300x150
                    putimage(1100, 100, &img_jn9);                   // 位置改为 (1100, 100)
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
    // EndBatchDraw();
}
void dqzb(ExMessage m) {
    //BeginBatchDraw();
    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 2;j++) {
             yuanbutton(1100 + 50 * i, 270 + 50 * j, 25, "");
        }
    }
 if (m.message == WM_LBUTTONDOWN) {
            for (int i = 0;i < 3;i++) {
                if (m.x > 1075 && m.x < 1125 && m.y>25 && m.y < 50) {
                    int z ;
                    z = i + 1;
                    switch (dqjszb[z]) {
                    case 1:
                    {
                        IMAGE img_zb1;
                        loadimage(&img_zb1, "tupian/zb1.jpg", 300, 150);
                        putimage(1100, 400, &img_zb1); // 基准尺寸 (300x150)，基准坐标 (1100, 400)
                        break;
                    }
                    case 2:
                    {
                        IMAGE img_zb2;
                        loadimage(&img_zb2, "tupian/zb2.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb2);                   // 坐标从 (600,100) → (1100,400)
                        break;
                    }
                    case 3:
                    {
                        IMAGE img_zb3;
                        loadimage(&img_zb3, "tupian/zb3.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb3);                   // 坐标从 (1000,100) → (1100,400)
                        break;
                    }
                    case 4:
                    {
                        IMAGE img_zb4;
                        loadimage(&img_zb4, "tupian/zb4.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb4);                   // 坐标从 (200,300) → (1100,400)
                        break;
                    }
                    case 5:
                    {
                        IMAGE img_zb5;
                        loadimage(&img_zb5, "tupian/zb5.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb5);                   // 坐标从 (600,300) → (1100,400)
                        break;
                    }
                    case 6:
                    {
                        IMAGE img_zb6;
                        loadimage(&img_zb6, "tupian/zb6.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb6);                   // 坐标从 (1000,300) → (1100,400)
                        break;
                    }
                    case 7:
                    {
                        IMAGE img_zb7;
                        loadimage(&img_zb7, "tupian/zb7.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb7);                   // 坐标从 (200,500) → (1100,400)
                        break;
                    }
                    case 8:
                    {
                        IMAGE img_zb8;
                        loadimage(&img_zb8, "tupian/zb8.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb8);                   // 坐标从 (400,500) → (1100,400)
                        break;
                    }
                    case 9:
                    {
                        IMAGE img_zb9;
                        loadimage(&img_zb9, "tupian/zb9.jpg", 300, 150); // 尺寸从 200x100 → 300x150
                        putimage(1100, 400, &img_zb9);                   // 坐标从 (1000,500) → (1100,400)
                        break;
                    }
                    default:break;
                    }
                    zhuangb akk;
                    akk = zhuangbei(z);
                    string b = "";
                    for (int x = 0;x < 7;x++) {
                        b += to_string(akk.sx[x]) + "/";
                    }
                    creatbutton(1100, 600, 1400, 700, b.c_str());
                    }
                 }
        }
   
    // EndBatchDraw();
}
void dqsx() {
    // 定义属性名称数组
    const char* attribute_names[] = {
        "血量", "血量上限", "攻击力", "防御力", "暴击率", "暴击伤害", "闪避率"
    };

    // 设置字体大小、加粗
    settextstyle(20, 0, "宋体"); // 700 表示加粗

    // 设置字体颜色为亮黄色，在深色背景下更醒目
    settextcolor(YELLOW);

    for (int x = 0; x < 7; x++) {
        char attr_str[50];
        sprintf(attr_str, "%s: %d", attribute_names[x], dqjssx[x]);
        // 计算文本输出的位置
        int x_pos = 0 + x % 2 * 125;
        int y_pos = 50 + x / 2 * 20;  // 调整行间距为 20
        outtextxy(x_pos, y_pos, attr_str);
    }
}
void renwu() {
    BeginBatchDraw();
    IMAGE img_renwu;
    loadimage(&img_renwu, "tupian/renwu.jpg", 61, 61);
    putimage(251+rw[0]*61, 1+rw[1]*61, &img_renwu);
    FlushBatchDraw();
}
void door()
{
    bool a = 0;
    for (int i = 0;i < 13;i++)
        for (int j = 0;j < 13;j++) {
            if (map[i][j] == 6 ) {
                a = 1;
                break;
            }
     }
    if (a==0) {
        flag++;
        init();
        game();
        win();
    }
}
void mapdayin() {
     for (int i = 0;i < 13;i++) {
        for (int j = 0;j < 13;j++) {
            creatbutton(251 + i * 61, 1 + 61 * j, 312 + i * 61, 62 + 61 * i, "");
        }
    }
}
void init() {
    //规定门的位置为（7，12），
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            map[i][j] = 0;
        }
    }//地图初始化
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            guai1[i][j] = 0;//guai1初始化
        }
    }

    //约定flag % 4==0时是新手村，（7，13）是初始门 （7，1）是结束门，（2，10）是酒馆 （9，10）是冒险协会，（2，5）是技能导师，（9，5）是铁匠铺
    if (flag % 4 == 0) {
        map[7][0] = 1;//结束门
        map[8][0] = 1;
        map[9][9] = 5;//酒馆
        map[10][9] = 5;
        map[3][9] = 3;//冒险协会
        map[4][9] = 3;
        map[3][3] = 2;//技能导师
        map[4][3] = 2;
        map[9][3] = 4;//铁匠铺
        map[10][3] = 4;
    }
    //约定flag%4为 1 2 3 的时候是森林，（7，13）是初始门 （7，1）是结束门，然后小怪、事件、陷阱、篝火、boss会有些变化
    else if (flag % 4 == 1) {
        map[7][0] = 1; // 结束门
        map[1][2] = 6; // boss
        map[5][3] = 7; // 小怪
        map[1][6] = 8; // 篝火
        map[4][5] = 9; // 陷阱
        map[1][9] = 10; // 事件
        guai1[1][2] = 2; // boss
        guai1[5][3] = 1; // 小怪
        
    }
    else if (flag % 4 == 2) {

        map[7][0] = 1;//结束门
        map[4][2] = 6;//boss
        map[6][2] = 7;//小怪
        map[2][6] = 8;//篝火
        map[4][6] = 9;//陷阱
        map[8][9] = 10;//事件
        guai1[4][2] = 1;//boss
        guai1[6][2] = 1;//小怪
    }
    else if (flag % 4 == 3) {

        map[7][0] = 1;//结束门
        map[6][6] = 6;//boss
        map[2][3] = 7;//小怪
        map[1][7] = 8;//篝火
        map[2][5] = 9;//陷阱
        map[3][9] = 10;//事件
        guai1[6][6] = 1;//boss
        guai1[2][3] = 1;//小怪
    }
    rw[0] = 7; rw[1] = 12;//角色位置初始化

}

void moves(int x,int y) {
    if (y< 13&&x<13&&x>=0&&y>=0) {//若为合法坐标
        switch (map[x][y])//（根据移动后的位置调用函数）
        {
        case 0://空位置，可以给角色移动
           rw[0]=x; 
           rw[1]=y;
            break;
        case 1://人的位置和门的位置重合
            door();//调用门函数
            break;
        case 2: //人的位置和map[][]=2技能导师重合
            jinengdaoshi();//调用技能导师函数
            break;
        case 3://人的位置和map[][]=3冒险协会重合
            guide(); //调用冒险协会函数
            break;
        case 4: //人的位置和map[][]=4铁匠铺
            tiejiangpu();//调用铁匠铺函数
            break;
        case 5://人的位置和map[][]=5酒馆
            jiuguan();//调用酒馆函数
            break;
        case 6://人的位置和map[][]=6boss
            fight(x,y);
            if (guai2[x][y].sx[0] == 0) {
                guai1[x][y] = 0;
                map[x][y] = 0;
                cailiao += 3;
            }
            guaiwuv();//调用boss函数
            guaiwuxinxi(x,y);
            break;
        case 7://人的位置和map[][]=7小怪
            fight(x,y);
            if (guai2[x][y].sx[0] == 0) {
                guai1[x][y] = 0;
                map[x][y] = 0;
                cailiao++;
            }
            guaiwuv();//调用小怪函数
            guaiwuxinxi(x,y);
            break;
        case 8: //人的位置和map[][]=8篝火
            gouhuo();//调用篝火函数
            map[x][y] = 0;
            break;
        case 9: //人的位置和map[][]=9陷阱
            xianjin();//调用陷阱函数
            map[x][y] = 0;
            break;
        case 10: //人的位置和map[][]=10事件
            event();//调用事件函数
            map[x][y] = 0;
            break;
        }
    }
}
void move(int i) {
    switch (i) {
    case 1: moves(rw[0], (rw[1]-1));
            break;
    case 2:moves((rw[0]-1), rw[1]);
        break;
    case 3:moves(rw[0], (rw[1] + 1));
        break;
    case 4:moves((rw[0] + 1), rw[1]);
        break;
    }
   }
void win() {
    if (flag == 20 ); {
        //胜利画面，返回主菜单;
        cleardevice();
        settextstyle(30, 0, "华文琥珀");
        settextcolor(RGB(30, 30, 30));
        setbkmode(TRANSPARENT);
        outtextxy(400, 200, "恭喜你，现在你是迷雾森林的老大了");
        Sleep(2000);
        //补一个让flag/dqjssx/dqjsjn/dqjszb，全部归零的函数
        exit(0);
    }
}//ok！
void wrong() {
    if (dqjssx[0] == 0) {
        //失败画面,返回主菜单;
        cleardevice();
        settextstyle(30, 0, "华文琥珀");
        settextcolor(RGB(30, 30, 30));
        setbkmode(TRANSPARENT);
        outtextxy(400, 200, "创业未半而中道崩殂");
        Sleep(2000);
        exit(0);
    }
    //补一个让flag/dqjssx/dqjsjn/dqjszb，全部归零的函数
}//ok！


void tiejiangpu() {
    // 随机生成装备编号
    int it_zb = rand() % 8 + 1;
   
    // 装备编号范围：1 - 8
    zhuangb zb = zhuangbei(it_zb);
    bool moneyNotEnough = false; // 标记钱是否不够

    while (1) {
        BeginBatchDraw();
        cleardevice();
        IMAGE img_tiejiangpus;
        loadimage(&img_tiejiangpus, "tupian/tiejiangpus.png", 1400, 800);
        putimage(0, 0, &img_tiejiangpus);
       // creatbutton(300, 50, 350, 50, "返回");
        ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        dqjn(m);
        dqzb(m);
        dqsx();
        zhuangb akk;
        akk = zhuangbei(it_zb);
        string b = "";
        for (int x = 0; x < 7; x++) {
            b += to_string(akk.sx[x]) + "/";
        }
        creatbutton(300, 400, 1050, 500, b.c_str());
        switch (it_zb) {
        case 1:
        {
            IMAGE img_zb1;
            loadimage(&img_zb1, "tupian/zb1.jpg", 800, 400);
            putimage(250, 0, &img_zb1);
            break;
        }
        case 2:
        {
            IMAGE img_zb2;
            loadimage(&img_zb2, "tupian/zb2.jpg", 800, 400);
            putimage(250, 50, &img_zb2);
            break;
        }
        case 3:
        {
            IMAGE img_zb3;
            loadimage(&img_zb3, "tupian/zb3.jpg", 800, 400);
            putimage(250, 50, &img_zb3);
            break;
        }
        case 4:
        {
            IMAGE img_zb4;
            loadimage(&img_zb4, "tupian/zb4.jpg", 800, 400);
            putimage(250, 50, &img_zb4);
            break;
        }
        case 5:
        {
            IMAGE img_zb5;
            loadimage(&img_zb5, "tupian/zb5.jpg", 800, 400);
            putimage(250, 50, &img_zb5);
            break;
        }
        case 6:
        {
            IMAGE img_zb6;
            loadimage(&img_zb6, "tupian/zb6.jpg", 800, 400);
            putimage(250, 50, &img_zb6);
            break;
        }
        case 7:
        {
            IMAGE img_zb7;
            loadimage(&img_zb7, "tupian/zb7.jpg", 800, 400);
            putimage(250, 50, &img_zb7);
            break;
        }
        case 8:
        {
            IMAGE img_zb8;
            loadimage(&img_zb8, "tupian/zb8.jpg", 800, 400);
            putimage(250, 50, &img_zb8);
            break;
        }
        case 9:
        {
            IMAGE img_zb9;
            loadimage(&img_zb9, "tupian/zb9.jpg", 800, 400);
            putimage(250, 50, &img_zb9);
            break;
        }
        }
        char price_str[20];
        sprintf(price_str, "价格: %d", zb.price);
        creatbutton(250, 600, 600, 700, price_str); // 调整按钮位置

        // 提供购买功能
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >= 250 && m.x <= 600 && m.y >= 600 && m.y <= 700) {
                if (qian >= zb.price) {
                    qian -= zb.price;
                    bool manlema = true;
                    for (int i = 0; i < 6; i++) {
                        if (dqjszb[i] == 0) {
                            dqjszb[i] = it_zb;
                            // 购买装备，更新人物属性
                            for (int j = 0; j < 7; j++) {
                                dqjssx[j] += zb.sx[j];
                            }
                            manlema = false;
                            break;
                        }
                    }
                    if (manlema) {
                        // 询问替换哪个
                        cleardevice();
                        outtextxy(100, 100, "装备栏已满，请选择要替换的装备:");
                        for (int i = 0; i < 6; i++) {
                            if (dqjszb[i] != 0) {
                                zhuangb old_zb = zhuangbei(dqjszb[i]);
                                char str[100];
                                sprintf(str, "装备 %d: %s", i + 1, old_zb.s.c_str());
                                outtextxy(100, 150 + i * 30, str);
                            }
                        }
                        while (1) {
                            if (peekmessage(&m, EX_MOUSE | EX_KEY)) {
                                if (m.message == WM_KEYDOWN) {
                                    if (m.vkcode >= '1' && m.vkcode <= '6') {
                                        int index = m.vkcode - '1';
                                        zhuangb old_zb = zhuangbei(dqjszb[index]);
                                        // 减去被替换装备的属性
                                        for (int j = 0; j < 7; j++) {
                                            dqjssx[j] -= old_zb.sx[j];
                                        }
                                        dqjszb[index] = it_zb;
                                        // 加上新装备的属性
                                        for (int j = 0; j < 7; j++) {
                                            dqjssx[j] += zb.sx[j];
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    outtextxy(300, 350, "钱不够，无法购买");
                }
            }
        }
        if (m.message == WM_KEYDOWN && m.vkcode == VK_ESCAPE) {
            a2 = 1;
            break;
        }
        if (m.message == WM_LBUTTONDOWN && m.x >= 300 && m.x <= 350 && m.y >= 0 && m.y <= 50) {
            a2 = a1;
            break;
        }
        FlushBatchDraw();
       
    }
}


void jinengdaoshi() {
    // 随机生成技能编号
    int it_jn = rand() % 2 + 1; // 技能编号范围：1 - 2
    Skill currentSkill = skill(it_jn);
    bool moneyNotEnough = false; // 标记钱是否不够
    while (1) {
        BeginBatchDraw();
        cleardevice();
        // 绘制图片
        IMAGE img_jinengdaoshis;
        loadimage(&img_jinengdaoshis, "tupian/jinengdaoshis.jpg", 1400, 800);
        putimage(0, 0, &img_jinengdaoshis);
        creatbutton(0, 50, 50, 100, "返回");
        ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        dqjn(m);
        dqzb(m);
        dqsx();
        switch (it_jn) {
        case 1:
        {
            IMAGE img_jn1;
            loadimage(&img_jn1, "tupian/jn1.jpg", 800, 400);
            putimage(250, 0, &img_jn1);
            break;
        }
        case 2:
        {
            IMAGE img_jn2;
            loadimage(&img_jn2, "tupian/jn2.jpg", 800, 400);
            putimage(250, 0, &img_jn2);
            break;
        }
        // 可以添加更多技能图片加载...
        }
        char price_str[20];
        sprintf(price_str, "价格: %d", currentSkill.price);
        creatbutton(250, 600, 600, 650, price_str);

        // 如果钱不够，显示提示信息
        if (moneyNotEnough) {
            settextstyle(30, 0, "宋体");
            settextcolor(RGB(30, 30, 30));
            setbkmode(TRANSPARENT);
            outtextxy(300, 350, "钱不够，无法购买技能");
        }

        // 提供交互选项
        if (m.message == WM_LBUTTONDOWN) {
            if (m.x >= 250 && m.x <= 600 && m.y >= 600 && m.y <= 650) {
                if (qian >= currentSkill.price) {
                    qian -= currentSkill.price;
                    bool manlema = true;
                    for (int i = 0; i < 3; i++) { // 技能栏长度为3
                        if (dqjsjn[i] == 0) {
                            dqjsjn[i] = it_jn;
                            // 购买技能，更新人物属性
                            for (int j = 0; j < 7; j++) {
                                dqjssx[j] += currentSkill.sx[j];
                            }
                            manlema = false;
                            break;
                        }
                    }
                    if (manlema) {
                        // 询问替换的技能
                        cleardevice();
                        outtextxy(400, 350, "技能栏已满，请选择要替换的技能:");
                        for (int i = 0; i < 3; i++) {
                            if (dqjsjn[i] != 0) {
                                Skill old_skill = skill(dqjsjn[i]);
                                char str[100];
                                sprintf(str, "技能 %d: %s", i + 1, old_skill.name.c_str());
                                outtextxy(100, 150 + i * 30, str);
                            }
                        }
                        while (1) {
                            if (peekmessage(&m, EX_MOUSE | EX_KEY)) {
                                if (m.message == WM_KEYDOWN) {
                                    if (m.vkcode >= '1' && m.vkcode <= '3') {
                                        int index = m.vkcode - '1';
                                        Skill old_skill = skill(dqjsjn[index]);
                                        // 减去被替换技能的属性
                                        for (int j = 0; j < 7; j++) {
                                            dqjssx[j] -= old_skill.sx[j];
                                        }
                                        dqjsjn[index] = it_jn;
                                        // 加上新技能的属性
                                        for (int j = 0; j < 7; j++) {
                                            dqjssx[j] += currentSkill.sx[j];
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    moneyNotEnough = false; // 购买成功，清除提示
                }
                else {
                    moneyNotEnough = true; // 钱不够，标记需要显示提示
                }
            }
        }
        if (m.message == WM_KEYDOWN && m.vkcode == VK_ESCAPE) {
            a2 = 1;
            break;
        }
        if (m.message == WM_LBUTTONDOWN && m.x >= 0 && m.x <= 50 && m.y >= 0 && m.y <= 50) {
            a2 = a1;
            break;
        }
        FlushBatchDraw();
    }
}

void jiuguan() {
    dqjssx[0] = dqjssx[1];
    BeginBatchDraw();
    cleardevice();
    IMAGE img_jiuguans;
    loadimage(&img_jiuguans, "tupian/jiuguans.jpg", 800, 800);
    putimage(300, 0, &img_jiuguans);
    FlushBatchDraw();
    Sleep(5000);
 }//ok!
void guide() {
    qian += cailiao;
    cailiao = 0;
}//ok!
void cun() {
BeginBatchDraw();
    init(); // 假设 init 函数用于初始化一些必要的数据
    
    IMAGE img_beijing2;
    loadimage(&img_beijing2, "tupian/beijing2.jpg", 1400, 800);
    putimage(0, 0, &img_beijing2);
    mapdayin();

    IMAGE img_maoxianxiehui;
    loadimage(&img_maoxianxiehui, "tupian/maoxianxiehui.jpg", 122, 61);
    putimage(251 + 61 * 3, 1 + 9 * 61, &img_maoxianxiehui);

    IMAGE img_jinengdaoshi;
    loadimage(&img_jinengdaoshi, "tupian/jinengdaoshi.jpg", 122, 61);
    putimage(251 + 61 * 3, 1 + 3 * 61, &img_jinengdaoshi);

    IMAGE img_tiejiangpu;
    loadimage(&img_tiejiangpu, "tupian/tiejiangpu.jpg", 122, 61);
    putimage(251 + 61 * 9, 1 + 3 * 61, &img_tiejiangpu);

    IMAGE img_jiuguan;
    loadimage(&img_jiuguan, "tupian/jiuguan.jpg", 122, 61);
    putimage(251 + 61 * 9, 1 + 9 * 61, &img_jiuguan);

    //EndBatchDraw();

    while (1) {
        
        IMAGE img_men;
        loadimage(&img_men, "tupian/men.jpg", 122, 61);
        putimage(251 + 61 * 7, 1, &img_men);

        int oldX = rw[0];
        int oldY = rw[1];
        renwu();

        string b;
        b = "当前金钱：" + to_string(qian);
        creatbutton(1050, 600, 1300, 700, b.c_str());
        string c;
        c = "当前材料：" + to_string(cailiao);
        creatbutton(1050, 700, 1300, 800, c.c_str());

        ExMessage m = { 0 };
        peekmessage(&m, EX_MOUSE | EX_KEY);
        dqjn(m);
        dqzb(m);
        dqsx();

        // 处理人物移动事件
        if (m.message == WM_KEYDOWN) {
            if (m.vkcode == VK_ESCAPE) {
                a2 = 1;
                break;
            }
            else if (m.vkcode == 'W') {
                move(1);
            }
            else if (m.vkcode == 'A') {
                move(2);
            }
            else if (m.vkcode == 'S') {
                move(3);
            }
            else if (m.vkcode == 'D') {
                move(4);
            }
            putimage(0, 0, &img_beijing2);

            // 重新绘制地图元素
            mapdayin();
            putimage(251 + 61 * 3, 1 + 9 * 61, &img_maoxianxiehui);
            putimage(251 + 61 * 3, 1 + 3 * 61, &img_jinengdaoshi);
            putimage(251 + 61 * 9, 1 + 3 * 61, &img_tiejiangpu);
            putimage(251 + 61 * 9, 1 + 9 * 61, &img_jiuguan);
            putimage(251 + 61 * 7, 1, &img_men);

            b = "当前金钱：" + to_string(qian);
            creatbutton(1050, 600, 1300, 700, b.c_str());

            c = "当前材料：" + to_string(cailiao);
            creatbutton(1050, 700, 1300, 800, c.c_str());


            dqjn(m);
            dqzb(m);
            dqsx();
            // 检查人物位置是否改变，如果改变则更新地图
            if (oldX != rw[0] || oldY != rw[1]) {
                // 重新绘制背景图
                putimage(0, 0, &img_beijing2);

                // 重新绘制地图元素
                mapdayin();
                putimage(251 + 61 * 3, 1 + 9 * 61, &img_maoxianxiehui);
                putimage(251 + 61 * 3, 1 + 3 * 61, &img_jinengdaoshi);
                putimage(251 + 61 * 9, 1 + 3 * 61, &img_tiejiangpu);
                putimage(251 + 61 * 9, 1 + 9 * 61, &img_jiuguan);
                putimage(251 + 61 * 7, 1, &img_men);
                
                b = "当前金钱：" + to_string(qian);
                creatbutton(1050, 600, 1300, 700, b.c_str());
                
                c = "当前材料：" + to_string(cailiao);
                creatbutton(1050, 700, 1300, 800, c.c_str());

               
                dqjn(m);
                dqzb(m);
                dqsx();
            }
        }
        
        //FlushBatchDraw();
    }
    EndBatchDraw();
}


void xianjin() {
   
    dqjssx[0] -= 50; // 扣除当前血量为 50
    if (dqjssx[0] < 0) {
        dqjssx[0] = 0; // 确保血量不会为负数
    }
    wrong(); // 检查是否失败
}
void fight(int x, int y) {
    int randomnumber = rand() % 100;
    if (dqjssx[6] <= randomnumber) {
        if (jineng3(dqjsjn[0]) <= randomnumber)
            jineng2(dqjsjn[0], x, y);
        else if (jineng3(dqjsjn[1]) <= randomnumber)
            jineng2(dqjsjn[1], x, y);
        else if (jineng3(dqjsjn[2]) <= randomnumber)
            jineng2(dqjsjn[2], x, y);
        else  jineng2(0, x, y);
    }
    randomnumber = rand() % 100;
    if (guai2[x][y].sx[6] <= randomnumber) {
        if (jineng3(guai2[x][y].jn[0]) <= randomnumber)
            jineng4(guai2[x][y].jn[0], x, y); // 未闪避，技能函数，结算人物和怪物血条属性，人物血条 dqjssx[1]
        else if (jineng3(guai2[x][y].jn[0]) <= randomnumber)
            jineng4(guai2[x][y].jn[0], x, y);
        else if (jineng3(guai2[x][y].jn[0]) <= randomnumber)
            jineng4(guai2[x][y].jn[0], x, y);
        else  jineng4(0, x, y);
    }
    wrong();
}
void event() {
    cleardevice();
    //随机数，调用事件库里的shijian1函数并接收
    int it_event = rand() % 2 +1;//假设一共有?个事件（待定）
   //图片
     switch (it_event) {  // 假设变量名也需要修改（如果原变量名是it_zb）
     case 1:
     {
         IMAGE img_sj1;
         loadimage(&img_sj1, "tupian/sj1.jpg", 1400, 800);
         putimage(0, 0, &img_sj1);
         break;
     }
     case 2:
     {
         IMAGE img_sj2;
         loadimage(&img_sj2, "tupian/sj2.jpg", 1400, 800);
         putimage(0, 0, &img_sj2);
         break;
     }
     case 3:
     {
         IMAGE img_sj3;
         loadimage(&img_sj3, "tupian/sj3.jpg", 1400, 800);
         putimage(0, 0, &img_sj3);
         break;
     }
     case 4:
     {
         IMAGE img_sj4;
         loadimage(&img_sj4, "tupian/sj4.jpg", 1400, 800);
         putimage(0, 0, &img_sj4);
         break;
     }
     case 5:
     {
         IMAGE img_sj5;
         loadimage(&img_sj5, "tupian/sj5.jpg", 1400, 800);
         putimage(0, 0, &img_sj5);
         break;
     }
     case 6:
     {
         IMAGE img_sj6;
         loadimage(&img_sj6, "tupian/sj6.jpg", 1400, 800);
         putimage(0, 0, &img_sj6);
         break;
     }
     case 7:
     {
         IMAGE img_sj7;
         loadimage(&img_sj7, "tupian/sj7.jpg", 1400, 800);
         putimage(0, 0, &img_sj7);
         break;
     }
     case 8:
     {
         IMAGE img_sj8;
         loadimage(&img_sj8, "tupian/sj8.jpg", 1400, 800);
         putimage(0, 0, &img_sj8);
         break;
     }
     case 9:
     {
         IMAGE img_sj9;
         loadimage(&img_sj9, "tupian/sj9.jpg", 1400, 800);
         putimage(0, 0, &img_sj9);
         break;
     }
            }
     while (1) {
        cleardevice();
        //捕捉鼠标动作
        ExMessage m;
        peekmessage(&m, EX_MOUSE | EX_KEY);
        if (m.message== WM_LBUTTONDOWN) {
            if (m.y>=600&&m.y<=800) {
                cleardevice();
                BeginBatchDraw();
                switch (it_event) {
                case 1:
                {
                    IMAGE img_sj1_1;
                    loadimage(&img_sj1_1, "tupian/sj1_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj1_1);
                    break;
                }
                case 2:
                {
                    IMAGE img_sj2_1;
                    loadimage(&img_sj2_1, "tupian/sj2_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj2_1);
                    break;
                }
                case 3:
                {
                    IMAGE img_sj3_1;
                    loadimage(&img_sj3_1, "tupian/sj3_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj3_1);
                    break;
                }
                case 4:
                {
                    IMAGE img_sj4_1;
                    loadimage(&img_sj4_1, "tupian/sj4_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj4_1);
                    break;
                }
                case 5:
                {
                    IMAGE img_sj5_1;
                    loadimage(&img_sj5_1, "tupian/sj5_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj5_1);
                    break;
                }
                case 6:
                {
                    IMAGE img_sj6_1;
                    loadimage(&img_sj6_1, "tupian/sj6_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj6_1);
                    break;
                }
                case 7:
                {
                    IMAGE img_sj7_1;
                    loadimage(&img_sj7_1, "tupian/sj7_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj7_1);
                    break;
                }
                case 8:
                {
                    IMAGE img_sj8_1;
                    loadimage(&img_sj8_1, "tupian/sj8_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj8_1);
                    break;
                }
                case 9:
                {
                    IMAGE img_sj9_1;
                    loadimage(&img_sj9_1, "tupian/sj9_1.jpg", 1400, 800);
                    putimage(0, 0, &img_sj9_1);
                    break;
                }
                }
                FlushBatchDraw();
                Sleep(5000);
                a2 = a1;
                break;
           }
            else if (m.y>800) {
                cleardevice();
                BeginBatchDraw();
                switch (it_event) {
                case 1:
                {
                    IMAGE img_sj1_2;
                    loadimage(&img_sj1_2, "tupian/sj1_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj1_2);
                    break;
                }
                case 2:
                {
                    IMAGE img_sj2_2;
                    loadimage(&img_sj2_2, "tupian/sj2_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj2_2);
                    break;
                }
                case 3:
                {
                    IMAGE img_sj3_2;
                    loadimage(&img_sj3_2, "tupian/sj3_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj3_2);
                    break;
                }
                case 4:
                {
                    IMAGE img_sj4_2;
                    loadimage(&img_sj4_2, "tupian/sj4_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj4_2);
                    break;
                }
                case 5:
                {
                    IMAGE img_sj5_2;
                    loadimage(&img_sj5_2, "tupian/sj5_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj5_2);
                    break;
                }
                case 6:
                {
                    IMAGE img_sj6_2;
                    loadimage(&img_sj6_2, "tupian/sj6_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj6_2);
                    break;
                }
                case 7:
                {
                    IMAGE img_sj7_2;
                    loadimage(&img_sj7_2, "tupian/sj7_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj7_2);
                    break;
                }
                case 8:
                {
                    IMAGE img_sj8_2;
                    loadimage(&img_sj8_2, "tupian/sj8_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj8_2);
                    break;
                }
                case 9:
                {
                    IMAGE img_sj9_2;
                    loadimage(&img_sj9_2, "tupian/sj9_2.jpg", 1400, 800);
                    putimage(0, 0, &img_sj9_2);
                    break;
                }
                }
                FlushBatchDraw();
                Sleep(5000);
                a2 = a1;
                break;
            }
            }
    }
}//事件前台
void cungaui() {
    for (int i = 0;i < 13;i++)
        for (int j = 0;j < 13;j++) {
            if (guai1[i][j]) {
                guai2[i][j] = guaiwu(guai1[i][j]);
            }
        }
}//ok!
IMAGE img_guaiwu[6];
void loadGuaiwuImages() {
    for (int i = 0; i < 6; i++) {
        char filename[50];
        sprintf(filename, "tupian/guaiwu%d.jpg", i + 1);
        loadimage(&img_guaiwu[i], filename, 61, 61);
    }
}
void guaiwuv() {
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++) {
            switch (guai1[i][j]) {
            case 1:
            {
                IMAGE img_guaiwu1;
                loadimage(&img_guaiwu1, "tupian/guaiwu1.jpg", 61, 61);  
                putimage(251 + 61 * i, 1 + 61 * j, &img_guaiwu1);
                break;
            }
            case 2:
            {
                IMAGE img_guaiwu2;  
                loadimage(&img_guaiwu2, "tupian/guaiwu2.jpg", 61, 61);
                putimage(251 + 61 * i, 1 + 61 * j, &img_guaiwu2);
                break;
            }
            case 3:
            {
                IMAGE img_guaiwu3;
                loadimage(&img_guaiwu3, "tupian/guaiwu3.jpg", 61, 61);
                putimage(251 + 61 * i, 1 + 61 * j, &img_guaiwu3);
                break;
            }
            case 4:
            {
                IMAGE img_guaiwu4;
                loadimage(&img_guaiwu4, "tupian/guaiwu4.jpg", 61, 61);
                putimage(251 + 61 * i, 1 + 61 * j, &img_guaiwu4);
                break;
            }
            case 5:
            {
                IMAGE img_guaiwu5;
                loadimage(&img_guaiwu5, "tupian/guaiwu5.jpg", 61, 61);
                putimage(251 + 61 * i, 1 + 61 * j, &img_guaiwu5);
                break;
            }
            case 6:
            {
                IMAGE img_guaiwu6;
                loadimage(&img_guaiwu6, "tupian/guaiwu6.jpg", 61, 61);
                putimage(251 + 61 * i, 1 + 61 * j, &img_guaiwu6);
                break;
            }
            default:continue;
            }

        }
}
void guaiwuxinxi(int x, int y) {
    if (guai1[x][y]) {
        
        creatbutton(0, 400,250 ,450,guai2[x][y].ming.c_str());
        string a;
        for (int i = 0;i < 7;i++) {
            a = to_string(guai2[x][y].sx[i]);
            a += "/";
           }
        settextstyle(10, 0, "宋体");
        settextcolor(RGB(30, 30, 30));
        setbkmode(TRANSPARENT);
        rectangle(0, 450, 250, 550);
        int chang = 250, kuan = 100;
        int textWidth = textwidth(a.c_str());
        int textHeight = textheight(a.c_str());
        outtextxy(x + (chang - textWidth) / 2, y + (kuan - textHeight) / 2, a.c_str());
        for (int i = 0;i < 3;i++) {
          yuanbutton(25+50*i,575 , 25, "");
       }
        int cout;
         ExMessage m1;
         peekmessage(&m1, EX_MOUSE );
        if (m1.message == WM_LBUTTONDOWN) {
            for (int i = 0;i < 3;i++)
                if (m1.x > 0 + 50 * i && m1.x < 50 + 50 * i && m1.y>550 && m1.y < 600) { cout = i + 1;
            switch (cout) {  // 假设变量名也需要修改（如果原变量名是it_zb）
            case 1:
            {
                IMAGE img_jn1;
                loadimage(&img_jn1, "tupian/jn1.jpg", 800, 400);
                putimage(250, 0, &img_jn1);
                break;
            }
            case 2:
            {
                IMAGE img_jn2;
                loadimage(&img_jn2, "tupian/jn2.jpg", 800, 400);
                putimage(250, 0, &img_jn2);
                break;
            }
            case 3:
            {
                IMAGE img_jn3;
                loadimage(&img_jn3, "tupian/jn3.jpg", 800, 400);
                putimage(250, 0, &img_jn3);
                break;
            }
            case 4:
            {
                IMAGE img_jn4;
                loadimage(&img_jn4, "tupian/jn4.jpg", 800, 400);
                putimage(250, 0, &img_jn4);
                break;
            }
            case 5:
            {
                IMAGE img_jn5;
                loadimage(&img_jn5, "tupian/jn5.jpg", 800, 400);
                putimage(250, 0, &img_jn5);
                break;
            }
            case 6:
            {
                IMAGE img_jn6;
                loadimage(&img_jn6, "tupian/jn6.jpg", 800, 400);
                putimage(250, 0, &img_jn6);
                break;
            }
            case 7:
            {
                IMAGE img_jn7;
                loadimage(&img_jn7, "tupian/jn7.jpg", 800, 400);
                putimage(250, 0, &img_jn7);
                break;
            }
            case 8:
            {
                IMAGE img_jn8;
                loadimage(&img_jn8, "tupian/jn8.jpg", 800, 400);
                putimage(250, 0, &img_jn8);
                break;
            }
            case 9:
            {
                IMAGE img_jn9;
                loadimage(&img_jn9, "tupian/jn9.jpg", 800, 400);
                putimage(250, 0, &img_jn9);
                break;
            }
            }
            }
        }
        
        }
    //当点击或者与某个怪物交战时，在左下角显示它的信息
}//ok!
void gouhuo() {
    BeginBatchDraw();
    IMAGE img_gouhuos;
    loadimage(&img_gouhuos, "tupian/gouhuos.jpg", 1400, 800);
    putimage(0, 0, &img_gouhuos);
    FlushBatchDraw();
    dqjssx[0] += dqjssx[1] * 1 / 10;
    if (dqjssx[0] > dqjssx[1])dqjssx[0] = dqjssx[1];
    Sleep(5000);
    }//ok!
void sen() {
    // 提前加载背景图片
    IMAGE img_beijing3;
    loadimage(&img_beijing3, "tupian/beijing3.jpg", 1400, 800);
    // 提前加载门图片
    IMAGE img_men;
    loadimage(&img_men, "tupian/men.jpg", 122, 61);
    // 提前加载篝火图片
    IMAGE img_gouhuo;
    loadimage(&img_gouhuo, "tupian/gouhuo.jpg", 61, 61);
    // 提前加载现金图片
    IMAGE img_xianjin;
    loadimage(&img_xianjin, "tupian/xianjin.jpg", 61, 61);
    // 提前加载人物图片
    IMAGE img_renwu;
    loadimage(&img_renwu, "tupian/renwu.jpg", 61, 61);

    while (1) {
        BeginBatchDraw();
        // 绘制背景图片
        putimage(0, 0, &img_beijing3);
        mapdayin();
        // 绘制门图片
        putimage(251 + 61 * 7, 1, &img_men);

        // 绘制篝火和现金图片
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                if (map[i][j] == 8) {
                    putimage(251 + i * 61, 1 + 61 * j, &img_gouhuo);
                }
                else if (map[i][j] == 9) {
                    putimage(251 + i * 61, 1 + 61 * j, &img_xianjin);
                }
            }
        }

        // 绘制人物图片
        putimage(251 + rw[0] * 61, 1 + rw[1] * 61, &img_renwu);

        dqsx();
        ExMessage m = { 0 };
        peekmessage(&m, EX_MOUSE | EX_KEY);
        dqzb(m);
        dqjn(m);
        guaiwuv();

        string b;
        b = "当前银币：" + to_string(qian);
        creatbutton(1050, 600, 1300, 700, b.c_str());
        string c;
        c = "当前材料：" + to_string(cailiao);
        creatbutton(1050, 700, 1300, 800, c.c_str());

        FlushBatchDraw();

        if (m.message == WM_KEYDOWN) {
            if (m.vkcode == VK_ESCAPE) {
                a2 = 1;
                break;
            }
            else if (m.vkcode == 'W') {
                move(1);
            }
            else if (m.vkcode == 'A') {
                move(2);
            }
            else if (m.vkcode == 'S') {
                move(3);
            }
            else if (m.vkcode == 'D') {
                move(4);
            }
        }
        else if (m.message == WM_LBUTTONDOWN) {
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 13; j++) {
                    if (m.x > 301 + 6 * i && m.x < 306 + 6 * i && m.y > 1 + 6 * j && m.y < 7 + 6 * j) {
                        guaiwuxinxi(i, j);
                    }
                }
            }
        }
        // Sleep(500);
    }
}

void game() {
    if (flag % 4) { sen(); }
    else { cun(); }
    g_save();
}//ok!
int main() {
    dutujian();
    initgraph(1400, 800, EX_SHOWCONSOLE);
    
    mciSendString("open MP3/bgm.mp3", NULL, 0, NULL);
    mciSendString("setaudio bgm volume to 300", NULL, 0, NULL);
    mciSendString("play MP3/bgm.mp3 repeat", NULL, 0, NULL);
    mciSendString("open MP3/yinxiao.mp3", NULL, 0, NULL);
    mciSendString("setaudio yinxiao volume to 300", NULL, 0, NULL);
    dqjssx[0] = 100;//血量
    dqjssx[1] = 100;//血量上限
    dqjssx[2] = 25;//攻击力
    dqjssx[3] = 5;//防御力
    dqjssx[4] = 5;//暴击率
    dqjssx[5] = 105;//暴击伤害
    dqjssx[6] = 5;//闪避率
    while (1) {
        switch (a2) {
        case 1:menu(); break;
        case 2:shz(); break;
        case 3:tuj(); break;
        case 4:tuj_zb(); break;
        case 5:tuj_jn(); break;
        case 6:tiejiangpu(); break;
        case 7:jinengdaoshi(); break;
        case 8:jiuguan(); break;
        case 9:gouhuo(); break;
        case 10:event(); break;
        case 11:game(); break;
        default:goto x;
        }
        a1 = a2;
    }
x:
    closegraph();
    xietujian();
    return 0;
}//ok!