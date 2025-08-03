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
const LL maxn=3e5+107;
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

int A[maxn*34];
int nxt[maxn*34][2],tot;
void update(int &x,int val,int add,int k) {
    if (!x) x=++tot; A[x]+=add;
    if (k==-1) return;
    int c=(val>>k)&1;
    update(nxt[x][c],val,add,k-1);
}
int query(int &x,int val,int k) {
    if (!A[x]) return INF;
    if (k==-1) return 0;
    int c=(val>>k)&1;
    if (A[nxt[x][c]]) return query(nxt[x][c],val,k-1);
    return query(nxt[x][c^1],val,k-1)|(1<<k);
}
int root;
int ans[maxn];
void solve(int l,int r,vector<ar3> &f,int cur) { // cur: current-min
    if (!f.size()) return;
    // printf("solve %d %d; cur=%d\n",l,r,cur);
    // for (auto now:f) printf("(%d-%d,%d) ",now[0],now[1],now[2]); puts("");
    int mid=(l+r)/2;
    vector<ar3> fl,fr;
    for (auto &now:f) {
        if (l==r&&now[2]==-1) continue;
        else if (now[0]<=l&&r<=now[1]) {
            // printf("insert %d\n",now[2]);
            cur=min(cur,query(root,now[2],30));
            update(root,now[2],1,30);
        } else {
            if (now[0]<=mid) fl.push_back(now);
            if (mid<now[1]) fr.push_back(now);
        }
    }
    for (auto &now:f)
        if (l==r&&now[2]==-1) ans[now[0]]=cur;
    if (l!=r) {
        solve(l,mid,fl,cur);
        solve(mid+1,r,fr,cur);
    }
    for (auto &now:f) {
        if (now[0]<=l&&r<=now[1]&&now[2]!=-1) {
            // printf("remove %d\n",now[2]);
            update(root,now[2],-1,30);
        }
    }
}
int main() {
    int n;
    scanf("%d",&n);
    memset(ans,0xff,sizeof(ans));
    vector<ar3> cur;
    map<int,vector<int>> MP;
    FOR_(i,1,n) {
        int op;
        scanf("%d",&op);
        if (op==1) {
            int x; scanf("%d",&x);
            MP[x].push_back(i);
        } else if (op==2) {
            int x; scanf("%d",&x);
            int l=MP[x].back();
            MP[x].pop_back();
            cur.push_back({l,i,x});
        } else {
            cur.push_back({i,i,-1});
        }
    }
    for (auto &now:MP) {
        for (int v:now.second) cur.push_back({v,n+1,now.first});
    }
    solve(1,n+1,cur,INF);
    FOR_(i,1,n) if (ans[i]!=-1) printf("%d\n",ans[i]);
}
/*
*/