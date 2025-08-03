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

#define DEBUG1
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
const LL maxn=5000+7;
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

vector<int> edge[maxn];
int Fa[maxn],D[maxn];
void dfs(int x,int father){
    Fa[x]=father;
    for (int v:edge[x]) if (v!=father)
        dfs(v,x);
}bool mark[5007][5007];
int used[5007];
vector<int> V;
int TaskA(){
    int n,m,a,b,_x,_y,i,j;
    if (scanf("%d%d%d%d%d%d",&n,&m,&a,&b,&_x,&_y)==EOF) return 1;
    FOR(i,1,n) edge[i].clear();
    FOR(i,1,n) FOR(j,1,n) mark[i][j]=0;
    FOR(i,1,n-1){
        int u,v,len;
        scanf("%d%d",&u,&v);
        u++; v++;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs(1,0);
    int ans=0;
    FOR(i,1,n) D[i]=edge[i].size(),ans^=D[i];
    FOR(i,1,n) used[i]=1;used[1]=0;
//    FOR(i,1,n) printf("%d ",D[i]);puts("");
    FOR(i,1,n) for (j=i;j;j=Fa[j]) mark[j][i]=1;
    FOR(i,1,m){
        int x=_x,y=_y;
        _x=(a*x+b*y+ans)%n; _y=(b*x+a*y+ans)%n;
        x=_x+1,y=_y+1;
//        printf("query : %d %d\n",_x,_y);
        V.clear();
        for (;x&&!mark[Fa[x]][y];x=Fa[x]){
            V.push_back(x);
            if (Fa[x]==1) continue;
            ans^=D[Fa[x]];
            D[Fa[x]]-=used[x];used[x]=0;
            ans^=D[Fa[x]];
//            printf("  changed: %d(%d) ans=%d\n",x,D[x],ans);
        }for (int v:V) Fa[v]=x;
//        FOR(j,1,n) printf("%d ",D[j]);puts("");
//        printf("ans : %d\n",ans);
    }
    printf("%d %d\n",_x,_y);
    return 0;
}
void initialize(){}
int main() {
	int startTime=clock();
	//initialize
	initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=100000;
//	scanf("%d",&T);
	while (T--) {
        startTime=clock();
        if (TaskA()) break;
        debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
	}
}
/*
*/
