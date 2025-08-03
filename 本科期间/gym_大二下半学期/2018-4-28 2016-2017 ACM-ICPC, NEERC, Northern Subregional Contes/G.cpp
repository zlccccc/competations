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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e5+7;
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

int in[maxn],out[maxn];
int fa[maxn][20],dep[maxn],sz[maxn];
int pos[maxn],tot;
vector<int> edge[maxn];
void dfs(int x,int f,int depth){
    int i;
    in[x]=++tot;pos[tot]=x;
    if (!edge[x].size()) sz[x]=1;
    fa[x][0]=f;dep[x]=depth;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]){
        dfs(v,x,depth+1);
        sz[x]+=sz[v];
    }out[x]=tot;
}inline int lca(int x,int y){
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=(1<<i)) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}int top[maxn];
set<int> nowtop;
set<int> nowlca[maxn];
int nowgangsters,nowall,nowans1;
int getsize(int x){
    if (!nowlca[x].size()) return 0;
    int l=*nowlca[x].begin(),r=*(--nowlca[x].end());
    int LCA=lca(pos[l],pos[r]);
//    dbgln(LCA);
    return sz[LCA];
}
int n,m,q;
int main() {
    int i;
    freopen("gangsters.in","r",stdin);
    freopen("gangsters.out","w",stdout);
    scanf("%d%d",&n,&q);
    FOR(i,2,n){
        int f;
        scanf("%d",&f);
        edge[f].push_back(i);
    }dfs(1,0,0);
    for (int v:edge[1])
        FOR(i,in[v],out[v]) top[pos[i]]=v;
    FOR(i,1,q){
        char s[2];int v;
        scanf("%s%d",s,&v);
        if (s[0]=='+'){
            nowgangsters++;
            int t=top[v];
            if (!nowlca[t].size()) nowans1++;
            else nowall-=getsize(t);
            nowlca[t].insert(in[v]);
            nowall+=getsize(t);
//            dbgln(t);
        }else{
            nowgangsters--;
            int t=top[v];
            nowall-=getsize(t);
            nowlca[t].erase(in[v]);
            if (!nowlca[t].size()) nowans1--;
            else nowall+=getsize(t);
//            dbgln(t);
        }printf("%d %d\n",nowans1,nowall-nowgangsters);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
7 6
1 2 1 3 3 3
+ 4
+ 5
+ 6
+ 7
- 6
- 5
*/
