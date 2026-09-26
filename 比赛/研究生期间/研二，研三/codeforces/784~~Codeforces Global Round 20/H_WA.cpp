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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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

struct node{
    ar3 A[2][2]; //ar3: L-cnt, R-cnt, ans
    node(){memset(A,0x3f,sizeof(A));}
}T[maxn*4];
node merge(const node &x,const node &y) {
    node ret;
    int xl,xr,yl,yr;
    REP(xl,2) REP(xr,2) REP(yl,2) REP(yr,2) {
        auto L=x.A[xl][xr],R=y.A[yl][yr];
        ar3 now={L[0],R[1],L[2]+R[2]};
        if (xr!=yl) {
            int k=min(L[1],R[0]);
            now[2]-=k; L[1]-=k; R[0]-=k;
        }
        if (xl==yl) now[0]+=R[0];
        if (xr==yr) now[1]+=L[1];
        if (ret.A[xl][yr][2]>now[2]) ret.A[xl][yr]=now;
    }
    return ret;
}
char str[maxn];
void build(int x,int l,int r) {
    if (l==r) {
        T[x].A[str[l]-'0'][str[l]-'0']=ar3{1,1,1};
        return;
    }
    int mid=(l+r)/2;
    build(x<<1,l,mid); build(x<<1|1,mid+1,r);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (l<=mid&&mid<r) return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
    if (l<=mid) return query(x<<1,l,r,L,mid);
    if (mid<r) return query(x<<1|1,l,r,mid+1,R);
}
int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    scanf("%s",str+1);
    build(1,1,n);
    int i;
    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        auto now=query(1,l,r,1,n);
        int x,y,ans=n;
        REP(x,2) REP(y,2) min_(ans,now.A[x][y][2]);
        printf("%d\n",ans);
    }
}
/*
*/