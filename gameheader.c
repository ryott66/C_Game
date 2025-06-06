﻿#include "gameheader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <tchar.h>

#include <windows.h> //for windows HANDL
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib") //for windows sndPlay .
#include <pdcurses.h>

#define ENEMY1 "スライム"
#define ENEMY2 "いぬ"
#define ENEMY3 "かいじん"
#define ENEMY4 "ゴブリン"


static const int DEF_UP = 0;
static const int DEF_DOWN = 1;
static const double EFFECT_MAGIC = 1.3;
static const int MP_MAGIC = 4;
static const int TYPEMAP0 = 0;
static const int TYPEMAP1 = 1;

void printTitle()
{
    const int margin_top = 3;
    const int margin_left = 8;

    const char *title[] = {
        "*******************************************************************************************************************",
        "                                                                                     ■■■■■■■■■■",
        "  |   ■■■■■■■■  ■■■     ■■   ■■ ■■■■■■■■ ■■        ■■   ■■■■■■■   ■■■     ■■    |   ■■        ■■",
        "  |      ■■    ■■ ■■    ■■  ■■  ■■       ■■■      ■■■  ■■     ■■  ■■ ■■   ■■    |  ■■  ■■■■■■  ■■",
        "  |      ■■   ■■■■■■■   ■■■■    ■■■■■■   ■■ ■■  ■■ ■■ ■■       ■■ ■■  ■■  ■■    | ■■■■■■    ■■■■■■",
        "  |      ■■  ■■     ■■  ■■  ■■  ■■       ■■  ■■■■  ■■  ■■     ■■  ■■   ■■ ■■    |  ■■  ■■■■■■  ■■",
        "  |      ■■ ■■       ■■ ■■   ■■ ■■■■■■■■ ■■   ■■   ■■   ■■■■■■■   ■■     ■■■    |   ■■        ■■",
        "                                                                                     ■■■■■■■■■■",
        "*******************************************************************************************************************"
    };

    for (int i = 0; i < sizeof(title)/sizeof(title[0]); i++) {
        move(margin_top + i, margin_left);  //カーソルを移動
        printw("%s", title[i]);
    }
    printw("\n");

    refresh();
}

void prologue(){
	clear();
	refresh();
	sndPlaySound(_T("Sound/war.wav"), SND_ASYNC);
	Sleep(5000);
	sndPlaySound(_T("Sound/warfight.wav"), SND_ASYNC);
	Sleep(3500);
	StopSound();
	printw("\t\t勇者 : うっ...");
	refresh();
	Sleep(2400);
	printw("\t\tこれで終わりなのか...？\n");
	refresh();

	Sleep(1000);
	sndPlaySound(_T("Sound/todome.wav"), SND_ASYNC);
	Sleep(3500);
	(void)wgetch(stdscr);
	clear();       // PDCurses の画面クリア
	refresh();     // 表示を更新

	sndPlaySound(_T("Sound/bgm1.wav"), SND_ASYNC);
	printw("\n\t\t200年前、勇者は魔王に敗れ、魔族の時代がはじまりました。\n");
	refresh();
	Sleep(2500);
	(void)wgetch(stdscr);
	printw("\t\t魔族に支配された人類は苦しい生活を送っています。\n");
	refresh();			
	Sleep(2500);
	(void)wgetch(stdscr);
	printw("\t\tあなたは、強くなるため旅にでました。\n");
	refresh();
	Sleep(2500);
	(void)wgetch(stdscr);
	printw("\t\t仲間を集め、魔王をたおして世界に平和を取りもどそう\n\n");
	refresh();
	Sleep(2500);
	(void)wgetch(stdscr);
	printw("\t\t---------------------最初の村-------------------------\n");
	refresh();
	Sleep(2500);
	(void)wgetch(stdscr);
}

