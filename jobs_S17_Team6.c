#include <stdio.h>
#include <string.h>

/**
 *SOURCES USED: https://deepanshubhatti.blogspot.com/2015/10/c-program-for-scheduling-algorithm.html?fbclid=IwAR2X72ksFL1A7GGlSiWVhZebFQxnb57YZaymu6GJDOn50bRU7cGRoKHp7tg
 https://deepanshubhatti.blogspot.com/2015/10/c-program-for-scheduling-algorithm-sjf.html?fbclid=IwAR3mGUoDo8tTc1cMvR5p9Jic0iKoP6Ijqjlx7vYhPwjKO4F4n5Lz2cevTx0
 *  
 */

typedef struct{
    char PID;
	int aTime;
	int bTime;
	int rTime;
	int wait;
	int exe;
}process;

int read(char PID[], int ArrivalTime[], int BurstTime[], int* NumberOfProcesses, int* Quanta)
{
	FILE *File;
	
	File = fopen("input.txt", "r");
	if(File == NULL)
	{
		printf("Error 404: File Not Found");
		return -1;
	}
	
	char Character;	
	int Number = 0, i, TemporaryNumber, Index = -2, NP = 0, NumberOfCommas = 0;
	int Values[11];
	
	for(i = 0; i < 11; i++) //Intializate Values
		Values[i] = 0;
			
	i = 0;
	while((Character = fgetc(File)) != EOF) //Read till the end of the File
		//printf("Character: %c\n", Character);
		if(Character > 64 && Character < 70) //Check if Character is between A, B, C, D, or E
		{
			PID[NP] = Character;
			NP++;
			//printf("Index after scanning a letter: %d\n", Index);
		}
		
		else if(Character == 44 || Character == 81) //Check if Character is a comma or a Q
		{
			if(NumberOfCommas > 0)
				if((i != 0) && (i % 2 == 0) && (Values[i] > Values[i - 2]))
				{
					printf("Arrival times must be greater than or equal to the arrival time before it");
					return -1;
				}
			
			else if((i % 2 == 1) && (Number < 0))
				{
					printf("Burst times must be greater than 0");
					return -1;
				}
			
			else
				{
					Values[i] = Number;
					i++;
				}
			
			Index++;
			Number = 0;
			NumberOfCommas++;
			//printf("Index after scanning a comma: %d\n", Index);
		}
		
		else if (Character == 61) //Check if Character is a =
			Number = 0;
		
		else if(Character > 47 && Character < 58) //Check if Character is an integer
		{		
			TemporaryNumber = Character - 48;
			
			//printf("i: %d, TemporaryNumber: %d\n", i, TemporaryNumber);
			
			Number = Number * 10 + (TemporaryNumber); //Convert char to int
			
			//printf("i: %d, Number: %d\n", i, Number);
		}
		
	fclose(File);
	
	File = fopen("input.txt", "r");
	if(File == NULL)
	{
		printf("Error 404: File Not Found");
		return -1;
	}
		
	//Get Quanta
	while((Character = fgetc(File)) != EOF)
		if (Character == 61)
			Number = 0;
			
		else if(Character > 47 && Character < 58)
		{		
			TemporaryNumber = Character - 48;
			
			//printf("TemporaryNumber: %d\n", TemporaryNumber);
			
			Number = Number * 10 + (TemporaryNumber); //Convert char to int
			
			//printf("Number: %d\n", Number);
			
			Values[2 * NP] = Number;
		}
	
	fclose(File);		
	
	/*\
	|*|	Format is PID, Arrival Time, and then Burst Time, 
	|*|	Indices start with 0, 
	|*|	if PID is disregarded, 
	|*|	Arrival Time will always be in even indices and Burst Time will always be in odd. 
	|*| 
	|*|	Each pair of Arrival Time and Burst Time is one process,
	|*|	Quanta is always after the processes.
	|*|	The formula is 2 * NumberOfProcesses.
	\*/

	*NumberOfProcesses = NP;
	*Quanta = Values[2 * NP];
	
	
	for(i = 0; i < NP; i++) //Transfer data from Values to ArrivalTime and BurstTime
	{
		ArrivalTime[i] = Values[2 * i];
		BurstTime[i] = Values[2 * i + 1];
	}
	
	for(i = 0; i < 11; i++)
		printf("Values[%d]: %d\n", i, Values[i]);
	printf("\nNumber of Processes: %d\n", *NumberOfProcesses);
	printf("PID\tArrival Time\tBurst Time\n");
	for(i = 0; i < 5; i++)
		printf("%c\t%d\t\t%d\n", PID[i], ArrivalTime[i], BurstTime[i]);
	printf("Quanta: %d\n", *Quanta);
}

void FCFS(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, char sFCFS[], float* FCFS_AWT)
{
	process tmp[NumberOfProcesses];
    int i, j, cTime = 0, totalWaitTime = 0;
    float aWait;

    for(i = 0; i < NumberOfProcesses; i++) {
        tmp[i].PID = PID[i];
        tmp[i].aTime = ArrivalTime[i];
        tmp[i].bTime = BurstTime[i];
        tmp[i].wait = 0;
    } 

    printf("\nFCFS\nGantt Chart: ");
    for ( i = 0; i < NumberOfProcesses; i++)
    {
        tmp[i].wait = tmp[i].wait + (cTime - tmp[i].aTime);
        for(j = 0; j < tmp[i].bTime; j++) {
            printf("%c", tmp[i].PID);
            cTime++;
        }
    }


    for(i = 0; i < NumberOfProcesses; i++) {
        totalWaitTime = totalWaitTime + tmp[i].wait;
    }

    (*FCFS_AWT) = (float)totalWaitTime/NumberOfProcesses;
    printf("\nAve Wait Time: %f\n\n", *FCFS_AWT);
}

