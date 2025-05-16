#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#include<tchar.h>
#include <locale.h>
#pragma comment(lib,"Winmm.lib")
#include<assert.h>
#include<stdlib.h>
#include<time.h>
#include <pdcurses.h>
#include"gameheader.h"
#include"gameio.h"


#define PARAMIN 1
#define PARAMAX 10
#define MAXHP 50
#define NORMALSORD 3
#define NORMALSORD_X 19
#define NORMALSORD_Y 3
#define NUNOHUKU 2
#define MAP_MAXLEN	80
#define RAND_BATTLE 11  //偶数じゃダメ、←乱数をこれで割った余りが0の時バトル開始で、その敵を、同じ乱数を2で割った余りでだしてるから
#define RAND_BATTLE1 5
#define HPFIR 50//HP at first
#define MPFIR 30// MP at first
#define STR_MAX	256
#define WEAPON	1
#define ARMOR	2
#define SHIELD	3
#define	HELMET	4
#define	NOEQUIP	0
#define SIZEMAX 20
/** 
#define KEY_LEFT 0x4B
#define KEY_RIGHT 0x4D
#define KEY_UP 0x48
#define KEY_DOWN 0x50
**/
#define ONE 0x31
#define TWO 0x32
#define THREE 0x33
#define FOUR 0x34
#define ENTER 0x0d
#define TYPEMAP0 0
#define TYPEMAP1 1





int main(void)
{

	// resizeConsoleWindow(1000, 700);      // ピクセル単位の画面サイズ調整
	// setConsoleBufferSize(120, 40);       // 文字数単位でスクロール領域確保
	// maximizeConsoleWindow();

	initscr();              // 画面初期化
	// setConsoleBufferSize(160, 60);
	resize_term(45, 130);
	clear();
	refresh();

	start_color();  //色

	if (!has_colors()) {
    	endwin();
    	printf("Color is not supported.\n");
    	return 1;
	}

	init_pair(1, COLOR_CYAN, COLOR_BLACK);   // slime
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); // dog
	init_pair(3, COLOR_GREEN, COLOR_BLACK);    // goblin





	noecho();               // 入力文字を表示しない
	cbreak();               // バッファリングせず即時入力にする
	keypad(stdscr, TRUE);   // 矢印キーなどの特殊キーを有効にする
	curs_set(0);            // カーソル非表示
	scrollok(stdscr, TRUE); 


	setlocale(LC_ALL, "");
	initialSettingGameIO();
	printTitle();
	sndPlaySound(_T("start.wav"), SND_ASYNC| SND_LOOP); //playSound関数が使えなかった（理由わからず）のでtimeSleep使うためだけにgameio入れました
	timeSleep(3000);
	(void)wgetch(stdscr); //wait key
	clear();       // PDCurses の画面クリア
	refresh();     // 表示を更新

	printw("		*************************************************************************************\n");
	refresh();

	printw("		Welcome to TAKEMON\n");
	refresh();
	(void)wgetch(stdscr);
	printw("		loading savadata\n		1 : yes\n		2 : no\n");
	refresh();

	player_t* pt = NULL;//パーティーへのポインタ
	player_t* you = NULL;

	if (yesno() == ONE) {
		pt = scanfile("savedata", pt);
		you = pt;
		sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound

	}
	else {

		printw("		Username\n		name : ");
		refresh();

		char name[16];
		wgetnstr(stdscr, name, sizeof(name) - 1);
		you = createPlayer(name);
		pt = you;

		printw("\n\n");
		refresh();

		print_player(*pt);
		// while (wgetch(stdscr) != ENTER);
		pushenter();
		printw("		Start\n");
		refresh();

		// while (wgetch(stdscr) != ENTER);
		pushenter();
		printw("		Watch the prologue\n		1 : Yes\n		2 : No\n");
		refresh();

		if (yesno() == ONE) {
			clear();       // PDCurses の画面クリア
			refresh();     // 表示を更新

			sndPlaySound(_T("war.wav"), SND_ASYNC); //Play sound
			timeSleep(5000);
			sndPlaySound(_T("warfight.wav"), SND_ASYNC); //Play sound
			timeSleep(3500);
			stopSound();
			printw("		Hero: Ugh...\n");
			refresh();

			timeSleep(3000);
			printw("		Is this the end...?\n");
			refresh();

			timeSleep(1000);
			sndPlaySound(_T("todome.wav"), SND_ASYNC); //Play sound
			timeSleep(3500);
			(void)wgetch(stdscr);
			clear();       // PDCurses の画面クリア
			refresh();     // 表示を更新

			sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound
			printw("\n		200 years ago, the hero was defeated by the Demon Lord, and the age of demons began.\n");
			refresh();
			timeSleep(2500);
			(void)wgetch(stdscr);
			printw("		Humanity, under the rule of the demons, lives in hardship.\n");
			refresh();			
			timeSleep(2500);
			(void)wgetch(stdscr);
			printw("		You set out on a journey to become stronger.\n");
			refresh();
			timeSleep(2500);
			(void)wgetch(stdscr);
			printw("		Find allies and defeat the Demon Lord to bring peace back to the world.\n\n");
			refresh();
			timeSleep(2500);
			(void)wgetch(stdscr);
			printw("		---------------------The First Village-------------------------\n");
			refresh();
			timeSleep(2500);
			(void)wgetch(stdscr);
		}
		else {
			sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound

		}
	}



	char map[][MAP_MAXLEN + 1] = {
		"######################################################################",
		"#    #  #              #                                             #",
		"#    #      # #       # #                                            #",
		"#    #     ##  #    #   #                                            #",
		"#    #  ########## ##                                                #",
		"#    #  #  ##     # ########    #      #                             #",
		"#    #  ######        #   #  #  #                                    #",
		"#    # #       #         ###### #                                    #",
		"#    #   @              #      ##                                    #",
		"#    ####      ####       #######                                    #",
		"#                                                                    #",
		"#                                                                    #",
		"#                                #                                   #",
		"#   ##########        #                                         #    #",
		"#                       #        #  ###                          #   #",
		"#                       #        #   ##                          #   #",
		"#                       #        #  ###                     ######   #",
		"#   ###    ###    #        #          #        #                 #   #",
		"#   ###    ###              #######        #                     #   #",
		"#                                                     @    #     #   #",
		"######################################################################"
	};
	map[12][10] = '@';
	map[6][42] = '@';

	
	equip_t normalsord = { WEAPON,"Normal sord",NORMALSORD, NORMALSORD_X, NORMALSORD_Y};
	map[normalsord.x][normalsord.y] = '*';

	int mapWidth = 0;
	int mapHeight = 0;
	int p_x = 0, p_y = 0;			//Position of player
	int pre_x = 0, pre_y = 0;		//Preposition of player

	mapWidth = strlen(map[0]);
	mapHeight = sizeof(map) / sizeof(map[0]);
	char player[] = "$";
	p_x = 1;
	p_y = 2;//player first position (1,1)
	int stbt = 0;//startbattle
	int move = 0;
	int tmpx = 0, tmpy = 0;
