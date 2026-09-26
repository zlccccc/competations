#include <sstream>
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
const LL maxn=2e5+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

vector<int> pri[maxn];
int cnt[maxn];
int solve() { // to-right
    int n,m,i; ll L,R;
    if (scanf("%d%d",&n,&m)!=2) return 0;
    scanf("%lld%lld",&L,&R);
    // set<pair<int,int>> S;
    set<int> S;
    int l=m+1,r=m; // l,r: kb
    FOR(i,1,n) { // L<=i*kb<=R --> L-1/b < i*kb <= R
        while (l>(L-1)/i+1) {
            l--;
            for (int v:pri[l]) {
                if (!cnt[v]) S.insert(v);
                cnt[v]++;
                // S.insert({v,l/v});
            }
        }
        while (r>R/i) {
            for (int v:pri[r]) {
                cnt[v]--;
                if (!cnt[v]) S.erase(v);
                // S.erase({v,r/v});
            }
            r--;
        }
        // printf("calculate i=%d; l,r=%d %d\n",i,l,r,(L-1)/i,R/i);
        // for (auto p:S) printf("inside %d %d mul=%d\n",p.first,p.second,p.first*p.second);
        bool tag=0;
        for (int a:pri[i]) {
            // x1/a*b=x2
            // y1/b*a=y2
            // b>a
            int lb=a+1,rb=n/(i/a);
            // y1=kb; y2=ka;
            // y1 in range(L,R)
            // b should be max; otherwise rk not okay
            auto it=S.lower_bound(lb);
            if (it==S.end()) continue;
            if ((*it)>rb) continue;
            // int b=(*it).first,k=(*it).second;
            int b=*it,k=min(R/i/b,(ll)m/b);
            printf("%d %d %d %d\n",i,k*b,i/a*b,k*a);
            tag=1;
            break;
        }
        if (!tag) puts("-1");
    }
    return 1;
}
int main() {
    int i;
    FOR(i,1,200000) {
        for (int j=i;j<=200000;j+=i) pri[j].push_back(i);
    }
    while (solve());
}
/*
1 7500
2 6000
5 4000
*/