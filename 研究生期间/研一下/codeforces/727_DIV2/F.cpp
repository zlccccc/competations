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
int A[maxn],S[maxn];
struct node{
    int lmax,rmax,sum;
}T[maxn*4];
node merge(const node &x,const node &y) {
    node ret;
    ret.sum=x.sum+y.sum;
    ret.lmax=max(x.lmax,y.lmax+x.sum);
    ret.rmax=max(x.rmax+y.sum,y.rmax);
    return ret;
}
void update(int x,int pos,int val,int L,int R) {
    if (L==R) {T[x].lmax=T[x].rmax=T[x].sum=val; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
    // printf("update-val: %d %d %d; (%d-%d=%d;%d)\n",x,pos,val,L,R,T[x].lmax,T[x].rmax);
}
node query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    node ret; ret.lmax=ret.rmax=ret.sum=0;
    int mid=(L+R)/2;
    if (l<=mid) ret=merge(query(x<<1,l,r,L,mid),ret);
    if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
vector<int> value[maxn];
int rv[maxn],lv[maxn];
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) value[A[i]].push_back(i);
    FOR(i,1,n) update(1,i,-1,1,n);
    FOR(i,1,n) {//smaller
        for (int v:value[i]) update(1,v,1,1,n);
        for (int v:value[i]) {
            node vl=query(1,1,v,1,n);
            node vr=query(1,v,n,1,n);
            // printf("get %d: (%d,%d+%d,%d);\n",v,vl.lmax,vl.rmax,vr.lmax,vr.rmax);
            lv[v]=vl.rmax+vr.lmax-1;
        }
    }
    FOR(i,1,n) update(1,i,-1,1,n);
    rFOR(i,1,n) {//smaller
        for (int v:value[i]) update(1,v,1,1,n);
        for (int v:value[i]) {
            node vl=query(1,1,v,1,n);
            node vr=query(1,v,n,1,n);
            rv[v]=vl.rmax+vr.lmax-1;
        }
    }
    // FOR(i,1,n) printf("%d ",lv[i]); puts("<- lv");
    // FOR(i,1,n) printf("%d ",rv[i]); puts("<- rv");
    FOR(i,1,n) printf("%d ",max((lv[i]-1)/2,rv[i]/2));
}
/*
*/