#include <stdio.h>
#include <queue>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
using namespace std;
const int M=505;
int n;        //迷宫大小 
int flag;     //判断迷宫是否为通路  0--否  1--是 
struct node {
	int x,y;   //当前位置的坐标 
	int fromx,fromy;   //当前位置坐标由上一个坐标的转移 
}path[M][M],NOW;
queue<node>Q;

int vis[M][M];       //标记数组，记录路径 
char MAP[M][M];      //地图储存 
char MAPdfs[M][M];   //dfs的地图使用 
char MAPbfs[M][M];   //bfs的地图使用 
int turnx[4] = {0, 1, 0, -1};  //x坐标的移动数组 
int turny[4] = {1, 0, -1, 0};  //y坐标的移动数组
 
void Start();    //初始化 
void Again();   //再次赋值 
void Make();    //生成迷宫 
void dfs(int s,int y,int step);   // dfs寻找迷宫路径 
void bfs();                       // bfs寻路 
void vispath(int x,int y);        // bfs记录迷宫路径
void Print_maze();                //打印迷宫 
void Print_bfs();                 //打印 bfs寻路路径 
void Print_dfs(int step);         //打印 dfs寻路路径 

int main() {
	cout<<"\n\n\n\n\n";
	cout<<"\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t------ 迷 宫 问 题 求 解  ------"<<endl;
	cout<<"\t\t\t\t\t------                    ------"<<endl;
	cout<<"\t\t\t\t\t--------- 程 序 设 计  ---------"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t---------------- code by LiYue -"<<endl;
	cout<<"\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	system("pause"); 
	while (1) {
		Start();
		flag=0;
		string choice;
		{
			system("cls");
			system("color 0F");
			cout<<"\n\n\n\n\n";
			cout<<"\n\t\t\t*******************************\n";
			cout<<"\t\t\t*\t                      *";
			cout<<"\n\t\t\t*\t请选择您的操作：      *\n";
			cout<<"\t\t\t*\t                      *";
			cout<<"\n\t\t\t*\t1.创建迷宫            *\n";
			cout<<"\t\t\t*\t                      *";
			cout<<"\n\t\t\t*\t2.退出程序            *\n";
			cout<<"\t\t\t*\t                      *";
			printf("\n\t\t\t*******************************\n");
			cin>>choice;     //用户选择操作 
			while (choice!="1"&&choice!="2") {    //错误特判 
				cout<<"\t\t\t输错了哦，请重新输入（ ￣ ▽ ￣ ）\n";
				cin>>choice;
			}
			if (choice == "2") return 0;
			Make();  //制作迷宫 
		}
		while (1) {
			Print_maze(); 
			cout<<"\n\t\t\t*********************************\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t请选择寻找出口的方式:   *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t1.dfs深度优先搜索       *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t2.bfs广度优先搜索       *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t3.返回上一界面          *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*********************************\n";
			
//			cout<<"\n请选择寻找出口的方式：\n"; 
//			cout<<"1.dfs深度优先搜索\n"; 
//			cout<<"2.bfs广度优先搜索\n"; 
//			cout<<"3.返回上一界面\n"; 
			
			flag=0;
			cin>>choice;     //用户选择操作 
			while (choice!="1"&&choice!="2"&&choice!="3") {  //错误特判 
				cout<<"\t\t\t输错了哦，请重新输入（ ￣ ▽ ￣ ）\n";
				cin>>choice;
			}
			
			if (choice == "1") flag=0, dfs(1,1,0);
			else if (choice == "2") vispath(n,n), Print_bfs();
			else if (choice == "3") break;
			
			cout<<"\n\t\t\t按 1 返回上一界面（ ￣ ▽ ￣ ）\n";
			cin>>choice;
			while (choice!="1") {   //错误特判 
				cout<<"\t\t\t输错了哦，请重新输入（ ￣ ▽ ￣ ）\n";
				cin>>choice; 
			}
			system("cls");
		}
	}
	return 0;
}

void Start() {      //初始化 
	memset(vis,0,sizeof(vis));
	memset(MAP,0,sizeof(MAP));
	memset(MAPdfs,0,sizeof(MAPdfs));
	memset(MAPbfs,0,sizeof(MAPbfs));
	while (!Q.empty()) Q.pop() ; 
}

