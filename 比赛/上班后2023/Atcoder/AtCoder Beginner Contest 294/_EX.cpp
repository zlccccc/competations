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
const LL maxn=1e6+107;
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

vector<int> reid(vector<int> _e,vector<int> eid,int tot) {
    vector<int> e(tot);
    REP_(i,(int)_e.size()) if (eid[i]!=-1) {
        for (int sta=_e[i];sta;) {
            int j=__builtin_ctz(sta); sta^=1<<j;
            // printf("%d %d %d\n",sta,i,j);
            if (eid[j]!=-1) e[eid[i]]|=1<<eid[j];
        }
    }
    return e;
}
// need split first
// solve second
int solve(vector<int> e,int k) {
    int n=e.size();
    if (n==0) return 1;
    if (n==1) return k;
    int min_deg=n+1,id=0; // id: current-id
    { // judge 0 and 1
        vector<int> eid(e.size(),-1);
        ll base=1; int tot=0;
        REP_(i,n) {
            if (min_deg>=__builtin_popcount(e[i])) min_deg=__builtin_popcount(e[i]),id=i;
            // if (i==n-1&&tot==0) eid[i]=tot++;
            // else 
            if (__builtin_popcount(e[i])==0) base=base*k%M;
            else eid[i]=tot++;
        }
        vector<int> newe=reid(e,eid,tot);
        // REP_(i,n) printf("%d ",eid[i]); puts("<- eid");
        // REP_(i,(int)newe.size()) {pr2(newe[i],newe.size()); puts("<- new_e");}
        if (tot!=n) return solve(newe,k)*base%M; // remove no-use-nodes
    }
    {
        // exp{(2^k-k)}
        ll oth;
        {
            vector<int> eid(e.size(),-1);
            int tot=0;// MASK-LOW-RANK
            REP_(i,n) if (i!=id) eid[i]=tot++;
            oth=solve(reid(e,eid,tot),k);
        }
        int ans=(ll)oth*k%M;
        for (int mask=e[id];mask;mask=(mask-1)&e[id]) {
            if (__builtin_popcount(mask)==1) add_(ans,M-oth);
            else {
                ll op=1; int tot=0;
                vector<int> eid(e.size(),-1);
                REP_(i,n) if (i!=id) if (!((mask>>i)&1)) eid[i]=tot++;
                REP_(i,n) if (i!=id) if ((mask>>i)&1) eid[i]=tot,op=M-op;
                vector<int> newe=reid(e,eid,tot+1);
                // printf("id=%d\n",id);
                // printf("solve %d\n",(int)e.size());
                // REP_(i,n) {pr2(e[i],n); puts("<- e");}
                // REP_(i,n) printf("%d ",eid[i]); puts("<- eid");
                // REP_(i,(int)newe.size()) {pr2(newe[i],newe.size()); puts("<- new_e");}
                if ((newe[tot]>>tot)&1) continue;
                int val=solve(newe,k);
                // printf("val=%d\n",val);
                add_(ans,val*op%M);
            }
        }
        return ans;
    }
    // n*3^n
    assert(n<=15);
    vector<int> okay(1<<n);
    // sub
    okay[0]=1;
    REP_(sta,(1<<n)) { // no edge
        int id=__builtin_ctz(sta);
        if (e[id]&sta) continue;
        okay[sta]|=okay[sta^(1<<id)];
        // if (okay[sta]) pr2(sta,tot); puts("<- okay");
    }
    ll now=1,ans=0;
    vector<int> dp(1<<n); dp[0]=1;

    // REP_(i,tot) {pr2(_e[i],tot); puts("<- e");}
    // REP_(i,n) {pr2(_e[i],n); puts("<- _e");}
    // REP_(i,n) printf("%d ",eid[i]); puts("<- eid");

    REP_(i,n) {
        vector<int> nxt(1<<n);
        now=now*(k-i)%M*powMM(i+1,M-2)%M;
        rep_(sta,1,(1<<n)) {
            for (int k=sta;k;k=(k-1)&sta) {
                if (okay[k]) add_(nxt[sta],dp[sta^k]);
                // pr2(k,n); pr2(sta,n); puts("<- trans");
            }
        }
        dp.swap(nxt);
        // printf("%d: %lld %lld\n",i,dp[(1<<n)-1],now);
        add_(ans,now*dp[(1<<n)-1]%M);
        // printf("%d: %lld %lld  %lld\n",i,dp[(1<<n)-1],now,mul);
    }
    return ans;
}
int main() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    vector<int> e(n);
    FOR_(i,1,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        u--; v--;
        e[u]|=1<<v; e[v]|=1<<u;
    }
    printf("%d\n",solve(e,k));
}
/*
6 5 2
1 2
2 3
3 4
4 1
1 6

4 2 2
1 2
3 4
*/