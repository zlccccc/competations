#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
vector<int>edge[N];
set<int>color[N];
int c[N];
int u,v;
int i,j,k;
int maxcolor;
void dfs(int v,int from){
    int i,k=1,u,n=edge[v].size();
    REP(i,n){
        u=edge[v][i];
        if (u==from) continue;
        while (color[v].count(k)) k++;
        color[v].insert(k);
        color[u].insert(k);
        color[u].insert(c[v]);
        c[u]=k;
        dfs(u,v);
    }
    if (k>maxcolor) maxcolor=k;
}
int main(){
	scanf("%d",&n);
	REP(i,n-1){
	    scanf("%d%d",&u,&v);
	    edge[u].push_back(v);
	    edge[v].push_back(u);
	}
	c[1]=1;
	color[1].insert(1);
	dfs(1,0);
	printf("%d",maxcolor);
	puts("");
	FOR(i,1,n) printf("%d ",c[i]);
}
/*
*/
