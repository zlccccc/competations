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
const LL maxn=3e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=63) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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
 
void solve(ll n) {
    ll i,ii,j,m=0;
    vector<ll> ans;
    //first
    REP(i,63) if ((i&1)&&((n>>i)&1)) { //first
        REP(j,63) if (!(j&1)&&((n>>j)&1)) {
            ll now=(1ll<<i)|(1ll<<j);
            if ((now|m)!=m) ans.push_back(now),m|=now;
            m|=now;
        } break;
    }
    REP(i,63) if (!(i&1)&&((n>>i)&1)) { //first
        REP(j,63) if ((j&1)&&((n>>j)&1)) {
            ll now=(1ll<<i)|(1ll<<j);
            if ((now|m)!=m) ans.push_back(now),m|=now;
        } break;
    }
    REP(i,63) if ((i&1)&&((n>>i)&1)) { //first
        rep(ii,i+1,63) if ((ii&1)&&((n>>ii)&1)) {
            rep(j,ii+1,63) if ((j&1)&&((n>>j)&1)) {
                ll now=(1ll<<i)|(1ll<<ii)|(1ll<<j);
                if ((now|m)!=m) ans.push_back(now),m|=now;
                m|=now;
            } break;
        } break;
    }
    REP(i,63) if (!(i&1)&&((n>>i)&1)) { //first
        rep(ii,i+1,63) if (!(ii&1)&&((n>>ii)&1)) {
            rep(j,ii+1,63) if (!(j&1)&&((n>>j)&1)) {
                ll now=(1ll<<i)|(1ll<<ii)|(1ll<<j);
                if ((now|m)!=m) ans.push_back(now),m|=now;
                m|=now;
            } break;
        } break;
    }
    printf("m=%lld; n=%lld\n",m,n);
    // sort(ans.begin(), ans.end());
    // ans.erase(unique(ans.begin(), ans.end()),ans.end());
    // printf("%d",(int)ans.size());
    // for (ll v:ans) printf(" %lld",v); puts("");
}
int solve2(ll n) {
    if (n%3==0) return 0*printf("1 %lld\n",n);
    ll all=0,now,p,i;  
    //same
    vector<ll> ans;
    REP(i,63) if ((n>>i)&1) all=(all+i%2+1)%3;
    REP(i,63) if ((n>>i)&1) if (all==i%2+1) ans.push_back(n^(1ll<<i));
    now=all; p=n;
    REP(i,63) if ((n>>i)&1) {
        now=(now+3-(i%2+1))%3; p^=1ll<<i;
        if (!now) break;
    } ans.push_back(p);
    now=all; p=n;
    rREP(i,63) if ((n>>i)&1) {
        now=(now+3-(i%2+1))%3; p^=1ll<<i;
        if (!now) break;
    } ans.push_back(p);
    printf("%d ",2);
    for (ll v:ans) for (ll u:ans) {
        if ((u|v)==n) return 0*printf("%lld %lld\n",u,v);
    }
    return 0;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    int i;
    // FOR(i,1,100) solve(rand());
    REP(_,T) {
        ll n;
        scanf("%lld",&n);
        solve2(n);
    }
}
/*
*/