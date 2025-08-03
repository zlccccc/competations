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

char A[maxn],B[maxn];
int to[27],comp[27];
int dp[1<<20|7];//judge 
int main() {
    int _T,_; _T=1;
    scanf("%d",&_T);
    FOR(_,1,_T){
        int n;
        scanf("%d",&n);
        scanf("%s%s",A,B);
        int i,k;
        REP(i,20) to[i]=comp[i]=0;
        REP(i,n) if (A[i]!=B[i]) {
            to[A[i]-'a']|=1<<(B[i]-'a');
            comp[B[i]-'a']|=1<<(A[i]-'a');
            comp[A[i]-'a']|=1<<(B[i]-'a');
            // printf("%d->%d\n",A[i]-'a'+1,B[i]-'a'+1);
        }
        REP(k,20) REP(i,20) if ((comp[i]>>k)&1) comp[i]|=comp[k];
        REP(i,(1<<20)) {
            dp[i]=INF; if (i==0) dp[i]=0;
            REP(k,20) if ((i>>k)&1) {//add from right
                int sta=i^(1<<k);
                int now=dp[sta]+min(1,comp[k]&sta)+min(1,to[k]&sta);//A->B->...->k
                min_(dp[i],now);
                // if (now) {pr2(i,4); pr2(comp[k],4); pr2(to[k],4); printf("k=%d; now=%d\n",k,now);}
            }
        }
        printf("%d\n",dp[(1<<20)-1]);
    }

}
/*
5
3
aab
bcc
4
cabc
abcb
3
abc
tsr
4
aabd
cccd
5
abcbd
bcdda

10
4
aabd
cccd

10
4
cabc
abcb
*/