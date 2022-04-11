#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <iostream>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

struct pages
{

    int memory[200];
    int count;
};

struct processes
{

    char name[20];
    int size;
};

void memoryOut(struct pages *page,int qP,int sP);
void workMod(struct pages *page,int qP);
void addProc(struct pages *page,int qP,int sP, struct processes *process,int *qProc,int *freepages);
void delPage(struct pages *page,int sP,int *freepages);
void delProc(struct pages *page,int qP,int sP, struct processes *process,int *qProc,int *freepages);
void stats(struct pages *page,int qP,int sP, struct processes *process,int *qProc,int *freepages, int sizeM);

int main()
{
	setlocale(LC_ALL, "rus"); 
    ////////////////MEMORY PAGES
    int sizeM,quanP,sizeP;//memory size, quantity of pages, size of pagede
    puts("ÓÑÒÀÍÎÂÈÒÜ ÎÁÚÅÌ ÏÀÌßÒÈ:");
    scanf("%i",&sizeM);
    puts("ÓÑÒÀÍÎÂÈÒÜ ÊÎËÈ×ÅÑÒÂÎ ÑÒĞÀÍÈÖ:");
    scanf("%i",&quanP);
    sizeP=sizeM/quanP;
    struct pages page[quanP];
    int i,j;
    int freepages[quanP];
    for(i=0;i<quanP;i++)
    {
        for(j=0;j<sizeP;j++)
        {
            page[i].memory[j]=0;
        }
        page[i].count=0;
        freepages[i]=0;
    }
    ////////////////PROCESSES
    int qProc=0;//quantity of processes
    struct processes process[100];
    ////////////////MENU
    int item;//menu item
    do
    {
        memoryOut(page,quanP,sizeP);
        puts("\n");
        puts("~~Ìåíş~~");
        puts("\n");
        puts("1) ÄÎÁÀÂÈÒÜ ÍÎÂÛÉ ÏĞÎÖÅÑÑ");
        puts("2) ÓÄÀËÈÒÜ ÒÎ×ÍÓŞ ÑÒĞÀÍÈÖÓ");
        puts("3) ÓÄÀËÈÒÜ ÒÎ×ÍÛÉ ÏĞÎÖÅÑÑ");
        puts("4) ÌÎÄÓËÈĞÓÉÒÅ ÏĞÎÈÇÂÎÄÈÒÅËÜÍÎÑÒÜ");
        puts("5) ÑÒÀÒÈÑÒÈÊÀ");
        puts("6) ÂÛÕÎÄ");
        scanf("%i",&item);
        memoryOut(page,quanP,sizeP);
        switch(item)
        {
            case 1:
            {
                addProc(page,quanP,sizeP,process,&qProc,freepages);
                break;
            }
            case 2:
            {
                delPage(page,sizeP,freepages);
                break;
            }
            case 3:
            {
                delProc(page,quanP,sizeP,process,&qProc,freepages);
                break;
            }
            case 4:
            {
                workMod(page,quanP);
                break;
            }
            case 5:
            {
                stats(page,quanP,sizeP,process,&qProc,freepages,sizeM);
                puts("\nÍàæìèòå ÷òî óãîäíî, ÷òîáû ïğîäîëæèòü...");
                getch();
                break;
            }
            case 6: {break;}
            default:
            {
                puts("ÍÅÏĞÀÂÈËÜÍÛÉ ĞÅÃÈÑÒĞ, ïîæàëóéñòà, âñòàâüòå äğóãîé...");
                getch();
                break;
            }
        }
    }
    while(item!=6);
    return 0;
}

