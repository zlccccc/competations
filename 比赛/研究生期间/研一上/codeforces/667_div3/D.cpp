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

int base[207];
ll A[27][7][207];//position; more; digit
int main() {
    // printf("%lld\n",(ll)2e19);
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        ll n; int s;
        scanf("%lld%d",&n,&s);
        int len=0; ll b=1,ans=INFF;
        memset(base,0,sizeof(base));
        while (n) base[len++]=n%10,n/=10;
        memset(A,0x3f,sizeof(A));
        int i,j,k,t; A[0][0][0]=0;
        FOR(i,0,17) {
            FOR(j,0,2) FOR(k,0,s) if (A[i][j][k]!=INFF) FOR(t,0,9) {
                ll mor=j+t+base[i]; ll nxtk=k,nxtj=0;
                while (mor>=10) mor-=10,nxtj++; nxtk+=mor;
                if (i!=17) min_(A[i+1][nxtj][nxtk],A[i][j][k]+b*t);
                else if (nxtk+nxtj<=s) min_(ans,A[i][j][k]+b*t);
                // printf("%d %d %d: %lld\n",i,j,k,A[i][j][k]);
            } b*=10;
        }
        printf("%lld\n",ans);
    }
}
/*
2
2 1
2 1
*/