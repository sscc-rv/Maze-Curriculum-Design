#include <stdio.h>
#include <queue>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
using namespace std;
const int M=505;
int n;        //�Թ���С 
int flag;     //�ж��Թ��Ƿ�Ϊͨ·  0--��  1--�� 
struct node {
	int x,y;   //��ǰλ�õ����� 
	int fromx,fromy;   //��ǰλ����������һ�������ת�� 
}path[M][M],NOW;
queue<node>Q;

int vis[M][M];       //������飬��¼·�� 
char MAP[M][M];      //��ͼ���� 
char MAPdfs[M][M];   //dfs�ĵ�ͼʹ�� 
char MAPbfs[M][M];   //bfs�ĵ�ͼʹ�� 
int turnx[4] = {0, 1, 0, -1};  //x������ƶ����� 
int turny[4] = {1, 0, -1, 0};  //y������ƶ�����
 
void Start();    //��ʼ�� 
void Again();   //�ٴθ�ֵ 
void Make();    //�����Թ� 
void dfs(int s,int y,int step);   // dfsѰ���Թ�·�� 
void bfs();                       // bfsѰ· 
void vispath(int x,int y);        // bfs��¼�Թ�·��
void Print_maze();                //��ӡ�Թ� 
void Print_bfs();                 //��ӡ bfsѰ··�� 
void Print_dfs(int step);         //��ӡ dfsѰ··�� 

int main() {
	cout<<"\n\n\n\n\n";
	cout<<"\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t--------------------------------"<<endl;
	cout<<"\t\t\t\t\t------ �� �� �� �� �� ��  ------"<<endl;
	cout<<"\t\t\t\t\t------                    ------"<<endl;
	cout<<"\t\t\t\t\t--------- �� �� �� ��  ---------"<<endl;
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
			cout<<"\n\t\t\t*\t��ѡ�����Ĳ�����      *\n";
			cout<<"\t\t\t*\t                      *";
			cout<<"\n\t\t\t*\t1.�����Թ�            *\n";
			cout<<"\t\t\t*\t                      *";
			cout<<"\n\t\t\t*\t2.�˳�����            *\n";
			cout<<"\t\t\t*\t                      *";
			printf("\n\t\t\t*******************************\n");
			cin>>choice;     //�û�ѡ����� 
			while (choice!="1"&&choice!="2") {    //�������� 
				cout<<"\t\t\t�����Ŷ�����������루 �� �� �� ��\n";
				cin>>choice;
			}
			if (choice == "2") return 0;
			Make();  //�����Թ� 
		}
		while (1) {
			Print_maze(); 
			cout<<"\n\t\t\t*********************************\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t��ѡ��Ѱ�ҳ��ڵķ�ʽ:   *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t1.dfs�����������       *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t2.bfs�����������       *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*\t3.������һ����          *\n";
			cout<<"\t\t\t*\t                        *";
			cout<<"\n\t\t\t*********************************\n";
			
//			cout<<"\n��ѡ��Ѱ�ҳ��ڵķ�ʽ��\n"; 
//			cout<<"1.dfs�����������\n"; 
//			cout<<"2.bfs�����������\n"; 
//			cout<<"3.������һ����\n"; 
			
			flag=0;
			cin>>choice;     //�û�ѡ����� 
			while (choice!="1"&&choice!="2"&&choice!="3") {  //�������� 
				cout<<"\t\t\t�����Ŷ�����������루 �� �� �� ��\n";
				cin>>choice;
			}
			
			if (choice == "1") flag=0, dfs(1,1,0);
			else if (choice == "2") vispath(n,n), Print_bfs();
			else if (choice == "3") break;
			
			cout<<"\n\t\t\t�� 1 ������һ���棨 �� �� �� ��\n";
			cin>>choice;
			while (choice!="1") {   //�������� 
				cout<<"\t\t\t�����Ŷ�����������루 �� �� �� ��\n";
				cin>>choice; 
			}
			system("cls");
		}
	}
	return 0;
}

