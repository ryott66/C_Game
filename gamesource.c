#include<stdio.h>
#include<windows.h>
#include<mmsystem.h>
#include<tchar.h>
#include <locale.h>
#pragma comment(lib,"Winmm.lib")
#include<stdlib.h>
#include<time.h>
#include <pdcurses.h>
#include"gameheader.h"

static const equip_t NORMAL_SWORD = {WEAPON, "普通の剣", 3, 3, 19};


#define RAND_BATTLE 15  //偶数ダメ←乱数をこれで割った余りが0の時バトル開始で、その敵を2で割った余りでだしてる
#define RAND_BATTLE1 15

typedef enum {
	MAP0 = 0,
	MAP1 = 1
} MAPTYPE;

//05/16: gcc gamesource.c gameheader.c gameio.c -o game.exe -L/mingw64/lib -lpdcurses -lwinmm

int main(void)
{
	// ウィンドウ初期化
	initscr();              
	resize_term(45, 130);
	clear();
	refresh();

	start_color();
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
	printTitle();
	sndPlaySound(_T("start.wav"), SND_ASYNC| SND_LOOP);
	Sleep(3000);
	(void)wgetch(stdscr); //wait key
	clear();       // PDCurses の画面クリア
	refresh();     // 表示を更新

	printw("\t\t*************************************************************************************\n");
	refresh();

	printw("\t\tTAKEMONへようこそ\n");
	refresh();
	(void)wgetch(stdscr);
	printw("\t\tセーブデータを読み込みますか？\n\t\t1 : はい\n\t\t2 : いいえ\n");
	refresh();

	player_t* pt = NULL;//パーティーへのポインタ
	player_t* you = NULL;

	if (choose_yes()) {
		pt = scanfile("savedata", pt);
		you = pt;
		sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound
	}
	else {
		printw("\t\tユーザー名を入力してください\n\t\tなまえ : ");
		refresh();
		char name[16];
		wgetnstr(stdscr, name, sizeof(name) - 1);
		you = createPlayer(name,0); //player id=0
		pt = you;
		printw("\n\n");
		refresh();
		print_player(*pt);
		pushenter();
		printw("\t\tゲームを開始します\n");
		refresh();
		pushenter();
		printw("\t\tプロローグを見ますか？\n\t\t1 : はい\n\t\t2 : いいえ\n");
		refresh();

		if (choose_yes()) {
			clear();
			refresh();

			sndPlaySound(_T("war.wav"), SND_ASYNC); //Play sound
			Sleep(5000);
			sndPlaySound(_T("warfight.wav"), SND_ASYNC); //Play sound
			Sleep(3500);
			StopSound();
			printw("\t\t勇者 : うっ...");
			refresh();

			Sleep(3000);
			printw("\t\tこれで終わりなのか...？\n");
			refresh();

			Sleep(1000);
			sndPlaySound(_T("todome.wav"), SND_ASYNC); //Play sound
			Sleep(3500);
			(void)wgetch(stdscr);
			clear();       // PDCurses の画面クリア
			refresh();     // 表示を更新

			sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound
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
	
	map[NORMAL_SWORD.y][NORMAL_SWORD.x] = '*';

	int mapWidth = 0;
	int mapHeight = 0;
	int p_y = 0, p_x = 0;			//Position of player

	mapWidth = strlen(map[0]);
	mapHeight = sizeof(map) / sizeof(map[0]);
	char player[] = "$";
	p_y = 1;
	p_x = 2;//player first position (1,1)
	int stbt = 0;//startbattle
	int move = 0;
	int tmpx = 0, tmpy = 0;
	MAPTYPE maptype = MAP0; //初期化

//	sndPlaySound(_T("bgm1.wav"), SND_ASYNC); //Play sound
	for (; p_x != mapWidth-2;) {//町を出るまで繰り返し
			maptype = MAP0;
			map[p_y][p_x] = player[0];
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

			map[p_y][p_x] = ' ';
			tmpy = p_y;
			tmpx = p_x;
			switch (move) {
			case KEY_LEFT:
				p_x--;
				break;
			case KEY_RIGHT:
				p_x++;
				break;
			case KEY_UP:
				p_y--;
				break;

			case KEY_DOWN:
				p_y++;
				break;
			default:;
			}
			if (map[p_y][p_x] == ' ') {
				//NR
			}
			else if ( p_y== NORMAL_SWORD.y && p_x == NORMAL_SWORD.x ) {
				printw("\n\t\t%sを手に入れた！\n", NORMAL_SWORD.name);
				refresh();

				pushenter();
				equipitem(you, NORMAL_SWORD);
				print_player(*you);
				pushenter();

			}
			else if (p_y == 12 && p_x == 10) {
				printw("\n\n\t\t村人 : 旅の人かい？\n");
				refresh();
				pushenter();
				printw("\t\t村人 : どうやら魔王には強力な幹部がいるらしいんだ\n");
				refresh();
				(void)wgetch(stdscr);
				printw("\t\t村人 : そのうちの１体がこの町の近くの洞窟にいるとか...\n");
				refresh();
				(void)wgetch(stdscr);
				printw("\t\t村人 : はやく平和が戻るといいな\n");
				refresh();
				(void)wgetch(stdscr);
				p_y = tmpy;
				p_x = tmpx;
			}
			else if (p_y == 6 && p_x == 42) {
				printw("\n\n\t\t村人 : こまったわねぇ...\n");
				refresh();
				pushenter();
				printw("\t\t村人 : 東に魔物の洞窟があるせいで町からでるのもこわいわ。\n");
				refresh();
				(void)wgetch(stdscr);
				p_y = tmpy;
				p_x = tmpx;
			}
			else{
				p_y = tmpy;
				p_x = tmpx;
			}
			
			stbt = rand_n(RAND_BATTLE) ;//start battle for probability of 1/RAND_BATTTLE
			if (stbt == 1) {
				runBattle(pt,maptype);
				if (pt->hp <= 0) {
					endwin();
					return 0;
				}
				else {
					//NR
				}
				printw("\t\tゲームを続けますか？\n");
				refresh();
				printw("\t\t1 : つづける\n\t\t2 : やめる\n");
				refresh();
				if (!choose_yes()) {
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
	printw("\t\t町を出ました。\n");
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
	p_y = 11;
	p_x = 2;//player first position (11,2)
	sndPlaySound(_T("adventure.wav"), SND_ASYNC); 
	for (; p_y != 0 && p_x != mapWidth1 - 1 ;) {
		maptype = MAP1;
		map1[p_y][p_x] = player[0];
		printMap(map1, mapHeight1, MAP_MAXLEN + 1);
		move = 0;
		while (1) {
    		move = wgetch(stdscr);
    		if (move == KEY_LEFT || move == KEY_RIGHT || move == KEY_UP || move == KEY_DOWN) {
        		break;
    		}
		}

		map1[p_y][p_x] = ' ';
		tmpy = p_y;
		tmpx = p_x;
		switch (move) {
		case KEY_LEFT:
			p_x--;
			break;
		case KEY_RIGHT:
			p_x++;
			break;
		case KEY_UP:
			p_y--;
			break;

		case KEY_DOWN:
			p_y++;
			break;
		default:;
		}
		if (map1[p_y][p_x] == ' ') {
			//NR
		}
		else {
			p_y = tmpy;
			p_x = tmpx;
		}

		stbt = rand_n(RAND_BATTLE1);//start battle for probability of 1/RAND_BATTTLE
		if (stbt == 1) {
			runBattle(pt,maptype);
			if (pt->hp <= 0) {
				endwin();
				return 0;
			}
			else {
				//NR
			}
			printw("\t\tゲームを続けますか？\n");
			refresh();
			printw("\t\t1 : つづける\n\t\t2 : やめる\n");
			refresh();

			if (!choose_yes()) {
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