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

int vl[507],vr[507];
int A[507];
int main() {
    int i,j,k,n,ans=0;
    scanf("%d",&n);
    FOR(i,1,n) {
        char c[3];
        scanf("%s",c);
        if (c[0]=='-') A[i]=-1;
        else scanf("%d",&A[i]);
    }
    FOR(k,1,n) {
        if (A[k]!=-1) {
            FOR(i,0,n) vl[i]=0;
            vl[0]=1;
            FOR(i,1,k-1) {
                if (A[i]==-1) {
                    add_(vl[0],vl[0]); FOR(j,0,i) add_(vl[j],vl[j+1]);
                } else if (A[i]<=A[k]) {
                    rFOR(j,1,i) add_(vl[j],vl[j-1]);
                } else FOR(j,0,i) vl[j]=vl[j]*2%M;
            }
            FOR(i,k+1,n) {
                if (A[i]==-1) {
                    FOR(j,0,i) add_(vl[j],vl[j+1]);
                } else if (A[i]<A[k]) { // REMOVE LEFT
                    rFOR(j,1,i) add_(vl[j],vl[j-1]);
                } else FOR(j,0,i) vl[j]=vl[j]*2%M;
            }
            FOR(i,0,n) add_(ans,(ll)vl[i]*A[k]%M);
            // printf("k=%d; ans=%d\n",k,ans);
            // FOR(i,0,n) printf("%d ",vl[i]); puts("<- vl");
            // FOR(i,0,n) printf("%d ",vr[i]); puts("<- vr");
        }
    }
    printf("%d\n",ans);
}
/*
14
+ 1
-
+ 1
-
+ 1
+ 225915953
+ 225915953
+ 225915953
+ 225915953
+ 225915953
+ 225915953
+ 225915953
-
+ 225915953
*/