void printslime()
{
    printw(
        "        ***********************************************************************\n"
        "        やせいの %s があらわれた！\n\n", ENEMY1);
    refresh();
    attron(COLOR_PAIR(1));
    printw(
        	"                                ■■                      \n"
        	"                               ■  ■                     \n"
        	"                              ■    ■                    \n"
        	"                              ■    ■                    \n"
        	"                             ■      ■                   \n"
        	"                           ■          ■                 \n");
    printw( "                          ■■              ■■               \n"
        	"                       ■■                   ■■            \n"
        	"                     ■                         ■         \n"
        	"                    ■      ■■■       ■■■        ■        \n"
        	"                   ■                             ■       \n"
        	"                    ■    ■■■           ■■■      ■        \n");
    printw( "                      ■     ■■■■■■■■■■■        ■          \n"
        	"                       ■■                   ■■■            \n"
        	"                          ■■■■■■■■■■■■■■■             \n ");
    attroff(COLOR_PAIR(1));
    refresh();
    printw("        ************************************************************************\n\n");
    refresh();

}

void printdog()
{
    printw(
        "        ***********************************************************************\n"
        "        やせいの %s があらわれた！\n\n",ENEMY2);
    refresh();
    attron(COLOR_PAIR(2));
    printw( "          ■■■           ■■■                  \n"
        	"          ■  ■          ■  ■■                \n"
        	"         ■    ■       ■■    ■■               \n");
    printw( "        ■  ■  ■■■■■■■■   ■■   ■              \n"
        	"        ■                      ■■            \n"
        	"        ■                     ■■             \n"
        	"        ■      ■       ■      ■■             \n"
        	"        ■■         ■         ■■              \n"
        	"         ■■       ■■■■       ■■              \n");
    printw( "         ■    ■■■■   ■■■■     ■■             \n"
        	"         ■■                  ■■              \n"
        	"           ■■■■■■■■■■■■■■■■                  \n"
        	"                                             \n");
    attroff(COLOR_PAIR(2));
    printw( "        ***********************************************************************\n\n");
    refresh();

}

void printboy()
{
    printw(
        	"        ***********************************************************************\n"
        	"        やせいの %s があらわれた！\n\n"
        	"                                                         \n"
        	"               ■■■■■■■■■                                       \n"
        	"            ■■          ■■■                              \n"
        	"           ■                ■                       \n",ENEMY3);
    printw( "          ■                  ■                                   \n"
        	"         ■ ■■■■■■■■■■■■■■■■  ■■                        \n"
        	"        ■ ■                  ■■■                      \n"
        	"        ■■    ■■■      ■■■     ■■                           \n"
        	"         ■         ■■         ■■                            \n"
        	"          ■                   ■                             \n");
    printw ("           ■    ■       ■    ■                          \n"
        	"            ■    ■■■■■■■    ■                      \n"
        	"             ■■          ■■                             \n"
        	"                ■■■■■■■■■                                     \n"
        	"                                                          \n"
        	"        ***********************************************************************\n\n");
    refresh();

}

void printgoblin()
{
    printw( "        ***********************************************************************\n"
        "        やせいの %s があらわれた！\n\n",ENEMY4);
    refresh();
    attron(COLOR_PAIR(3));
    printw(
        	"                      ■■                           \n"
        	"                  ■■■■■■■■■■                       \n"
        	"                ■■          ■■                     \n"
        	"          ■    ■■             ■■     ■             \n"
        	"         ■ ■  ■■               ■■  ■  ■            \n"
        	"        ■  ■■                  ■■■   ■■            \n");
    printw( "         ■  ■■                   ■  ■■             \n"
        	"          ■■ ■  ■■■       ■■■    ■ ■■              \n"
        	"           ■ ■  ■ ■■     ■ ■■    ■ ■               \n"
        	"     ■     ■ ■   ■■      ■■      ■■                \n"
        	"    ■ ■     ■■                  ■■                 \n"
        	"    ■ ■        ■   ■    ■    ■■■                   \n");
    printw( "    ■ ■        ■■   ■■■■■  ■■  ■■                  \n"
        	"    ■ ■     ■■   ■■     ■ ■■   ■■■                 \n"
        	"     ■ ■   ■■       ■■■■■     ■■  ■                \n"
        	"     ■ ■  ■   ■               ■■  ■■               \n"
        	"     ■■■■  ■■  ■             ■■  ■■                \n"
        	"      ■■■   ■  ■       ■■■■■  ■■■■■■               \n");
    printw( "        ■■ ■  ■       ■■        ■■■                \n"
        	"          ■■■  ■         ■■■■■■■                   \n"
        	"               ■   ■■■■■         ■■                \n"
        	"             ■   ■■      ■■■■      ■               \n"
        	"            ■   ■■           ■■     ■              \n"
        	"             ■   ■■            ■■    ■             \n");
    printw( "               ■   ■■            ■■  ■             \n"
        	"                ■■■■               ■■■             \n"
        	"                                                   \n");
    attroff(COLOR_PAIR(3));
    refresh();
    printw("        ***********************************************************************\n\n");
    refresh();
}

