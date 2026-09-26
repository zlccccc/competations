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

vector<ll> v;
int f[maxn];
ll ans;
void solve(ll x,int pos,ll nowans) {
    if (pos==0) {ans=min(ans,nowans+x); return;}
    if (x<=1000000) {ans=min(ans,nowans+f[x]); return;}
    ll maxv=x/v[pos]; //min-count-inside
    int i;
    rFOR(i,0,maxv) {
        if (maxv+nowans>ans) return;
        solve(x-i*v[pos],pos-1,nowans+i);
    }
}
int main() {
    int i;
    ll x;
    v.push_back(1);
    for (x=6;x<=1e12;x=x*6) v.push_back(x);
    for (x=9;x<=1e12;x=x*9) v.push_back(x);
    sort(v.begin(),v.end());
    // printf("%d\n",(int)v.size());
    // for (ll k:v) printf("%lld ",k); puts("<- k");
    const int MAX=1e6;
    FOR(i,1,MAX) {
        f[i]=i;
        for (ll k:v) if (k<=i) min_(f[i],f[i-k]+1);
        else break;
    }
    // FOR(i,1,20) printf("%d ",f[i]); puts("<- f");
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        ll n; scanf("%lld",&n);
        ans=INF;
        solve(n,v.size()-1,0);
        printf("%lld\n",ans);
    }
}
/*
4
6
9
998244353
1000000007
*/