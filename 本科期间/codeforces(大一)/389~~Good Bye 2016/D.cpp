#include <cstdio>
#include <cmath>
const int N=500;
const int INF=20000000;
int n,i,j;
int T;
bool a[N*2][N*2];
bool b[N*2][N*2][32][5];
int t0[31];
int num;
void paint(int x,int y,int k,int t)
{
	if (k==n) return;
	if (b[x][y][k][t]) return;
	b[x][y][k][t]=1;
	int num=0;
	int i;
		if (t==0) y--;
		if (t==1) x++;
		if (t==2) y++;
		if (t==3) x--;
	for (i=0;i<t0[k];i++){
		if (t==0) a[x][y-i]=1;
		if (t==1) a[x+i][y]=1;
		if (t==2) a[x][y+i]=1;
		if (t==3) a[x-i][y]=1;
	}
		if (t==0) y-=t0[k]-1;
		if (t==1) x+=t0[k]-1;
		if (t==2) y+=t0[k]-1;
		if (t==3) x-=t0[k]-1;
	k++;
	if (k==n) return;
	for (i=1;i<=t0[k];i++)
	{
		if (t==0) {a[x+i][y-i]=1;a[x-i][y-i]=1;}
		if (t==1) {a[x+i][y-i]=1;a[x+i][y+i]=1;}
		if (t==2) {a[x+i][y+i]=1;a[x-i][y+i]=1;}
		if (t==3) {a[x-i][y-i]=1;a[x-i][y+i]=1;}
	}
	i--;//n
	if (t==0) {paint(x+i,y-i,k+1,0);paint(x+i,y-i,k+1,1);paint(x-i,y-i,k+1,0);paint(x-i,y-i,k+1,3);}
	if (t==1) {paint(x+i,y-i,k+1,0);paint(x+i,y-i,k+1,1);paint(x+i,y+i,k+1,1);paint(x+i,y+i,k+1,2);}
	if (t==2) {paint(x+i,y+i,k+1,1);paint(x+i,y+i,k+1,2);paint(x-i,y+i,k+1,2);paint(x-i,y+i,k+1,3);}
	if (t==3) {paint(x-i,y-i,k+1,3);paint(x-i,y-i,k+1,0);paint(x-i,y+i,k+1,2);paint(x-i,y+i,k+1,3);}
}
int main()
{
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",t0+i);
	paint(250,250,0,3);
	for (i=230;i<262;i++){
		for (j=230;j<272;j++) if (a[i][j]) printf("#");
		else printf(" ");
		printf("\n");
	}
	for (i=0;i<N*2;i++)
		for (j=0;j<N*2;j++) if (a[i][j]) num++;
	printf("%d",num);
}