void runBattle(player_t* dt,int maptype)
{
	enemy_t ene = { "0" };
	enemy_t slime = { ENEMY1,7,5,2,20 };
	enemy_t dog = { ENEMY2,9,6,6,30 };
	enemy_t boy = { ENEMY3,12,13,2,40 };
	enemy_t goblin = { ENEMY4,18,13,7,50 };

	clear();       // PDCurses の画面クリア
	refresh();     // 表示を更新

	int ep = 0;//enemy paturn
	if (maptype == TYPEMAP0) {
		ep = rand_n(2);//MAP0では1と2、すなわちスライムと犬しかでない
	}
	else if (maptype == TYPEMAP1) {
		ep = rand_n(2)+2;//3と4、怪人とゴブリン
	}
	switch (ep) {
	case 1:
		printslime();
		ene = slime;
		break;
	case 2:
		printdog();
		ene = dog;
		break;
	case 3:
		printboy();
		ene = boy;
		break;
	case 4:
		printgoblin();
		ene = goblin;
		break;
	default:;
	}
	sndPlaySound(_T("Sound/battle.wav"), SND_ASYNC);
	pushenter();
	int dme = 0, dmi = 0; //"damage" to enemy from me and to me from enemy
	int type;//up or down gobrin turn
	char ch1 = '0';//choosen number by player.
	int cti2 = 0;//count number of my using "2:bougyo"
	int cte2 = 0, cte3 = 0, cte4 = 0;//count number of enemy's using "2:double", "3:up", and "4:down"
	int turn = 0;//今何ターン目か
	int finbougyo = 0;

	for (; ene.hp > 0;) {  //if slaim is alive, player should repeat choice
		turn++;
		if (turn == finbougyo) {
			dt->protect *= 1 / 2;
			cti2--;//ぼうぎょが使えるようになる
		}
		printw("\t\t%s (HP: %d)(MP: %d) vs %s (HP: %d)\n",dt->name, dt->hp,dt->mp, ene.name, ene.hp);
		refresh();
		(void)wgetch(stdscr);
		printw("\t\t1.こうげき\n\t\t2.ぼうぎょ\n\t\t3.まほう (消費MP: %d)\n\t\t4.にげる\n\n\n",MP_MAGIC);
		refresh();
		ch1 = '0';
		while (ch1 < '1' || ch1 > '4') {  //wgetchはASCIIをintで返す⇒"1"は49, "3"は51
    		ch1 = wgetch(stdscr);
		}
		if (dt->mp < MP_MAGIC && ch1 == THREE) {
			ch1 = 0;
			printw("\t\tMPがたりません\n");
			refresh();
			(void)wgetch(stdscr);
		}
		else {
			//NR
		}
		switch (ch1) {
		case ONE:
			printw("\t\t%sをこうげきした！\n\n", ene.name);
			refresh();
			sndPlaySound(_T("Sound/attack.wav"), SND_ASYNC);
			Sleep(1200);
			sndPlaySound(_T("Sound/battle cut.wav"), SND_ASYNC);
			dme = calcDamage(attackplayer(dt),ene.defence);
			printw("\t\t%s (HP: %d) に %d のダメージ！\n", ene.name, ene.hp, dme);
			refresh();
			ene.hp -= dme;
			(void)wgetch(stdscr);
			break;
		case TWO:
			printw("\t\tぼうぎょをかためた！\n");
			sndPlaySound(_T("Sound/buf.wav"), SND_ASYNC);
			Sleep(1200);
			sndPlaySound(_T("Sound/battle cut.wav"), SND_ASYNC);

			refresh();
			if (cti2 == 0) {
				printw("\t\tぼうぎょ力が2倍になった！\n");
				refresh();
				dt->protect *= 2;
				finbougyo = turn + 3;
				cti2++;
			} else {
				printw("\t\tしかしなにも起こらなかった。\n");
				refresh();
			}
			break;
		case THREE:
			dt->mp -= MP_MAGIC;
			printw("\t\tこうげきまほうをとなえた！\n");
			refresh();
			sndPlaySound(_T("Sound/explosion.wav"), SND_ASYNC);
			Sleep(1200);
			sndPlaySound(_T("Sound/battle cut.wav"), SND_ASYNC);
			dme = (double)calcDamage(attackplayer(dt), ene.defence) * EFFECT_MAGIC;
			printw("\t\t%s (HP: %d) に %d のダメージ！\n", ene.name, ene.hp, dme);
			refresh();
			ene.hp -= dme;
			(void)wgetch(stdscr);
			break;
		case FOUR:
			printw("\t\t%sからにげだした…\n", ene.name);
			refresh();
			sndPlaySound(_T("Sound/game over.wav"), SND_ASYNC);
			(void)wgetch(stdscr);
			return;
		default:;
		}
		if (ene.hp> 0) { //if enemy is alive, enemy should atack
			(void)wgetch(stdscr);
			// if (ene.name == ENEMY4) {
			if (strcmp(ene.name, ENEMY4) == 0){
				if (rand_n(2) == 1) {// enemy does normal attack for 1/2 
					printw("\t\t%sのこうげき！\n", ene.name);
					refresh();
					sndPlaySound(_T("Sound/goblin.wav"), SND_ASYNC);
					Sleep(1000);
					sndPlaySound(_T("Sound/attack.wav"), SND_ASYNC);
					Sleep(1200);;
					sndPlaySound(_T("Sound/battle cut2.wav"), SND_ASYNC);
					dmi = calcDamage(ene.attack,defenceplayer(dt));
					printw("\t\t%d のダメージをうけた！\n", dmi);
					refresh();
					dt->hp -= dmi;
				}
				else {  //enemy does special attack for 1/2
					switch (rand_n(4)) {
					case 1:
						printw("\t\t%sはスワップをつかった！\n", ene.name);
						refresh();
						sndPlaySound(_T("Sound/gobmagic.wav"), SND_ASYNC);
						Sleep(3000);
						sndPlaySound(_T("Sound/battle cut2.wav"), SND_ASYNC);
						Sleep(1200);
						swap(&dt->hp, &dt->mp);
						printw("\t\tHPとMPが入れかわった！\n\t\tHP(%d) MP(%d)\n", dt->hp, dt->mp);
						refresh();
						break;
					case 2:
						printw("\t\t%sはダブルをつかった！\n", ene.name);
						refresh();
						int rn_db = 0; //random double success
						rn_db = rand_n(2) - 1;   //  (1 or 2)-1  →　(0 or 1)
						if (cte2 == 0) {
							if (doublepower(&ene.attack, &ene.defence, rn_db)) {
								sndPlaySound(_T("Sound/gobmagic.wav"), SND_ASYNC);
								Sleep(3000);
								sndPlaySound(_T("Sound/battle cut.wav"), SND_ASYNC);
								Sleep(1200);
								printw("\t\t%sのこうげき力とぼうぎょ力が2倍になった！\n", ene.name);
								refresh();
								cte2++;//enemy uses double, ct2 become 1
							}
							else {
								printw("\t\tしかし失敗した！\n");
								refresh();
							}
						}
						else {
							printw("\t\tしかしなにも起こらなかった。\n");
							refresh();
						}

						break;
					case 3:
						printw("\t\t%sはパワーアップをつかった！\n", ene.name);
						refresh();
						if (cte3 == 0) {
							sndPlaySound(_T("Sound/gobmagic.wav"), SND_ASYNC);
							Sleep(3000);
							sndPlaySound(_T("Sound/battle cut2.wav"), SND_ASYNC);
							Sleep(1200);
							type = DEF_UP;
							changeParam(&ene.attack, type);
							printw("\t\t%sのこうげき力が60%%上がった！\n", ene.name);
							refresh();
							cte3++;
						}
						else {
							printw("\t\tしかしなにも起こらなかった。\n");
							refresh();
						}
						break;
					case 4:
						printw("\t\t%sはダウンを使った！\n", ene.name);
						refresh();
						if (cte4 == 0) {
							sndPlaySound(_T("Sound/gobmagic.wav"), SND_ASYNC);
							Sleep(3000);
							sndPlaySound(_T("Sound/battle cut.wav"), SND_ASYNC);
							Sleep(1200);
							type = DEF_DOWN;
							changeParam(&dt->protect, type);
							printw("\t\tぼうぎょ力が60%%下がった！\n");
							refresh();
							cte4++;
						}
						else {
							printw("\t\tしかしなにも起こらなかった。\n");
							refresh();
						}
						break;
					default:;
					}
				}
			}
			else {
				printw("\t\t%sのこうげき！\n", ene.name);
				refresh();
				sndPlaySound(_T("Sound/attack.wav"), SND_ASYNC);
				Sleep(1200);
				sndPlaySound(_T("Sound/battle cut2.wav"), SND_ASYNC);
				dmi = calcDamage(ene.attack, defenceplayer(dt));
				printw("\t\t%d のダメージをうけた！\n", dmi);
				refresh();
				dt->hp -= dmi;
			}
			(void)wgetch(stdscr);
			if (dt->hp <= 0) {  //if player is killed, program should finish.
				printw("\t\t%sにやられてしまった…\n", ene.name);
				refresh();
				sndPlaySound(_T("Sound/game over.wav"), SND_ASYNC);
				(void)wgetch(stdscr);
				printw("\t\tこの世界の勇者ではなかったようだ…\n");
				refresh();
				(void)wgetch(stdscr);
				return;
			}
			else {
				//NR
			}
		}
		else {}
	}
	printw("\t\t敵をたおした！\n");//if enemy is dead, player don't have to repeat choice because of "for sentence".
	sndPlaySound(_T("Sound/win.wav"), SND_ASYNC);
	if (cte4 == 1) {
		dt->protect *= 2;
	}
	else {
		//NR
	}
	dt->exp += ene.exp;
	printw("\t\t%d の経験値を手に入れた！\n", ene.exp);
	refresh();
	(void)wgetch(stdscr);

	for (; dt->exp > reqexp(dt);) {
    	clear();
		refresh();
		levelup(dt);
		print_player(*dt);
		sndPlaySound(_T("Sound/levelup.wav"), SND_ASYNC);
	}
	(void)wgetch(stdscr);
	return;
}

