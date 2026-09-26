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

char str[67];
ll A[maxn];
int Sum[1<<16|7],Count[1<<16|7];
int B[maxn],id[maxn];
int main() {
    int n,m,i,j,k,t,_;
    scanf("%d%d%*d",&n,&m);
    FOR(i,1,n) {
        scanf("%s",str);
        REP(k,m) A[i]=A[i]<<1|(str[k]-'0');
    } int nowans=0; ll ans=0;
    REP(i,(1<<16)) Count[i]=__builtin_popcount(i);
    FOR(_,1,100) {
        int tot=0;
        int rx=rand()%n+1;
        random_shuffle(A+1,A+1+n);
        FOR(i,1,n) B[i]=0;
        REP(t,m) if ((A[rx]>>t)&1) id[tot++]=t;
        if (tot==0) continue;
        FOR(i,1,n) REP(t,tot) if ((A[i]>>id[t])&1) B[i]|=1<<t;
        int len=(1<<tot);
        REP(t,len) Sum[t]=0;
        FOR(i,1,n) Sum[B[i]]++;
        for(i=2;i<=len;i<<=1){
            for(j=0;j<len;j+=i){
                for(k=j;k<j+i/2;k++){
                    int l=k,r=k+i/2;
                    Sum[l]+=Sum[r];
                }
            }
        }
        REP(t,len) if (Sum[t]+Sum[t]>=n&&Count[t]>nowans) {
            nowans=Count[t]; ans=0;
            REP(i,tot) if ((t>>i)&1) ans|=1ll<<id[i];
        }
        // pr2(A[1],m); printf(" check <- %d\n",nowans);
        // FOR(i,1,n) pr2(B[i],tot); puts("<- A");
        // REP(t,len) {pr2(t,tot); printf("%d <\n",Sum[t]);}
        // system("pause");
    } rREP(i,m) printf("%d",(int)((ans>>i)&1));
}
/*
4 5 4
00000
00000
11111
11111
*/