int sjfChecker(process pr[], int NumberOfProcesses, int cTime) {
    int i, time = 99, res;
    for(i = 0; i < NumberOfProcesses; i++) {
        if(pr[i].aTime <= cTime && pr[i].exe == 0) {
            if(time > pr[i].bTime) {
                time = pr[i].bTime;
                res = i;
            }
        }
    }

    pr[res].exe = 1;
    return res;
}

void SJF(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, char sSJF[], float* SJF_AWT)
{

    process tmp[NumberOfProcesses];
    int i, j=0, curProcess, cTime = 0, totalWaitTime = 0;
    float aWait;
    int chart[50];

    for(i = 0; i < NumberOfProcesses; i++) {
        tmp[i].PID = PID[i];
        tmp[i].aTime = ArrivalTime[i];
        tmp[i].bTime = BurstTime[i];
        tmp[i].rTime = BurstTime[i];
        tmp[i].wait = 0;
        tmp[i].exe = 0;
    } 

    printf("SJF\nGantt Chart: ");
    for(i = 0; i < NumberOfProcesses; i++) {
        curProcess = sjfChecker(tmp, NumberOfProcesses, cTime);
        tmp[curProcess].wait = cTime - tmp[curProcess].aTime;
        cTime = cTime + tmp[i].bTime;
        aWait = aWait + tmp[i].wait;
        chart[i] = curProcess;   
    }

    for(i = 0; i < NumberOfProcesses; i++) {
        printf("%c", tmp[chart[i]].PID);
    }

    (*SJF_AWT) = aWait/NumberOfProcesses;
    printf("\nAve Wait Time: %f\n\n", *SJF_AWT);
}

void RR(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, int Quanta, char sRR[], float* RR_AWT)
{
	int i, j, cTime = 0, rem = NumberOfProcesses, flag = 0;
	float aWait = 0.0;
	process tmp[NumberOfProcesses];

	for(i = 0; i < NumberOfProcesses; i++) {
        tmp[i].PID = PID[i];
        tmp[i].aTime = ArrivalTime[i];
        tmp[i].bTime = BurstTime[i];
        tmp[i].rTime = BurstTime[i];
        tmp[i].wait = 0;
        tmp[i].exe = 0;
    } 
	i = 0;
	printf("Round Robin\nGantt Chart: ");

	for(cTime = 0, i = 0; rem != 0;) {
		if(tmp[i].rTime <= Quanta && tmp[i].rTime > 0) {
			cTime = cTime + tmp[i].rTime;
			printf("%c", tmp[i].PID);
			tmp[i].rTime = 0;
			flag = 1;
		}
		else if(tmp[i].rTime > 0) {
			tmp[i].rTime = tmp[i].rTime - Quanta;
			cTime = cTime + Quanta;
			printf("%c", tmp[i].PID);
		}
		if(tmp[i].rTime	== 0 && flag == 1) {
			rem--;
			tmp[i].wait = cTime - tmp[i].aTime - tmp[i].bTime;
			aWait = aWait + cTime - tmp[i].aTime - tmp[i].bTime;
			flag == 0;
		}
		if(i == NumberOfProcesses-1) {
			i = 0;
		}
		else if(tmp[i+1].aTime <= cTime) {
			i++;
		}
		else {
			i = 0;
		}
	}

	printf("\n%f\n", aWait);

	(*RR_AWT) = aWait / NumberOfProcesses;

	printf("\nAve Wait Time: %f\n", *RR_AWT);
}

int main (void)
{
	char PID[5], sFCFS[99], sSJF[45], sSTR[45], sRR[45];
	float FCFS_AWT = 0, SJF_AWT = 0, STR_AWT = 0, RR_AWT = 0;
	int ArrivalTime[5], BurstTime[5], NumberOfProcesses, Quanta = 0, i;
	
	for(i = 0; i < 5; i++) //Initialize PID, ArrivalTime, and BurstTime
	{
		PID[i] = 0;
		ArrivalTime[i] = 0;
		BurstTime[i] = 0;
	}
	
	for(i = 0; i < 5; i++) //Initialize sFCFS, sSJF, sSTR, and sRR
	{
		sFCFS[i] = 0;
		sSJF[i] = 0;
		sSTR[i] = 0;
		sRR[i] = 0;
	}
	
	read(PID, ArrivalTime, BurstTime, &NumberOfProcesses, &Quanta);
	
	FCFS(PID, ArrivalTime, BurstTime, NumberOfProcesses, sFCFS, &FCFS_AWT);
	SJF (PID, ArrivalTime, BurstTime, NumberOfProcesses, sSJF, &SJF_AWT);
	//STR (PID, ArrivalTime, BurstTime, NumberOfProcesses, sSTR, &STR_AWT);
	RR(PID, ArrivalTime, BurstTime, NumberOfProcesses, Quanta, sRR, &RR_AWT);
	
	//write(Quanta, FCFS_AWT, SJF_AWT, STR_AWT, RR_AWT, sFCFS, sSJF, sSTR, sRR);

	system("pause");
}
