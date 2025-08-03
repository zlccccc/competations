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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q;
vector<pair<int,int> > edge[maxn];
int i,j,k;
LL a[maxn];
int mark[maxn],nxt_edge[maxn];
int U,V,id;
void dfs(int x,int color){
    mark[x]=color;
    for (auto now:edge[x])
        if (mark[now.first]==-1)
            dfs(now.first,color^1),nxt_edge[now.second]=1;
        else if (!id&&mark[now.first]==color)
            U=x,V=now.first,id=now.second;
}
LL ans[maxn];
void solve(int x){
    mark[x]=1;
    for (auto now:edge[x])
        if (nxt_edge[now.second]&&!mark[now.first]){
            solve(now.first);
            LL value=a[now.first];
            ans[now.second]+=a[now.first];
            a[x]-=a[now.first];
            a[now.first]-=a[now.first];
        }
}
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%I64d",&a[i]);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].emplace_back(make_pair(v,i));
        edge[v].emplace_back(make_pair(u,i));
    }
//    FOR(i,1,n) random_shuffle(edge[i].begin(),edge[i].end());
    FOR(i,1,n) mark[i]=-1;
    U=1;dfs(1,0);
    FOR(i,1,n) mark[i]=0;
    solve(U);
    if (id&&a[U]){
        ans[id]=a[U]/2;
        a[V]-=a[U]/2;
        a[U]-=a[U]/2;
    }FOR(i,1,n) mark[i]=0;
    solve(U);
    if (a[U]) return 0*puts("NO");
    puts("YES");
    FOR(i,1,m) printf("%I64d\n",ans[i]);
}
/*
*/
