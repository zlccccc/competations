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
const LL maxn=5e5+107;
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

int T[maxn<<2];
void update(int x,int pos,int val,int L,int R) {
    T[x]=max(T[x],val);
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    else update(x<<1|1,pos,val,mid+1,R);
}
int query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int ret=0,mid=(L+R)/2;
    if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
vector<int> edge[maxn];
int in[maxn],out[maxn],tot;
void dfs(int x) {
    in[x]=++tot;
    for (int v:edge[x]) dfs(v);
    out[x]=tot;
}
int A[maxn];
int main() {
    int i,n,m;
    scanf("%d%d",&n,&m);
    FOR(i,2,n) {
        int f; scanf("%d",&f);
        edge[f].push_back(i);
    } dfs(1);
    FOR(i,1,m) scanf("%d",&A[i]);
    rFOR(i,1,m) {
        int now=query(1,in[A[i]]+1,out[A[i]],1,n)+1;
        // printf("%d: %d %d  %d\n",A[i],in[A[i]]+1,out[A[i]],now);
        update(1,in[A[i]],now,1,n);
    } printf("%d\n",T[1]);
}
/*
*/