//	sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound
	for (; p_y != mapWidth-2;) {//町を出るまで繰り返し
			map[p_x][p_y] = player[0];
			printMap(map, mapHeight, MAP_MAXLEN + 1);
			move = 0;

			/*for (; move != KEY_LEFT && move != KEY_RIGHT && move != KEY_UP && move != KEY_DOWN;) {
				move = wgetch(stdscr);
			}*/
			while (1) {
    			move = wgetch(stdscr);
    			if (move == KEY_LEFT || move == KEY_RIGHT || move == KEY_UP || move == KEY_DOWN) {
        			break;
    			}
			}

			map[p_x][p_y] = ' ';
			tmpx = p_x;
			tmpy = p_y;
			switch (move) {
			case KEY_LEFT:
				p_y--;
				break;
			case KEY_RIGHT:
				p_y++;
				break;
			case KEY_UP:
				p_x--;
				break;

			case KEY_DOWN:
				p_x++;
				break;
			default:;
			}
			if (map[p_x][p_y] == ' ') {
				//NR
			}
			else if ( p_x== normalsord.x && p_y == normalsord.y ) {
				printw("\n		You obtained a basic sword!\n");
				refresh();

				pushenter();
				equipitem(you, normalsord);
				print_player(*you);
				pushenter();

			}
			else if (p_x == 12 && p_y == 10) {
				printw("\n\n		Villager : Are you a traveler ?\n");
				refresh();
				pushenter();
				printw("		Villager : I heard the Demon Lord has powerful generals.\n");
				refresh();
				(void)wgetch(stdscr);
				printw("		Villager : One of them is said to be in the cave near this town...\n");
				refresh();
				(void)wgetch(stdscr);
				printw("		Villager : I hope peace returns soon.\n");
				refresh();
				(void)wgetch(stdscr);
				p_x = tmpx;
				p_y = tmpy;
			}
			else if (p_x == 6 && p_y == 42) {
				printw("\n\n		Villager : Oh dear...\n");
				refresh();
				pushenter();
				printw("		Villager : There is a demon cave to the east, and we’re too scared to even leave town.\n");
				refresh();
				(void)wgetch(stdscr);
				p_x = tmpx;
				p_y = tmpy;
			}
			else{
				p_x = tmpx;
				p_y = tmpy;
			}
			
			stbt = rand_n(RAND_BATTLE) ;//start battle for probability of 1/RAND_BATTTLE
			if (stbt == 1) {
				runBattle(pt,TYPEMAP0);
				if (pt->hp <= 0) {
					endwin();
					return 0;
				}
				else {
					//NR
				}
				printw("		Continue the game\n");
				refresh();
				printw("		1 : Yes\n		2 : No\n");
				refresh();
				if (yesno() == TWO) {
					save(pt);
					endwin();
					return 0;
				}
				else {
					//NR
				}
				sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound

			}
			else {
				//NR
			}
	}
	clear();
	refresh();
	printw("		You have left the town.\n");
	refresh();
	(void)wgetch(stdscr);	



	char map1[][MAP_MAXLEN + 1] = {
		"                                                                                ",
		"########################################                                      ",
		"#                                      ######                                 ",
		"#                                        ####      #                          ",
		"#                                     ##   #      ##                          ",
		"#                                             # ##                           ",
		"#                                ##            ####                           ",
		"#                    #    ###  #              #  #                           ",
		"#                  #  ## ##     #          ####                             ",
		"#                   ### # ### #              ##                              ",
		"#                    ## ##### ##              #                              ",
		"#                   ## ##  # #  # #            #                            ",
		"#                    # #  # ## ####           #                             ",
		"#                     #    ##      #               #                         ",
		"#                          #                          #                       ",
		"#                                                      #                      ",
		"#                                                      #                      ",
		"#                                                      #                      ",
		"#                                         ###       #                        ",
		"##                                      #  ##      #                        ",
		"# #                                  ## # ###   #                        ",
		"###                                ##  ##  ##  #                        ",
		"# ####                            #  ####### #                        ",
		"########################################                                      "
	};


	int mapWidth1 = 0;
	int mapHeight1 = 0;


	mapWidth1 = strlen(map1[0]);
	mapHeight1 = sizeof(map1) / sizeof(map1[0]);
	p_x = 11;
	p_y = 2;//player first position (11,2)
	sndPlaySound(_T("adventure.wav"), SND_ASYNC); 
	for (; p_x != 0 && p_y != mapWidth1 - 1 ;) {
		map1[p_x][p_y] = player[0];
		printMap(map1, mapHeight1, MAP_MAXLEN + 1);
		move = 0;
		while (1) {
    		move = wgetch(stdscr);
    		if (move == KEY_LEFT || move == KEY_RIGHT || move == KEY_UP || move == KEY_DOWN) {
        		break;
    		}
		}

		map1[p_x][p_y] = ' ';
		tmpx = p_x;
		tmpy = p_y;
		switch (move) {
		case KEY_LEFT:
			p_y--;
			break;
		case KEY_RIGHT:
			p_y++;
			break;
		case KEY_UP:
			p_x--;
			break;

		case KEY_DOWN:
			p_x++;
			break;
		default:;
		}
		if (map1[p_x][p_y] == ' ') {
			//NR
		}
		else {
			p_x = tmpx;
			p_y = tmpy;
		}

		stbt = rand_n(RAND_BATTLE1);//start battle for probability of 1/RAND_BATTTLE
		if (stbt == 1) {
			runBattle(pt,TYPEMAP1);
			if (pt->hp <= 0) {
				endwin();
				return 0;
			}
			else {
				//NR
			}
			printw("		Continue the game\n");
			refresh();
			printw("		1 : Yes\n		2 : No\n");
			refresh();

			if (yesno() == TWO) {
				save(pt);
			}
			else {
				//NR
			}
			sndPlaySound(_T("adventure.wav"), SND_ASYNC); //Play sound
		}
		else {
			//NR
		}
	}


	endwin();
	return 0;
}