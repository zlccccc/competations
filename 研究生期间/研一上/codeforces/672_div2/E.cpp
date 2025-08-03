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
const LL maxn=3e5+107;
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

int n;
int A[2][81][81][81*81];//;count-of-id
int prefix[87];
int ans[87];
int main() {
    int i,j,k,t;
    scanf("%d",&n);
    FOR(i,1,n) {
        scanf("%d",&prefix[i]);
        prefix[i]+=prefix[i-1];//notsame: move=abssum
    }
    int cnt=0;
    auto now=A[0],nxt=A[1];
    FOR(i,0,n) FOR(j,0,i) FOR(k,0,i*(i+1)/2) now[i][j][k]=-INF;//k:already-moved
    now[0][0][0]=0;
    FOR(i,0,n-1) {
        i++;
        FOR(j,0,i) FOR(k,0,i-j) {
            FOR(t,0,i*(i+1)/2) nxt[j][k][t]=-INF;
        } i--;
        FOR(j,0,i) FOR(k,0,i-j) {//1s; 0s
            FOR(t,0,i*(i+1)/2) if (now[j][k][t]!=-INF) {//i-count; j-prefixsum; k-movecount
                // printf("val=(%d %d %d) Cnt=%d: %d;\n",i,j,k,t,now[j][k][t]);
                cnt++;
                // max_(A[i+1][j+k][0][t+abs(j+k-prefix[i+1])],A[i][j][k][t]);//1
                // max_(A[i+1][j][k+1][t+abs(j+k+1-prefix[i+1])],A[i][j][k][t]+j);//0
                max_(nxt[j+k][0][t+abs(i+1-(j+k)-prefix[i+1])],now[j][k][t]);//1
                max_(nxt[j][k+1][t+abs(i+1-(j+k+1)-prefix[i+1])],now[j][k][t]+j);//0
                // printf("  A1=(%d %d %d) Cnt=%d: %d;\n",i+1,j+k,0,t+abs(j+k+1-prefix[i+1]),now[j][k][t]);
                // printf("  A0=(%d %d %d) Cnt=%d: %d;\n",i+1,j,k+1,t+abs(j+k-prefix[i+1]),now[j][k][t]+j);
            }
        } swap(now,nxt);
        // system("pause");
    }
    // printf("cnt=%d\n",cnt);
        int ans=0;
    FOR(i,0,n*(n-1)/2) {
        REP(j,n) ans=max(ans,now[j][(n-prefix[n])-j][i]);
        printf("%d%c",ans," \n"[i==n*(n-1)/2]);
    }
}
/*
5
0 0 1 0 0
*/