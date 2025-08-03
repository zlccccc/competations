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

pll P[maxn];
void solve () {
    int i,n; ll k;
    // A[i]+B[i]>=k --> k-=B[i], judge(A[i])[judge-limit]{+B[i]<=A[i]}
    scanf("%d%lld",&n,&k);
    FOR(i,1,n) scanf("%lld%lld",&P[i].first,&P[i].second);
    P[n+1].first=P[n+1].second=0;
    sort(P+2,P+1+n,[&](pll x,pll y) {
        return x.first+x.second>y.first+y.second;
    });
    // 特判first
    if (k<=P[1].first) {puts("YES"); return;}
    if (k>P[1].first+P[1].second) {puts("NO"); return;}
    k-=P[1].second; // not first!
    // others
    priority_queue<pll> Q;
    FOR(i,2,n+1) {
        // limit: k+p.second > P[i].first+P[i].second (could not remove more)
        // judge: k+p.second <= p.first
        while (Q.size()&&(i==n+1||k+Q.top().first>P[i].first+P[i].second)) { // select the first one
            auto p=Q.top(); Q.pop();
            swap(p.first,p.second);
            if (k+p.second<=p.first) {
                // printf("k=%lld; p.first,second=%d %d\n",k,p.first,p.second);
                puts("YES"); return;
            } // first
        }
        if (i==n+1) {puts("NO"); return;}
        if (k<=P[i].first) {puts("YES"); return;}
        if (k<=P[i].first+P[i].second) {
            k-=P[i].second;
            Q.push({P[i].second,P[i].first});
        } else Q.push({0,P[i].first}); // could not remove, but could check
    }
    assert(0);
    // puts("NO");
    // puts("Not Solved");
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
10
6 6
3 3 1 1 1 1 1 1 1 1 1 1 1

4 16
5 3
8 12
10 7
15 1
4 16
8 12
10 7
15 1
5 3
4 16
10 7
15 1
5 3
8 12
4 16
15 1
5 3
8 12
10 7
1 1000000000
500000000 500000000
2 1000000000
1 999999999
1 1

1 12
1 100000000
*/