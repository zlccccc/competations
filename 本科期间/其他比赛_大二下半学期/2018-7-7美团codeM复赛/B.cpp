#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*2];
int head[maxn],etot;
inline void addedge(int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
int nowans;
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
void tarjan(int x) {
    low[x]=dfn[x]=++tot;
    S[++top]=x;
    vis[x]=1;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(!dfn[v]) {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if(vis[v])
            low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x]) {
        int cnt=0;
        while(1) {
            int now=S[top--]; cnt++;
            vis[now]=0;
            if (cnt>1) nowans=1;
            if(now==x) break;
        }
    }
}
int U[maxn],V[maxn];
inline void add(ll &A,ll B){A+=B;(A>=M)&&(A-=M);}
int TaskA(){
    int i,j,n,m;
    scanf("%d%d",&n,&m); int lastans=0;
    FOR(i,1,m) {
        scanf("%d%d",&U[i],&V[i]);
        U[i]=(U[i]+n-2-lastans)%n+1;
        V[i]=(V[i]+n-2-lastans)%n+1;
        lastans=1;
    }
//    FOR(i,1,m) debug("%d %d\n",U[i],V[i]);
    int l=0,r=m+1;
//    FOR(i,1,m) if (U[i]==0||V[i]==0) r=i;
    while (l+1<r){
        int mid=(l+r)/2; etot=0; nowans=0;
        FOR(i,1,n) head[i]=-1,dfn[i]=0;
        FOR(i,1,mid) addedge(U[i],V[i]);
        FOR(i,1,n) if (!dfn[i]) tarjan(i);
        if (nowans) r=mid;
        else l=mid;
    }//debug("%d\n",r);
    FOR(i,1,l) puts("1");
    FOR(i,r,m) puts("0");
    return 0;
}
void initialize(){}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
