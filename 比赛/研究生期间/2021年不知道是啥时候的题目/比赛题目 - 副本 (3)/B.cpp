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
const LL maxn=1e6+107;
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

int isprime[maxn],A[57];
char s[maxn];
int solve() {
    int n,i,j,k,o,p;
    scanf("%d%s",&n,s+1);
    FOR(i,1,n) A[i]=s[i]-'0';
    FOR(i,1,n) {
        int t=A[i];
        if (!isprime[t]) return 0*printf("1\n%d\n",t);
    }
    FOR(i,1,n) FOR(j,i+1,n){
        int t=A[i]*10+A[j];
        if (!isprime[t]) return 0*printf("2\n%d\n",t);
    }
    FOR(i,1,n) FOR(j,i+1,n) FOR(k,j+1,n){
        int t=A[i]*100+A[j]*10+A[k];
        if (!isprime[t]) return 0*printf("3\n%d\n",t);
    }
    FOR(i,1,n) FOR(j,i+1,n) FOR(k,j+1,n) FOR(o,k+1,n){
        int t=A[i]*1000+A[j]*100+A[k]*10+A[o];
        if (!isprime[t]) return 0*printf("4\n%d\n",t);
    }
    FOR(i,1,n) FOR(j,i+1,n) FOR(k,j+1,n) FOR(o,k+1,n) FOR(p,o+1,n){
        int t=A[i]*10000+A[j]*1000+A[k]*100+A[o]*10+A[p];
        if (!isprime[t]) return 0*printf("5\n%d\n",t);
    }
}
int main() {
    int i;
    FOR(i,2,1000000) isprime[i]=1;
    FOR(i,2,1000000) if (isprime[i]) for (int j=i+i;j<=1000000;j+=i) isprime[j]=0;
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
*/