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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1.5e5+107;
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

int val;
int cnt[maxn*37];
int son[maxn*37][2],tot;
int root;
void insert(int &x,int k,int depth) {
    if (!x) x=++tot,cnt[tot]=0,son[tot][0]=son[tot][1]=0;
    cnt[x]++;
    // if (depth==0) printf("%d : %d\n",x,k); 
    if (depth==-1) return;
    insert(son[x][(k>>depth)&1],k,depth-1);
}
int solve2(int x,int y,int depth) {
    if (!x||!y) return 0;
    int c=(val>>depth)&1,ret=0;
    if (c) {
        int x0y1=solve2(son[x][0],son[y][1],depth-1),x1y0=solve2(son[x][1],son[y][0],depth-1);
        add_(ret,(ll)x0y1*x1y0%M);
        add_(ret,(ll)x0y1*(powMM(2,cnt[son[x][1]])+powMM(2,cnt[son[y][0]])-1)%M);
        add_(ret,(ll)x1y0*(powMM(2,cnt[son[x][0]])+powMM(2,cnt[son[y][1]])-1)%M);
        add_(ret,(powMM(2,cnt[son[x][0]])+M-1)*(powMM(2,cnt[son[y][0]])+M-1)%M);
        add_(ret,(powMM(2,cnt[son[x][1]])+M-1)*(powMM(2,cnt[son[y][1]])+M-1)%M);
    } else {
        add_(ret,solve2(son[x][0],son[y][0],depth-1));
        add_(ret,solve2(son[x][1],son[y][1],depth-1));
    } 
    // printf("solve2 %d %d %d; c=%d; ret=%d\n",x,y,depth,c,ret);
    return ret;
}
int solve1(int x,int depth) {
    if (!x) return 0;
    // printf("solve1 %d %d\n",x,depth);
    int c=(val>>depth)&1,ret;
    if (!c) ret=(solve1(son[x][0],depth-1)+solve1(son[x][1],depth-1))%M;
    else {
        ret=(powMM(2,cnt[son[x][0]])+powMM(2,cnt[son[x][1]])+M+M-2)%M;
        add_(ret,solve2(son[x][0],son[x][1],depth-1));
    }
    // printf("solve1 %d %d; c=%d; ret=%d\n",x,depth,c,ret);
    return ret;
}
int main() {
    int n,i; root=0; tot=0;
    scanf("%d%d",&n,&val); val++;
    FOR(i,1,n) {
        int x; scanf("%d",&x);
        insert(root,x,30);
    }
    printf("%d\n",solve1(root,30));
}
/*
*/