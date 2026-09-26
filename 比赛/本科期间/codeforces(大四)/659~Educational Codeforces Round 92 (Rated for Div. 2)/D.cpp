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

int cnt[10][10];
char str[maxn];
int main() {
    int _T,_; _T=1;
    scanf("%d",&_T);
    FOR(_,1,_T){
        int i; int n;
        ll l1,r1,l2,r2,k;
        scanf("%d%lld",&n,&k);
        scanf("%lld%lld%lld%lld",&l1,&r1,&l2,&r2);
        if (l1>l2) swap(l1,l2),swap(r1,r2);
        ll ans=0;
        if (l2<r1) {
            int dr=min(r1,r2);
            k-=(dr-l2)*n;
            r1-=dr-l2; r2-=dr-l2;
        } if (k<=0) {printf("%lld\n",ans); continue;}
        // printf("solve 1 done; %lld-%lld %lld-%lld; remain k=%lld\n",l1,r1,l2,r2,k);
        ll tow_ans=INFF;
        FOR(i,1,n) {
            ans+=max(0ll,l2-r1);
            ll maxdel=max(r2,r1)-min(l2,l1);
            maxdel=min(k,maxdel);
            k-=maxdel; ans+=maxdel;//one
            min_(tow_ans,ans+2*k);
            if (!k) break;
        }
        // printf("solve 2 done; %lld-%lld %lld-%lld; remain k=%lld\n",l1,r1,l2,r2,k);
        printf("%lld\n",tow_ans);
    }
}
/*
2
5
01011
11100
*/