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
const LL maxn=1e5+107;
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

//树分治会T吧...
int m;
int A[maxn];
int orval[2][100],andval[2][100];
ll dp[2][100][2007];//position,dp
int main() {
    int n,i,j,k,o,tot=0;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    ll (*now)[2007]=dp[0],(*nxt)[2007]=dp[1];
    int *nowor=orval[0],*nxtor=orval[1];
    int *nowand=andval[0],*nxtand=andval[1];
    // now[1][1]=1;
    // printf("%d %d  %d %d\n",dp[0][1][1],now[1][1],dp[0],now);
    int MAX=0; REP(i,30) MAX|=1<<i;
    ++tot; nowor[tot]=0; nowand[tot]=MAX;
    FOR(j,0,k) now[tot][j]=-INFF; now[tot][0]=0;
    FOR(i,1,n) {
        int nxttot=0;
        FOR(o,1,tot) {
            int OR=nowor[o]|A[i],AND=nowand[o]&A[i];
            if (!nxttot||OR!=nxtor[nxttot]||AND!=nxtand[nxttot]) {
                ++nxttot; nxtor[nxttot]=OR; nxtand[nxttot]=AND;
                FOR(j,0,k) nxt[nxttot][j]=-INFF;
            }
            FOR(j,0,k) max_(nxt[nxttot][j],now[o][j]);
        }
        ++nxttot; nxtor[nxttot]=0; nxtand[nxttot]=MAX;
        FOR(j,0,k) nxt[nxttot][j]=-INFF;
        FOR(o,1,nxttot-1) {
            FOR(j,1,k) {
                max_(nxt[nxttot][j],nxt[o][j-1]+(nxtor[o]^nxtand[o]));
            }
        }
        // printf("%d:\n",i);
        // FOR(o,1,nxttot) {
        //     printf("(%d %d)",nxtor[o],nxtand[o]);
        //     FOR(j,0,k) {
        //         printf("%lld ",nxt[o][j]);
        //     } puts("");
        // }
        swap(tot,nxttot);
        swap(now,nxt);
        swap(nowor,nxtor);
        swap(nowand,nxtand);
    }
    printf("%lld\n",now[tot][k]);
}
/*
4
10 3 2
5 3 1
15 5 3
29 4 5

7 4
11 45 14 19 19 8 10

*/