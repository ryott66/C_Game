#include <stdbool.h>

#pragma once

#define ONE 0x31
#define TWO 0x32
#define THREE 0x33
#define FOUR 0x34
#define ENTER 0x0d

#define STR_MAX 256 //静的配列サイズ定義に使う
#define MAP_MAXLEN 80

static const int HPFIR=35;//HP at first
static const int MPFIR=30;// MP at first
static const int SIZEMAX=20; //char_size

typedef enum {
    NOEQUIP = 0,
    WEAPON = 1,
    ARMOR = 2,
    SHIELD = 3,
    HELMET = 4
} EquipType;

typedef struct equip {
	EquipType type;
	char name[STR_MAX];
	int point;
	int x;
	int y;
} equip_t;

typedef struct player {
	int id;
	char name[STR_MAX]; 
	int level;
	int hp;  
	int mp; 
	int power;
	int protect;
	int speed;
	int exp;
	double g_rate;
	equip_t weapon;
	equip_t armor;
	equip_t shield;
	equip_t helmet;
	struct player* prev;
	struct player* next;
} player_t;

typedef struct enemy {
	char name[STR_MAX];
	int hp;
	int attack;
	int defence;
	int exp;
}enemy_t;

void printTitle();
void printslime();
void printdog();
void printboy();
void printgoblin();
void runBattle(player_t* dt, int maptype);
int calcDamage(int attack, int defence);
int rand_n(int n);//retrurn number 'random 1�`n' 
void printMap(char map[][MAP_MAXLEN + 1], int row, int column);
void swap(int* dt1, int* dt2);
int doublepower(int* dt1, int* dt2,int n);
void changeParam(int* dt, int type);
void print_player(player_t dt1);
player_t* createPlayer(char name[], int id);
int reqexp(player_t* dt);
void levelup(player_t* dt);
void printfile(char name[], player_t* pt);
player_t* scanfile(char name[], player_t* pt);
int hpmax(player_t* dt);
int mpmax(player_t* dt);
void save(player_t* pt);
bool choose_yes(void);
void pushenter(void);
void equipitem(player_t* dt, equip_t item);
int attackplayer(player_t* dt);
int defenceplayer(player_t* dt);
void StopSound(void);











