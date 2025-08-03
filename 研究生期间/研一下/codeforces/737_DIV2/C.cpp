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
const LL M=1e9+7;
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

int solve(int n,int x,int y,int k) {
    int a,ret=0;
    if (!n) return x>=y;
    REP(a,(1<<k)) ret+=solve(n-1,x&a,y^a,k);
    return ret;
}
ll F[maxn][2];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i;
        scanf("%d%d",&n,&m);
        if (n&1) {
            int l=powMM(2,n-1)+1;
            printf("%lld\n",powMM(l,m));
        } else {
            int ans=0; F[0][0]=1;//same
            FOR(i,1,m) {
                F[i][0]=(ll)F[i-1][0]*(powMM(2,n-1)+M-1)%M;//same
                F[i][1]=((ll)F[i-1][0]+(ll)F[i-1][1]*powMM(2,n))%M;//more
            } ans=(F[m][0]+F[m][1])%M;
            // powMM(powMM(2,n-1),m)*(powMM(2,m)+M-1)%M;
            // FOR(i,1,k) add_(ans,(ll)powMM(powMM(2,n-1),i)%M);
            // printf("%d %d\n",F[m][0],F[m][1]);
            printf("%d\n",ans);
        }
        // printf("solve=%d\n",solve(n,(1<<m)-1,0,m));
    }
}
/*
10
3 1
3 2
3 3
3 4
4 1
4 2
4 3
4 4
*/