void Start() {      //��ʼ�� 
	memset(vis,0,sizeof(vis));
	memset(MAP,0,sizeof(MAP));
	memset(MAPdfs,0,sizeof(MAPdfs));
	memset(MAPbfs,0,sizeof(MAPbfs));
	while (!Q.empty()) Q.pop() ; 
}

void Again() {     //�� MAP�е�ֵ���� MAPbfs�� MAPdfs�� 
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
	cout<<"\n\t\t\t��������������Թ��߳����߳������1����\n";
	cin>>n;
	//system("cls");  //���� 
	printf("\n\t\t\t�Թ���������ȴ�1~3��");
	while (1) {
		srand(time(NULL));     //�Ե�ǰʱ��Ϊ���ӣ����������
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				int num=rand()%3;  //�������ɵ����������ǽ/· 
				if (num==0) {
					MAP[i][j]='X';  //ǽ 
				} else {
					MAP[i][j]='O';  //· 
				}
			}
		}
		Again();     //�� MAP�е�ֵ���� MAPbfs�� MAPdfs�� 
		bfs();    //�ж��Ƿ�ͨ·�������˳�������������������Թ� 
		if (flag==1) break; 
	}
}

void dfs(int x,int y,int step) {
	if (flag) return;
	if (x==n&&y==n) {    //�ҵ��յ� 
		flag=1; 
		Sleep(3000);
		Print_dfs(step);   //��ӡ·�� 
		Again();     //�� MAP�е�ֵ���� MAPbfs�� MAPdfs�� 
		return;
	}
	for (int i=0;i<4;i++) {      //�����õ�Ķ����ϱ��ĸ����� 
		int nextx=x+turnx[i];
		int nexty=y+turny[i];
		if (nextx>=1&&nextx<=n&&nexty>=1&&nexty<=n&&(MAPdfs[nextx][nexty]=='S'||MAPdfs[nextx][nexty]=='O'||MAPdfs[nextx][nexty]=='E')) {  //�߽��ж���ͨ·�ж� 
			MAPdfs[nextx][nexty]='o';
			if (nextx!=n||nexty!=n) Print_dfs(step);    //��ӡ·�� 
			dfs(nextx,nexty,step+1);    //�Ӹõ����Ѱ��·�� 
			if (flag) return;        //���ҵ�ͨ·����ֱ�ӻ��� 
			MAPdfs[nextx][nexty]='x';   //���� ���õ���Ϊδ����״̬ 
			Print_dfs(step);         //��ӡ·�� 
		}
	}
} 

void bfs() {
	int nx,ny;  //��һ������� x��yֵ 
	path[1][1].x=path[1][1].y=1;
	Q.push(path[1][1]);
	while (!Q.empty()) {    //�����л�����ʱ������Ѱ· 
		NOW=Q.front();    //����ʱ�Ķ�ͷ������ǰλ�ã�ȡ�� 
		Q.pop();        //��ͷ���� 
		if (NOW.x ==n && NOW.y ==n) {   //�ҵ����� 
			flag=1;       //������ǣ���������жϸ��Թ��Ƿ���ͨ· 
			return;
		}
		for (int i=0;i<4;i++) {    //�����õ�Ķ����ϱ��ĸ����� 
			nx=NOW.x+turnx[i]; 
			ny=NOW.y+turny[i];
			if (nx>=1 && nx<=n && ny>=1 && ny<=n && MAPbfs[nx][ny]!='X') {  //Խ���ͨ·�ж� 
				path[nx][ny].x =nx;
				path[nx][ny].y =ny;
				path[nx][ny].fromx  =NOW.x ;
				path[nx][ny].fromy  =NOW.y ;  //��¼·�� 
				MAPbfs[nx][ny]='X';    //������ҹ���·
				Q.push(path[nx][ny]) ;    //���õ���� 
			}
		}
	}
}

void vispath(int x,int y) {    //�����õݹ顢���ݣ�����Ѱ�ҡ���ǡ���ӡ·�� 
	memset(vis,0,sizeof(vis)); //��ʼ�� 
	if (x==1&&y==1) {       
		vis[1][1]=1;
		Print_bfs();   //����㿪ʼ��ӡ·�� 
		return;      //�ҵ����󣬿�ʼ���ݣ��������·�� 
	}
	int fx=path[x][y].fromx ;
	int fy=path[x][y].fromy ;
	vispath(fx,fy);    //�����Ҹõ�ĸ���� 
	vis[path[x][y].x ][path[x][y].y ]=1;    //���ݺ󽫸õ����ϱ��
	Print_bfs();       //��ӡ·�� 
}

