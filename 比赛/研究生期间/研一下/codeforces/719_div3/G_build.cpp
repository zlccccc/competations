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
const LL M=998244353;
const LL maxn=4e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

int n,m;
inline int getid(int x,int y){
    return (x-1)*m+y;
}
struct node {
    int n; LL d;
    node(int _n=0,LL _d=0):n(_n),d(_d) {};
    const bool operator <(const node &A)const {
        if (d!=A.d) return d>A.d;//注意!!! 否则为未优化的bellmanford
        return n>A.n;
    }
};
vector<node> edge[maxn];
void addedge(int x,int y,int val) {
    // printf("%d->%d: %d\n",x,y,val);
    edge[x].push_back(node(y,val));
}
priority_queue<node> Q;
ll dis[maxn];
int id[2007][2007];
int main() {
    int i,j,w;
    scanf("%d%d%d",&n,&m,&w);
    memset(id,0xff,sizeof(id));
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&id[i][j]);
    FOR(i,1,n) FOR(j,1,m) if (id[i][j]>=0) {
        if (id[i+1][j]>=0) addedge(getid(i,j),getid(i+1,j),w);
        if (id[i-1][j]>=0) addedge(getid(i,j),getid(i-1,j),w);
        if (id[i][j+1]>=0) addedge(getid(i,j),getid(i,j+1),w);
        if (id[i][j-1]>=0) addedge(getid(i,j),getid(i,j-1),w);
        if (id[i][j]>0) {
            addedge(getid(i,j),n*m+1,id[i][j]);
            addedge(n*m+1,getid(i,j),id[i][j]);
        }
    }
    FOR(i,1,n*m+1) dis[i]=INFF;
    dis[1]=0;
    Q.push(node(1,0));
    while (Q.size()) {
        node x=Q.top(); Q.pop();
        // printf("%d: %lld\n",x.n,x.d);
        if (dis[x.n]!=x.d) continue;//!
        for (node y:edge[x.n]) {
            if (dis[y.n]>x.d+y.d) {
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
    if (dis[getid(n,m)]!=INFF) printf("%lld\n",dis[getid(n,m)]);
    else puts("-1");
}
/*
6 1 2
*/