void stats(struct pages *page,int qP,int sP, struct processes *process,int *qProc,int *freepages, int sizeM)
{
    int i,j,k,local_count=0;
    float free=0, busy=0;
    int free1=0, busy1=0;
    float fp=0, bp=0;
    float perc;
    for(i=0;i<qP;i++)
    {
        for(j=0;j<sP;j++)
        {
            if((page+i)->memory[j]!=0)
            {
                local_count++;
                busy++;
                busy1++;
            }
            else
            {
                free++;
                free1++;
            }
        }
        if(local_count==0)
        {
            if(sP==0)
            {
                printf("Íîìåğ ñòğàíèöû. %2i Ñâîáîäíîé , ïàìÿòè îñòàëîñü - %.1f\n",i+1,fabs(sP-free));
            }
            else
            {
                printf("Íîìåğ ñòğàíèöû. %2i Ñâîáîäíîé, ïàìÿòè îñòàëîñü - %.1f\n",i+1,free);
            }
            fp++;
        }
        else
        {
            if(sP==0)
            {
                printf("Íîìåğ ñòğàíèöû %2i çàíÿò, ïàìÿòü çàíÿòà - %.1f\n",i+1,fabs(sP-busy));
            }
            else
            {
                printf("Íîìåğ ñòğàíèöû %2i çàíÿò, ïàìÿòü çàíÿòà - %.1f\n",i+1,busy);
            }
            bp++;
        }
        local_count=0;
        free=0;
        busy=0;
    }
    //printf("---%.0f-%.0f---", fp, bp);    
    perc=fp/(fp+bp);
    printf("Ñâîáîäíûå ñòğàíèöû - %.2f ïğîöåíòîâ", perc*100);
    printf("\nÎÁÙÈÉ ÎÁÚÅÌ ÏÀÌßÒÈ - %d\n",qP*sP-busy1);
}

void memoryOut(struct pages *page,int qP,int sP)
{
    system("cls");
    int i,j,k;
    for(i=0;i<qP;i++)
    {
        if(i%4==0)
        {
            printf("\n");
            for(k=0;k<sP*4+37;k++)
                printf("~");
            printf("\n");   
        }   
        else
            puts("\n");
        puts("\n");
        printf("×èñëî. - %2i [",i+1);
        for(j=0;j<sP;j++)
        {
            if((page+i)->memory[j]==0)
                printf("0");
            else
            {
                SetConsoleTextAttribute(console,4);
                printf("1");
                SetConsoleTextAttribute(console,7);
            }   
        }
        printf("] Êîë-âî îáğàùåíèé - %2i",(page+i)->count);
    }
    printf("\n\n");
}

void workMod(struct pages *page,int qP)
{
    int ranNum=rand()%10+1;//random quantity of treatments
    int ranP;//randomPage
    int i;
    for(i=0;i<ranNum;i++)
    {
        ranP=rand()%qP;
        (page+ranP)->count+=2;
    }
}

