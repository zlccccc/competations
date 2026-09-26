#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <map>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <utility>
#include <bitset>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define rep(i,a,b) for (int i=(a);i<(b);i++)
#define per(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,a,b) for (int i=(a);i<=(b);i++)
#define PER(i,a,b) for (int i=(b);i>=(a);i--)
#define de(x) cout<<">> "<<#x<<" = "<<x<<endl;
using namespace std;
typedef int LL;

const int INF = 0x3f3f3f3f;
const int MAXN = 1000005; // 1e6;
int n,m;
LL bit[4][2050][2050];
void add(LL c[][2050], int a, int b, LL x)
{
	for (int i=a;i<=n;i+=i&-i)
	for (int j=b;j<=m;j+=j&-j)  
	{
		c[i][j]+=x;
	}
}
LL sum(LL c[][2050], int a, int b)
{
	LL ret=0;
	for(int i=a;i;i-=i&-i)
	for(int j=b;j;j-=j&-j) 
	{
		ret+=c[i][j];
	}
	return ret;
}
void ADD(int x1, int y1, int x2, int y2, LL d)
{
	add(bit[0],x1,y1,d);add(bit[0],x1,y2+1,-d);add(bit[0],x2+1,y1,-d);add(bit[0],x2+1,y2+1,d);
	
	add(bit[1],x1,y1,d*x1);add(bit[1],x1,y2+1,-d*x1);add(bit[1],x2+1,y1,-d*(x2+1));add(bit[1],x2+1,y2+1,(x2+1)*d);
	add(bit[2],x1,y1,d*y1);add(bit[2],x1,y2+1,-d*(y2+1));add(bit[2],x2+1,y1,-d*y1);add(bit[2],x2+1,y2+1,d*(y2+1));
	add(bit[3],x1,y1,d*x1*y1);add(bit[3],x1,y2+1,-d*(y2+1)*x1);add(bit[3],x2+1,y1,-d*y1*(x2+1));add(bit[3],x2+1,y2+1,d*(x2+1)*(y2+1));
}
LL getsum(LL x, LL y)
{
	return sum(bit[0], x, y)*(x+1)*(y+1) - sum(bit[1],x,y)*(y+1) - sum(bit[2],x,y)*(1+x)+ sum(bit[3],x,y);
}
LL SUM(int x1, int y1, int x2, int y2)
{
	LL ret= getsum(x2, y2) + getsum(x1-1, y1-1) - getsum(x1-1, y2) - getsum(x2, y1-1);

	return ret;
}
int main()
{
	// freopen("in.txt","r",stdin);
	char op[5];

	int a,b,c,d,delta;
	scanf("%s%d%d",op,&n,&m);
	while(~scanf("%s%d%d%d%d",op,&a,&b,&c,&d))
	{
		if (op[0]=='L')
		{
			scanf("%d",&delta);
			ADD(a,b,c,d,delta);
		}
		else
		{
			printf("%d\n",SUM(a,b,c,d));
		}
	}
	return 0;
}

