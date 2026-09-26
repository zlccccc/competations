#include <iostream>
#include <fstream>
using namespace std;
const long maxn=1000;
const long maxx=10000000;

ifstream fin("e:\\cchkk\\cchkk6.in");
ofstream fout("e:\\cchkk.out");

struct node{
	int num;
	node *next;
};

node *G[maxn+1],*p;
int dis[maxn+1][maxn+1],pos[maxn+1][maxn+1];
int  N,E,C,M,i,j,aa,bb;
double f[maxn+1][maxn+1];

void BFS(int v){
	int fp,rp,state[maxn+1],i;
	node *p;
	for (i=1;i<=N;i++)dis[i][v]=maxx;
	fp=1;rp=1;state[1]=v;dis[v][v]=0;pos[v][v]=v;
	
	while (fp<=rp) {
		p=G[state[fp]];
		while (p!=NULL) {
			if (dis[p->num][v]>dis[state[fp]][v]+1){
				dis[p->num][v]=dis[state[fp]][v]+1;
				pos[p->num][v]=state[fp];
				rp++;state[rp]=p->num;
			}
			if (dis[p->num][v]==dis[state[fp]][v]+1 && pos[p->num][v]>state[fp])
				pos[p->num][v]=state[fp];
			p=p->next;
		}
		fp++;
	}
}

double Calc(int v1,int v2){
	double addnum;
	node *p;
	int temp,posnum;
	if (f[v1][v2]>=0) return f[v1][v2];
	
	temp=pos[pos[v1][v2]][v2];
	if (temp==v2) {f[v1][v2]=1;return f[v1][v2];}
	p=G[v2];addnum=Calc(temp,v2);posnum=1;
	while (p!=NULL) {
		if (temp!=p->num)addnum+=Calc(temp,p->num);
		p=p->next;posnum++;
	}
	f[v1][v2]=addnum/posnum+1;
	return f[v1][v2];
}

int main(){
	fin >> N >> E ;
	fin >> C >> M ;
	memset(G,0,sizeof(G));
	for (i=1;i<=E;i++){
		fin >> aa >> bb;
		p=new(node);p->num=bb;p->next=G[aa];G[aa]=p;
		p=new(node);p->num=aa;p->next=G[bb];G[bb]=p;
	}

	for (i=1;i<=N;i++) BFS(i);

	for (i=1;i<=N;i++) for (j=1;j<=N;j++) f[i][j]=-1;
	fout << Calc(C,M) << endl;
	return 1;
}