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

map<pii,ll> MP;
double value[maxn][2];
double p[maxn];
void solve() {
    int n,i,k;
    scanf("%d%lf",&n,&p[1]);
    p[1]=1-p[1];
    FOR(i,2,n) p[i]=pow(p[1],i);//not have
    value[0][0]=0; value[0][1]=INF;
    value[1][1]=0; value[1][0]=1;//1:have; 0:unknown
    FOR(i,2,n) {
        value[i][0]=value[i][1]=i;
        FOR(k,1,i-1) {
            // double pkleft=
            double f1=1+((1-p[k])*value[k][1]
                       +p[k]*(1-p[i-k])*value[i-k][1]
                       +(1-p[k])*value[i-k][0])/(1-p[k]*p[i-k]);
            double f2=value[k][0]+value[i-k][0];
            min_(value[i][1],f1);//p[k]:not have
            min_(value[i][0],f2);//p[k]:not have
            // printf("update: %f %f, %f %f %f\n",f1,f2,(1-p[i])*value[k][0]/(1-p[i]),p[k]*(1-p[i-k])*value[i-k][1],(1-p[k])*value[i-k][0]);
        }
        // printf("  niit: %f %f %f\n",value[i][0],value[i][1],1-p[i]);
        min_(value[i][0],1+(1-p[i])*value[i][1]);
        // printf("  final: %f %f\n",value[i][0],value[i][1]);
    }
    printf("%.14f\n",value[n][0]);
}
int main() {
    solve();
    // while (1) solve();
}
/*
2 0.1
3 0.2
*/