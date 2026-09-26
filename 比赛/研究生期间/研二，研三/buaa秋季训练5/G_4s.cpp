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
const LL maxn=2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
LL M=1e9+7;
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

typedef array<int,4> ar4;
typedef array<int,2> ar2;
int val[maxn];
inline int lowbit(int x) {return x&-x;}
void update(int x) {
    for (;x<=2e6;x+=lowbit(x)) val[x]++;
}
int query(int x) {
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=val[x];
    return ret;
}

vector<int> V;
ar4 A[maxn];
ar4 B[maxn]; // pos(L|R),type,val(X|Y),id
int ans[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d%d%d",&A[i][0],&A[i][1],&A[i][2],&A[i][3]);
    auto getid=[&](int x) {
        return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
    };
    FOR(i,1,n) V.push_back(A[i][0]),V.push_back(A[i][2]);
    sort(V.begin(),V.end());
    FOR(i,1,n) A[i][0]=getid(A[i][0]),A[i][2]=getid(A[i][2]);
    V.clear();
    FOR(i,1,n) V.push_back(A[i][1]),V.push_back(A[i][3]);
    sort(V.begin(),V.end());
    FOR(i,1,n) A[i][1]=getid(A[i][1]),A[i][3]=getid(A[i][3]);
    V.clear();

    // FOR(i,1,n) printf("%d %d %d %d\n",A[i][0],A[i][1],A[i][2],A[i][3]); puts("<- A");
    auto solve=[&]() {
        int i,tot=0;
        sort(B+1,B+1+n*2);
        FOR(i,1,2e6) val[i]=0;
        FOR(i,1,n*2) {
            // printf("pos=%d; op=%d; val=%d; id=%d\n",B[i][0],B[i][1],B[i][2],B[i][3]);
            if (B[i][1]==0) ans[B[i][3]]+=tot-query(B[i][2]);
            if (B[i][1]==1) tot++,update(B[i][2]);
        }
        // FOR(i,1,n) printf("%d ",ans[i]); puts("<- ans");
    };
    // x,l,y,r = 0,1,2,3
    FOR(i,1,n) B[i]={A[i][0],0,A[i][1],i},B[i+n]={A[i][2],1,A[i][3],i}; solve(); //y<x; r<l
    FOR(i,1,n) B[i]={A[i][1],0,2*n+1-A[i][2],i},B[i+n]={A[i][3],1,2*n+1-A[i][0],i}; solve(); //r<l; x>y;
    FOR(i,1,n) B[i]={2*n+1-A[i][2],0,2*n+1-A[i][3],i},B[i+n]={2*n+1-A[i][0],1,2*n+1-A[i][1],i}; solve(); //x>y; l<r
    FOR(i,1,n) B[i]={2*n+1-A[i][3],0,A[i][0],i},B[i+n]={2*n+1-A[i][1],1,A[i][2],i}; solve(); //l<r, y<x
    FOR(i,1,n) printf("%d\n",n-1-ans[i]);
}
/*

3
-1 -1 -3 -3
-2 -2 -5 -5
-4 -4 -6 -6

*/