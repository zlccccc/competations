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

ll merge(ll x,ll y) {
    if (!x||!y) return x|y;
    while (!(x&1)) x>>=1;
    while (!(y&1)) y>>=1;
    while (x!=y) {
        if (x<y) swap(x,y); x=x^y;
        while (!(x&1)) x>>=1;
    } return x;
}
ll T[maxn*4];
inline void update(int x,int pos,ll val,int L,int R) {
    if (L==R) {while (!(val&1)) val>>=1; T[x]=val; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    else update(x<<1|1,pos,val,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
inline ll query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2; ll ret=0;
    if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
int main() {
    int i,n,m;
    scanf("%d",&n);
    FOR(i,1,n) {
        ll k;
        scanf("%lld",&k);
        update(1,i,k,1,n);
    } scanf("%d",&m);
    FOR(i,1,m) {
        int op; ll l,r;
        scanf("%d%lld%lld",&op,&l,&r);
        if (op==1) update(1,l,r,1,n);
        else printf("%lld\n",query(1,l,r,1,n));
    }

}
/*
3
3 5 15
3
2 1 3
1 2 11
2 1 2
*/