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
const LL maxn=407*2+107;
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

int n;
ll g[maxn][maxn];
ll lx[maxn],ly[maxn],slack[maxn];
int linky[maxn],par[maxn];
bool visy[maxn];
void augment(int root){
    std::fill(visy+1,visy+n+1,false);
    std::fill(slack+1,slack+n+1,INFF);
    int py; linky[py=0]=root;
    do{
        visy[py]=true;
        int x=linky[py],_y=0,y; ll d=INFF;
        FOR(y,1,n) if (!visy[y]){
            int tmp=lx[x]+ly[y]-g[x][y];
            if (tmp<slack[y]){
                slack[y]=tmp; par[y]=py;
            } if (slack[y]<d) {
                d=slack[y]; _y=y;
            }
        } FOR(y,0,n){
            if (visy[y]){
                lx[linky[y]]-=d;
                ly[y]+=d;
            } else slack[y]-=d;
        } py=_y;
    } while (linky[py]!=-1);
    do {
        int pre=par[py];
        linky[py]=linky[pre];
        py=pre;
    } while (py);
}
ll KM() {
    int i,y;
    FOR(i,1,n) {
        lx[i]=0; ly[i]=0; linky[i]=-1;
        FOR(y,1,n) max_(lx[i],g[i][y]);
    } ll ret=0;
    FOR(i,1,n) augment(i);
    FOR(i,1,n) ret+=g[linky[i]][i];
    return ret;
}
int A[maxn],B[maxn],P[maxn],Q[maxn];
int main() {
    int i,j;
    scanf("%d",&n);
    // mincostflow::init(n*2+2);
    // int S=n*2+1,T=n*2+2;
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) scanf("%d",&P[i]);
    FOR(i,1,n) scanf("%d",&B[i]);
    FOR(i,1,n) scanf("%d",&Q[i]);
    // FOR(i,1,n) mincostflow::addedge(S,i,1,0);
    // FOR(i,1,n) mincostflow::addedge(i+n,T,1,0);
    FOR(i,1,n) FOR(j,1,n) {
        g[i][j]=-(max(0,P[i]-B[j])+max(0,Q[j]-A[i]));
    }
    // auto P=mincostflow::mincostflow(S,T,n*2+2,n);
    printf("%lld\n",-KM());
}
/*
3
4 10 4
6 1 10
1 9 3
4 9 8

5
3 10 2 1 5
9 7 2 10 1
1 6 10 8 0
9 4 4 1 8
*/