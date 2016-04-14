#include<stdio.h>
#include<conio.h>

struct time
{
	int job_no;
	int alloc_time[10];
	int arriv_time[10];
	int cpu_burst;
	int flag;
	int cnt ;
}t[10];

struct cal_time
{
	int tt;
	int wt;
}ct[10];


void main()
{
	int i,wt[10][10]={0},cnt,cpu[10]={0},k,m,gantt[20]={0},alloc,j,temp,temp1,temp2,flag=0,qua;
	clrscr();

	printf("Enter no.of processes:-\t");
	scanf("%d",&m);
	for(i=0;i<m;i++)
	{
		printf("\n\tEnter process number:-\t");
		scanf("%d",&t[i].job_no);
		printf("\n\tEnter arrival time of the process %d:-\t",t[i].job_no);
		scanf("%d",&t[i].arriv_time[0]);
		printf("\n\tEnter cpu burst time of the process %d:-\t",t[i].job_no);
		scanf("%d",&t[i].cpu_burst);
	}
	printf("\n\tEnter quantum value:-\t");
	scanf("%d",&qua);

	for(i=0;i<m;i++)
		cpu[i]=t[i].cpu_burst;
//-----------------------------------------------------------------
	i=0;j=0;k=0;
	cnt=0;
	gantt[0]=t[0].arriv_time[0];
	t[0].alloc_time[0]=t[0].arriv_time[0];
	//t[0].cnt++;
	while(!flag)
	{
		if(t[i].arriv_time[t[i].cnt]<t[i+1].arriv_time[k])
		{
			if(t[i].arriv_time[t[i].cnt]<(t[i].arriv_time[0]+t[i].cpu_burst))
			{
				if(cpu[i]>qua)
				{
					gantt[cnt+1]= gantt[cnt]+qua;
					t[i].arriv_time[t[i].cnt+1]=gantt[cnt+1];
					t[i].alloc_time[t[i].cnt]=gantt[cnt];
					cpu[i]=cpu[i]-qua;
					j++;
					cnt++;
					t[i].cnt++;
				}
				else
				{
					gantt[cnt+1]=gantt[cnt]+cpu[i];
					t[i].arriv_time[t[i].cnt+1]=gantt[cnt+1];
					t[i].alloc_time[t[i].cnt+1]=gantt[cnt];
					cpu[i]=0;
					t[i].flag=1;
				}
			}
			else
				break;
		}
		else
		{
			i++;
			flag=1;
			j=0;
		}
	}

	i=1;
	j=0;
	while(gantt[cnt]<38)
	{
		if(i==m)
		{
			i=0;
		}
		if(t[i].flag!=1)
		{
			if(cpu[i]>qua)
			{
				gantt[cnt+1]=gantt[cnt]+qua;
				t[i].arriv_time[t[i].cnt+1]=gantt[cnt+1];
				t[i].alloc_time[t[i].cnt]=gantt[cnt];
				cpu[i]=cpu[i]-qua;
				j++;
				cnt++;
				t[i].cnt++;
			}
			else
			{
				gantt[cnt+1]=gantt[cnt]+cpu[i];
				t[i].arriv_time[t[i].cnt+1]=gantt[cnt+1];
				t[i].alloc_time[t[i].cnt]=gantt[cnt];
				t[i].flag=1;
				cpu[i]=0;
				cnt++;
				t[i].cnt++;
				j++;
			}
		}
		i++;
	}

	for(i=0;i<7;i++)
	{
		for(j=0;j<t[i].cnt;j++)
		{
			wt[i][j]=t[i].alloc_time[j]-t[i].arriv_time[j];
			ct[i].wt=ct[i].wt+wt[i][j];
		}
		ct[i].tt=ct[i].wt+t[i].cpu_burst;
	}

	for(i=0;i<20;i++)
		printf("\t%d",gantt[i]);
	printf("\n");
	printf("\nJob_no\tAlloc_tim\tArriv_tim\tCPU_burst\tWT\tTT");
	for(i=0;i<m;i++)
	{
		printf("\n\n%d\t%d\t\t%d\t\t%d\t\t%d\t%d",t[i].job_no,t[i].alloc_time[0],t[i].arriv_time[0],t[i].cpu_burst,ct[i].wt,ct[i].tt);
	   //	getch();
	}
	getch();
}