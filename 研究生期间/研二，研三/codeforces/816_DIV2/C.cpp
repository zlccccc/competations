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

//UVALive 8191 
set<pii> POS;
int n;
ll ans=0;
int A[maxn];
void rem(int l,int r) {
    if (l==r+1) return;
    ll le=l-1,ri=n-r+1-1;
    ans-=(ll)n*(n+1)/2-le*(le+1)/2-ri*(ri+1)/2;
    POS.erase(make_pair(l,r));
}
void add(int l,int r) {
    if (l==r+1) return;
    ll le=l-1,ri=n-r+1-1;
    ans+=(ll)n*(n+1)/2-le*(le+1)/2-ri*(ri+1)/2;
    POS.insert(make_pair(l,r));
}
void split(int pos) { // split pos and pos+1
    auto it=POS.upper_bound(make_pair(pos,INF)); it--;
    auto now=*it;
    assert(now.second>=pos+1);
    rem(now.first,now.second);
    add(now.first,pos);
    add(pos+1,now.second);
    // printf("split %d: %d %d; ans=%lld\n",pos,now.first,now.second,ans);
}
void merge(int pos) { // split pos and pos+1
    auto it=POS.upper_bound(make_pair(pos,INF));
    auto rig=*it;
    it--; auto lft=*it;
    assert(rig.first==pos+1);
    rem(lft.first,lft.second);
    rem(rig.first,rig.second);
    add(lft.first,rig.second);
    // printf("merge %d (%d %d); ans=%lld\n",pos,lft.first,rig.second,ans);
}
void update(int p,int x) {
    // printf("update %d %d\n",p,x);
    // for (auto p:POS) printf("(%d,%d) ",p.first,p.second); puts("");
    if (p!=1&&A[p]==A[p-1]) split(p-1);
    if (p!=n&&A[p]==A[p+1]) split(p);
    A[p]=x;
    if (p!=1&&A[p]==A[p-1]) merge(p-1);
    if (p!=n&&A[p]==A[p+1]) merge(p);
}
int main() {
    int m,i,x;
    scanf("%d%d",&n,&m);
    POS.insert(make_pair(1,n));
    ans=(ll)n*(n+1)/2;
    FOR(i,1,n) scanf("%d",&x),update(i,x);
    FOR(i,1,m) {
        int p,x;
        scanf("%d%d",&p,&x);
        update(p,x);
        printf("%lld\n",ans);
    }
}
/*
*/