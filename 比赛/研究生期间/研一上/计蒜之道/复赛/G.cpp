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

struct vnode{ll x,y;};
vnode mul(vnode x,vnode y) {
    vnode ret;
    ret.x=(x.x*y.x+x.y*y.y)%M;
    ret.y=(x.x*y.y+x.y*y.x)%M;
    return ret;
}
vnode powMM(vnode a,int b) {
    vnode ret; ret.x=1; ret.y=0;
    for (; b; b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}

int CNT[maxn][37];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll getvalue(int x,int y,int v) {//x-0; y-1
    int ret=0,i;
    // FOR(i,1,x) if (i&1) add_(ret,C(x,i)*powMM(v,i)%M);
    vnode vret=powMM(vnode{1,v},x);
    ret=vret.y;
    // if (x) printf("fir %d : %d  y=%lld\n",x,ret,vret.y);
    ret=ret*powMM((1+v),y)%M;
    return ret;
}
int main() {
    int i,n,m;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        int v,k;
        scanf("%d",&v);
        REP(k,32) {
            CNT[i][k]=CNT[i-1][k];
            CNT[i][k]+=(v>>k)&1;
        }
    }
    // puts("???");
    FOR(i,1,m) {
        int l,r,val;
        scanf("%d%d%d",&l,&r,&val);
        int ans=0,k;
        REP(k,32) {
            int x=CNT[r][k]-CNT[l-1][k];
            ll noww=getvalue(x,r-l+1-x,val);
            // if (x) printf("get %d %d %d  %lld\n",x,r-l+1-x,val,noww);
            add_(ans,(noww<<k)%M);
        } printf("%d\n",ans);
    }
}
/*
*/