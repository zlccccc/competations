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
#include <unordered_set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

// #define DEBUG
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// 倒着
map<ll,ll> MP;
int op[maxn],val[maxn],mul[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    ll inv2=powMM(2,M-2),pw=1,inv=1;
    int div_tot=0;
    FOR(i,1,n) {
        scanf("%d",&op[i]);
        if (op[i]==1) {
            scanf("%d",&val[i]); mul[i]=inv;
        } else if (op[i]==2) {
            scanf("%d",&val[i]); div_tot=min(div_tot+val[i],INF);
        } else {
            val[i]=div_tot;
            if (!div_tot) {
                pw=pw*2%M; inv=inv*inv2%M; // pw: all multiply
            } else div_tot=min(div_tot*2,INF);
        }
    }
    FOR(i,1,n) mul[i]=mul[i]*pw%M;
    vector<int> sub;
    div_tot=0;
    ll ans=0;
    rFOR(i,1,n) {
        if (op[i]==1) {
            val[i]-=div_tot;
            if (val[i]<=0) continue;
            // printf("i=%d: val=%d\n",i,val[i]);
            ll now=1;
            pw=powMM(2,sub.size());
            for (int v:sub) {
                pw=pw*inv2%M;
                if (val[i]>v) val[i]-=v,add_(now,pw); // pw: other
            }
            // printf("%lld*%lld; div=%d\n",now,mul[i],div_tot);
            // for (int v:sub) printf("%d ",v); puts("<- sub");
            add_(ans,now*mul[i]%M);
        } else if (op[i]==2) {
            div_tot=min(div_tot+val[i],INF);
        } else {
            if (val[i]!=INF&&val[i]!=0) sub.push_back(val[i]);
        }
    }
    printf("%lld\n",ans);
}
/*
*/