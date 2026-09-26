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

int A[maxn],id[maxn],B[maxn];
int rnk[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i,k;
        scanf("%d%d",&n,&k);
        FOR(i,1,n) scanf("%d",&A[i]),B[i]=A[i];
        if (n==k) {puts("1000000000"); continue;}
        int ans=0;
        // d(u,v)=min{min(A[u]->A[v]),min{A[x]}*2}
        // -> maximize=min{min(A[i],A[i+1]),A[x]*2}
        // ans = the maximum possible diameter
        FOR(i,1,n) id[i]=i;
        sort(id+1,id+1+n,[&](int i,int j){
            return A[i]<A[j];
        });
        FOR(i,1,n) rnk[id[i]]=i;
        sort(B+1,B+1+n);
        // 都不挨着
        max_(ans,B[k+1]);
        FOR(i,1,n-1) {
            // not set
            {
                int nk=k;
                int MIN=B[nk+1];
                max_(ans,min(MIN*2,min(A[i],A[i+1])));
                // printf("remove zero: nk=%d min %d %d\n",i,nk,MIN*2,min(A[i],A[i+1]));
            }
            // set x
            {
                int nk=k-1;
                if (min(rnk[i],rnk[i+1])<=nk+1) nk++; // remove nk objs
                int MIN=B[nk+1];
                max_(ans,min(MIN*2,max(A[i],A[i+1])));
                // printf("remove %d: nk=%d min %d %d\n",i,nk,MIN*2,max(A[i],A[i+1]));
            }
            // set x and y
            {
                int nk=k-2;
                if (min(rnk[i],rnk[i+1])<=nk+1) nk++; // remove nk objs
                if (max(rnk[i],rnk[i+1])<=nk+1) nk++; // remove nk objs
                if (nk>=0) {
                    int MIN=B[nk+1];
                    max_(ans,MIN*2);
                    // printf("remove %d %d: nk=%d %d\n",i,i+1,nk,MIN*2);
                }
            }
        }
        min_(ans,1000000000);
        printf("%d\n",ans);
    }
}
/* 
6 5
1 1 1 1 1 1

100000 100000

10000 10000

4 4
1 1 2 2

*/