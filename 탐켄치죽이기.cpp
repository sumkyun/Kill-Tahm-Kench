#include <Windows.h>
#include<bangtal.h>
#include <iostream>
#include<math.h>

#define T 0.1 //시간, 속도와 관련, 커질수록 느려짐
#define MAXX 960
#define MAXY 400
#define MINX 0
#define MINY 100
#define MAXHUNT 10

using namespace std;

using namespace bangtal;

ScenePtr  scene1;

struct point {
    int x;
    int y;
};

int dr(point a, point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct skill {
    int dam;
    int ct;
    bool stack = false;
    bool isuse;

    void upskill(int b, int c, bool d)
    {
        dam = b;
        ct = c;
        isuse = d;
    }
};

bool iop = true;
int hunt = 0;
int hunt1 = 0;
int yuiop = MAXHUNT;
bool qwe = false;
int hunt2 = 0;
int newscore = -100;
int score = 0;
bool llls = true;

class TK
{
public:
    point p;
    int gaze = 10;
    int wher;
    ObjectPtr c;
    bool islive = false;
    bool isshow = false;

    void inittk()
    {
        p.y = (MAXY - MINY) / (MAXHUNT + 1) * yuiop;
        yuiop--;

        if (iop)
        {
            p.x = MINX;
            c = Object::create("images/오른탐켄치.png", scene1, p.x, p.y);
            wher = 2;
            iop = false;
        }
        else
        {
            p.x = MAXX;
            c = Object::create("images/탐켄치.png", scene1, p.x, p.y);
            wher = 0;
            iop = true;
        }

        c->setScale(0.35f);
        c->hide();
    }
};

class EZ
{
public:
    point p; //현재 위치 정보
    int ad; //공격력
    int gaze; //체력
    int speed;
    int wher;

    void initxy()
    {
        p.x = MAXX / 2 + MINX / 2;
        p.y = MAXY / 2 + MINY / 2;
        ad = 70;
        speed = 10;
        wher = 1;

        return;
    } //초기설정

    void upad(int n)
    {
        ad += n; return;
    }

    void upspeed(int n)
    {
        speed += n; return;
    }
};

TK tk[MAXHUNT];
EZ sebier;

void main() {


    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    scene1 = Scene::create("룸1", "images/배경.jpg");
    ScenePtr  scene2 = Scene::create("룸2", "images/신의권.png");
    auto eq = Sound::create("images/이쿠.mp3");
    auto tong = Sound::create("images/통.mp3");
    auto puck = Sound::create("images/퍽.mp3");
    auto dea = Sound::create("images/죽음.mp3");
    auto you = Sound::create("images/당신.mp3");
    auto start1 = Object::create("images/게임시작.png", scene2, 500, 200);
    auto restart1 = Object::create("images/다시하기.png", scene1, 500, 300);
    auto yourpoint = Object::create("images/점수.png", scene1, 500, 100);
    start1->setScale(0.7f);
    restart1->setScale(0.7f);
    yourpoint->setScale(0.7f);

    for (int i = 0; i < MAXHUNT; i++)
        tk[i].inittk();
    sebier.initxy();


    restart1->hide();
    yourpoint->hide();

    auto timer2345 = Timer::create(4.0f);

    start1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        hunt2 = 0;
        you->play();
        timer2345->start();
        return 0;

        });

    timer2345->setOnTimerCallback([&](TimerPtr t)->bool {


        for (int i = 0; i < 10; i++) //7초 딜레이
        {
            t->set(7.0f);
            t->start();
        }
        scene1->enter();
        return true;
        });

    yourpoint->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        char llps[100];
        if (score > newscore)
        {
            sprintf_s(llps, "%d마리 탐켄치를 사냥하셨습니다. 신기록입니다.", score);
            newscore = hunt;
        }
        else
            sprintf_s(llps, "%d마리 탐켄치를 사냥하셨습니다.", score);

        char* const iiii = &llps[0];
        showMessage(iiii);
        llps[0] = NULL;
        return 0;
        });

    skill Q;
    bool isQ = false;
    bool iswalk = false;
    bool isW = 0;
    bool sde = false;

    tk[0].c->show();
    tk[0].islive = true;

    ObjectPtr lss = Object::create("images/오른리신.png", scene1, MAXX / 2 + MINX / 2, MAXY / 2 + MINY / 2); //리신

    lss->setScale(0.3f);



    //탐켄치 생성, 움직임
    auto timer1 = Timer::create(7.0f);
    timer1->setOnTimerCallback([&](TimerPtr t)->bool {


        if (hunt2 - hunt > 3)
        {

            for (int i = 0; i < MAXHUNT; i++)
            {
                tk[i].c->hide();
                tk[i].islive = false;
            }
            tk[5].c->hide();
            cout << "했음" << endl;
            tk[5].islive = false;
            llls = false;
            lss->hide();

            score = hunt;
            restart1->show();
            yourpoint->show();

            return 0;
        }

        tk[hunt1].isshow = true;//새로운 탐켄치 생성
        tk[hunt1].gaze = 10 + 3 * hunt2;
        tk[hunt1].islive = true;
        tk[hunt1].c->show();

        hunt1++;

        if (hunt1 >= MAXHUNT - 1)
            hunt1 = 0;

        hunt2++; //생성된 숫자

        for (int i = 0; i < 10 + hunt2 * 2; i++) //7초 딜레이
        {
            t->set(7.0f);
            t->start();
        }
        return true;
        });
    if (llls)
        timer1->start();

    auto timer4 = Timer::create(0.1f);
    timer4->setOnTimerCallback([&](TimerPtr t)->bool {

        for (int l = 0; l < MAXHUNT; l++)
        {

            if (tk[l].wher == 2)
            {
                if (tk[l].gaze < 8)
                    tk[l].c->setImage("images/오른탐켄치혀.png");
                else
                    tk[l].c->setImage("images/오른탐켄치.png");
                if (tk[l].p.x + 30 + 4 * l > MAXX)
                {
                    tk[l].wher = 0;


                    tk[l].c->setImage("images/탐켄치.png");
                }
                else
                {
                    tk[l].p.x += 30 + 4 * l;
                }
            }
            else if (tk[l].wher == 0)
            {
                if (tk[l].gaze < 8)
                    tk[l].c->setImage("images/탐켄치혀.png");
                else
                    tk[l].c->setImage("images/탐켄치.png");
                if (tk[l].p.x - 30 - 4 * l < MINX)
                {
                    tk[l].wher = 2;


                    tk[l].c->setImage("images/오른탐켄치.png");
                }
                else
                {
                    tk[l].p.x -= 30 + 4 * l;
                }
            }

            tk[l].c->locate(scene1, tk[l].p.x, tk[l].p.y + 20);
        }

        for (int i = 0; i < 100; i++)
        {
            t->set(0.1f);
            t->start();
        }

        return true;
        });
    if (llls)
        timer4->start();

    restart1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        iop = true;
        llls = true;
        hunt = 0;
        hunt1 = 0;
        qwe = false;
        hunt2 = 0;
        restart1->hide();
        yourpoint->hide();
        sebier.initxy();
        lss->show();
        timer1->start();
        timer4->start();
        return 0;

        });


    //키보드, 리신 움직임
    scene1->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool {

        if (!llls) return 0;

        int c = key;

        switch (c) {

        case 4:
            if (!isQ) {
                isW = 0;
                sebier.p.x += 20;
                if (sebier.p.x > MAXX)
                    sebier.p.x = MAXX;
                sebier.wher = 2;

                lss->locate(scene1, sebier.p.x, sebier.p.y);

                if (iswalk)
                {
                    lss->setImage("images/오른리신1.png");
                    iswalk = false;
                }
                else
                {
                    lss->setImage("images/오른리신.png");
                    iswalk = true;
                }
            }break;
        case 1:
            if (!isQ) {
                isW = 0;
                sebier.p.x -= 20;
                if (sebier.p.x < MINX)
                    sebier.p.x = MINX;
                sebier.wher = 0;

                lss->locate(scene1, sebier.p.x, sebier.p.y);

                if (iswalk)
                {
                    lss->setImage("images/리신1.png");
                    iswalk = false;
                }
                else
                {
                    lss->setImage("images/리신.png");
                    iswalk = true;
                }
            }break;
        case 19:
            if (!isQ) {
                isW = 0;
                sebier.p.y -= 20;
                if (sebier.p.y < MINY)
                    sebier.p.y = MINY;

                lss->locate(scene1, sebier.p.x, sebier.p.y);

                if (iswalk)
                {
                    if (sebier.wher == 2)
                        lss->setImage("images/오른리신1.png");
                    else
                        lss->setImage("images/리신1.png");
                    iswalk = false;
                }
                else
                {
                    if (sebier.wher == 2)
                        lss->setImage("images/오른리신.png");
                    else
                        lss->setImage("images/리신.png");
                    iswalk = true;
                }
            }break;
        case 23:
            if (!isQ) {
                isW = 0;
                sebier.p.y += 20;
                if (sebier.p.y > MAXY)
                    sebier.p.y = MAXY;

                lss->locate(scene1, sebier.p.x, sebier.p.y);

                if (iswalk)
                {
                    if (sebier.wher == 2)
                        lss->setImage("images/오른리신1.png");
                    else
                        lss->setImage("images/리신1.png");
                    iswalk = false;
                }
                else
                {
                    if (sebier.wher == 2)
                        lss->setImage("images/오른리신.png");
                    else
                        lss->setImage("images/리신.png");
                    iswalk = true;
                }
            }break;
        case 10: //펀치
            if (!isQ) { //스킬을 쓰는 중

                if (sebier.wher == 2)
                {
                    if (!isW)
                    {
                        eq->play();

                        lss->setImage("images/오른리신펀치.png");
                        sebier.p.x += 10;
                        lss->locate(scene1, sebier.p.x, sebier.p.y);

                        for (int i = 0; i < MAXHUNT; i++)
                            if (tk[i].p.x - sebier.p.x < 120 && tk[i].p.x >= sebier.p.x && abs(sebier.p.y - tk[i].p.y) < 80 && tk[i].islive == true)
                            {
                                puck->play();
                                tk[i].gaze--;
                            }

                        isW = 1;
                        isQ = false;
                    }
                    else
                    {
                        lss->setImage("images/오른리신.png");
                        isW = 0;
                    }
                }
                else
                {
                    if (!isW)
                    {
                        isQ = true;
                        eq->play();
                        lss->setImage("images/리신펀치.png");

                        for (int i = 0; i < MAXHUNT; i++)
                            if (sebier.p.x - tk[i].p.x <= 310 && sebier.p.x - tk[i].p.x >= 150 && abs(sebier.p.y - tk[i].p.y) < 80 && tk[i].islive == true)
                            {
                                puck->play();
                                tk[i].gaze--;
                            }
                        sebier.p.x -= 10;
                        lss->locate(scene1, sebier.p.x, sebier.p.y);


                        isW = 1;
                        isQ = false;
                    }
                    else
                    {
                        lss->setImage("images/리신.png");
                        isW = 0;
                    }
                }


                for (int i = 0; i < MAXHUNT; i++)
                    if (tk[i].gaze == 0)

                    {
                        dea->play();
                        tk[i].c->hide();
                        tk[i].islive = false;
                        hunt++;
                        tk[i].gaze--;
                    }

            }
            break;
        }

        return 0;
        });


    startGame(scene2);
}