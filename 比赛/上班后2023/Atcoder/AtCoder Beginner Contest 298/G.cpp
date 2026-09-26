// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=5e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int n,m,T;
ll A[7][7];
ll MAX[7][7][7][7][67][507]; // MAX<=A的时候,MIN最小值最大是多少
ll sum(int xl,int xr,int yl,int yr) {
    return A[xr][yr]-A[xl-1][yr]-A[xr][yl-1]+A[xl-1][yl-1];
}
vector<ll> val;
ll getid(ll now) {
    return lower_bound(val.begin(),val.end(),now)-val.begin();
}
bool check(ll mid) {
    // printf("solve mid=%lld\n",mid);
    FOR_(xl,1,n) FOR_(xr,xl,n) FOR_(yl,1,m) FOR_(yr,yl,m) {
        FOR_(k,1,(xr-xl+1)*(yr-yl+1)) REP_(t,(int)val.size()) MAX[xl][xr][yl][yr][k][t]=-INFF;
    }
    FOR_(lx,1,n) FOR_(ly,1,m) {
        FOR_(xl,1,n-lx+1) FOR_(yl,1,m-ly+1) {
            int xr=xl+lx-1,yr=yl+ly-1;
            // not split
            ll nowsum=sum(xl,xr,yl,yr);
            max_(MAX[xl][xr][yl][yr][1][getid(nowsum)],nowsum);
            // split
            FOR_(xm,xl,xr-1) {
                FOR_(kl,1,(xm-xl+1)*(yr-yl+1)) {
                    FOR_(kr,1,(xr-xm)*(yr-yl+1)) {
                        REP_(t,(int)val.size()) {
                            ll cur=min(MAX[xl][xm][yl][yr][kl][t],MAX[xm+1][xr][yl][yr][kr][t]);
                            if (cur==-INFF) continue;
                            // printf("solve merge x %d->%d %d\n",cur,val[t],kl+kr);
                            if (cur+mid<val[t]) continue; // cannot merge
                            max_(MAX[xl][xr][yl][yr][kl+kr][t],cur);
                        }
                    }
                }
            }
            FOR_(ym,yl,yr-1) {
                FOR_(kl,1,(xr-xl+1)*(ym-yl+1)) {
                    FOR_(kr,1,(xr-xl+1)*(yr-ym)) {
                        REP_(t,(int)val.size()) {
                            ll cur=min(MAX[xl][xr][yl][ym][kl][t],MAX[xl][xr][ym+1][yr][kr][t]);
                            if (cur==-INFF) continue;
                            // printf("solve merge y %d->%d kl,kr=%d,%d\n",cur,val[t],kl,kr);
                            if (cur+mid<val[t]) continue; // cannot merge
                            max_(MAX[xl][xr][yl][yr][kl+kr][t],cur);
                        }
                    }
                }
            }
            FOR_(k,1,(xr-xl+1)*(yr-yl+1)) {
                // REP_(t,(int)val.size()) if (MAX[xl][xr][yl][yr][k][t]!=-INFF) {
                //     printf("x=%d-%d; y=%d-%d; val=%d; k times=%d: MAX=%d->%d; mid=%lld\n",xl,xr,yl,yr,t,k,MAX[xl][xr][yl][yr][k][t],val[t],mid);
                // }
                rep_(t,1,(int)val.size()) max_(MAX[xl][xr][yl][yr][k][t],MAX[xl][xr][yl][yr][k][t-1]);
            }
        }
    }
    {
        int xl=1,xr=n,yl=1,yr=m;
        REP_(t,(int)val.size()) {
            ll cur=MAX[xl][xr][yl][yr][T][t];
            // if (cur!=-INFF) {
            //     printf("check ans x=%d-%d; y=%d-%d; val=%d; k times=%d: MAX=%d->%d; mid=%lld\n",xl,xr,yl,yr,t,T,MAX[xl][xr][yl][yr][T][t],val[t],mid);
            // }
            if (cur+mid>=val[t]) return 1;; // cannot merge
        }
    }
    return 0;
}
int main() {
    scanf("%d%d%d",&n,&m,&T); T++;
    FOR_(x,1,n) FOR_(y,1,m) scanf("%lld",&A[x][y]);
    FOR_(x,1,n) FOR_(y,1,m) A[x][y]+=A[x][y-1]+A[x-1][y]-A[x-1][y-1];
    FOR_(xl,1,n) FOR_(xr,xl,n) FOR_(yl,1,m) FOR_(yr,yl,m) {
        val.push_back(sum(xl,xr,yl,yr));
    }
    sort(val.begin(),val.end());
    // FOR_(x,1,n) FOR_(y,1,m) printf("%lld%c",A[x][y]," \n"[y==m]);
    // for (int v:val) printf("%d ",v); puts("<- val");
    val.erase(unique(val.begin(),val.end()),val.end());
    ll l=-1,r=INFF;
    ll l=-1,r=5;
    while (l+1<r) {
        ll mid=(l+r)/2;
        if (check(mid)) r=mid;
        else l=mid;
    }
    printf("%lld\n",r);
}
/*
2 3 4
2 3 4
4 1 3
*/