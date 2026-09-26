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
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int dfn[maxn],low[maxn],tot;
bool vis[maxn];
int S[maxn],top;
int id[maxn],cnt;
vector<int> edge[maxn];
void tarjan(int x,int fa){
    low[x]=dfn[x]=++tot;
    S[++top]=x;vis[x]=1;
    for (int v:edge[x]) if (v!=fa){
        if (!dfn[v]){
            tarjan(v,x);
            low[x]=min(low[x],low[v]);
        }else if (vis[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }if (low[x]==dfn[x]){
        cnt++;
        while (1){
            int now=S[top--];
            vis[now]=0;id[now]=cnt;
            if (now==x) break;
        }
    }
}
int U;
int dep[maxn];
void dfs(int x,int depth){
    dep[x]=depth;
    if (dep[x]>dep[U]) U=x;
    for (int v:edge[x]) if (dep[v]==-1) dfs(v,depth+(id[x]!=id[v]));
}
int TaskA(){
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }tarjan(1,0);U=1;
    FOR(i,1,n) dep[i]=-1;dfs(1,0);
//    FOR(i,1,n) printf("%d ",id[i]);puts("");
//    FOR(i,1,n) printf("%d ",dep[i]);puts("");
    FOR(i,1,n) dep[i]=-1;dfs(U,0);
    printf("%d\n",dep[U]);
}
int main() {
	int startTime=clock();
	//initialize
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
