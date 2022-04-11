#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

char name1[10],name2[10],name3[10];
int duration1, duration2, duration3;
int prior1,prior2,prior3;
int time1, time2, time3;

struct processes
{
	char name[10];
	int duration;
	int prior;
	int time;
	char symb[5];
	int left;
};

int main()
{
	int minPriority,minDuration,currentInd;
	setlocale(LC_ALL,"RUS");
	struct processes process[3];
	
	for (int i=0;i<3;i++)
	{
		printf("Процесс %d: \n-----------------------\n",i);
		fflush(stdin);
		puts("Введите имя процесса: ");
		gets(process[i].name);
		
		puts("Введите длительность процесса: ");
		scanf("%d",&process[i].duration);
		
		puts("Введите приоритет процесса: ");
		scanf("%d",&process[i].prior);
		
		puts("Введите время появления процесса: ");
		scanf("%d",&process[i].time);
		
		process[i].left=process[i].duration;
	}
	
	int timeAll=process[0].duration+process[1].duration+process[2].duration;
	
	printf("%d\n",timeAll);
	
	puts(" Квант | P0 | P1 | P2 |");
	
	for (int i=1;i<=timeAll;i++)
	{
		
		
		minPriority=100;
		minDuration=timeAll;
		
		for(int k=0;k<3;k++)
		{
			if (process[k].time<=i && process[k].left>0)
			{
				if (process[k].prior<=minPriority)
				{
					minPriority=process[k].prior;
					if (process[k].duration<minDuration)
					{
						minDuration=process[k].duration;
						currentInd=k;
					}
				}
			}
		}
		
		for (int k=0;k<3;k++)
		{
			if(currentInd==k && process[k].left>0)
				strcpy(process[k].symb,"И");
			else if(process[k].time<=i && process[k].left>0)
				strcpy(process[k].symb,"Г");
			else
				strcpy(process[k].symb," ");
		}
		//printf("%7d|%4s|%4s|%4s|\n",i,process[0].symb,process[1].symb,process[2].symb);
		printf("%7d|%4s|%4s|%4s|\n",i,process[0].symb,process[1].symb,process[2].symb);
		process[currentInd].left--;
	}
	
	
	fflush(stdin);
	getchar();
	return 0;
	
}
