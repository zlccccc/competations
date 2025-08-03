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

ll val[100],k[100];
int tot;
bool done;
ll A,B,C,D;
void dfs(int pos,ll v) {
    if (done) return;
    // printf("dfs %d %lld; val=%lld,k=%lld\n",pos,v,val[pos],k[pos]);
    if (pos==tot) {
        // printf("dfs %lld\n",v);
        ll x=v,y=A*B/v;
        x=C/x*x; y=D/y*y;
        if (x>A&&y>B) {printf("%lld %lld\n",x,y); done=1;}
        return;
    }
    int i;
    FOR(i,0,k[pos]) dfs(pos+1,v),v*=val[pos];
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        memset(val,0,sizeof(val));
        memset(k,0,sizeof(k));
        ll a,b;
        scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
        a=A; b=B; tot=0;
        for (ll i=2;i*i<=a||i*i<=b;i++) {
            val[tot]=i; k[tot]=0;
            while (a%i==0) k[tot]++,a/=i;
            while (b%i==0) k[tot]++,b/=i;
            if (k[tot]) tot++;
        }
        if (a!=1) val[tot]=a,k[tot]=1,tot++;
        if (a==b&&b!=1) b=1,k[tot-1]++;
        if (b!=1) val[tot]=b,k[tot]=1,tot++;
        done=0;
        dfs(0,1);
        if (!done) puts("-1 -1");
    }
}
/*
2 3
1 2 5
3 4 6
*/