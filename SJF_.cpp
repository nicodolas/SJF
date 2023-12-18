#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 100000
typedef struct process
{
	int ID, WT, AT, BT, TAT;
}PS;
PS a[10];
void menu();
void SJF_DocQuyen();

void SJF_KhongDocQuyen();
void inGantt(PS a[], int& n);
void main()
{
	int choose;
	do
	{
		system("cls");
		menu();
		do
		{
			printf("\nChon menu: ");
			scanf("%d", &choose);
			if (choose < 0 || choose > 2)
				printf("\nKhong hop le. Hay nhap lai!");//asas
		} while (choose < 0 || choose > 2);
		switch (choose)
		{
		case 1:
		{
			SJF_DocQuyen();

			system("pause");
		} break;

		case 2:
		{
			SJF_KhongDocQuyen();

			system("pause");
		} break;
		case 0:
			exit(0);
			break;

		default:
			break;
		}
	} while (choose != 0);
}
void menu(){
	printf("************************************SJF************************************\n");
	printf("1.SJF Doc Quyen \n");
	printf("2.SJF Khong Doc Quyen\n");
	printf("0.Exit\n");
	printf("****************************************************************************\n");
}
void SJF_DocQuyen(){
	int bt[20], p[20], wt[20], tat[20], i, j, n, pos, temp;
	printf("Nhap so luong tien trinh:");
	scanf("%d", &n);

	printf("Nhap thoi gian xu ly\n");
	for (i = 0; i<n; i++)
	{
		printf("p%d:", i + 1);
		scanf("%d", &bt[i]);
		p[i] = i + 1;
	}


	for (i = 0; i<n; i++)
	{
		pos = i;
		for (j = i + 1; j<n; j++)
		{
			if (bt[j]<bt[pos])
				pos = j;
		}

		temp = bt[i];
		bt[i] = bt[pos];	//selection sort
		bt[pos] = temp;

		temp = p[i];
		p[i] = p[pos];		//selection sort
		p[pos] = temp;
	}

	wt[0] = 0;
	for (i = 1; i<n; i++)
	{
		wt[i] = 0;
		for (j = 0; j<i; j++)
			wt[i] += bt[j];
	}
	printf("Tien trinh	TG xu ly	TG cho	TG Hoan thanh\n");
	for (i = 0; i<n; i++)
	{
		tat[i] = bt[i] + wt[i];
		printf("%d	\t%d	\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
	}
	printf("\nGantt:\n");
	//Gantt
	for (int i = 0; i < n; i++)
	{
		printf("   P%d  ", p[i]);
	}
	printf("\n");
	printf("0---->");
	for (int i = 0; i < n - 1; i++)
	{
		printf("%d----->", tat[i]);
	}
	printf("%d\n", tat[n - 1]);

}
void SJF_KhongDocQuyen(){
	int n, temp[10];
	int count = 0, t = 0, min;
	printf("Nhap so luong tien trinh:\n");
	scanf("%d", &n);
	printf("Nhap thoi gian den va thoi gian xu ly tien trinh\n");
	printf("	AT	BT\n");
	for (int i = 0; i<n; i++)
	{
		printf("p%d\t", i + 1);
		scanf("%d%d", &a[i].AT, &a[i].BT);
		a[i].ID = i + 1;
		temp[i] = a[i].BT;		// copy TGXL vao temp
	}

	//Khoi tao tien trinh cuoi cung voi thoi gian MAX
	a[9].BT = MAX;
	for (t = 0; count != n; t++)
	{
		// for finding min burst
		min = 9;
		for (int i = 0; i<n; i++)
		{
			if (a[i].BT<a[min].BT && (a[i].AT <= t && a[i].BT>0))
			{
				min = i;
			}

		}

		a[min].BT = a[min].BT - 1;	//Tien tri duoc xu ly
						
		// if any process is completed
		if (a[min].BT == 0)
		{
			// one process complete
			count++;
			a[min].WT = t + 1 - a[min].AT - temp[min];	//thoi gian cho= TGHT -TGD -TGXL
			a[min].TAT = t + 1 - a[min].AT;				//thoi gian hoan thanh =TGHT -TGD
		}



	}

	// printing of the answer
	printf("Id	WT	TAT\n");
	for (int i = 0; i<n; i++)
	{
		printf("%d\t%d\t%d\n", a[i].ID, a[i].WT, a[i].TAT);
	}


}
