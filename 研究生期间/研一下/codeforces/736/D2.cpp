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
const LL maxn=6000+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
int gcd(int a, int b) {return b?gcd(b,a%b):a;}
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

pii A[maxn];
int g[maxn][maxn],GCD_[7][7];
int f[4][4][4];//gcd,dx,dy)
int main() {
    int n,i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&A[i].first,&A[i].second);
    FOR(i,1,n) FOR(j,1,i-1) {
        g[i][j]=g[j][i]=gcd(abs(A[i].first-A[j].first),abs(A[i].second-A[j].second))&3;
    } FOR(i,1,n) A[i].first&=3,A[i].second&=3;
    // S=a+b/2-1; b=\sum gcd(dx,dy)
    // a=S-b/2+1; a: A-B-C = A-B ^ A-C ^ B-C
    // only calculate gcd
    // Emmmm... the area of the fence is an integer --> we use 110/000
    ll ans0=0,ans1=0;
    // REP(i,7) REP(j,7) GCD_[i][j]=gcd(i,j);
    FOR(i,1,n) {
        memset(f,0,sizeof(f));
        FOR(j,1,n) if (i!=j) f[g[i][j]][A[j].first][A[j].second]++;//A-B, A-C
        int g0,g1;
        int x0,y0,x1,y1;
        int x2=A[i].first,y2=A[i].second;
        REP(g0,4) REP(g1,4) if (!((g0^g1)&1)) {//integer
            REP(x0,4) REP(y0,4) REP(x1,4) REP(y1,4) {
                int cx=f[g0][x0][y0],cy=f[g1][x1][y1];
                if (g0==g1&&x0==x1&&y0==y1) cy--;
                if (!cx||!cy) continue;
                int g2=gcd(abs(x0-x1),abs(y0-y1));//same odd
                // int g2=GCD_[abs(x0-x1)&3][abs(y0-y1)&3];
                if (g2&1) continue; // M
                int now=4000-(g0+g1+g2);
                int siz=x0*(y1-y2)+x1*(y2-y0)+x2*(y0-y1);
                now+=siz;
                // if (now&1) continue;
                now>>=1; now-=1;
                if (!(now&1)) continue;
                if (g0&1) ans1+=cx*cy;
                else ans0+=cx*cy;
                // printf("i=%d: (%d,%d,%d), (%d,%d,%d), (%d,%d,%d); now=%d siz=%d %d (%d:%lld;%lld)\n",i,g0,x0,y0,g1,x1,y1,g2,x2,y2,now,siz&3,cx*cy,g0&1,ans0,ans1);
            }
        }
    }
    printf("%lld\n",ans0/6+ans1/2);
}
/*
10
170 59
129 54
5 98
129 37
58 193
154 58
24 3
13 138
136 144
174 150

7
170 59
129 54
5 98
129 37
58 193
154 58
24 3

*/