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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
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

pii Pos[2007*2007];
char Ans[2007][2007];
int main() {
    int n,k,i,j; scanf("%d%d",&n,&k);
    FOR(i,1,n) FOR(j,1,n) {
        int val;
        scanf("%d",&val);
        Pos[val]={i-j,i+j};
    }
    //max(abs(dx),abs(dy))>k // one is okay
    int Minx=INF,Miny=INF,Maxx=-INF,Maxy=-INF;
    rFOR(i,1,n*n) {
        int win=1; // lose
        int dx=Pos[i].first,dy=Pos[i].second;
        if (dx-Minx>k||Maxx-dx>k) win=0;
        if (dy-Miny>k||Maxy-dy>k) win=0;
        int x=(dx+dy)/2,y=(dy-dx)/2;
        // printf("solve(%d,%d): dx,dy= %d %d; lose x:[%d-%d], y:[%d-%d]\n",x,y,dx,dy,Minx,Maxx,Miny,Maxy);
        if (win) {
            Ans[x][y]='M';
            min_(Minx,dx); min_(Miny,dy);
            max_(Maxx,dx); max_(Maxy,dy);
        } else Ans[x][y]='G';
    }
    FOR(i,1,n) puts(Ans[i]+1);
}
/*
*/