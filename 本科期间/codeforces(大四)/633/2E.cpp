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

int A[maxn],n;
bool mark[maxn];
void init(){
    int i,j;
    FOR(i,1,1000) if (!mark[i]){
        if (i==n+1) printf("i=%d\n",i);
        FOR(j,i+1,1000) if (!mark[j]&&!mark[i^j]) {
            A[++n]=i; A[++n]=j; A[++n]=i^j;
            mark[i]=mark[j]=mark[i^j]=1;
            break;
        }
    }
}
//1 2 3 4(first)
//1 3 4 2(second)
//1 4 2 3(third)
int p[10][10];
ll solve(ll x,ll now,int k) {
    if (now==1) return 0;
    int part=(x/(now/4))&3;
    // printf("solve: %lld %lld %d;part=%d:+%lld\n",x,now,k,part,p[k][part]*now/4);
    return solve(x%now,now/4,k)+p[k][part]*now/4;
}
ll getvalue(ll n){
    ll now=1;
    while (now<=n) now*=4; now/=4;
    ll ans=solve((n-now)/3,now,(n-now)%3)+now*((n-now)%3+1);
    // printf("getvalue %lld : %lld %lld\n",n,solve(n-now,now,n%3),now*(n%3+1));
    return ans;
}
void print(){
    int i;
    FOR(i,1,258) {
        printf("%d ",A[i]);
        printf("(%lld) ",getvalue(i));
        if (i%3==0) puts("");
    }
}
int main() {
    // init();
    p[0][0]=0; p[0][1]=1; p[0][2]=2; p[0][3]=3;
    p[1][0]=0; p[1][1]=2; p[1][2]=3; p[1][3]=1;
    p[2][0]=0; p[2][1]=3; p[2][2]=1; p[2][3]=2;
    // print();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        ll n;
        scanf("%lld",&n);
        printf("%lld\n",getvalue(n));
    }
}
/*
5
5
1 2 3 4 5
6
1 2 3 4 5 6
*/