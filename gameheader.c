#include "gameio.h"
#include"gameheader.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include<tchar.h>

#include<windows.h> //for windows HANDL
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib") //for windows sndPlay .
#include <pdcurses.h>

#define ENEMY1 "SLIME"
#define ENEMY2 "DOG"
#define ENEMY3 "STRANGER"
#define ENEMY4 "GOBLIN"




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
        "                                                                                     ##########",
        "  |   ########  ###     ##   ## ######## ##        ##   #######   ###     ##    |   ##        ##",
        "  |      ##    ## ##    ##  ##  ##       ###      ###  ##     ##  ## ##   ##    |  ##  ######  ##",
        "  |      ##   #######   ####    ######   ## ##  ## ## ##       ## ##  ##  ##    | ######    ######",
        "  |      ##  ##     ##  ##  ##  ##       ##  ####  ##  ##     ##  ##   ## ##    |  ##  ######  ##",
        "  |      ## ##       ## ##   ## ######## ##   ##   ##   #######   ##     ###    |   ##        ##",
        "                                                                                     ##########",
        "*******************************************************************************************************************"
    };

    for (int i = 0; i < sizeof(title)/sizeof(title[0]); i++) {
        move(margin_top + i, margin_left);  //カーソルを移動
        printw("%s", title[i]);
    }
	printw("\n");

    refresh();
}

void printslime()
{
    printw(
        "		***********************************************************************\n"
        "		A wild %s appeared!!\n\n", ENEMY1);
    refresh();
    attron(COLOR_PAIR(1));
    printw(
        	"                               ##                      \n"
        	"                              #  #                     \n"
        	"                             #    #                    \n"
        	"                             #    #                    \n"
        	"                            #      #                   \n"
        	"                          #          #                 \n");
    printw( "                      ##              ##               \n"
        	"                  ##                      ##           \n"
        	"                 #                           #         \n"
        	"                #       ###       ###         #        \n"
        	"                #                              #       \n"
        	"                 #    ##              ##      #        \n");
    printw( "                   #     #############      #          \n"
        	"                     ##                 ###            \n"
        	"                        ###############                \n ");
    attroff(COLOR_PAIR(1));
    refresh();
    printw("		************************************************************************\n\n");
    refresh();

}

void printdog()
{
    printw(
        	"		***********************************************************************\n"
        	"		A wild %s appeared!!\n\n",ENEMY2);
	refresh();
    attron(COLOR_PAIR(2));
    printw( "          ###           ###                  \n"
        	"          #  #          #  ##                \n"
        	"         #    #       ##    ##               \n");
    printw( "        #  #  ########   ##   #              \n"
        	"        #                      ##            \n"
        	"        #                     ##             \n"
        	"        #      #       #      ##             \n"
        	"        ##         #         ##              \n"
        	"         ##       ####       ##              \n");
    printw( "         #    ####   ####     ##             \n"
        	"         ##                  ##             \n"
        	"           #################                 \n"
        	"                                             \n");
    attroff(COLOR_PAIR(2));
    printw( "		***********************************************************************\n\n");
    refresh();

}

void printboy()
{
    printw(
        	"		***********************************************************************\n"
        	"		A wild %s appeared!!\n\n"
        	"                                                         \n"
        	"               #########                                       \n"
        	"            ##          ###                                          \n"
            "           #                #                       \n",ENEMY3);
    printw( "          #                  #                                   \n"
        	"         # ####################                           \n"
        	"        # #                  ###         \n"
        	"        ##    ###      ###     ##                           \n"
        	"         #         ##         ##                            \n"
        	"          #                   #                             \n");
    printw ("           #    #       #    #                          \n"
        	"            #    #######    #                      \n"
        	"             ##          ##                             \n"
        	"                #########                                     \n"
        	"                                                          \n"
        	"		***********************************************************************\n\n");
    refresh();

}

