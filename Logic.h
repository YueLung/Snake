#ifndef _LOGIC_H_ 
#define _LOGIC_H_

#include <windows.h>
#include <stdio.h>

typedef unsigned int bool;
#define false 0
#define true 1

#define KY_UP 72
#define KY_DOWN 80
#define KY_LEFT 75
#define KY_RIGHT 77
#define KY_SPACE 32

typedef enum { ST_INIT , ST_UP , ST_DOWN , ST_LEFT , ST_RIGHT , ST_END , ST_ANY } State;

typedef struct Point
{
	int x;
	int y;
	struct Point *next;
}Point;

typedef struct data
{
	Point *snakeHead;
	Point *score;
	int key;
	bool firstTimePlay;
	int velocity;
}Data;

typedef struct
{
    State state;
    bool (*isallow)(Data*);
    State (*onAction)(Data*);
}Transition;

extern const Transition transTable[];
extern int transSum;

bool isAllowStateInit(Data*);
bool isAllowGetScore(Data*);
bool isAllowGameOver(Data*);
bool isAllowStateUp(Data*);
bool isAllowStateDown(Data*);
bool isAllowStateLeft(Data*);
bool isAllowStateRight(Data*);
bool isAllowNewGame(Data*);

State onInitEvent(Data*);
State onGetScoreEvent(Data*);
State onGameOverEvent(Data*);
State onPressEvent(Data*);
State onNewGameEvent(Data*);

void setCusPos(int,int);
void setPosValue(int,int,char);
void setPointOnScreen(Point*);
void initView();
bool isScoreOnSnake(int,int,Point*);

State getKey2State(int);
int getState2Key(State); 

Point* createSnake(int);
Point* createScore(Point*);
Point* getSnakeSecondLast(Point*);

#endif
