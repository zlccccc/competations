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

int A[maxn];
int n;
vector<int> ans;
void push(int l,int r) { // dir=0: ->; 
    int i;
    if (l<=r) FOR(i,l,r) {ans.push_back(i%n); A[i%n]^=A[(i+1)%n];}
    else rFOR(i,r,l) {ans.push_back(i%n); A[i%n]^=A[(i+1)%n];}
}
void vis(const char *info) {
    int i;
    REP(i,n) pr2(A[i],n); puts(info);
}
void solve(int i,int j) { // i->j
    // printf("solve %d %d\n",i,j);
    int _i=i,_j=j;
    for (int l=j-i+1;l>1;l-=2) { // length
        push(j-1,i);
        if (l!=2) push(i+1,j-1);
        // printf("l=%d ",l); vis("solve");
        i++; j--;
    }
    if (_i<=(_i+_j)/2-1) push(_i,(_i+_j)/2-1);
    // vis("solve_final");
}
void SOLVE(int N) {
    int i; n=N;
    REP(i,n) A[i]=1<<i;
    solve(0,n-1);
    // vis("forward");
    solve((n+1)/2,n/2+n-1);
    // vis("mid");
    solve(0,n-1);
    // vis("backward");
}
// xor: A[i]^=A[j]; A[j]^=A[i]; A[i]^=A[j];
int main() {
    // SOLVE(6);
    // SOLVE(7);
    scanf("%d",&n);
    SOLVE(n);
    printf("%d\n",ans.size());
    for (auto now:ans) printf("%d ",now);
}
/*
*/