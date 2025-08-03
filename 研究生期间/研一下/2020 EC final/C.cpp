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
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

uint64_t x;
uint64_t Rand() {//this is a xor-shift random generator
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
uint64_t getRand(uint64_t val) {
    x=val; Rand(); return x;
}
int n;
int A[maxn],id[maxn];
int Mod[maxn];
bool check(uint64_t ans) {
    x=ans; int i;
    FOR(i,1,n) {
        if ((int)(Rand()%i)!=Mod[i]) return 0;
    } return 1;
}

namespace LB {
    typedef unsigned long long BaseType;
    const int MaxBit=64;
    struct L_B {
        BaseType b[MaxBit]; int v[MaxBit];
        L_B() {clear();}
        void clear() {memset(b,0,sizeof(b)); memset(v,0,sizeof(v));}
        void insert(BaseType x,int val) {
            int i;
            rREP(i,MaxBit) if ((x>>i)&1) {
                if (!b[i]) b[i]=x,v[i]=val; x^=b[i]; val^=v[i];
            }
        }
        BaseType XORMIN(BaseType x) {
            int i;
            rREP(i,MaxBit) if ((b[i]^x)<x) x^=b[i];
            return x;
        }
        void rebuild() {
            int i,j;
            rREP(i,MaxBit) {
                rREP(j,i) if ((b[i]>>j)&1) b[i]^=b[j],v[i]^=v[j];
            }
            // REP(i,MaxBit) {
            //     pr2(b[i]); printf("  <- b  %d  %d   (%d)\n",v[i],i,!!b[i]);
            // }
        }
    } lb;
}
using namespace LB;
uint64_t val[67];
vector<pair<ull,int> > limit;
int Count[maxn];
int main() {
    // x=123214; Rand();
    // pr2(x); puts("");
    // x=1245732; Rand();
    // pr2(x); puts("");
    // x=123214^1245732; Rand();
    // pr2(x); puts("");
    int i,k;
    // REP(i,64) {pr2(getRand(1ull<<i)); puts("");}

    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]),id[A[i]]=i;
    rFOR(i,1,n) {
        int pos=id[i];
        Mod[i]=pos-1;
        swap(A[i],A[pos]);
        swap(id[A[pos]],id[A[i]]);
    }
    // FOR(i,1,n) printf("%d ",Mod[i]); puts("<- id");
    // FOR(i,1,n) printf("%d ",A[i]);  puts("<- A");
    // FOR(i,1,n) swap(A[i],A[Mod[i]+1]);
    // FOR(i,1,n) printf("%d ",A[i]);  puts("<- swap A");
    REP(k,64) val[k]=1ull<<k;
    FOR(i,1,n) { //limit: popcount(subset(x))%2==0
        REP(k,64) val[k]=getRand(val[k]);
        for (int t=1;!(i&t);t<<=1) {
            uint64_t now=0;
            REP(k,64) if (val[k]&t) now|=1ull<<k;
            // if (now) {pr2(now); printf("<- insert  %d %d\n",i,!!(Mod[i]&t));}
            lb.insert(now,!!(Mod[i]&t));
        }
    }
    lb.rebuild();
    REP(i,64) if (lb.b[i]) limit.push_back(make_pair(lb.b[i],lb.v[i]));
    uint64_t lowb,maxi=1<<20;
    rep(lowb,1,maxi) Count[lowb]=Count[lowb&(lowb-1)]+1;
    // rep(lowb,1,10) printf("%d ",Count[lowb]); puts("<- count");
    // pr2(16659580358178468547ull); puts("");
    // pr2(lb.XORMIN(8277940081036386588ull)); printf("<-  %llu ans\n",lb.XORMIN(8277940081036386588));
    // printf("%llu\n",8277940081036386588ull&(maxi-1));
    REP(lowb,maxi) {//maximize
        uint64_t tocheck=lowb; bool checkfirst=1;
        for (auto p:limit) {
            uint64_t b=p.first; int v=p.second;
            if (v^(Count[b&lowb]&1)) {
                // if (lowb==287004) {
                //     pr2(b&lowb); printf("  <- count=%d  v=%d; checkfirst=%d\n",Count[b&lowb],v,checkfirst);
                //     pr2(b&lowb);
                // }
                if (!(b^(b&(maxi-1)))) checkfirst=0;
                else tocheck^=b^(b&(maxi-1));
            }
        }
        // if (checkfirst) {
        //     // pr2(lowb);
        //     pr2(tocheck);
        //     printf("%llu\n",tocheck);
        // }
        if (checkfirst&&check(tocheck)) {printf("%llu\n",tocheck); break;}
    }
}
/*

50
36 22 24 21 27 50 28 14 25 34 18 43 47 13 30 7 10 48 20 16 29 9 8 15 3 31 12 38 19 49 37 1 46 32 4 44 11 35 6 33 26 5 45 17 39 40 2 23 42 41

*/