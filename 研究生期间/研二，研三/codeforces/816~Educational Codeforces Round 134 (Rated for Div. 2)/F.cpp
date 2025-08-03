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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace maxflow {
    typedef LL type;
    const type INF=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
    } edge[maxn*50];
    int head[maxn],tot;
    int addedge(int from,int to,type cap,type rcap=0) {
        edge[tot]=node(to,cap,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
        return tot-2;
    }
    int gap[maxn],dep[maxn],cur[maxn];
    void bfs(int s,int t,int n) {//t好像没啥用啊=_=
        static int Q[maxn],ST,ED;
        memset(dep+1,0xff,n*sizeof(int));
        memset(gap+1,0,n*sizeof(int));
        gap[0]=1; dep[t]=0;
        ST=0; ED=-1; Q[++ED]=t;
        while (ST<=ED) {
            int u=Q[ST++];
            for (int i=head[u]; ~i; i=edge[i].next) {
                int v=edge[i].to;
                if (dep[v]!=-1) continue;
                Q[++ED]=v; dep[v]=dep[u]+1;
                gap[dep[v]]++;
            }
        }
    }
    int S[maxn];
    type sap(int s,int t,int n) {
        bfs(s,t,n);
        memcpy(cur+1,head+1,n*sizeof(int));
        int top=0,u=s; type ret=0;
        while (dep[s]<n) {
            if (u==t) {
                type MIN=INF,inser=0,i;
                REP(i,top) if (MIN>edge[S[i]].cap)
                    MIN=edge[S[i]].cap,inser=i;
                REP(i,top) {
                    edge[S[i]].cap-=MIN,edge[S[i]^1].cap+=MIN;
                } ret+=MIN; top=inser; u=edge[S[top]^1].to;
                continue;
            } bool flag=0; int v;
            for (int i=cur[u]; ~i; i=edge[i].next) {
                v=edge[i].to;
                if (edge[i].cap&&dep[v]+1==dep[u]) {
                    flag=1; cur[u]=i; break;
                }
            } if (flag) {
                S[top++]=cur[u]; u=v; continue;
            } int MIN=n;
            for (int i=head[u]; ~i; i=edge[i].next) {
                v=edge[i].to;
                if (edge[i].cap&&dep[v]<MIN)
                    MIN=min(MIN,dep[v]),cur[u]=i;
            } gap[dep[u]]--;
            if (ret>INF) return ret;//not okay
            if (!gap[dep[u]]) return ret;
            dep[u]=MIN+1; gap[dep[u]]++;
            if (u!=s) u=edge[S[--top]^1].to;
        } return ret;
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int)); tot=0;
    }
}
int idx[maxn];
int main() {
    int n1,n2,m,q;
    scanf("%d%d%d%d",&n1,&n2,&m,&q);
    maxflow::init(n1+n2+2);
    int S=n1+n2+1,T=n1+n2+2;
    FOR(i,1,n1) maxflow::addedge(S,i,1);
    FOR(i,1,n2) maxflow::addedge(i+n1,T,1);
    FOR(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        idx[i]=maxflow::addedge(x,y,1);
    }
    int cut=maxflow::sap(S,T);
    ll sum=0;
    FOR(i,1,m) if (!maxflow::edge[i].cap) sum+=i;
}
/*
*/