void Print_maze() {
	system("cls");
	cout<<"\n\t\t\t�������ĵ�ͼ���£� �� �� �� ��:\n";
	cout<<"\t\t\t     S--���   E--����\n";
	cout<<"\t\t\t     O--ͨ·   X--ǽ��\n\n";
	for (int i=1;i<=n;i++) {
		cout<<"\t\t\t\t";
		for (int j=1;j<=n;j++) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			if (MAP[i][j]=='X') {
				SetConsoleTextAttribute(hConsole,6);   //�ı�������ɫ 
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
	if (!flag) {     //δ�ߵ��յ�ʱ��·����ӡ 
		cout<<"\t\t\t\tdfsѰ·������ʾ��\n\n";
		for (int i=1;i<=n;i++) {
			cout<<"\t\t\t\t";
			for (int j=1;j<=n;j++) {
				if (MAP[i][j]=='S'||MAP[i][j]=='E') {
					SetConsoleTextAttribute(hConsole,2);
					cout<<MAP[i][j]<<" "; 
					continue;
				}
				if (MAPdfs[i][j]!='X' && MAPdfs[i][j]!='O') {   //������߹���·�� 
					if (MAPdfs[i][j]=='x') {
						SetConsoleTextAttribute(hConsole,4);
					} else {
						SetConsoleTextAttribute(hConsole,2);
						cout<<"�� ";   //��ӡͨ· 
						continue;
					}
				} else {
					if (MAP[i][j]=='X') {
						SetConsoleTextAttribute(hConsole,6);   //�ı�������ɫ 
					} else {
						SetConsoleTextAttribute(hConsole,15);
					}
				}
				cout<<MAPdfs[i][j]<<" ";
			}
			cout<<"\n";
		}
		SetConsoleTextAttribute(hConsole,11);
		cout<<"\n\t\t\t\t��·������Ϊ "<<step+1<<" �� �� �� �� ��"<<"\n";
	} else {
		cout<<"\t\t\t\t����·����\n\n";
		for (int i=1;i<=n;i++) {
			cout<<"\t\t\t\t";
			for (int j=1;j<=n;j++) {
				if (MAP[i][j]=='S'||MAP[i][j]=='E') {
					SetConsoleTextAttribute(hConsole,2);
					cout<<MAP[i][j]<<" "; 
					continue;
				}
				if (MAPdfs[i][j]!='X' && MAPdfs[i][j]!='O') {   //������߹���·�� 
					if (MAPdfs[i][j]=='x') {
						SetConsoleTextAttribute(hConsole,15);
					} else {
						SetConsoleTextAttribute(hConsole,2);
						cout<<"�� ";
						continue;
					}
				} else {
					if (MAP[i][j]=='X') {
						SetConsoleTextAttribute(hConsole,6);   //�ı�������ɫ 
					} else {
						SetConsoleTextAttribute(hConsole,15);
					}
				}
				cout<<MAPdfs[i][j]<<" ";
			}
			cout<<"\n";
		}
		SetConsoleTextAttribute(hConsole,11);
		cout<<"\n\t\t\t\t��·�ܾ�����Ϊ��"<<step-1<<"\n";
	} 
	SetConsoleTextAttribute(hConsole,15);
}

void Print_bfs() {
	Sleep(450);
	system("cls");
	cout<<"\t\t\t\t��bfs�ѵã����·�����£�\n\n";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i=1;i<=n;i++) {
		cout<<"\t\t\t\t";
		for (int j=1;j<=n;j++) {
			if (vis[i][j]) {
				SetConsoleTextAttribute(hConsole,2);
				cout<<"�� "; 
				continue;
			} else {
				if (MAP[i][j]=='X') {
					SetConsoleTextAttribute(hConsole,6);   //�ı�������ɫ 
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
