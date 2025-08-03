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
const LL maxn=2e5+107;
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

//assert _x=x1/d, _y=y1/d; x2=(_x*_y)=>max
vector<int> fac[maxn];
set<int> S;
int cnt[maxn];
int main() {
    int n,m,i; ll l,r;
    scanf("%d%d%lld%lld",&n,&m,&l,&r);
    FOR(i,1,200000) {
        for (int j=i;j<=200000;j+=i) fac[j].push_back(i);
    } int lb=m+1,rb=m;
    FOR(i,1,n) {//x1>x2<=n
        ll ly=(l+i-1)/i,ry=r/i;
        while (ly<lb) {
            lb--;
            for (int v:fac[lb]) {
                if (!cnt[v]) S.insert(v);
                cnt[v]++;
            }
        }
        while (ry<rb) {
            for (int v:fac[rb]) {
                cnt[v]--;
                if (!cnt[v]) S.erase(S.lower_bound(v));
            }
            rb--;
        } bool okay=0;
        for (int _x:fac[i]) {
            int a=_x,b=i/_x;
            auto it=S.upper_bound(b);
            if (it==S.end()||*it>n/a) continue;
            int c=*it,d=rb/c;//d:exist
            printf("%d %d %d %d\n",a*b,c*d,a*c,b*d);
            okay=1; break;
        } if (!okay) puts("-1");
    }
}
/*
2
2 1
2 1
*/