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

int A[maxn],pos[maxn],pre[maxn];
int F[maxn],G[maxn],tmp[maxn];
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        scanf("%d",&A[i]);
        pre[i]=pos[A[i]];
        pos[A[i]]=i;
    } F[0]=1;//从前往后匹配,最多匹配到x的方案数
    FOR(i,2,m) {//需要记录pervious_last
        int noww=0,j,k;
        FOR(k,0,n) if (F[k]){
            FOR(j,0,n) G[j]=0; G[k]=1; noww=0;
            FOR(j,k,n) {//end at this position
                add_(G[j],noww);
                if (pre[j]>k) add_(G[j],M-G[pre[j]]%M);//new
                add_(noww,G[j]);
                printf("noww=%d(%d) ",noww,G[pre[j]]);
            }
            FOR(j,k,n) add_(tmp[j],(ll)(G[j]*F[k])%M);
            FOR(j,0,n) printf(" -- %d ",G[j]); puts("");
        }
        FOR(j,0,n) F[j]=tmp[j],tmp[j]=0;
        FOR(j,0,n) printf("%d ",F[j]); puts("");
    } int ans=0;
    FOR(i,0,n) add_(ans,F[i]);
    printf("%d\n",ans);
}
/*
*/