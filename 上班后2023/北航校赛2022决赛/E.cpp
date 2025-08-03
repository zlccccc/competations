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

int MIN[maxn*4];
int tot;
void update(int x,int pos,int val,int L,int R) {
    min_(MIN[x],val);
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
}
int query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return MIN[x];
    int mid=(L+R)/2,ret=INF;
    if (l<=mid) ret=min(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=min(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
vector<pii> V[maxn];
vector<pii> Q[maxn];
int Ans[maxn];
int main() {
    memset(MIN,0x3f,sizeof(MIN));
    int n,q,L; scanf("%d%d%d",&n,&q,&L);
    FOR_(i,1,n) {
        int l,r;
        scanf("%d%d",&l,&r);
        V[l].push_back({r,i});
    }
    FOR_(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        Q[l].push_back({r,i});
    }
    FOR_(i,1,L) {
        for (auto p:V[i]) update(1,p.first,p.second,1,L);
        for (auto p:Q[i]) {
            int ans=query(1,p.first,L,1,L);
            if (ans==INF) Ans[p.second]=0;
            else Ans[p.second]=ans;
        }
    }
    FOR_(_,1,q) printf("%d\n",Ans[_]);
}
/*
3 7 10
4 5
1 4
1 6
2 4
3 6
3 5
1 1
1 10
4 4
5 5
*/