void Again() {     //把 MAP中的值赋给 MAPbfs和 MAPdfs中 
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			MAPbfs[i][j] = MAP[i][j];
			MAPdfs[i][j] = MAP[i][j];
		}
	}
	MAPbfs[1][1]=MAPdfs[1][1]=MAP[1][1]='S';
	MAPbfs[n][n]=MAPdfs[n][n]=MAP[n][n]='E';
}

void Make() {
	system("cls");
	cout<<"\n\t\t\t请输入制作随机迷宫边长（边长需大于1）：\n";
	cin>>n;
	//system("cls");  //清屏 
	printf("\n\t\t\t迷宫制作中请等待1~3秒");
	while (1) {
		srand(time(NULL));     //以当前时间为种子，生成随机数
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				int num=rand()%3;  //根据生成的随机数设置墙/路 
				if (num==0) {
					MAP[i][j]='X';  //墙 
				} else {
					MAP[i][j]='O';  //路 
				}
			}
		}
		Again();     //把 MAP中的值赋给 MAPbfs和 MAPdfs中 
		bfs();    //判断是否通路，是则退出函数，否则继续生成迷宫 
		if (flag==1) break; 
	}
}

void dfs(int x,int y,int step) {
	if (flag) return;
	if (x==n&&y==n) {    //找到终点 
		flag=1; 
		Sleep(3000);
		Print_dfs(step);   //打印路径 
		Again();     //把 MAP中的值赋给 MAPbfs和 MAPdfs中 
		return;
	}
	for (int i=0;i<4;i++) {      //遍历该点的东西南北四个方向 
		int nextx=x+turnx[i];
		int nexty=y+turny[i];
		if (nextx>=1&&nextx<=n&&nexty>=1&&nexty<=n&&(MAPdfs[nextx][nexty]=='S'||MAPdfs[nextx][nexty]=='O'||MAPdfs[nextx][nexty]=='E')) {  //边界判断与通路判断 
			MAPdfs[nextx][nexty]='o';
			if (nextx!=n||nexty!=n) Print_dfs(step);    //打印路径 
			dfs(nextx,nexty,step+1);    //从该点继续寻找路径 
			if (flag) return;        //若找到通路，则直接回溯 
			MAPdfs[nextx][nexty]='x';   //否则 将该店设为未访问状态 
			Print_dfs(step);         //打印路径 
		}
	}
} 

void bfs() {
	int nx,ny;  //下一个坐标的 x，y值 
	path[1][1].x=path[1][1].y=1;
	Q.push(path[1][1]);
	while (!Q.empty()) {    //队列中还有数时，继续寻路 
		NOW=Q.front();    //将此时的队头（即当前位置）取出 
		Q.pop();        //队头出队 
		if (NOW.x ==n && NOW.y ==n) {   //找到出口 
			flag=1;       //做个标记，方便后续判断该迷宫是否有通路 
			return;
		}
		for (int i=0;i<4;i++) {    //遍历该点的东西南北四个方向 
			nx=NOW.x+turnx[i]; 
			ny=NOW.y+turny[i];
			if (nx>=1 && nx<=n && ny>=1 && ny<=n && MAPbfs[nx][ny]!='X') {  //越界和通路判定 
				path[nx][ny].x =nx;
				path[nx][ny].y =ny;
				path[nx][ny].fromx  =NOW.x ;
				path[nx][ny].fromy  =NOW.y ;  //记录路径 
				MAPbfs[nx][ny]='X';    //标记已找过的路
				Q.push(path[nx][ny]) ;    //将该点入队 
			}
		}
	}
}

void vispath(int x,int y) {    //运用用递归、回溯，做到寻找、标记、打印路径 
	memset(vis,0,sizeof(vis)); //初始化 
	if (x==1&&y==1) {       
		vis[1][1]=1;
		Print_bfs();   //从起点开始打印路径 
		return;      //找到起点后，开始回溯，输出最终路径 
	}
	int fx=path[x][y].fromx ;
	int fy=path[x][y].fromy ;
	vispath(fx,fy);    //不断找该点的父结点 
	vis[path[x][y].x ][path[x][y].y ]=1;    //回溯后将该点做上标记
	Print_bfs();       //打印路径 
}

