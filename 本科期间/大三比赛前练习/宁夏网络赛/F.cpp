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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=407+7;
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
    int to;LL cap;int next;
    node(int t=0,LL c=0,int n=0):to(t),cap(c),next(n){}
}edge[maxn*50];
int head[maxn];
int tot;
void addedge(int from,int to,LL cap,int rcap=0){
//    printf("add: %d %d %d\n",from,to,cap);
    edge[tot].to=to;edge[tot].next=head[from];
    edge[tot].cap=cap;head[from]=tot++;
    edge[tot].to=from;edge[tot].next=head[to];
    edge[tot].cap=rcap;head[to]=tot++;
}
queue<int> Q;
int gap[maxn],dep[maxn],cur[maxn];
void bfs(int s,int t){
    memset(dep,0xff,sizeof(dep));
    memset(gap,0,sizeof(gap));
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
LL sap(int s,int t,int n){
    bfs(s,t);
    memcpy(cur,head,sizeof(head));
    int top=0,u=s;
    LL ret=0;
    while (dep[s]<n){
        if (u==t){
            LL MIN=INFF;int inser,i;
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
void solve(){
    int n,m;
    int i,j;
    LL k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n+m+2) head[i]=-1;
    tot=0;
    int s=n+m+1,t=n+m+2;
    LL ans=0;
    FOR(i,1,n){
        scanf("%lld",&k);
        addedge(s,i,k);
        ans+=k;
    }FOR(i,1,m){
        scanf("%lld",&k);
        addedge(i+n,t,k);
//        ans-=k;
    }FOR(i,1,n){
        int n1,n2;
        scanf("%d%d",&n1,&n2);
        FOR(j,1,n1){
            int f;
            scanf("%d",&f);
            addedge(i,f+n,INFF);
        }FOR(j,1,n2){
            int f;
            scanf("%d",&f);
            addedge(i,f,INFF);
        }
    }printf("%lld\n",ans-sap(s,t,n+m+2));
}
int main() {
    int i,j,k;
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
2
3 3
600000000000000 200000000000000 400000000000000
100000000000000 200000000000000 300000000000000
1 2 1 2 3
1 0 2
1 0 3

3 4
600 400 200
100 200 300 1000
2 1 1 2 3
1 0 1
1 0 1
*/
