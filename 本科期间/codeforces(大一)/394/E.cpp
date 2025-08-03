#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}



vector<LL> a[N];
LL b;
bool J[N];
vector<LL> c;
LL x[N],y[N];
LL e[N];
LL x0[4]={0,1, 0,-1};
LL y0[4]={1,0,-1, 0};
LL n,m;
LL i,j,k,k0;
LL u,v;
int main()
{
	scanf("%I64d",&n);
	REP(i,n-1) scanf("%I64d%I64d",&u,&v),a[u].push_back(v),a[v].push_back(u);
	FOR(i,1,n) if (a[i].size()>4){
		printf("NO");
		return 0;
	}
	printf("YES\n");
	x[0]=y[0]=0;
	e[1]=4;
	k=30;
	c.push_back(1);
	J[1]=1;
	REP(i,n){
		k0=c[i];b=0;
//		printf("%d %d %d %d        %I64d %I64d\n",k0,b,e[k0],a[k0].size(),x[k0],y[k0]);
		REP(j,a[k0].size())
			if (!J[a[k0][j]]){
				if (b==e[k0]) b++;
				x[a[k0][j]]=x[k0]+x0[b]*(1<<k);
				y[a[k0][j]]=y[k0]+y0[b]*(1<<k);
				e[a[k0][j]]=b^2;
				c.push_back(a[k0][j]);
				J[a[k0][j]]=1;
				b++;
			}
		k--;
	}
	FOR(i,1,n) printf("%I64d %I64d\n",x[i],y[i]);
}
/*
10
2 5
5 6
6 1
6 7
6 8
5 10
5 3
2 9
2 4
*/