int calcDamage(int attack, int defence)
{
	int dm;
	dm = attack - (defence / 6);
	if (dm <= 0) {
		dm = 0;
	}
	else {
		//NR
	}
	return dm;
}

int rand_n(int n)
{
	n = (int)(rand() % n) + 1;
	return n;
}

void printMap(char map[][MAP_MAXLEN + 1], int row, int column)
{
    const int margin_top = 5;
    const int margin_left = 10;

    clear();

    for (int i = 0; i < row; i++) {
        move(i + margin_top, margin_left);  // 各行の先頭位置を調整
        for (int j = 0; j < strlen(map[i]); j++) {
            printw("%c", map[i][j]);
        }
    }

    refresh();
}

void swap(int* hp, int* mp)
{
	int tmp = 0;
	tmp = *hp;
	*hp = *mp;
	*mp = tmp;
	if (*hp == 0) {
		*hp = 1;
	}
	else {
		//NR
	}
}

int doublepower(int* dt1, int* dt2,int n)
{
	int ret;
	if (n) {  //if(n==1)と同義
		*dt1 *= 2;
		*dt2 *= 2;
		ret = 1;
	}
	else {
		ret = 0;
	}
	return ret;
}

void changeParam(int* dt, int type)
{
	if (type == DEF_UP) {
		*dt = (double)*dt * 1.6;
	}
	else if (type == DEF_DOWN) {
		*dt = (double)*dt * 0.4;
	}
	else {//NR
	}
}

