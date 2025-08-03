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
const LL maxn=2e6+7;
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

int n;
int pos[maxn];
vector<pii> Q1[maxn],Q2[maxn];
int MAX[maxn],ans[maxn];
inline int lowbit(int x) {return x&-x;}
inline void update(int x,int val) {
    x=n+1-x;
    for (;x<=n;x+=lowbit(x)) max_(MAX[x],val);
}
inline int query(int x) {
    x=n+1-x;
    int ret=0;
    for (;x;x-=lowbit(x)) ret=max(ret,MAX[x]);
    return ret;
}
int A[maxn];
set<int> S;//right-max-values
int fa[maxn];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    int i,q;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    scanf("%d",&q);
    FOR(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        Q1[r].push_back(make_pair(l,i));
        Q2[l].push_back(make_pair(r,i));
    }
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,n) {
        int prev=pos[A[i]];
        if (prev) fa[prev]=prev+1;
        update(prev+1,i-prev-1);
        pos[A[i]]=i;
        for (auto now:Q1[i]) {
            int l=now.first,id=now.second;
            int lmax=getfa(l);
            max_(ans[id],i-lmax);
            max_(ans[id],query(l));
            // printf("%d->%d: r=%d mid=%d\n",l,i,i-lmax,query(l));
            // for (int v:S) printf("%d ",v); puts("<- Set inside");
        }
    } S.clear();
    FOR(i,1,2000000) pos[i]=0;
    FOR(i,1,n) fa[i]=i;
    rFOR(i,1,n) {
        int prev=pos[A[i]];
        if (prev) fa[prev]=prev-1;
        pos[A[i]]=i;
        for (auto now:Q2[i]) {
            int r=now.first,id=now.second;
            int rmax=getfa(r);
            max_(ans[id],rmax-i);
            // printf("%d->%d: left=%d\n",i,r,rmax-i);
            // for (int v:S) printf("%d ",v); puts("<- Set inside");
        }
    } S.clear();
    FOR(i,1,q) printf("%d\n",ans[i]);
}
/*
10
1 3 2 3 3 2 2 1 3 2
10
2 4
1 3
2 5
1 1
1 4
1 10
3 6
2 7
3 8
9 10

12
1 1 2 3 4 5 6 7 8 9 1 1
10
2 4
1 3
2 12
1 12
1 11
1 10
3 6
2 7
3 8
6 10
*/