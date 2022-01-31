#include "Logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
  

int main(int argc, char *argv[]) 
{	
	Data data;
	int timer=0;	
	State cur_state = ST_INIT;
	data.firstTimePlay = true;
	data.velocity =0;
		
	while(1)
	{
		Sleep(20);
		timer++;
		
		if(data.firstTimePlay == true || timer>20 - (data.velocity*5))	
		{
			timer=0;
			data.firstTimePlay = false;
			
			data.key = getState2Key(cur_state);
			
			int i=0;
			for(i;i<transSum;++i)
			{
				if(transTable[i].state == cur_state || transTable[i].state == ST_ANY)
				{
					if(transTable[i].isallow(&data))
					{
						cur_state = transTable[i].onAction(&data);
						break;
					}
				}
			}
		}	
						
		if(kbhit())
		{
			timer=0;
			data.key=getch();
			Sleep(10);
			
			int i=0;
			for(i;i<transSum;++i)
			{
				if(transTable[i].state == cur_state || transTable[i].state == ST_ANY)
				{
					
					if(transTable[i].isallow(&data))
					{					
						cur_state = transTable[i].onAction(&data);						
						break;
					}
				}
			}
		}	
		
		setCusPos(25,10);	
	}
	
	return 0;
}



