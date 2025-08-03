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
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

const int mod = 998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    // mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (;t;t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
// struct comb {
//     vector<mint> fac,inv; // f:fac; g:inv
//     comb() {}
//     comb(int MAX):fac(MAX),inv(MAX) {
//         fac[0] = 1;
//         rep_(i,1,MAX) fac[i] = fac[i-1]*i;
//         inv[MAX-1] = fac[MAX-1].pow(mod-2);
//         rrep_(i,1,MAX) inv[i-1] = inv[i]*i;
//     }
//     mint operator()(int a, int b) {
//         if (a < b) return 0;
//         return fac[a]*inv[b]*inv[a-b];
//     }
// } C(maxn);

int n;
vector<vector<int>> edge;
vector<pii> P[307];
int solve(int l,int r,vector<vector<int>> &dis) {
    int ret=INF;
    if (l==r) {
        FOR_(i,1,n) if (l!=i&&edge[l][i]!=INF) {
            FOR_(j,i+1,n) if (l!=j&&edge[l][j]!=INF&&dis[i][j]!=INF) {
                int now=edge[l][i]+edge[l][j]+dis[i][j]; // 经过l的最小环
                // printf("i=%d; j=%d; now=%d\n",i,j,now);
                for (auto &p:P[l]) { // 除了最小环外再加一条边
                    if (p.second==i||p.second==j) continue;
                    // printf("p.second=%d\n",p.second);
                    ret=min(ret,now+p.first);
                    break;
                }
            }
        }
        // printf("solve l=%d\n",l);
        // FOR_(i,1,n) FOR_(j,1,n) printf("%d%c",dis[i][j]," \n"[j==n]); puts("");
    } else {
        int mid=(l+r)/2;
        vector<vector<int>> nxtdis;
        nxtdis=dis;
        FOR_(k,mid+1,r) FOR_(i,1,n) FOR_(j,1,n)
            nxtdis[i][j]=min(nxtdis[i][j],nxtdis[i][k]+nxtdis[k][j]);
        ret=min(ret,solve(l,mid,nxtdis));
        nxtdis=dis;
        FOR_(k,l,mid) FOR_(i,1,n) FOR_(j,1,n)
            nxtdis[i][j]=min(nxtdis[i][j],nxtdis[i][k]+nxtdis[k][j]);
        ret=min(ret,solve(mid+1,r,nxtdis));
    }
    // printf("solve %d -> %d: %d\n",l,r,ret);
    return ret;
}
int main() {
    int m;
    scanf("%d%d",&n,&m);
    edge=vector<vector<int>>(n+1,vector<int>(n+1,INF));
    FOR_(i,1,m) {
        int x,y,d;
        scanf("%d%d%d",&x,&y,&d);
        edge[x][y]=edge[y][x]=d;
        P[x].push_back({d,y});
        P[y].push_back({d,x});
    }
    FOR_(i,1,n) sort(P[i].begin(),P[i].end());
    FOR_(i,1,n) edge[i][i]=0;
    int ans=solve(1,n,edge);
    if (ans==INF) puts("-1"); else printf("%d\n",ans);
}
/*
8 12
1 2 1
1 3 100
1 4 100
1 5 100
1 6 100
1 7 1
1 8 1
2 3 1
3 4 1
4 5 1
5 6 1
6 7 1
*/