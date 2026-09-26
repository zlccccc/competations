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

//Cayley-Hamilton theorem
//然而我板子没写...
const int Mx=507;
struct matrix{
    int A[Mx];
    matrix(){memset(A,0,sizeof(A));}
}base,fin;
int MAX;
matrix mul(const matrix &A,const matrix &B){
    matrix C; int i,j;
    REP(i,MAX) REP(j,MAX) add_(C.A[(i+j)%MAX],(ll)A.A[i]*B.A[j]%M);
    return C;
}
matrix poww(matrix a,ll b) {
    matrix ret; ret.A[0]=1;//self-to-self
    for (;b;b>>=1ll,a=mul(a,a)) {
        if (b&1) ret=mul(ret,a);
    }
    return ret;
}
ll ans[Mx];
int main() {
    int n,i,j; ll k,a,b,c; scanf("%d%lld",&n,&k);
    scanf("%lld%lld%lld",&a,&b,&c); MAX=n;
    ll del=powMM(a+b+c,M-2);
    a=a*del%M; b=b*del%M; c=c*del%M;
    base.A[1]=a; base.A[n-1]=b; base.A[0]=c;
    fin=poww(base,k);

    REP(i,n) {
        ll k; scanf("%lld",&k);
        REP(j,n) add_(ans[(i+j)%n],k*fin.A[j]%M);
    }
    REP(i,n) printf("%lld ",ans[i]);
}
/*
4 2
1 1 2
1 1 0 0
*/