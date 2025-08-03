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
const LL maxn=1e6+107;
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


char s[maxn],t[maxn];
int dp[maxn][2];//0:no add; 1:add
int main() {
    int _T,_; _T=1;
    scanf("%d",&_T);
    FOR(_,1,_T){
        int n,i; dp[0][1]=1; dp[0][0]=0;
        scanf("%d%s%s",&n,s+1,t+1); 
        FOR(i,n+1,n+30) s[i]=t[i]='0';
        n+=30;
        int now=0;
        FOR(i,1,n) if (s[i]!=t[i]) now++;
        int ans=now;
        FOR(i,1,n) {
            dp[i][0]=dp[i][1]=INF; //tozero->toone
            dp[i][0]=dp[i-1][0]+(s[i]!=t[i]);
            min_(dp[i][0],dp[i-1][1]+(s[i]!='0')+(t[i]!='1'));//1->0; and 1
            dp[i][1]=(s[i]!='1')+(t[i]!='0')+dp[i-1][1];//0->1; add; 1->1
            // printf("%d %d\n",dp[i][0],dp[i][1]);
        }
        printf("%d\n",dp[n][0]);
    }
}
/*
20
5
11111
00000
5
10100
01010
5
00000
00001
8
00111111
00000000
*/