void Print_maze() {
	system("cls");
	cout<<"\n\t\t\t制作出的地图如下（ ￣ ▽ ￣ ）:\n";
	cout<<"\t\t\t     S--入口   E--出口\n";
	cout<<"\t\t\t     O--通路   X--墙体\n\n";
	for (int i=1;i<=n;i++) {
		cout<<"\t\t\t\t";
		for (int j=1;j<=n;j++) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			if (MAP[i][j]=='X') {
				SetConsoleTextAttribute(hConsole,6);   //改变字体颜色 
			} else {
				SetConsoleTextAttribute(hConsole,15);
			}
			cout<<MAP[i][j]<<" ";
		}
		cout<<"\n";
	}
}
void Print_dfs(int step) {
	Sleep(450);
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!flag) {     //未走到终点时的路径打印 
		cout<<"\t\t\t\tdfs寻路过程演示：\n\n";
		for (int i=1;i<=n;i++) {
			cout<<"\t\t\t\t";
			for (int j=1;j<=n;j++) {
				if (MAP[i][j]=='S'||MAP[i][j]=='E') {
					SetConsoleTextAttribute(hConsole,2);
					cout<<MAP[i][j]<<" "; 
					continue;
				}
				if (MAPdfs[i][j]!='X' && MAPdfs[i][j]!='O') {   //如果是走过的路径 
					if (MAPdfs[i][j]=='x') {
						SetConsoleTextAttribute(hConsole,4);
					} else {
						SetConsoleTextAttribute(hConsole,2);
						cout<<"▋ ";   //打印通路 
						continue;
					}
				} else {
					if (MAP[i][j]=='X') {
						SetConsoleTextAttribute(hConsole,6);   //改变字体颜色 
					} else {
						SetConsoleTextAttribute(hConsole,15);
					}
				}
				cout<<MAPdfs[i][j]<<" ";
			}
			cout<<"\n";
		}
		SetConsoleTextAttribute(hConsole,11);
		cout<<"\n\t\t\t\t该路径长度为 "<<step+1<<" （ ￣ ▽ ￣ ）"<<"\n";
	} else {
		cout<<"\t\t\t\t最终路径：\n\n";
		for (int i=1;i<=n;i++) {
			cout<<"\t\t\t\t";
			for (int j=1;j<=n;j++) {
				if (MAP[i][j]=='S'||MAP[i][j]=='E') {
					SetConsoleTextAttribute(hConsole,2);
					cout<<MAP[i][j]<<" "; 
					continue;
				}
				if (MAPdfs[i][j]!='X' && MAPdfs[i][j]!='O') {   //如果是走过的路径 
					if (MAPdfs[i][j]=='x') {
						SetConsoleTextAttribute(hConsole,15);
					} else {
						SetConsoleTextAttribute(hConsole,2);
						cout<<"▋ ";
						continue;
					}
				} else {
					if (MAP[i][j]=='X') {
						SetConsoleTextAttribute(hConsole,6);   //改变字体颜色 
					} else {
						SetConsoleTextAttribute(hConsole,15);
					}
				}
				cout<<MAPdfs[i][j]<<" ";
			}
			cout<<"\n";
		}
		SetConsoleTextAttribute(hConsole,11);
		cout<<"\n\t\t\t\t该路总径长度为："<<step-1<<"\n";
	} 
	SetConsoleTextAttribute(hConsole,15);
}

void Print_bfs() {
	Sleep(450);
	system("cls");
	cout<<"\t\t\t\t由bfs搜得，最短路径如下：\n\n";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i=1;i<=n;i++) {
		cout<<"\t\t\t\t";
		for (int j=1;j<=n;j++) {
			if (vis[i][j]) {
				SetConsoleTextAttribute(hConsole,2);
				cout<<"▋ "; 
				continue;
			} else {
				if (MAP[i][j]=='X') {
					SetConsoleTextAttribute(hConsole,6);   //改变字体颜色 
				} else {
					SetConsoleTextAttribute(hConsole,15);
				}
			}
			cout<<MAP[i][j]<<" ";
		}
		cout<<"\n";
	} 
	SetConsoleTextAttribute(hConsole,15);
}
