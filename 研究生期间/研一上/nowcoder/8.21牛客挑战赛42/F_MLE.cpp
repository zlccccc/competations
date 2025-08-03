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
const LL maxn=1e5+107;
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
 
typedef bitset<90*90> BIT;
//n*90*90/64
vector<int> ksum[maxn];
BIT bit[90][90][90];
vector<int> v;
int A[90][90];
int val[90*90];
int solve(BIT x) { //todo speed up it
    int res=0; int i;
    // REP(i,90*90) if (x[i])  printf("i=%d\n",i);
    REP(i,90*90) if (x[i]) add_(res,val[i]);
    return res;
}
int main() {
    int n,limit,i,j,k,sum=0;
    scanf("%d%d",&n,&limit);
    FOR(i,1,limit) add_(sum,powMM(i,limit));
    FOR(i,1,n) FOR(j,1,n) {
        scanf("%d",&A[i][j]);
        v.push_back(A[i][j]);
    } sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    REP(i,(int)v.size()) {
        val[i]=powMM(v[i],limit);
    }
    FOR(i,1,n) {
        FOR(j,1,n) {//j to k
            A[i][j]=lower_bound(v.begin(),v.end(),A[i][j])-v.begin();
            bit[i][j][j].set(A[i][j]);
        }
        FOR(j,1,n) FOR(k,j+1,n)
            bit[i][j][k]=bit[i][j][k-1]|bit[i][k][k];
    }
    // FOR(i,1,n) FOR(j,1,n) printf("%d%c",A[i][j]," \n"[j==n]);
    int m;
    scanf("%d",&m);
    FOR(i,1,m) {
        int x,y,X,Y;
        scanf("%d%d%d%d",&x,&y,&X,&Y);
        //y-Y
        if (x>X) swap(x,X);
        if (y>Y) swap(y,Y);
        BIT now;
        FOR(j,x,X) now|=bit[j][y][Y];
        printf("%lld\n",(sum+M-solve(now))%M);
    }
}
/*
6 1
1 0 0 1 1 1
 
6 2
1 0 0 1 1 1
*/