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
#include <functional>
#include <random>
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
// ll M=1;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
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
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

bool mark[maxn];
vector<int> edge[maxn];
int base[maxn]; int h; // solve
int dfs(int x,int fa) {
    int ret=INF; if (base[x]) ret=h;
    for (int v:edge[x]) if (v!=fa) ret=min(ret,dfs(v,x)-1);
    // printf("dfs; %d: ret=%d\n",x,ret);
    ret=max(ret,0);
    if (!ret) mark[x]|=1;
    return ret;
}
int mA[maxn],mB[maxn],H;
int main() {
    int n,i,nA,nB,x;
    scanf("%d%d",&n,&H);
    FOR(i,1,n-1) {
        int x,y; scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    scanf("%d",&nA); FOR(i,1,nA) scanf("%d",&x),mA[x]=1;
    scanf("%d",&nB); FOR(i,1,nB) scanf("%d",&x),mB[x]=1;
    int cnt=0;
    FOR(i,1,n) mark[i]=0; mark[1]=1;
    FOR(i,1,n) base[i]=mA[i]; h=0; dfs(1,0);
    FOR(i,1,n) base[i]=mB[i]; h=H; dfs(1,0);
    FOR(i,1,n) cnt+=mark[i]; cnt--;
    // FOR(i,1,n) printf("%d ",mark[i]); puts(",- mark");
    FOR(i,1,n) mark[i]=0; mark[1]=1;
    FOR(i,1,n) base[i]=mB[i]; h=0; dfs(1,0);
    FOR(i,1,n) base[i]=mA[i]; h=H; dfs(1,0);
    FOR(i,1,n) cnt+=mark[i]; cnt--;
    printf("%d\n",cnt*2);
}
/*

*/