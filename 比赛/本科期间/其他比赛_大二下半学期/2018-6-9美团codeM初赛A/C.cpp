#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
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

vector<pair<int,int> > edge[maxn];
int fa[maxn][20];
int dep[maxn];
LL len[maxn];
void dfs(int x,int f,LL length,int depth){
	int i;dep[x]=depth;len[x]=length;
	fa[x][0]=f;
	rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (auto now:edge[x]) if (now.first!=f)
        dfs(now.first,x,(length+now.second)%M,depth+1);
}
int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
LL dis(int x,int y){
	return len[x]+len[y]-2*len[lca(x,y)];
}
int n,m;
int i,j;
int main() {
    LL all=0;
    scanf("%d",&n);
    FOR(i,1,n-1){
        int x,y,z,l;
        scanf("%d%d%d%d",&x,&y,&z,&l);
        all+=(LL)(l/2*2)*z%M;l%=2;
        if (l==1){
            all+=z*2;
            z=M-z;
        }edge[x].push_back(make_pair(y,z));
        edge[y].push_back(make_pair(x,z));
        all%=M;
    }dfs(1,0,0,0);
    scanf("%d",&m);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%lld\n",((dis(u,v)+all)%M+M)%M);
    }
    return 0;
}
/*
*/