void print_player(player_t dt1)
{
    printw("\t\tid：%d\n", dt1.id); refresh();
    printw("\t\tなまえ：%s\n", dt1.name); refresh();
    printw("\t\tレベル：%d\n", dt1.level); refresh();
    printw("\t\tHP：%d\n", dt1.hp); refresh();
    printw("\t\tMP：%d\n", dt1.mp); refresh();
    printw("\t\tこうげき力：%d\n", dt1.power); refresh();
    printw("\t\tぼうぎょ力：%d\n", dt1.protect); refresh();
    printw("\t\tスピード：%d\n", dt1.speed); refresh();
    printw("\t\t経験値：%d\n", dt1.exp); refresh();
    printw("\t\t成長率：%lf\n", dt1.g_rate); refresh();
    if (dt1.weapon.type == NOEQUIP) {
        printw("\t\t武器：なし\n"); refresh();
    } else {
        printw("\t\t武器：%s\n", dt1.weapon.name); refresh();
        printw("\t\tつよさ：%d\n", dt1.weapon.point); refresh();
    }
    if (dt1.armor.type == NOEQUIP) {
        printw("\t\t服：なし\n"); refresh();
    } else {
        printw("\t\t服：%s\n", dt1.armor.name); refresh();
        printw("\t\tつよさ:%d\n", dt1.armor.point); refresh();
    }
    if (dt1.shield.type == NOEQUIP) {
        printw("\t\t盾：なし\n"); refresh();
    } else {
        printw("\t\t盾：%s\n", dt1.shield.name); refresh();
        printw("\t\tつよさ：%d\n", dt1.shield.point); refresh();
    }
    if (dt1.helmet.type == NOEQUIP) {
        printw("\t\tヘルメット：なし\n"); refresh();
    } else {
        printw("\t\tヘルメット：%s\n", dt1.helmet.name); refresh();
        printw("\t\tつよさ：%d\n", dt1.helmet.point); refresh();
    }
    printw("\n\n"); refresh();
}

