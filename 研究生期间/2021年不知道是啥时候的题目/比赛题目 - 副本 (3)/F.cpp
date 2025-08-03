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
const LL maxn=2e5+107;
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

vector<int> P;
int isprime[maxn];
int F[maxn];
ll query(int x,int y) {
    printf("? %d %d\n",x,y);
    fflush(stdout);
    ll ret;
    // ret=(ll)F[x]*F[y]/gcd(F[x],F[y]);
    scanf("%lld",&ret);
    return ret;
}
int A[maxn];
ll f[107][107];
void solve() {
    int i,n;
    fflush(stdout);
    scanf("%d",&n);
    // FOR(i,1,n) scanf("%d",&F[i]);
    FOR(i,1,n) A[i]=0;
    if (n<=100) {
        int a,b,c,d,j;
        ll mx1=0,mx2=0;
        FOR(i,1,n) FOR(j,i+1,n) {
            f[i][j]=f[j][i]=query(i,j);
            ll now=f[i][j];
            if (now%2==1) continue;
            if (now>mx1) mx2=mx1,c=a,d=b,mx1=now,a=i,b=j;
            else if (now>mx2) mx2=now,c=i,d=j;
        }
        if (a==c||a==d) swap(a,b);//a is max
        ll t=0; while (t*(t+1)<=mx1) t++;
        // printf("a,b,c,d=%d %d %d %d; mx=%lld %lld, t=%d\n",a,b,c,d,mx1,mx2,t);
        A[a]=t; A[b]=t-1; int l=t-n+1;
        rFOR(i,l,t-2) {
            int j;
            FOR(j,1,n) if (!A[j]) {
                // ll now=query(j,b);
                ll now=f[j][b];
                if (now==(ll)i*(i+1)) break;
            } b=j; A[b]=i;
        }
    } else {
        int a,b,p=0;
        FOR(i,1,1000) {
            int x=1,y=1;
            while (x==y) {
                x=(rand()<<16|rand())%n+1;
                y=(rand()<<16|rand())%n+1;
            }
            ll now=query(x,y);
            for (auto pri:P) {
                if (now%pri==0&&pri>p) a=x,b=y,p=pri;//pri,not-pri
                if ((ll)pri*pri>now) break;
            }
        }
        int x=1; while (x==a||x==b) x=(rand()<<16|rand())%n+1;
        if (query(a,x)%p!=0) swap(a,b); A[a]=p;// a is pri
        FOR(i,1,n) if (i!=a) A[i]=query(i,a)/p;
    }
    printf("! ");
    FOR(i,1,n) printf("%d%c",A[i]," \n"[i==n]);
}
int main() {
    int i;
    FOR(i,2,200000) isprime[i]=1;
    FOR(i,2,200000) if (isprime[i]) {
        P.push_back(i);
        for (int j=i+i;j<=200000;j+=i) isprime[j]=0;
    }
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
*/