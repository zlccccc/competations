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
const LL maxn=1e5+107;
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
 
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int base[107][107][107][107],below[107][107];//(a,b) <- (x,y)
int pw[107];//pow(x,n)
void init() {
    int i,j,x,y,u,v;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    FOR(i,0,31) FOR(j,0,31) {//base
        base[i][j][i][j]=1;
        FOR(x,0,i) FOR(y,0,j) if (x!=i||y!=j) { //base
            ll bbase=C(i,x)*C(j,y)%M;
            FOR(u,0,x) FOR(v,0,y) {
                add_(base[i][j][u][v],M-bbase*base[x][y][u][v]%M);
            }
        }
    }
    FOR(i,0,80) FOR(j,0,80) {
        FOR(x,0,i) FOR(y,0,j) {
            if ((x+y*2)%3==0) add_(below[i][j],C(i,x)*C(j,y)%M);
        }
    }
}
int main() {
    // startTimer();
    init();
    // printTimer();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        ll n,a;
        int c0=0,c1=0,i,j;
        scanf("%lld%lld",&n,&a);
        REP(i,63) if ((a>>i)&1) {
            if (i&1) c1++;
            else c0++;
        }
        int ans=0;
        FOR(i,0,c0) FOR(j,0,c1) if (base[c0][c1][i][j]&&below[i][j]){
            add_(ans,base[c0][c1][i][j]*powMM(below[i][j],n)%M);
        }
		FOR(i,0,c0) {
			FOR(j,0,c1) printf("%lld ",powMM(M-1,i+j+1)*(ll)base[c0][c1][i][j]%M); puts("");
		}
        printf("%d\n",ans);
    }
}
/*
*/