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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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

int n,m,k;
pair<ll,int> dp[maxn];
int A[maxn];
pair<ll,int> solve_slope(ll w,int output=0) {//slope
    static int Q[maxn],head=0,tail=0;
    int i;
    head=tail=0;
    Q[0]=0;
    FOR(i,1,n+1) {
        if (Q[head]==i-m-1) head++;
        dp[i]=dp[Q[head]];
        dp[i].first+=A[i]-w; dp[i].second++;
        // if (output) printf("dp=(%lld,%d), l,r=%d %d; i-m=%d\n",dp[i].first,dp[i].second,head,tail,i-m);
        while (head<=tail&&dp[Q[tail]]>dp[i]) tail--;
        Q[++tail]=i;
    }
    pair<ll,int> ans=dp[n];
    FOR(i,n-m+1,n) ans=min(ans,dp[i]);
    // printf("w=%lld: %lld %d\n",w,ans.first,ans.second);
    // printf("%d %d\n",dp[n+1].first,dp[n+1].second);
    return ans;
}
ll solve() {//n,m
    ll l=-1000000000,r=1000000000;
    while (l+1<r) {
        ll mid=l+(r-l)/2;
        auto ans=solve_slope(mid);
        if (ans.second>k) r=mid;
        else l=mid;
        // printf("l=%lld; r=%lld; m=%d, dp[n]=%d; k=%d\n",l,r,m,ans.second,k);
    } auto ans=solve_slope(l,1);
    // 这里的意义: 假设每次的答案都是最后一次的斜率
    // 然后, 二分这个斜率, 找到答案后减去每次的贡献
    // printf("l=%lld; m=%d\n",l,m);
    return ans.first+l*k;
}
int main() {
    int i;
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        scanf("%d%d%d",&n,&m,&k);
        FOR(i,1,n) scanf("%d",&A[i]);
        printf("%lld\n",solve());
    }
}
/*
2
6 2 4
1 1 4 5 1 4
7 2 4
1 9 1 9 8 1 0
*/