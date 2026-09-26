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
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
const LL maxn=2e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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

const int mod = 1e9+7;
// const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
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
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
// struct comb {
//     vector<mint> f, g; // f:fac; g:inv
//     comb() {}
//     comb(int mx):f(mx+1),g(mx+1) {
//         f[0] = 1;
//         rREP_(i,mx) f[i] = f[i-1]*i;
//         g[mx] = f[mx].pow(mod-2);
//         for (int i=mx; i>0; i--) g[i-1] = g[i]*i;
//     }
//     mint operator()(int a, int b) {
//         if (a < b) return 0;
//         return f[a]*g[b]*g[a-b];
//     }
// } C(maxn);

int A[maxn],ID[maxn];
vector<pii> R[maxn];
array<mint,2> AddL[maxn],AddR[maxn];
ll Ins[maxn],Div[maxn];
void solve() {
    int n,MAX=0;
    scanf("%d",&n);
    FOR_(i,1,n) scanf("%d",&A[i]),max_(MAX,A[i]);
    FOR_(i,1,n) A[i]=MAX-A[i];
    FOR_(i,n+1,n+n) A[i]=A[i-n];
    // FOR_(i,1,n+n) printf("%d ",A[i]); puts("<- divided");
    FOR_(i,1,n+n) ID[i]=i;
    FOR_(i,2,n+n) if (A[i]==A[i-1]) ID[i]=ID[i-1]; A[n+n+1]=0;
    stack<pii> que;
    FOR_(i,1,n+n) R[i].clear();
    FOR_(i,1,n+n) AddL[i]={0,0},AddR[i]={0,0};
    FOR_(i,1,n+n) Ins[i]=Div[i]=0;
    FOR_(i,1,n+n) { // 预处理
        int id=ID[i];
        if (A[i]>A[i-1]) { //添加left
            que.push({i,A[i]-A[i-1]}); // left -> this
        }
        if (A[i]>A[i+1]) {
            int SIZE=A[i]-A[i+1];
            while (SIZE) {
                int x=min(SIZE,que.top().second);
                que.top().second-=x; SIZE-=x;
                R[que.top().first].push_back({i,x});
                if (que.top().second==0) que.pop();
            }
        }
    }
    ll cnt=0;
    mint cost=0;
    mint left[3],right[3];
    REP_(t,3) left[t]=right[t]=0;
    FOR_(i,1,n+n-1) {
        for (auto p:R[i]) {
            AddR[i][0]+=mint(p.second)*mint(i); // 0+1+...+k
            AddR[i][1]+=mint(p.second);
            AddR[p.first+1][0]-=mint(p.second)*mint(i);
            AddR[p.first+1][1]-=mint(p.second);

            AddL[i][0]+=mint(p.second)*mint(p.first); // -k-...-1-0
            AddL[i][1]+=mint(p.second);
            AddL[p.first+1][0]-=mint(p.second)*mint(p.first);
            AddL[p.first+1][1]-=mint(p.second);

            Ins[i]+=p.second;
            Div[p.first]-=p.second; // 没有right了
        }
        REP_(t,2) right[t]+=AddR[i][t];
        cnt+=Ins[i];
        cost+=(right[1]*i-right[0])*2+right[1];
        // printf("solve - first %d : %lld %lld\n",i,cnt.x,cost.x);
        if (i>n) {
            REP_(t,2) left[t]+=AddL[i-n][t];
            cnt+=Div[i-n];
            cost-=(left[0]-left[1]*(i-n))*2+left[1];
        }
        // printf("solve %d : %lld %lld\n",i,cnt.x,cost.x);
        // printf("left & right = %d %d %d; %d %d %d\n",left[0].x,left[1].x,left[2].x,right[0].x,right[1].x,right[2].x);
        // for (auto p:R[i]) printf("%d->%d(%d) ",i,p.first,p.second); puts("  <- R");
        if (i>=n) printf("%lld %lld\n",cnt,cost.x);
    }
}
int main() {
    int T; T=1;
    scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
1
8
6 5 6 4 2 6 2 2
*/