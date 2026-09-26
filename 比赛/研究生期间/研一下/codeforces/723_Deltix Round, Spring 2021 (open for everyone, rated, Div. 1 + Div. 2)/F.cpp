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
const LL maxn=2e5+107;
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

struct Node{
    int x,y,t;
}A[17],B[107];
int DNM[1<<14|7][107];
int DNN[1<<14|7][17];
int mint[1<<14|7][107];//min-time
int maxc[1<<14|7][107];//max-count
inline int dis(const Node &A,const Node &B) {
    return abs(A.x-B.x)+abs(A.y-B.y);
}
int main() {
    int i,n,m;
    scanf("%d%d",&n,&m);
    REP(i,n) scanf("%d%d",&A[i].x,&A[i].y);
    REP(i,m) scanf("%d%d%d",&B[i].x,&B[i].y,&B[i].t);
    sort(B,B+m,[&](const Node &x,const Node &y){
        return x.t<y.t;
    });
    memset(mint,0x3f,sizeof(mint));
    memset(DNM,0x3f,sizeof(DNM));
    memset(DNN,0x3f,sizeof(DNN));
    int x,y,k;//x
    REP(k,n) mint[1<<k][0]=0;
    REP(k,m) DNM[0][k]=0;
    REP(k,(1<<n)) REP(y,n) if ((k>>y)&1) {
        REP(x,m) min_(DNM[k][x],dis(A[y],B[x]));
        REP(x,n) min_(DNN[k][x],dis(A[y],A[x]));
    }
    int ans=0;
    REP(k,(1<<n)) {
        REP(x,m) {
            if (k==0) max_(maxc[k][x],1);//start
            else REP(y,x+1) if (mint[k][y]+DNM[k][x]<=B[x].t) max_(maxc[k][x],y+1);//A->B
            REP(y,x) if (maxc[k][y]&&B[y].t+dis(B[y],B[x])<=B[x].t) max_(maxc[k][x],maxc[k][y]+1);//B->B
            ans=max(ans,maxc[k][x]);
            // pr2(k,n); printf("id=%d:maxcount=%d; t=%d\n",x,maxc[k][x],B[x].t);
            // REP(y,x+1) printf("%d+%d ",mint[k][y],DNM[k][x]); puts("<- A->B");
            // REP(y,x) printf("%d ",B[y].t+dis(B[y],B[x])); puts("<- B->B");
            // REP(y,n) if (!((k>>y)&1)) {pr2(k|(1<<y),n); printf("%d ",B[x].t+dis(B[x],A[y])); puts("<- bx");}
            if (maxc[k][x]) min_(mint[k][maxc[k][x]],B[x].t);//move back
            if (maxc[k][x]) REP(y,n) if (!((k>>y)&1)) min_(mint[k|(1<<y)][maxc[k][x]],B[x].t+dis(B[x],A[y]));//B->A
        }
        REP(y,n) if (!((k>>y)&1)) REP(x,m+1) min_(mint[k|(1<<y)][x],mint[k][x]+DNN[k][y]);//A->A; merging
        // REP(y,m+1) printf("%d ",mint[k][y]); puts("<- mint");
    }
    printf("%d\n",ans);
}
/*
3 5
1 1
1 9
2 9
6 7 1
5 3 9
7 4 5
2 3 5
9 9 7
*/