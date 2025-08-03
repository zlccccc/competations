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

struct node{
    int to,cap,next;
    node(int t=0,int c=0,int n=0):to(t),cap(c),next(n){}
}edge[maxn*50];
int head[maxn];
int tot;
void addedge(int from,int to,int cap,int rcap=0){
    edge[tot].to=to;edge[tot].next=head[from];
    edge[tot].cap=cap;head[from]=tot++;
    edge[tot].to=from;edge[tot].next=head[to];
    edge[tot].cap=rcap;head[to]=tot++;
}
int CNT_N;
queue<int> Q;
int gap[maxn],dep[maxn],cur[maxn];
void bfs(int s,int t){
    int i;
    FOR(i,1,CNT_N) dep[i]=-1,gap[i]=0;
//    memset(dep,0xff,sizeof(dep));
//    memset(gap,0,sizeof(gap));
    gap[0]=1;
    dep[t]=0;
    Q.push(t);
    while (Q.size()){
        int u=Q.front();Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if (dep[v]!=-1) continue;
            Q.push(v);
            dep[v]=dep[u]+1;
            gap[dep[v]]++;
        }
    }
}
int S[maxn];
int sap(int s,int t,int n){
    int i;
    bfs(s,t);
    FOR(i,1,CNT_N) cur[i]=head[i];
//    memcpy(cur,head,sizeof(head));
    int top=0,u=s,ret=0;
    while (dep[s]<n){
        if (u==t){
            int MIN=INF,inser,i;
            REP(i,top) if (MIN>edge[S[i]].cap)
                MIN=edge[S[i]].cap,inser=i;
            REP(i,top) edge[S[i]].cap-=MIN,
                edge[S[i]^1].cap+=MIN;
            ret+=MIN;
            top=inser;
            u=edge[S[top]^1].to;
            continue;
        }
        bool flag=0;
        int v;
        for (int i=cur[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if (edge[i].cap&&dep[v]+1==dep[u]){
                flag=1;
                cur[u]=i;
                break;
            }
        }
        if (flag){
            S[top++]=cur[u];
            u=v;
            continue;
        }
        int MIN=n;
        for (int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if (edge[i].cap&&dep[v]<MIN)
                MIN=min(MIN,dep[v]),cur[u]=i;
        }
        gap[dep[u]]--;
        if (!gap[dep[u]]) return ret;
        dep[u]=MIN+1;
        gap[dep[u]]++;
        if (u!=s) u=edge[S[--top]^1].to;
    }
    return ret;
}
int ans;
int n,m;
int main() {
    int i,j,k,t,q;
    scanf("%d",&q);
    while (q--){
        memset(head,-1,sizeof(head));
        int n,m,s,t;tot=0;
        scanf("%d%d",&n,&m);
        s=n+m+1;t=n+m+2;CNT_N=n+m+2;ans=0;
        FOR(i,1,n) scanf("%d",&k),addedge(i,t,k,0),ans+=k;
        FOR(i,1,m) scanf("%d",&k),addedge(s,i+n,k,0);
        FOR(i,1,m){
            scanf("%d",&k);
            FOR(j,1,k){
                int pos;
                scanf("%d",&pos);
                addedge(i+n,pos,INF,0);
            }
        }
//        printf("ini: %d\n",ans);
        printf("%d\n",ans-sap(s,t,n+m+2));
    }
    return 0;
}
/*
*/