player_t* createPlayer(char name[], int id)
{
	player_t* pt = NULL;
	pt = (player_t*)calloc(1, sizeof(player_t));//callocは領域確保の後、最初のアドレスが返ってくる。→「player_tのアドレス」の型で返ってくるようにキャストする
	snprintf(pt->name, sizeof(pt->name),"%s", name);
	pt->id = id;
	pt->level = 1;
	pt->mp = MPFIR;
	pt->hp = HPFIR;

	/*printf("今から%sのたいりょく、ちから、まもり、すばやさがきまります。良い数がでるようにENTERをおしてください\n", name);
	printf("たいりょく：");
	(void)wgetch(stdscr);
	pt->hp = rand_n(11) + 39;    //40~50
	printf("%d\n\nちから：", pt->hp);
	(void)wgetch(stdscr);
	pt->power = rand_n(6) + 4;
	printf("%d\n\nまもり：", pt->power);
	(void)wgetch(stdscr);
	pt->protect = rand_n(6) + 4;
	printf("%d\n\nすばやさ：", pt->protect);
	(void)wgetch(stdscr);
	pt->speed = rand_n(6) + 4;
	printf("%d\n\n", pt->speed);
	(void)wgetch(stdscr);*/

	pt->power = 5;
	pt->protect = 5;
	pt->speed = 5;

	pt->exp = 0;
	pt->g_rate = 1.5;
	pt->weapon.type = NOEQUIP;
	pt->armor.type = NOEQUIP;
	pt->shield.type = NOEQUIP;
	pt->helmet.type = NOEQUIP;
	char noeq[64] = "なし";
	snprintf(pt->weapon.name, sizeof(pt->weapon.name), "%s", noeq);
	snprintf(pt->armor.name, sizeof(pt->armor.name), "%s", noeq);
	snprintf(pt->shield.name, sizeof(pt->shield.name), "%s", noeq);
	snprintf(pt->helmet.name, sizeof(pt->helmet.name), "%s", noeq);
	pt->next = NULL;
	pt->prev = NULL;

	return pt;
}

