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
const LL maxn=3e5+107;
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

struct seg{
    ll T[maxn*4],lz[maxn*4]; ll MAX[maxn*4];
    void build(int x,int L,int R) {
        if (L==R) {
            T[x]=0; lz[x]=0; MAX[x]=0;
            return;
        } int mid=(L+R)/2;
        build(x<<1,L,mid); build(x<<1|1,mid+1,R);
        MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
    }
    void pushdown(int x) {
        if (lz[x]) {
            lz[x<<1]+=lz[x]; T[x<<1]+=lz[x]; MAX[x<<1]+=lz[x];
            lz[x<<1|1]+=lz[x]; T[x<<1|1]+=lz[x]; MAX[x<<1|1]+=lz[x];
            lz[x]=0;
        }
    }
    void _update(int x,int l,int r,ll val,int L,int R) {
        // printf("%d %d %d %lld %d %d\n",x,l,r,val,L,R);
        if (l<=L&&R<=r) {
            lz[x]+=val; T[x]+=val; MAX[x]+=val;
            return;
        } int mid=(L+R)/2;
        pushdown(x);
        if (l<=mid) _update(x<<1,l,r,val,L,mid);
        if (mid<r) _update(x<<1|1,l,r,val,mid+1,R);
        MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
    }
    void update(int x,int l,int r,ll val,int L,int R){
        // printf("upd %d %d %d %lld\n",x,l,r,val);
        _update(x,l,r,val,L,R);
    }
    ll query(int x,int l,int r,int L,int R) {
        if (l<=L&&R<=r) {
            return MAX[x];
        } int mid=(L+R)/2; ll ret=-INFF;
        pushdown(x);
        if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
        if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
        MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
        return ret;
    }
}T[2];
//区间: left区间小于x: ans=max(ans,value)
vector<pii> V[maxn][2];
ll w[maxn][2];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int i;
    FOR(i,1,n) scanf("%lld",&w[i][0]);
    FOR(i,1,n) scanf("%lld",&w[i][1]);
    FOR(i,1,m) {
        int t,l,r,c;
        scanf("%d%d%d%d",&t,&l,&r,&c);
        t--; V[r][t].push_back(make_pair(l,(ll)c));
    }
    T[0].build(1,0,n); T[1].build(1,0,n);
    FOR(i,1,n) {
        int o;
        REP(o,2) {
            T[o].update(1,0,i-1,w[i][o],0,n);
            sort(V[i][o].begin(), V[i][o].end());
            reverse(V[i][o].begin(), V[i][o].end());
            for (auto now:V[i][o]) {
                int pos=now.first; ll mor=now.second;
                T[o].update(1,0,pos-1,mor,0,n);
            }
        }
        ll fx=T[0].query(1,0,i-1,0,n);
        ll fy=T[1].query(1,0,i-1,0,n);
        ll fin=max(fx,fy);
        T[0].update(1,i,i,fin,0,n);
        T[1].update(1,i,i,fin,0,n);
        // printf("%lld %lld\n",fx,fy);
        if (i==n) printf("%lld\n",fin);
    }
    if (n==0) puts("0");
}
/*
2 4
1 0
0 0
1 2 2 1
1 2 2 1
2 2 2 1
2 1 2 6


5 5
-10 -3 -10 -10 -10 
0 2 0 0 0
1 1 1 11
1 2 2 11
1 3 3 11
1 4 4 11
1 5 5 11

5 4
0 0 0 0 0
0 0 0 0 0
2 1 2 3
2 1 2 3
2 2 2 5
2 2 4 1
*/