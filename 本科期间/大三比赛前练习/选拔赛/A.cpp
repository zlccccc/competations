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
const LL M=1e9+7;
const LL maxn=5e5+7;
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

struct node{
    int n;LL d;
    node(){}
    node(int _n,LL _d):n(_n),d(_d){};
    const bool operator < (const node &A) const{
        if (d!=A.d) return d>A.d;
        return n>A.n;
    }
};
vector<node> edge[maxn];
LL dis[maxn];
priority_queue<node> Q;
void dij(int s,int n){
    int i;
    FOR(i,1,n) dis[i]=INFF;
    dis[s]=0;
    Q.push(node(s,0));
    while(Q.size()){
        node x=Q.top();
        Q.pop();
        if (dis[x.n]!=x.d) continue;
        for (node y:edge[x.n]){
            if (dis[y.n]>x.d+y.d){
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
}
int n,p,s,t;
int dep[maxn];
void dfs(int x,int fa,int d){
    dep[x]=d;
    for (auto now:edge[x]) if (now.n!=fa)
        dfs(now.n,x,d+1);
}inline void addedge(int u,int v,int len){
    edge[u].push_back(node(v,len));
}
int main() {
    int i,j,T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d%d%d",&n,&p,&s,&t);
        FOR(i,1,n*2+1) edge[i].clear();
        FOR(i,1,n-1){
            int u,v,len;
            scanf("%d%d%d",&u,&v,&len);
            addedge(u,v,len);
            addedge(v,u,len);
        }dfs(1,0,2);
        FOR(i,1,n){
            addedge(i,n+dep[i]-1,p);
            addedge(i,n+dep[i]+1,p);
            addedge(n+dep[i],i,0);
        }dij(s,n*2+1);
        static int x=0;
        printf("Case #%d: %lld\n",++x,dis[t]);
    }
}
/*
*/
