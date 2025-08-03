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
const LL maxn=1e5+107;
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

//prefix sum=0:not ok
struct node{
    int amin,bmin,sum;
}T[maxn<<2],lb,rb;
bool tag[maxn<<2];
node merge(const node &x,const node &y) {
    node ret;//min:from_left
    ret.amin=min(x.amin,y.amin+x.sum);
    ret.bmin=min(x.bmin,y.bmin-x.sum);
    ret.sum=x.sum+y.sum;
    return ret;
}
void reverse(int x) {
    tag[x]^=1;
    swap(T[x].amin,T[x].bmin);
    T[x].sum=-T[x].sum;
}
void pushdown(int x) {
    if (tag[x]) {
        reverse(x<<1); reverse(x<<1|1);
        tag[x]=0;
    }
}
char str[maxn];
void build(int x,int L,int R) {
    if (L==R) {
        if (str[L]=='(') T[x]=lb;
        else T[x]=rb; return;
    } int mid=(L+R)/2;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) {
        reverse(x); return;
    } int mid=(L+R)/2;
    pushdown(x);
    if (l<=mid) update(x<<1,l,r,L,mid);
    if (mid<r) update(x<<1|1,l,r,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
int main() {
    lb.amin=0; lb.bmin=-1; lb.sum=1;//(
    rb.amin=-1; rb.bmin=0; rb.sum=-1;//)
    int n,q,i;
    scanf("%d%d",&n,&q);
    scanf("%s",str+1);
    build(1,1,n);
    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        update(1,l,r,1,n);
        if (T[1].amin==0&&T[1].sum==0) puts("Yes");
        else puts("No");
    }
}
/*
*/