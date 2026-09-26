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

int mark[127][127]; // not useful
void solve() {
    int n=5,_;
    FOR(_,0,20) {
        int x,y;
        mark[0][0]|=1;
        rREP(x,n) rREP(y,n) if (mark[x][y]&1) {
            if (!(mark[x][y]&2)) mark[x][y+1]|=1;
            else mark[x+1][y]|=1;
            mark[x][y]&=2; mark[x][y]^=2;
        }
        mark[0][0]|=1;
        printf("i=%d\n",_);
        REP(x,n) REP(y,n) printf("%d%c",mark[x][y]&1," \n"[y==n-1]);
        puts("");
    }
}
ll C1[256],C2[257];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        ll t; int x,y;
        scanf("%lld%d%d",&t,&x,&y);
        t-=x+y;
        if (t<0) {puts("NO"); continue;}
        memset(C1,0,sizeof(C1));
        memset(C2,0,sizeof(C2));
        C1[0]=t; C2[0]=t+1; // number
        int i,j;
        FOR(i,1,x+y) {
            rREP(j,i) {
                C1[j+1]+=C1[j]/2,C1[j]-=C1[j]/2;
                C2[j+1]+=C2[j]/2,C2[j]-=C2[j]/2;
            }
        }
        // FOR(i,0,x+y) printf("%lld ",C1[i]); puts("<-C1");
        // FOR(i,0,x+y) printf("%lld ",C2[i]); puts("<-C2");
        FOR(i,0,x+y) if (C1[i]!=C2[i]) break;
        if (i==x) puts("YES");
        else puts("NO");
    }
}
/*
2 3
1 2 5
3 4 6
*/