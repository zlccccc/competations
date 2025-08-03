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
const LL maxn=1.2e6+107;
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

char ans[107][107];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,k,i,j,mustx=0,musty=0;
        scanf("%d%d%d",&n,&m,&k);
        FOR(i,1,n) ans[i][m+1]=0;
        FOR(i,1,n) FOR(j,1,m) ans[i][j]='a';//front
        if (n&1) {
            mustx+=m/2;
            REP(i,m) ans[n][i+1]=((i/2)&1)+'y';
        }
        if (m&1) {
            musty+=n/2;
            REP(i,n) ans[i+1][m]=((i/2)&1)+'y';
        }
        int remain=n*m/2-mustx-musty;
        // printf("must %d %d; remain=%d\n",mustx,musty,remain);
        if (!(mustx<=k&&k-mustx<=remain)) puts("NO");
        else {
            k-=mustx;
            if ((remain&1)!=(k&1)) puts("NO");
            else {
                puts("YES");
                FOR(i,1,n/2) FOR(j,1,m/2) {
                    int base=(i+j)%4*2+'a';
                    int x=i*2-1,y=j*2-1;
                    if (k) {
                        k-=2;
                        ans[x][y]=ans[x][y+1]=base;
                        ans[x+1][y]=ans[x+1][y+1]=base+1;
                    } else {
                        ans[x][y]=ans[x+1][y]=base;
                        ans[x][y+1]=ans[x+1][y+1]=base+1;
                    }
                }
                FOR(i,1,n) puts(ans[i]+1);
            }
        }
    }
}
/*
8
4 4 2
10 10 10
10 11 10
11 10 10
*/