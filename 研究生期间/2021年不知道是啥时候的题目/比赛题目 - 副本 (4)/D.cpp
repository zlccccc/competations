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

int val[maxn];
int A[maxn];
int get(int op,int x,int y) {
    if (op==0) printf("and ");
    if (op==1) printf("or ");
    printf("%d %d\n",x,y);
    fflush(stdout);
    // if (op==0) return val[x]&val[y];
    // if (op==1) return val[x]|val[y];
    int ret; scanf("%d",&ret);
    return ret;
}
int f[4][4],g[4][4];
int main() {
    int _T,_; _T=1;
    // scanf("%d",&_T);
    FOR(_,1,_T){
        int n,i,j,k;
        scanf("%d%d",&n,&k);
        // FOR(i,1,n) scanf("%d",&val[i]);
        FOR(i,1,3) FOR(j,i+1,3) {
            g[i][j]=get(0,i,j);
            f[i][j]=get(1,i,j);
        }
        A[1]=A[2]=A[3]=0;
        REP(i,31) {
            int a,b,c;
            REP(a,2) REP(b,2) REP(c,2) {
                if (((f[1][2]>>i)&1)!=(a|b)) continue;
                if (((f[1][3]>>i)&1)!=(a|c)) continue;
                if (((f[2][3]>>i)&1)!=(b|c)) continue;
                if (((g[1][2]>>i)&1)!=(a&b)) continue;
                if (((g[1][3]>>i)&1)!=(a&c)) continue;
                if (((g[2][3]>>i)&1)!=(b&c)) continue;
                A[1]|=a<<i; A[2]|=b<<i; A[3]|=c<<i;
            }
        }
        FOR(i,4,n) {
            A[i]=get(0,1,i)^get(1,1,i)^A[1];
        }
        // FOR(i,1,n) printf("%d ",A[i]); puts("<- A");
        sort(A+1,A+1+n);
        printf("finish %d\n",A[k]);
        fflush(stdout);
    }
}
/*
7 6
1 6 4 2 3 5 4
*/