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

ll A[maxn];
ll solve(int n,int l,int k) {
    ll ans=0; int cnt=n-l+1;
    int i,j;
    FOR(i,1,(n+k-1)/k) {
        int del=min(l-k,cnt); cnt-=del;
        ans+=(ll)A[i*k]*del;
        // FOR(j,1,del) printf("add-%lld\n",A[i*k]);
        del=min(k,cnt); cnt-=del;
        FOR(j,1,del) ans+=A[i*k+j-1];
        // FOR(j,1,del) printf("add-%lld\n",A[i*k+j-1]);
    } return ans;
}
int main() {
    int _T,_; _T=1;
    scanf("%d",&_T);
    FOR(_,1,_T){
        int n,i,l,k;
        scanf("%d%d%d",&n,&l,&k); 
        FOR(i,1,n) scanf("%lld",&A[i]);
        sort(A+1,A+1+n);
        ll ansmax=0,ansmin=0;
        ansmin=solve(n,l,l-k+1);
        reverse(A+1,A+1+n);
        ansmax=solve(n,l,k);
        printf("%lld %lld\n",ansmax,ansmin);
    }
}
/*
10
6 4 2
1 2 3 4 5 6
6 4 1
1 2 3 4 5 6
6 4 1
2 2 2 2 2 2
5 4 3
5 4 1 2 3
5 1 1
5 4 1 2 3

9 8 7
1 2 3 4 5 6 7 8 9 10
*/