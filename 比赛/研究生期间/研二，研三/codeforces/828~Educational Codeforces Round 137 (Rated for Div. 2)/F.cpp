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

int _l,_r;
struct node{
    int A[2][2];
    node() {A[0][0]=A[1][1]=1; A[0][1]=A[1][0]=0;}
    node(int a00,int a01,int a10,int a11) {
        A[0][0]=a00; A[0][1]=a01;
        A[1][0]=a10; A[1][1]=a11;
    }
}T[maxn*4];
inline node mul(node x,node y) {
    node ret; ret.A[0][0]=ret.A[1][1]=0;
    int i,j,k;
    REP(i,2) REP(j,2) REP(k,2) {
        add_(ret.A[i][k],(ll)x.A[i][j]*y.A[j][k]%M);
    }
    return ret;
}
void update(int x,int l,int r,node val,int L=1,int R=3e5+7) {
    if (l<=L&&R<=r) {
        T[x]=mul(T[x],val);
        return;
    }
    T[x<<1]=mul(T[x<<1],T[x]);
    T[x<<1|1]=mul(T[x<<1|1],T[x]);
    T[x]=node();
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
}
ll ans=0;
void query(int x,int L=1,int R=3e5+7) {
    if (L==R) {
        int now;
        if (_l<=L&&R<=_r) now=T[x].A[1][1];
        else now=T[x].A[0][1];
        // if (L<=13) printf("%d ",now);
        add_(ans,now);
        return;
    }
    T[x<<1]=mul(T[x<<1],T[x]);
    T[x<<1|1]=mul(T[x<<1|1],T[x]);
    T[x]=node();
    int mid=(L+R)/2;
    query(x<<1,L,mid);
    query(x<<1|1,mid+1,R);
}
node f0(3,0,1,2);// 0,1->0,1
node f1(1,2,1,2);// 0,1->0,1
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) {
        int l,r;
        scanf("%d%d",&l,&r); l++; l++; r++; r++;
        if (i==1) _l=l,_r=r;
        else {
            update(1,1,l-1,f0);
            update(1,r+1,3e5+7,f0);
            update(1,l,r,f1);
            // query(1); puts("");
        }
    }
    ans=0;
    query(1);
    printf("%lld\n",ans);
}
/*
4
3 5
4 8
2 2
1 9

*/