void addProc(struct pages *page,int qP,int sP, struct processes *process,int *qProc,int *freepages)
{
	setlocale(LC_ALL, "rus"); 
    int i,j,n=0;
    puts("ÄÎÁÀÂËÅÍÈÅ ÏĞÎÖÅÑÑÀ");
    puts("ÓÑÒÀÍÎÂÈÒÜ ÍÀÇÂÀÍÈÅ ÏĞÎÖÅÑÑÀ:");
    scanf("%s",(process+*qProc)->name);
    puts("ÓÑÒÀÍÎÂÈÒÜ ĞÀÇÌÅĞ ÏĞÎÖÅÑÑÀ:");
    scanf("%i",&((process+*qProc)->size));
    int size=(process+*qProc)->size;
    int a=size/sP;//quantity of pages
    int b=size%sP;//quantity of remaining memory
    int freePage=0;
    for(i=0;i<qP;i++)
        if(*(freepages+i)==0)
            freePage++;
    if(b==0)
        if(freePage>=a)
            n=1;
    if(b!=0)
        if(freePage>a)
            n=1;
    if(n==1)
    {
        for(i=0;i<qP;i++)
            if(*(freepages+i)==0 && size)
            {
                *(freepages+i)=*qProc+1;
                for(j=0;j<sP && size;j++)
                {
                    (page+i)->memory[j]=*qProc+1;
                    size-=1;
                }
                freePage-=1;
            }
    }
    else
    {
        if(size>qP*sP)
        {
            puts("ÎØÈÁÊÀ: ÍÅÄÎÑÒÀÒÎ×ÍÎ ÎÑÒÀËÎÑÜ ÏÀÌßÒÈ");
            puts("ÍÀÆÌÈÒÅ ËŞÁÓŞ ÊËÀÂÈØÓ ÄËß ÏĞÎÄÎËÆÅÍÈß...");
            getch();
        }
        else
        {
            int minCount,flag,minPos;
            while(size)
            {
                minCount=100;
                minPos=qP-1;
                for(i=qP-1;i>=0;i--)
                {
                    if((page+i)->count<=minCount)
                    {
                        if(*(freepages+i)!=*qProc+1)
                        {
                            minCount=(page+i)->count;
                            minPos=i;
                        }
                    }
                }
                (page+minPos)->count+=2;
                if(freePage)
                {
                    flag=1;
                    for(i=0;i<qP && flag;i++)
                        if(*(freepages+i)==0)
                        {
                            *(freepages+i)=*qProc+1;
                            flag=0;
                            freePage-=1;
                            for(j=0;j<sP && size;j++)
                            {
                                (page+i)->memory[j]=*qProc+1;
                                (page+i)->count=0;
                                size-=1;
                            }
                        }
                }
                else if(size)
                {
                    (page+minPos)->count=0;
                    for(i=0;i<sP;i++)
                    {
                        (page+minPos)->memory[i]=0;
                    }
                    for(i=0;i<sP && size;i++)
                    {
                        (page+minPos)->memory[i]=*qProc+1;
                        size-=1;
                    }
                    *(freepages+minPos)=*qProc+1;
                }
                (page+minPos)->count=0;
            }
        }
    }
    *qProc+=1;
    puts("ÏĞÎÖÅÑÑ ÄÎÁÀÂËÅÍ");
    puts("ÍÀÆÌÈÒÅ ËŞÁÓŞ ÊËÀÂÈØÓ ÄËß ÏĞÎÄÎËÆÅÍÈß...");
    getch();
}

void delPage(struct pages *page,int sP,int *freepages)
{
	setlocale(LC_ALL, "rus"); 
    puts("ÓÄÀËÅÍÈÅ ÑÒĞÀÍÈÖÛ");
    int number,i;
    puts("ÈÍÄÅÊÑ ÑÒĞÀÍÈÖÛ ÄËß ÓÄÀËÅÍÈß:");
    scanf("%i",&number);
    number-=1;
    (page+number)->count=0;
    for(i=0;i<sP;i++)
    {
        (page+number)->memory[i]=0;
    }
    *(freepages+number)=0;
    puts("ÑÒĞÀÍÈÖÀ ÁÛËÀ ÓÄÀËÅÍÀ");
    puts("ÍÀÆÌÈÒÅ ËŞÁÓŞ ÊËÀÂÈØÓ ÄËß ÏĞÎÄÎËÆÅÍÈß...");
    getch();
}

void delProc(struct pages *page,int qP,int sP, struct processes *process,int *qProc,int *freepages)
{
	setlocale(LC_ALL, "rus"); 
    puts("ÓÄÀËÅÍÈÅ ÏĞÎÖÅÑÑÀ");
    int number,i,j;
    puts("ÓÊÀÇÀÒÅËÜ ÏĞÎÖÅÑÑÀ ÓÄÀËÅÍÈß:");
    scanf("%i",&number);
    for(i=0;i<qP;i++)
    {
        if(*(freepages+i)==number)
        {
            *(freepages+i)=0;
            for(j=0;j<sP;j++)
            {
                (page+i)->memory[j]=0;
            }
        }
    }
    for(i=number-1;i<*qProc-1;i++)
    {
        *(process+i)=*(process+i+1);
    }
    *qProc-=1;
    puts("ÏĞÎÖÅÑÑ ÓÄÀËÅÍ");
    puts("ÍÀÆÌÈÒÅ ËŞÁÓŞ ÊËÀÂÈØÓ ÄËß ÏĞÎÄÎËÆÅÍÈß...");
    getch();
}

