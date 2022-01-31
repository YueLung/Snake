#include "Logic.h"

const int HEIGHT = 10;
const int WIDTH  = 20;

const int  STARTPOS_X = 15;
const int  STARTPOS_Y = 5;

const char POINT_GRAPGH='*';
const char EMPTY_GRAPGH=' ';

const int INIT_SNAKE_X = 8 ;
const int INIT_SNAKE_Y = 5 ;

const int INIT_SNAKE_BODY_SUM = 2; 

const Transition transTable[]={
						 {ST_INIT ,&isAllowStateInit ,&onInitEvent    },
						 {ST_ANY  ,&isAllowGetScore  ,&onGetScoreEvent},	
						 {ST_ANY  ,&isAllowGameOver  ,&onGameOverEvent},	 
						 {ST_UP   ,&isAllowStateUp   ,&onPressEvent   },
						 {ST_DOWN ,&isAllowStateDown ,&onPressEvent   },
						 {ST_LEFT ,&isAllowStateLeft ,&onPressEvent   },
						 {ST_RIGHT,&isAllowStateRight,&onPressEvent   },
						 {ST_END  ,&isAllowNewGame	 ,&onNewGameEvent }
						};
						
int transSum = sizeof(transTable)/sizeof(*transTable);						

//********isAllow Fun**********
bool isAllowStateInit(Data *data)
{
	return true;
}

bool isAllowGetScore(Data *data)
{
	if(!data->snakeHead)
		return false;
	int next_x = data->snakeHead->x;
	int next_y = data->snakeHead->y;
	
	switch(data->key)
	{
		case KY_RIGHT:
			next_x++;
			break;	
		case KY_LEFT:
			next_x--;
			break;
		case KY_DOWN:
			next_y++;
			break;
		case KY_UP:
			next_y--;
			break;		
	}
	if(next_x==20) next_x=0;
	if(next_x==-1) next_x=19;
	if(next_y==10) next_y=0;
	if(next_y==-1) next_y=9;
	
	if(next_x == data->score->x && next_y == data->score->y)
	{
		return true;
	}	
	
	return false;
}

bool isAllowGameOver(Data *data)
{
	if(!data->snakeHead)
		return false;
	Point *detectSnake = data->snakeHead->next->next; //從第3個開始檢查 
	
	int next_x = data->snakeHead->x;
	int next_y = data->snakeHead->y;
	
	switch(data->key)
	{
		case KY_RIGHT:
			next_x++;
			break;	
		case KY_LEFT:
			next_x--;
			break;
		case KY_DOWN:
			next_y++;
			break;
		case KY_UP:
			next_y--;
			break;		
	}
	if(next_x==20) next_x=0;
	if(next_x==-1) next_x=19;
	if(next_y==10) next_y=0;
	if(next_y==-1) next_y=9;
	
	while(detectSnake!=NULL)
	{
		if(next_x==detectSnake->x && next_y==detectSnake->y)
			return true;
			
		detectSnake = detectSnake->next;	
	}
}

bool isAllowStateUp(Data *data)
{
	int keyCode = data->key;
	
	if(keyCode == KY_UP || keyCode == KY_LEFT || keyCode == KY_RIGHT)
		return true;
	
	return false;	
}

bool isAllowStateDown(Data *data)
{
	int keyCode = data->key;
	
	if(keyCode == KY_DOWN || keyCode == KY_RIGHT || keyCode == KY_LEFT)
		return true;
	
	return false;	
}

bool isAllowStateLeft(Data *data)
{
	
	int keyCode = data->key;
	
	if(keyCode == KY_LEFT || keyCode == KY_UP || keyCode == KY_DOWN)
		return true;
	
	return false;	
}

bool isAllowStateRight(Data *data)
{
	int keyCode = data->key;
	
	if(keyCode == KY_RIGHT || keyCode == KY_UP || keyCode == KY_DOWN)
		return true;
	
	return false;	
}

bool isAllowNewGame(Data *data)
{
	int keyCode = data->key;
	
	if(keyCode == KY_SPACE)
		return true;
	
	return false;
}
//*****************************

//*********onAction*********
State onInitEvent(Data *data)
{
	initView();
	
	int tmp = 0;
	do{
		setCusPos(7,12);	
		printf("                               ");
		setCusPos(7,12);
		printf("輸入難度(1~3):");
		scanf("%d",&tmp);
		
	}while(tmp<1 || tmp>3);
	
	data->velocity = tmp;
	
	
	data->snakeHead = createSnake(INIT_SNAKE_BODY_SUM);
	data->score = createScore(data->snakeHead);
	setPointOnScreen(data->snakeHead);
	setPointOnScreen(data->score);
	return ST_LEFT;
}

State onGetScoreEvent(Data *data)
{
	setPosValue(data->score->x,data->score->y,'*');

	data->score->next = data->snakeHead;
	data->snakeHead = data->score;
	
	setCusPos(25,10);	

	data->score = createScore(data->snakeHead);
	setPointOnScreen(data->score);
	
	return getKey2State(data->key);
}

