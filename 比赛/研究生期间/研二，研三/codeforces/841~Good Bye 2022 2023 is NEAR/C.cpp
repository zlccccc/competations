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
const LL maxn=4e5+107;
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

ll A[maxn];
bool isprime[1006];
int cnt[100][100];
int main() {
    vector<int> p;
    {
        int i,j;
        memset(isprime,1,sizeof(isprime));
        for (i=2;i<=100;i++) if (isprime[i]) {
            p.push_back(i);
            for (j=i+i;j<=100;j+=i) isprime[j]=0;
        }
        // printf("%d ",p.size());
    }
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int i,j,k,n;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%lld",&A[i]);
        sort(A+1,A+1+n);
        for (int v:p) REP(k,v) cnt[v][k]=0;
        bool mark=0; // no
        FOR(i,1,n) FOR(j,i+1,n) {//x!=0
            if (A[i]==A[j]) mark=1;
            else {
                ll g=abs(A[i]-A[j]);
                if (g==1) continue;
                // MP[g].insert(A[i]%g);
                // if (MP[g].size()==g) mark=1;
                for (int v:p) if (g%v==0) cnt[v][A[i]%v]=1;
            }
        }
        for (int v:p) {
            int all=0;
            REP(k,v) all+=cnt[v][k];
            if (all==v) mark=1;
        }
        // if (S.count(1)) S.erase(1);
        if (mark) puts("NO");
        else puts("YES");
    }
}
/*
*/