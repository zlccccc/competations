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
const LL maxn=2e5+107;
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

map<int,int> fac[maxn];
int inv[maxn];
void preprocess() {
    int i,j;
    FOR(i,2,200000) if (!fac[i].size()) {
        for (j=i;j<=200000;j+=i) {
            for (int k=j;k%i==0;k/=i) fac[j][i]++;
        }
    }
    FOR(i,1,200000) inv[i]=powMM(i,M-2); 
}
vector<array<int,3> > edge[maxn];
map<int,int> MP[maxn]; // id,count
void dfs(int x,int fa) {
    for (auto now:edge[x]) {
        int v=now[0];
        if (v==fa) continue;
        dfs(v,x);
        for (auto k:fac[now[1]]) MP[v][k.first]+=k.second;//multiply
        for (auto k:fac[now[2]]) MP[v][k.first]=max(0,MP[v][k.first]-k.second);//divide;
        if (MP[v].size()>MP[x].size()) swap(MP[v],MP[x]);
        for (auto nowval:MP[v]) max_(MP[x][nowval.first],nowval.second); //nowx.first: multiply ??
        map<int,int>().swap(MP[v]);
        // printf("dfs: %d-%d\n",x,v);
        // for (auto now:MP[x]) printf("%d,%d ",now.first,now.second); puts("<- dfsxy,now");
    }
    // printf("x=%d\n",x);
    // for (auto now:MP[x]) printf("%d,%d ",now.first,now.second); puts("<- now");
}
int nowans;
void dfs2(int x,int fa,int nowval) {
    // printf("dfs2: %d: %d\n",x,nowval);
    add_(nowans,nowval);
    for (auto now:edge[x]) {
        int v=now[0];
        if (v==fa) continue;
        int down=nowval;
        mul_(down,inv[now[1]]);
        mul_(down,now[2]);
        dfs2(v,x,down);
    }
}
int main() {
    preprocess();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i;
        scanf("%d",&n);
        FOR(i,1,n) vector<array<int,3> >().swap(edge[i]),MP[i].clear();
        FOR(i,1,n-1) {
            int u,v,x,y,g;
            scanf("%d%d%d%d",&u,&v,&x,&y);
            g=gcd(x,y); x/=g; y/=g;
            edge[u].push_back({v,x,y});
            edge[v].push_back({u,y,x});
        } dfs(1,0);
        int nowval=1;
        for (auto now:MP[1]) mul_(nowval,powMM(now.first,now.second));
        // printf("nowval=%d\n",nowval);
        nowans=0;
        dfs2(1,0,nowval);
        printf("%d\n",nowans);
    }
}
/*
10
4
999999999 999999999 999999999 999999999
*/