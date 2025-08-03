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

ll A[maxn],B[maxn],Ans[maxn];
int S[maxn];
int main() {
    int n;
    while (~scanf("%d",&n)) {
        int i;
        FOR(i,1,n) scanf("%lld%lld",&A[i],&B[i]); B[0]=0;
        rFOR(i,0,n-1) B[i]=max(B[i],B[i+1]);
        FOR(i,0,n) B[i]*=2;
        int idpos=1,st=1,ed=0,k;
        // Ans: prev都做过了
        //Ans[k]<=A[i]: min(B[k+1])+A[i]
        //A[i]<Ans[k]: min(Ans[k]+B[k+1])
        FOR(i,1,n) {//f(x)=min{max(A[i],Ans[k])+B[k+1]}; A down, B up, Ans up
            while (idpos<i&&Ans[idpos]<=A[i]) idpos++;
            while (st<=ed&&Ans[S[st]]<=A[i]) st++;
            Ans[i]=A[i]+B[idpos];
            if (st<=ed) min_(Ans[i],Ans[S[st]]+B[S[st]+1]);
            while (st<=ed&&Ans[S[ed]]+B[S[ed]+1]>=Ans[i]+B[i+1]) ed--;
            S[++ed]=i;
            // printf("%d: %lld; mor=%lld; A=%lld; idpos=%d;+B=%lld\n",i,Ans[i],Ans[i]+B[i+1],A[i],idpos,B[idpos-1]);
            // FOR(k,st,ed) printf("%d(%lld) ",S[k],Ans[S[k]]+B[S[k]+1]); puts("<- k");
        } printf("%lld\n",Ans[n]);
    }
}
/*
*/