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

int A[maxn];
// map<int,int> MP;
int MP[(int)(2.2e7)],MID0=1.1e7;
int CNT[maxn],MID=100000;
int main() {
    int n,i,j,k,ans=0;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(k,-50,50) {
        int nowans=0;
        // MP.clear(); MP[0]=0;
        FOR(i,1,n) {
            MP[A[i]-i*k+MID0]++;
            nowans=max(nowans,MP[A[i]-i*k+MID0]);
        }
        FOR(i,1,n) MP[A[i]-i*k+MID0]=0;
        // FOR(i,1,n) MP[A[i]-i*k]++;
        // for (auto now:MP) nowans=max(nowans,now.second);
        ans=max(ans,nowans);
    }
    // printf("firts-nowans=%d\n",ans);
    FOR(i,1,n) CNT[i]=0;
    FOR(i,1,n) {
        FOR(j,i+1,min(i+2000,n)) if ((A[j]-A[i])%(j-i)==0) CNT[(A[j]-A[i])/(j-i)+MID]++;
        FOR(j,i+1,min(i+2000,n)) if ((A[j]-A[i])%(j-i)==0) max_(ans,CNT[(A[j]-A[i])/(j-i)+MID]+1),CNT[(A[j]-A[i])/(j-i)+MID]=0;
    }
    printf("%d\n",n-ans);
}
/*
10
4
999999999 999999999 999999999 999999999
*/