void printgoblin()
{
    printw( "		***********************************************************************\n"
        	"		A wild %s appeared!!\n\n",ENEMY4);
    refresh();
    attron(COLOR_PAIR(3));
    printw(
        	"                      ##                           \n"
        	"                  ##########                       \n"
        	"                ##          ##                     \n"
        	"          #    ##             ##     #             \n"
        	"         # #  ##               ##  #  #            \n"
        	"        #  ##                  ###   ##            \n");
    printw( "         #  ##                   #  ##             \n"
        	"          ## #  ###       ###    # ##              \n"
        	"           # #  # ##     # ##    # #               \n"
        	"     #     # #   ##      ##      ##                \n"
        	"    # #     ##                  ##                 \n"
        	"    # #        #   #    #    ###                   \n");
    printw( "    # #        ##   #####  ##  ##                  \n"
        	"    # #     ##   ##     # ##   ###                 \n"
        	"     # #   ##       #####     ##  #                \n"
        	"     # #  #   #               ##  ##               \n"
        	"     ####  ##  #             ##  ##                \n"
        	"      ###   #  #       #####  ##                   \n");
    printw( "        ## #  #       ##        ###                \n"
        	"          ###  #         #######                   \n"
        	"               #   #####         ##                \n"
        	"             #   ##      ####      #               \n"
        	"            #   ##           ##     #              \n"
        	"             #   ##            ##    #             \n");
    printw( "               #   ##            ##  #             \n"
        	"                ####               ###             \n"
        	"                                                   \n");
    attroff(COLOR_PAIR(3));
    refresh();
    printw("		***********************************************************************\n\n");
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
	sndPlaySound(_T("battle.wav"), SND_ASYNC); //Play sound
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
		printw("		%s (HP: %d)(MP: %d) vs %s (HP: %d)\n",dt->name, dt->hp,dt->mp, ene.name, ene.hp);
		refresh();
		(void)wgetch(stdscr);
		ch1 = '0';
		printw("		1.Attack\n		2.Guard\n		3.Magic (MP Cost: %d)\n		4.Run Away\n\n\n",MP_MAGIC);
		refresh();
		for (; ch1 !=ONE&& ch1 != TWO && ch1 != THREE && ch1 != FOUR; ch1 = wgetch(stdscr)) {}
		if (dt->mp < MP_MAGIC && ch1 == THREE) {
			ch1 = 0;
			printw("		Not enough MP!\n");
			refresh();
			(void)wgetch(stdscr);
		}
		else {
			//NR
		}
		switch (ch1) {
		case ONE:
			printw("		You attacked the %s!\n\n", ene.name);
			refresh();
			sndPlaySound(_T("attack.wav"), SND_ASYNC);
			(void)wgetch(stdscr);
			sndPlaySound(_T("battle cut.wav"), SND_ASYNC);
			dme = calcDamage(attackplayer(dt),ene.defence);
			printw("		%s (HP: %d) takes %d damage!\n", ene.name, ene.hp, dme);
			refresh();
			ene.hp -= dme;
			(void)wgetch(stdscr);
			break;
		case TWO:
			printw("		You brace yourself for the attack.\n");
			sndPlaySound(_T("buf.wav"), SND_ASYNC);
			(void)wgetch(stdscr);
			sndPlaySound(_T("battle cut.wav"), SND_ASYNC);

			refresh();
			if (cti2 == 0) {
				printw("		Your defense is doubled!\n");
				refresh();
				dt->protect *= 2;
				finbougyo = turn + 3;
				cti2++;
			} else {
				printw("		But you can't use it again — nothing happened.\n");
				refresh();
			}
			break;
		case THREE:
			dt->mp -= MP_MAGIC;
			printw("		You cast an attack spell!\n");
			refresh();
			sndPlaySound(_T("explosion.wav"), SND_ASYNC);
			(void)wgetch(stdscr);
			sndPlaySound(_T("battle cut.wav"), SND_ASYNC);
			dme = (double)calcDamage(attackplayer(dt), ene.defence) * EFFECT_MAGIC;
			printw("		%s (HP: %d) takes %d damage!\n", ene.name, ene.hp, dme);
			refresh();
			ene.hp -= dme;
			(void)wgetch(stdscr);
			break;
		case FOUR:
			printw("		You turned your back and ran from the %s...\n", ene.name);
			refresh();
			sndPlaySound(_T("game over.wav"), SND_ASYNC);
			(void)wgetch(stdscr);
			return;
		default:;
		}
		if (ene.hp> 0) { //if enemy is alive, enemy should atack
			(void)wgetch(stdscr);
			// if (ene.name == ENEMY4) {
			if (strcmp(ene.name, ENEMY4) == 0){
				if (rand_n(2) == 1) {// enemy does normal attack for 1/2 
					printw("		%s attacks!\n", ene.name);
					refresh();
					sndPlaySound(_T("goblin.wav"), SND_ASYNC); //Play sound
					Sleep(1000);
					sndPlaySound(_T("attack.wav"), SND_ASYNC);
					Sleep(1000);
					sndPlaySound(_T("battle cut2.wav"), SND_ASYNC);
					dmi = calcDamage(ene.attack,defenceplayer(dt));
					printw("		You take %d damage!\n", dmi);
					refresh();
					dt->hp -= dmi;
				}
				else {  //enemy does special attack for 1/2
					switch (rand_n(4)) {
					case 1:
						printw("		%s used Swap!\n", ene.name);
						refresh();
						sndPlaySound(_T("gobmagic.wav"), SND_ASYNC);
						Sleep(3000);
						sndPlaySound(_T("battle cut2.wav"), SND_ASYNC);
						(void)wgetch(stdscr);
						swap(&dt->hp, &dt->mp);
						printw("		Your HP and MP have switched places!\n		HP(%d) MP(%d)\n", dt->hp, dt->mp);
						refresh();
						break;
					case 2:
						printw("		%s used Double!\n", ene.name);
						refresh();
						int rn_db = 0; //random double success
						rn_db = rand_n(2) - 1;   //  (1 or 2)-1  →　(0 or 1)
						if (cte2 == 0) {
							if (doublepower(&ene.attack, &ene.defence, rn_db)) {
								sndPlaySound(_T("gobmagic.wav"), SND_ASYNC);
								Sleep(3000);
								sndPlaySound(_T("battle cut.wav"), SND_ASYNC);
								(void)wgetch(stdscr);
								printw("		%s's attack and defense have doubled!\n", ene.name);
								refresh();
								cte2++;//enemy uses double, ct2 become 1
							}
							else {
								printw("		But it failed!\n");
								refresh();
							}
						}
						else {
							printw("		But he can't use it again — nothing happened.\n");
							refresh();
						}

						break;
					case 3:
						printw("		%s used Power Up!\n", ene.name);
						refresh();
						if (cte3 == 0) {
							sndPlaySound(_T("gobmagic.wav"), SND_ASYNC);
							Sleep(3000);
							sndPlaySound(_T("battle cut2.wav"), SND_ASYNC);
							(void)wgetch(stdscr);
							type = DEF_UP;
							changeParam(&ene.attack, type);
							printw("		%s's attack power increased by 60%!\n", ene.name);
							refresh();
							cte3++;
						}
						else {
							printw("		But he can't use it again — nothing happened.\n");
							refresh();
						}
						break;
					case 4:
						printw("		%s used Defense Down!\n", ene.name);
						refresh();
						if (cte4 == 0) {
							sndPlaySound(_T("gobmagic.wav"), SND_ASYNC);
							Sleep(3000);
							sndPlaySound(_T("battle cut.wav"), SND_ASYNC);
							(void)wgetch(stdscr);
							type = DEF_DOWN;
							changeParam(&dt->protect, type);
							printw("		Your defense decreased by 60%!\n");
							refresh();
							cte4++;
						}
						else {
							printw("		But he can't use it again — nothing happened.\n");
							refresh();
						}
						break;
					default:;
					}
				}
			}
			else {
				printw("		%s attacks!\n", ene.name);
				refresh();
				sndPlaySound(_T("attack.wav"), SND_ASYNC);
				(void)wgetch(stdscr);
				sndPlaySound(_T("battle cut2.wav"), SND_ASYNC);
				dmi = calcDamage(ene.attack, defenceplayer(dt));
				printw("		You take %d damage!\n", dmi);
				refresh();
				dt->hp -= dmi;
			}
			(void)wgetch(stdscr);
			if (dt->hp <= 0) {  //if player is killed, program should finish.
				printw("		You were defeated by the %s…\n", ene.name);
				refresh();
				sndPlaySound(_T("game over.wav"), SND_ASYNC);
				(void)wgetch(stdscr);
				printw("		It seems you are not the hero this world needed...\n");
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
	printw("		You defeated the enemy!\n");//if enemy is dead, player don't have to repeat choice because of "for sentence".
	sndPlaySound(_T("win.wav"), SND_ASYNC);
	if (cte4 == 1) {
		dt->protect *= 2;
	}
	else {
		//NR
	}
	dt->exp += ene.exp;
	printw("		Gained %d EXP!\n", ene.exp);		
	refresh();
	(void)wgetch(stdscr);

	for (; dt->exp > reqexp(dt);) {
    	clear();
		refresh();
		levelup(dt);
		print_player(*dt);
		sndPlaySound(_T("levelup.wav"), SND_ASYNC);
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
            addch(map[i][j]);
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
    printw("		id:%d\n", dt1.id); refresh();
    printw("		Name:%s\n", dt1.name); refresh();
    printw("		Level:%d\n", dt1.level); refresh();
    printw("		HP:%d\n", dt1.hp); refresh();
    printw("		MP:%d\n", dt1.mp); refresh();
    printw("		Power:%d\n", dt1.power); refresh();
    printw("		Defense:%d\n", dt1.protect); refresh();
    printw("		Speed:%d\n", dt1.speed); refresh();
    printw("		Exp:%d\n", dt1.exp); refresh();
    printw("		Growth-Rate:%lf\n", dt1.g_rate); refresh();
    if (dt1.weapon.type == NOEQUIP) {
        printw("		Weapon:None\n"); refresh();
    } else {
        printw("		Weapon:%s\n", dt1.weapon.name); refresh();
        printw("		Point:%d\n", dt1.weapon.point); refresh();
    }
    if (dt1.armor.type == NOEQUIP) {
        printw("		Armor:None\n"); refresh();
    } else {
        printw("		Armor:%s\n", dt1.armor.name); refresh();
        printw("		Point:%d\n", dt1.armor.point); refresh();
    }
    if (dt1.shield.type == NOEQUIP) {
        printw("		Shield:None\n"); refresh();
    } else {
        printw("		Shield:%s\n", dt1.shield.name); refresh();
        printw("		Point:%d\n", dt1.shield.point); refresh();
    }
    if (dt1.helmet.type == NOEQUIP) {
        printw("		Helmet:None\n"); refresh();
    } else {
        printw("		Helmet:%s\n", dt1.helmet.name); refresh();
        printw("		Point:%d\n", dt1.helmet.point); refresh();
    }
    printw("\n\n"); refresh();
}

player_t* createPlayer(char name[], int id)
{
	player_t* pt = NULL;
	pt = (player_t*)calloc(1, sizeof(player_t));//callocは領域確保の後、最初のアドレスが返ってくる。→「player_tのアドレス」の型で返ってくるようにキャストする
	sprintf(pt->name, "%s", name);
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
	char noeq[64] = "None";
	sprintf(pt->weapon.name, "%s", noeq);
	sprintf(pt->armor.name, "%s", noeq);
	sprintf(pt->shield.name, "%s", noeq);
	sprintf(pt->helmet.name, "%s", noeq);
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
	printw("		%s leveled up!\n", dt->name);
	dt->exp -= reqexp(dt);//levelより先
	dt->level++;       //expの後
	dt->hp = hpmax(dt);
	dt->mp = mpmax(dt);
	dt->power += dt->g_rate*2;
	dt->protect += dt->g_rate*2;
	dt->speed += dt->g_rate*2;
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
		printw("Save data not found.\n");
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
    printw("		Do you want to save your progress?\n"); refresh();
    printw("		1 : Yes\n		2 : No\n"); refresh();
    if (choose_yes())
    {
        printfile("savedata", pt);
        printw("		Game saved successfully!\n"); refresh();
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