bool choose_yes() {
    char input = '0';
    while (true) {
        input = wgetch(stdscr);
		if (input == ONE){
			return true;
		}else if (input == TWO){
			return false;
		}
		else{
			//NR
		}
    }
}

void pushenter(void)
{
    int ch;
    while ((ch = wgetch(stdscr)) != '\n' && ch != '\r' && ch != KEY_ENTER);
}

int reqexp(player_t* dt)
{
	int ret = 0;
	ret = (dt->level * 20) + 100;
	return ret;
}

void levelup(player_t* dt)
{
	(void)wgetch(stdscr);
	printw("\t\t%s のレベルがあがった！\n", dt->name);
	dt->exp -= reqexp(dt);//levelより先
	dt->level++;       //expの後
	dt->hp = hpmax(dt);
	dt->mp = mpmax(dt);
	dt->power += dt->g_rate*2;
	dt->protect += dt->g_rate*2;
	dt->speed += dt->g_rate*2;
}

void save_menu(player_t* pt) {
	bool savecheck=false;
    char filename[30];
    int selected =0; //ASCII⇒int


	while(savecheck==false){
    	printw("\t\tセーブスロットを選んでください\n");
    	for (int i = 1; i <= 3; ++i) {
    	    char filename[30];
    	    snprintf(filename, sizeof(filename), "save%d.txt", i);
    	    FILE* fp = fopen(filename, "r");
    	    if (fp) {
    	        player_t tmp; //簡易的なセーブデータ読み出し(name & level) ファイルから一個ずつ読み込むからidも必要
    	        fscanf(fp, "%d", &tmp.id);
    	        fscanf(fp, "%s", tmp.name);
    	        fscanf(fp, "%d", &tmp.level);
    	        fclose(fp);
    	        printw("\t\t%d : 上書き（スロット%d） → %s（Lv.%d）\n", i, i, tmp.name, tmp.level);
    	    } else {
    	        printw("\t\t%d : 新規作成（スロット%d）\n", i, i);
    	    }
    	}

    	int ch = '0';
    	while (ch < '1' || ch > '3') {
    	    ch = wgetch(stdscr);
    	}

    	selected = ch - '0'; //ASCII⇒int
    	snprintf(filename, sizeof(filename), "save%d.txt", selected);
		//上書き確認
    	FILE* fp_check = fopen(filename, "r");
    	if (fp_check) {
    	    fclose(fp_check);
    	    printw("\t\tこのスロットにはすでにセーブがあります。\n");
    	    printw("\t\t上書きしてもよろしいですか？\n");
    	    printw("\t\t1 : はい\n\t\t2 : いいえ\n");
    	    refresh();
    	    if (!choose_yes()) {
    	        printw("\t\tセーブをキャンセルしました。\n");
    		}else{
				savecheck=true;
			}
    	}else{
			savecheck=true;
		}
	}

    printfile(filename, pt);
    printw("\t\tスロット%dにセーブしました\n", selected);
    (void)wgetch(stdscr);
}

