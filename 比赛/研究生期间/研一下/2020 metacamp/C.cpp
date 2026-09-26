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

int A[maxn],B[maxn],C[maxn];
int la[maxn],ra[maxn];
int lb[maxn],rb[maxn];
int Ca[maxn],Cb[maxn];
int main() {
    int n,m,l,i; bool ok=0;
    while (~scanf("%d%d%d",&n,&m,&l)){
        if (ok) puts(""); ok=1;
        FOR(i,1,n) scanf("%d",&A[i]);
        FOR(i,1,m) scanf("%d",&B[i]);
        FOR(i,1,l) scanf("%d",&C[i]);
        int pos;//C
        bool okay=1;
        pos=1; FOR(i,1,n) if (pos<=l&&A[i]==C[pos]) la[pos++]=i; la[0]=0; if (pos<=l) okay=0;
        pos=l; rFOR(i,1,n) if (pos>=1&&A[i]==C[pos]) ra[pos--]=i; ra[l+1]=n+1;
        pos=1; FOR(i,1,m) if (pos<=l&&B[i]==C[pos]) lb[pos++]=i; lb[0]=0; if (pos<=l) okay=0;
        pos=l; rFOR(i,1,m) if (pos>=1&&B[i]==C[pos]) rb[pos--]=i; rb[l+1]=m+1;
        // FOR(i,1,l) printf("(%d-%d) ",la[i],ra[i]); puts("<- a pos");
        // FOR(i,1,l) printf("(%d-%d) ",lb[i],rb[i]); puts("<- b pos");
        FOR(i,1,max(max(n,m),l)) Ca[i]=Cb[i]=0;
        int pla=1,pra=0,plb=1,prb=0;
        if (okay) {
            FOR(i,1,l+1) {
                int LA=la[i-1]+1,RA=ra[i]-1;
                int LB=lb[i-1]+1,RB=rb[i]-1;
                if (LA>RA||LB>RB) continue;
                // printf("check %d-%d; %d-%d\n",LA,RA,LB,RB);
                while (pla!=LA) Ca[A[pla]]--,pla++;
                while (plb!=LB) Cb[B[plb]]--,plb++;
                while (pra!=RA) {pra++,Ca[A[pra]]++; if (Ca[A[pra]]>0&&Cb[A[pra]]>0) okay=0;}
                while (prb!=RB) {prb++,Cb[B[prb]]++; if (Ca[B[prb]]>0&&Cb[B[prb]]>0) okay=0;}
            }
        }
        if (okay) printf("YES");
        else printf("NO");
    }
}
/*
4 5 2
1 2 3 4
3 4 2 1 3
2 3
1 1 1
1
1
1
2 2 1
1 2
2 1
2
3 2 1
1 2 3
2 3
1
2 2 1
1 2
1 2
1
*/