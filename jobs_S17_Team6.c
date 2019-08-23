

#include <stdio.h>
#include <string.h>

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
	int Number = 0, i, TemporaryNumber, Index = -1, NP = 0;
	int Values[11];
	
	for(i = 0; i < 11; i++) //Intializate Values
		Values[i] = 0;
			
	i = 0;
	while((Character = fgetc(File)) != EOF) //Read till the end of the File
	{
		//printf("Character: %c\n", Character);
		if(Character > 64 && Character < 70) //Check if Character is between A, B, C, D, or E
		{
			PID[NP] = Character;
			NP++;
			//printf("Index after scanning a letter: %d\n", Index);
		}
		
		else if(Character == 44) //Check if Character is a comma
		{
			Index++;
			Number = 0;
			//printf("Index after scanning a comma: %d\n", Index);
		}
		
		else if (Character == 61)
			Number = 0;
		
		else if(Character > 47 && Character < 58) //Check if Character is an integer
		{		
			TemporaryNumber = Character - 48;
			
			//printf("i: %d, TemporaryNumber: %d\n", i, TemporaryNumber);
			
			Number = Number * 10 + (TemporaryNumber); //Convert char to int
			
			//printf("i: %d, Number: %d\n", i, Number);
			
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
		}
	}

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

int write(int Quanta, float FCFS_AWT, float SJF_AWT, float STR_AWT, float RR_AWT, char sFCFS[10], char sSJF[10], char sSTR[10], char sRR[10])
{
	FILE* File = fopen("input.txt", "a");
	if(File == NULL)
	{
		printf("Error 404: File Not Found");
		return -1;
	}
		
	fprintf(File, "\n");
	
	//Append First Come First Serve
	fprintf(File, "*FCFS*\n%s\nAWT = %f", sFCFS, FCFS_AWT);
	fprintf(File, "\n\n");
	
	//Append Shortest Job First
	fprintf(File, "*SJF*\n%s\nAWT = %f", sSJF, SJF_AWT);
	fprintf(File, "\n\n");
	
	//Append Shortest Time Remaining
	fprintf(File, "*STR*\n%s\nAWT = %f", sSTR, STR_AWT);
	fprintf(File, "\n\n");
	
	//Append Round Robin
	fprintf(File, "*RR Q= %d*\n%s\nAWT = %f", Quanta, sRR, RR_AWT);
	
	fclose(File);
}

 /*
<**
 \*
	void BubbleSort(char PID[], int ArrivalTime[], int BurstTime[])
	{
		int i, j, temp;
		
		for(i = 0; i < NumberOfProcesses; i++)
			for(j = 0; j < (NumberOfProcesses - i - 1); j++)
				if(ArrivalTime[j] > ArrivalTime[j + 1])
				{
					//Sort PID
					temp = PID[j];
					PID[j] = PID[j + 1];
					PID[j + 1] = temp;
					
					//Sort ArrivalTime
					temp = ArrivalTime[j];
					ArrivalTime[j] = ArrivalTime[j + 1];
					ArrivalTime[j + 1] = temp1;
					
					//Sort BurstTime
					temp = BurstTime[j];
					BurstTime[j] = BurstTime[j + 1];
					BurstTime[j + 1] = temp;
				}
	}
*\
**>
*/

void FCFS(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, char sFCFS[], float* FCFS_AWT)
{
	int i, j, ServiceTime = 0;
		
	for(j = 0; j < NumberOfProcesses; j++) //Run through all of the processes
	{
		for(i = 0; i < BurstTime[j]; i++) //Gantt Chart
		sFCFS[i + j] = 'A' + j;
				
		//Calculating Total Waiting Time
		ServiceTime += ArrivalTime[j];
		(*FCFS_AWT) += ServiceTime - BurstTime[j];
	}
	
	//Calculating Average Waiting Time
	(*FCFS_AWT) /= NumberOfProcesses;
	
	printf("sFCFS = %s\n", sFCFS);
	printf("FCFS AWT = %f\n", *FCFS_AWT);
}

void SJF(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, char sSJF[], float* SJF_AWT)
{








}


void STR(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, char sSTR[], float* STR_AWT)
{








}

void RR(char PID[], int ArrivalTime[], int BurstTime[], int NumberOfProcesses, int Quanta, char sRR[], float* RR_AWT)
{
	int i, j, h, RemainingTime[5], maximum = 0, loops;
	
	for(i = 0; i < NumberOfProcesses; i++) 
	{
		RemainingTime[i] = BurstTime[i]; //Transfer BurstTime to RemainingTime
		if (BurstTime[i] > maximum) //Find longest process
	       maximum = BurstTime[i];
	}
	
	printf("Longest Process = %d\n", maximum);
	
	/*\ 
	|*|	Longest process divide by quanta will cover all of the BurstTimes
	|*|	But the longest process may have an odd numbered length, as such add one more loop
	\*/  
	
	loops = maximum / Quanta;
	
	printf("Number of loops required = %d\n", loops + 1);
	
	for(h = 0; h < loops + 1; h++)
		for(i = 0; i < NumberOfProcesses; i++)
		{
			if((RemainingTime[i] > 0) && (RemainingTime[i] >= Quanta)) //Skip over finished processes
				for(j = 0; j < Quanta; j++)
					sRR[i + j] = 'A' + i;
			else if (RemainingTime[i] < Quanta)	//Prevent excess entries
				for(j = 0; j < RemainingTime[i]; j++) 
					sRR[i + j] = 'A' + i;
			
			RemainingTime[i] -= Quanta; //Decrement remaining time after every pass
		}
	
	
	printf("Quanta = %d\n", Quanta);
	printf("sRR = %s\n", sRR);
	printf("RR AWT = %f\n", *RR_AWT);
}

int main (void)
{
	char PID[5], sFCFS[45], sSJF[45], sSTR[45], sRR[45];
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
	
	//FCFS(PID, ArrivalTime, BurstTime, NumberOfProcesses, sFCFS, &FCFS_AWT);
	//SJF (PID, ArrivalTime, BurstTime, NumberOfProcesses, sSJF, &SJF_AWT);
	//STR (PID, ArrivalTime, BurstTime, NumberOfProcesses, sSTR, &STR_AWT);
	RR  (PID, ArrivalTime, BurstTime, NumberOfProcesses, Quanta, sRR, &RR_AWT);
	
	//write(Quanta, FCFS_AWT, SJF_AWT, STR_AWT, RR_AWT, sFCFS, sSJF, sSTR, sRR);
}