void printfile(char name[], player_t* pt)
{
	FILE* fp;
	fp = fopen(name, "w");
	for (; pt != NULL; pt = pt->next) {
		fprintf(fp, "%d\t%s\t%d\t%d\t%d\t%d\t%d\n%d\t%d\t%lf\n"
			"%d\t%s\t%d \n%d\t%s\t%d \n%d\t%s\t%d \n%d\t%s\t%d\n"
			, pt->id, pt->name, pt->level,pt->hp,pt->mp ,pt->power, pt->protect, pt->speed,
			pt->exp, pt->g_rate, pt->weapon.type, pt->weapon.name, pt->weapon.point
			, pt->armor.type, pt->armor.name, pt->armor.point, pt->shield.type, pt->shield.name, pt->shield.point
			, pt->helmet.type, pt->helmet.name, pt->helmet.point);
	}
	fclose(fp);
}

player_t* scanfile(char name[], player_t* pt)
{
	FILE* fp;
	fp = fopen(name, "r");
	if (fp != NULL) {
		player_t* dt = NULL;
		dt = (player_t*)calloc(SIZEMAX, sizeof(player_t));
		int ct = 0;
		for (int i = 0; fscanf(fp, "%d", &dt[i].id) != EOF; i++) {

			fscanf(fp, "%s", dt[i].name);
			fscanf(fp, "%d", &dt[i].level);
			fscanf(fp, "%d", &dt[i].hp);
			fscanf(fp, "%d", &dt[i].mp);
			fscanf(fp, "%d", &dt[i].power);
			fscanf(fp, "%d", &dt[i].protect);
			fscanf(fp, "%d", &dt[i].speed);
			fscanf(fp, "%d", &dt[i].exp);
			fscanf(fp, "%lf", &dt[i].g_rate);
			fscanf(fp, "%d", &dt[i].weapon.type);
			fscanf(fp, "%s", dt[i].weapon.name);
			fscanf(fp, "%d", &dt[i].weapon.point);
			fscanf(fp, "%d", &dt[i].armor.type);
			fscanf(fp, "%s", dt[i].armor.name);
			fscanf(fp, "%d", &dt[i].armor.point);
			fscanf(fp, "%d", &dt[i].shield.type);
			fscanf(fp, "%s", dt[i].shield.name);
			fscanf(fp, "%d", &dt[i].shield.point);
			fscanf(fp, "%d", &dt[i].helmet.type);
			fscanf(fp, "%s", dt[i].helmet.name);
			fscanf(fp, "%d", &dt[i].helmet.point);
			ct++;
		}
		pt = &dt[0];
		dt[ct - 1].next = NULL;
		dt[0].prev = NULL;
		for (int i = 0; i < ct - 1; i++) {
			dt[i].next = &dt[i + 1];
			dt[i + 1].prev = &dt[i];
		}

		fclose(fp);
	}
	else {
		printw("\t\tセーブデータが見つかりません\n");
	}

	return pt;
}

int hpmax(player_t* dt)
{
	int hp;
	hp = (HPFIR-3) + (double)dt->level * 2 * dt->g_rate;
	return hp;
}

int mpmax(player_t* dt)
{
	int mp;
	mp = MPFIR + (double)dt->level * 2 * dt->g_rate;
	return mp;
}

void save(player_t* pt)
{
    printw("\t\tセーブしますか?\n"); refresh();
    printw("\t\t1 : はい\n		2 : いいえ\n"); refresh();
    if (choose_yes())
    {
        save_menu(pt);
        // printw("		セーブしました!\n"); refresh();
        (void)wgetch(stdscr);
    }
}

void equipitem(player_t* dt, equip_t item)
{
	switch (item.type) {
	case 1:
		dt->weapon = item;
		break;
	case 2:
		dt->armor = item;
		break;
	case 3:
		dt->shield = item;
		break;
	case 4:
		dt->helmet = item;
		break;
	}
}

int attackplayer(player_t* dt)
{
	int ret=0;
	ret = dt->power + dt->weapon.point;
	return ret;
}

int defenceplayer(player_t* dt)
{
	int ret = 0;
	ret = dt->protect + dt->armor.point + dt->shield.point + dt->helmet.point;
	return ret;
}

void StopSound(void)
{
    sndPlaySound(NULL, SND_ASYNC);
}

