#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=250000+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
    int n;LL d;
    node(){}
    node(int _n,LL _d):n(_n),d(_d){};
    const bool operator <(const node &A)const {
        if (d!=A.d) return d>A.d;//注意!!! 否则为未优化的bellmanford
        return n>A.n;
    }
};
vector<node> edge[maxn];
priority_queue<node> Q;
LL dis[maxn];
void dij(int s,int n){
    int i;
    FOR(i,1,n) dis[i]=INFF;
    dis[s]=0;
    Q.push(node(s,0));
    while (Q.size()){
        node x=Q.top();Q.pop();
        if (dis[x.n]!=x.d) continue;
        for (node y:edge[x.n]){
            if (dis[y.n]>x.d+y.d){
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
}
int q,m,n;
inline int getid(int x,int y){
    return (x-1)*m+y;
}
int a[507][507];
int ax[]={0,0,-1,1};
int ay[]={-1,1,0,0};
void addedge(int u,int v,int val){
//    printf("%d->%d  %d\n",u,v,val);
    edge[u].push_back(node(v,val));
}
int main(){
    scanf("%d%d%d",&q,&n,&m);
	while (q--){
		int i,j,k,s,t;
        FOR(i,1,n*m+2) edge[i].clear();
        FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]);
		s=n*m+1;t=n*m+2;
		FOR(i,1,n) {
		    if (a[i][1]) addedge(s,getid(i,1),max(0,a[i][1]));
            if (a[i][m]) addedge(getid(i,m),t,max(0,0));
		}FOR(i,1,m){
		    if (a[1][i]) addedge(getid(1,i),t,max(0,0));
            if (a[n][i]) addedge(s,getid(n,i),max(0,a[n][i]));
		}
		FOR(i,1,n) FOR(j,1,m){
            REP(k,4){
                int x=i+ax[k],y=j+ay[k];
                if (!a[i][j]||!a[x][y]) continue;
                edge[getid(i,j)].push_back(node(getid(x,y),max(0,a[x][y])));
            }
		}dij(s,n*m+2);
		if (dis[t]!=INFF) printf("%lld\n",dis[t]);
		else puts("-1");
//		printf("getid(%d %d):%d\n",n,m,getid(n,m));
	}
}
/*
6 3 3
0 2 2
3 2 3
2 2 0
0 1 2
-1 1 -1
2 1 0
0 1 2
0 0 0
2 1 0
0 2 2
3 2 3
2 2 0
0 1 2
-1 1 -1
2 1 0
0 1 2
0 0 0
2 1 0
*/
