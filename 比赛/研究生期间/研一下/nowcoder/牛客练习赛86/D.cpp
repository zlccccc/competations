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

int A[maxn];
int Cnt[maxn];
int main() {
    int n,i,k;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    int all2=0,max2=0,ans=0;
    FOR(i,1,n-1) if (A[i]==A[i+1]) Cnt[A[i]]++; else ans++;
    FOR(i,1,n) all2+=Cnt[i],max2=max(max2,Cnt[i]);
    int p2=min(all2-max2,all2/2),rem2=min(p2,k);
    k-=rem2; ans+=rem2*2; all2-=rem2*2;
    // printf("rem2=%d; k=%d; p2=%d; all2=%d ansnow=%d\n",rem2,k,p2,all2,ans);
    ans+=min(all2,k);//one; not right

    int max1=0;
    FOR(i,1,n) Cnt[i]=0;
    FOR(i,1,n) Cnt[A[i]]++;
    FOR(i,1,n) max1=max(max1,Cnt[i]);
    ans=min(ans,(n-max1)*2);//fix one
    printf("%d\n",ans);
}
/*
5 0
1 1 1 2 2
10 1
1 1 1 2 2 2 1 1 1 1
10 3
1 1 1 2 2 3 1 1 1 1
*/