State onGameOverEvent(Data *data)
{
	while(data->snakeHead)
	{
		Point *tmp = data->snakeHead->next;
		free(data->snakeHead);
		data->snakeHead=tmp;
	}

	if(data->score)
	{
		free(data->score);
		data->score=NULL;
	}
	setCusPos(7,12);
	printf("Game Over!!!!!!!\r\n");
	setCusPos(4,13);
	printf("Press Space To Start New Game");
	return ST_END;
}

State onPressEvent(Data* data)
{
	State returnState = ST_ANY;
	Point *secondLast = getSnakeSecondLast(data->snakeHead);
	Point *last = secondLast->next;
	setPosValue(last->x,last->y,EMPTY_GRAPGH);
	setCusPos(25,10);
	
	switch(data->key)
	{
		case KY_RIGHT:
			last->x = data->snakeHead->x + 1;
			last->y = data->snakeHead->y;
			returnState = ST_RIGHT;
			break;	
		case KY_LEFT:
			last->x = data->snakeHead->x - 1;
			last->y = data->snakeHead->y;
			returnState = ST_LEFT;
			break;
		case KY_DOWN:
			last->x = data->snakeHead->x;
			last->y = data->snakeHead->y + 1;
			returnState = ST_DOWN;
			break;
		case KY_UP:
			last->x = data->snakeHead->x;
			last->y = data->snakeHead->y - 1;
			returnState = ST_UP;
			break;		
	}
	if(last->x==WIDTH)  last->x=0;
	if(last->x==-1)     last->x=19;
	if(last->y==HEIGHT) last->y=0;
	if(last->y==-1) 	last->y=9;
	
	setPosValue(last->x,last->y,POINT_GRAPGH);
	
	secondLast->next = NULL;
	last->next = data->snakeHead;
	data->snakeHead = last;
	
	return returnState;
}

State onNewGameEvent(Data *data)
{
	data->firstTimePlay = true;
	return ST_INIT;
}

//******************************

void setCusPos(int x , int y)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;  
    Pos.X = STARTPOS_X+(2*x); 
	Pos.Y = STARTPOS_Y+y;
    SetConsoleCursorPosition(hOut, Pos);
}

void setPosValue(int x , int y , char index)
{
	setCusPos(x,y);
	printf("%c",index);

}

void initView()
{
	setCusPos(0,-3);
	printf("                                               ");
	
	int i = 0;
	
	for(i=-1;i<21;++i)
	{
		setCusPos(i,-1);
		printf("-");
		setCusPos(i,10);
		printf("-");
	}
	
	for(i=0;i<10;++i)
	{
		setCusPos(-1,i);
		printf("|                                         |\n");
	}
	
	setCusPos(7,12);
	printf("                              ");
	setCusPos(4,13);
	printf("                               ");
	
	setCusPos(25,10);
}

bool isScoreOnSnake(int x , int y ,Point* snakeHead)
{
	struct Point *ptr = snakeHead;
	
	while(ptr!=NULL){
		if(x==ptr->x && y==ptr->y)
			return true;
		ptr = ptr->next;	
	}
	
	return false;
}


Point* createSnake(int bodyNum)
{
	Point *snakeHead = (struct Point*)malloc(sizeof(struct Point));
	snakeHead->x = INIT_SNAKE_X;
	snakeHead->y = INIT_SNAKE_Y ;
	
	Point *ptr = snakeHead;
	
	int i = 1;
	for(i ;i<=bodyNum;++i)
	{
		Point *tmp = (struct Point*)malloc(sizeof(struct Point));
		tmp->x = INIT_SNAKE_X+i;
		tmp->y = INIT_SNAKE_Y;
		ptr->next = tmp;
		ptr = ptr->next;
	}
	
	ptr->next = NULL;	
	return snakeHead;	
}

Point* createScore(Point *snakeHead)
{
	int x ,y;
	
	do{
		srand(time(NULL));
		
		x = (rand()% 19);
		y = (rand()% 9);
		
	}while(isScoreOnSnake(x,y,snakeHead));	
	
	Point* score = (struct Point*)malloc(sizeof(struct Point));
	score->x = x;
	score->y = y;
	score->next= NULL;
	
	return score;
}

void setPointOnScreen(Point *snake)
{
	Point *ptr = snake;

	while(ptr!=NULL){
		setCusPos(ptr->x,ptr->y);
		printf("*");
		ptr = ptr->next; 
	}
	
	setCusPos(25,10);
}

Point* getSnakeSecondLast(Point *snakeHead)
{
	Point *res = snakeHead;
	
	while(res->next->next!=NULL)
		res = res->next;
				
	return res;
}

State getKey2State(int key)
{
	switch(key)
	{
		case KY_RIGHT:
			return ST_RIGHT;
			break;	
		case KY_LEFT:
			return ST_LEFT;
			break;
		case KY_DOWN:
			return ST_DOWN;
			break;
		case KY_UP:
			return ST_UP;
			break;		
	}
}

int getState2Key(State state)
{
	switch(state)
	{
		case ST_RIGHT:
			return KY_RIGHT;
			break;	
		case ST_LEFT:
			return KY_LEFT;
			break;
		case ST_DOWN:
			return KY_DOWN;
			break;
		case ST_UP:
			return KY_UP;
			break;		
	}
}

