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
// const LL M=998244353;
ll M=1;
const LL maxn=3e5+107;
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
typedef array<int,4> ar4;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

const int MAX=30;
int n;
struct bit {
    ll value[maxn];
    bit() {
        memset(value,0,sizeof(value));
    }
    inline int lowbit(int x) {
        return x&-x;
    }
    void update(int x,int val) {
        for (;x<=n;x+=lowbit(x)) value[x]+=val;
    }
    ll query(int x) {
        ll ret=0;
        for (;x;x-=lowbit(x)) ret+=value[x];
        return ret;
    }
    ll query(int l,int r) {
        return query(r)-query(l-1);
    }
}T[MAX];
map<int,ll> HASH;
int A[maxn];
int main() {
    int q,i,k;
    srand(time(0));
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) {
        if (!HASH.count(A[i])) HASH[A[i]]=rng(); int hsh=HASH[A[i]];
        REP(k,MAX) if ((hsh>>k)&1) T[k].update(i,1);
    }
    // FOR(i,1,n) printf("%lld ",HASH[i]);
    FOR(i,1,q) {
        int op;
        scanf("%d",&op);
        if (op==1) {
            int p,x;
            scanf("%d%d",&p,&x);
            if (!HASH.count(x)) HASH[x]=rng(); int hsh=HASH[x];
            REP(k,MAX) if ((hsh>>k)&1) T[k].update(p,1);
            hsh=HASH[A[p]];
            REP(k,MAX) if ((hsh>>k)&1) T[k].update(p,-1);
            A[p]=x;
        } else {
            int l,r,x,ans=1;
            scanf("%d%d%d",&l,&r,&x);
            REP(k,MAX) if (T[k].query(l,r)%x) {ans=0; break;}
            // REP(k,MAX) printf("%lld ",T[k].query(l,r)); puts("<- T");
            if (ans) puts("YES");
            else puts("NO");
        }

    }
}
/*
*/