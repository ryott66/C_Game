#pragma once
#define STR_MAX	256
#define MAP_MAXLEN 80

#define HPFIR 35//HP at first
#define MPFIR 30// MP at first
#define WEAPON	1
#define ARMOR	2
#define SHIELD	3
#define	HELMET	4
#define	NOEQUIP	0
#define SIZEMAX 20

typedef struct equip {	//����
	int type;		//�^�C�v�i�Ȃ�=NOEQUIP�j
	char name[STR_MAX];	//����
	int point;		//�C���l
	int x;
	int y;
} equip_t;

typedef struct player {  //�Q�[���v���C���[�^
	int id;			//�L�����N�^ID
	char name[STR_MAX]; 	//���O
	int level;		//���x��
	int hp;        //������傭
	int mp;         //mp
	int power;		//������
	int protect;		//�݂̂܂���
	int speed;		//�f����
	int exp;			//�o���l
	double g_rate;		//������
	equip_t weapon;	//����
	equip_t armor;	//�Z
	equip_t shield;	//��
	equip_t helmet;	//��
	struct player* prev;	//�O�̃L�����ւ̃|�C���^
	struct player* next;	//���̃L�����ւ̃|�C���^
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
player_t* createPlayer(char name[]);
int reqexp(player_t* dt);
void levelup(player_t* dt);
void printfile(char name[], player_t* pt);
player_t* scanfile(char name[], player_t* pt);
int hpmax(player_t* dt);
int mpmax(player_t* dt);
void save(player_t* pt);
char yesno(void);
void pushenter(void);
equip_t equipitem(player_t* dt, equip_t item);
int attackplayer(player_t* dt);
int defenceplayer(player_t* dt);











