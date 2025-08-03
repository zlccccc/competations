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

typedef array<int,3> ar3;

int A[2007][2007];
int rpre[2007][2007],rnxt[2007][2007]; // pref,next
int cpre[2007][2007],cnxt[2007][2007];
int n,m;
vector<ar3> ans;
bool vis[maxn][2];
bool merged[2007][2007][2];
void chk_append(int x,int y,int dir) {
    if (dir==0) {
        if (rnxt[rnxt[0][y]][y]==n+1&&!vis[y][1]) {
            // printf("push x=%d %d !row\n",rnxt[0][y],y);
            ans.push_back({1,y,A[rnxt[0][y]][y]});
            vis[y][1]=1;
        }
    } else {
        if (cnxt[x][cnxt[x][0]]==m+1&&!vis[x][0]) {
            // printf("push %d y=%d !col\n",x,cnxt[x][0]);
            ans.push_back({0,x,A[x][cnxt[x][0]]});
            vis[x][0]=1;
        }
    }

}
void merge(int x,int y,int dir=0) { // remove x,y
    if (merged[x][y][dir]) return;
    merged[x][y][dir]=1;
    // printf("merge %d %d dir=%d\n",x,y,dir);
    if (dir==0) {
        int pre=rpre[x][y],nxt=rnxt[x][y];
        rnxt[pre][y]=nxt; rpre[nxt][y]=pre;
        chk_append(x,y,0);
    } else {
        int pre=cpre[x][y],nxt=cnxt[x][y];
        cnxt[x][pre]=nxt; cpre[x][nxt]=pre;
        chk_append(x,y,1);
    }
}
void check(int x,int y,int dir=0) { // check previous-i
    if (dir==0) {
        if (A[x][y]==A[rpre[x][y]][y]) merge(x,y,dir);// remove one
    }
    if (dir==1) {
        if (A[x][y]==A[x][cpre[x][y]]) merge(x,y,dir);
    }
}
int main() {
    int _,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j]);
    // if (n==1&&m==1) {puts("1"); printf("1 1 %d\n",A[1][1]);}
    FOR(i,0,n+1) FOR(j,0,m+1) {
        rpre[i][j]=i-1; rnxt[i][j]=i+1;
        cpre[i][j]=j-1; cnxt[i][j]=j+1;
    }
    FOR(i,1,n) FOR(j,1,m) {
        check(i,j,0); check(i,j,1);
        chk_append(i,j,0);
        chk_append(i,j,1);
    }
    REP(_,(int)ans.size()) {
        int pos=ans[_][1],dir=ans[_][0];
        // printf("solve pos=%d dir=%d; ans size=%d\n",pos,dir,ans.size());
        // puts("row down");
        // FOR(i,0,n) {FOR(j,1,m) if (!vis[i][0]&&!vis[j][1]) printf("%d ",rnxt[i][j]); puts("");}
        // puts("col right");
        // FOR(i,1,n) {FOR(j,0,m) if (!vis[i][0]&&!vis[j][1]) printf("%d ",cnxt[i][j]); puts("");}
        // puts("row down");
        // for (int i=0;i!=n+1;i=rnxt[i][1]) FOR(j,1,m) printf("%d%c",rnxt[i][j]," \n"[j==m]);
        // puts("col right");
        // FOR(i,1,n) {for (int j=0;j!=m+1;j=cnxt[i][j]) printf("%d ",cnxt[i][j]); puts("");}
        if (dir==0) {
            FOR(j,1,m) merge(pos,j,dir),check(rnxt[pos][j],j,dir);
            // for (j=cnxt[pos][0];j!=m+1;j=cnxt[pos][j]) merge(pos,j,dir),check(rnxt[pos][j],j,dir);
        } else {
            FOR(i,1,n) merge(i,pos,dir),check(i,cnxt[i][pos],dir);
            // for (i=rnxt[0][pos];i!=n+1;j=rnxt[i][pos]) merge(i,pos,dir),check(i,cnxt[i][pos],dir);
        }
    }
    if ((int)ans.size()!=n+m) puts("-1");
    else {
        printf("%d\n",ans.size());
        reverse(ans.begin(), ans.end());
        for (auto now:ans) printf("%d %d %d\n",now[0]+1,now[1],now[2]);
    }
}
/*
3 4
4 5 4 4
1 5 3 6
2 5 2 6

3 4
4 4 4 2
1 1 1 2
4 4 4 4

1 1
1

1 3
1 2 3
*/