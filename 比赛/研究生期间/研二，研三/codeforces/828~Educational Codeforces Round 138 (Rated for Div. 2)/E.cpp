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
const LL maxn=2e6+107;
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

char pools[maxn],*s[maxn];
int poold[maxn],*d[maxn];
bool mrk[maxn],*mark[maxn];
pii poolp[maxn],*p[maxn];
deque<pii> Q;
void push(int i,int j,int dis) {
    if (s[i][j]=='.') dis++,Q.push_back({i,j});
    else Q.push_front({i,j});
    d[i][j]=dis; mark[i][j]=0;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i,j;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) s[i]=pools+(i-1)*(m+1),d[i]=poold+(i-1)*(m+1);
        FOR(i,1,n) mark[i]=mrk+(i-1)*(m+1),p[i]=poolp+(i-1)*(m+1);
        FOR(i,1,n) scanf("%s",s[i]+1);
        // puts("read done ??");
        FOR(i,1,n) FOR(j,1,m) {
            // printf("i,j=%d %d\n",i,j);
            mark[i][j]=1; d[i][j]=INF; p[i][j]={0,0};
            if (i!=1&&s[i-1][j]=='#') mark[i][j]=0;
            if (i!=n&&s[i+1][j]=='#') mark[i][j]=0;
            if (j!=1&&s[i][j-1]=='#') mark[i][j]=0;
            if (j!=m&&s[i][j+1]=='#') mark[i][j]=0;
            if (s[i][j]=='#') mark[i][j]=1;
        }
        j=1;
        FOR(i,1,n) if (mark[i][j]) push(i,j,0);
        while (Q.size()) {
            auto pp=Q.front(); Q.pop_front();
            i=pp.first; j=pp.second;
            // printf("dfs solve %d %d\n",i,j);
            int ax,ay;
            FOR(ax,-1,1) FOR(ay,-1,1) {
                if (ax&&ay) {
                    if (1<=i+ax&&i+ax<=n&&1<=j+ay&&j+ay<=m&&mark[i+ax][j+ay]) {
                        push(i+ax,j+ay,d[i][j]),p[i+ax][j+ay]={i,j};
                    }
                }
            }
            // if (i!=1&&s[i-1][j]=='#'&&!mark[i-1][j]&&!d[i-1][j]) push(i-1,j,d[i][j]),p[i-1][j]={i,j};
            // if (i!=n&&s[i+1][j]=='#'&&!mark[i+1][j]&&!d[i+1][j]) push(i+1,j,d[i][j]),p[i+1][j]={i,j};
            // if (j!=1&&s[i][j-1]=='#'&&!mark[i][j-1]&&!d[i][j-1]) push(i,j-1,d[i][j]),p[i][j-1]={i,j};
            // if (j!=m&&s[i][j+1]=='#'&&!mark[i][j+1]&&!d[i][j+1]) push(i,j+1,d[i][j]),p[i][j+1]={i,j};
        }
        int ans=INF;
        j=m;
        FOR(i,1,n) ans=min(ans,d[i][j]);
        if (ans==INF) {puts("NO"); continue;}
        FOR(i,1,n) if (ans==d[i][j]) {
            while (1) {
                auto pp=p[i][j];
                s[i][j]='#';
                i=pp.first; j=pp.second;
                // printf("backtrace %d %d\n",i,j);
                if (i==0&&j==0) break;
            }
            break;
        }
        puts("YES");
        FOR(i,1,n) puts(s[i]+1);
    }
}
/*
4
2 4
.#..
..#.
3 3
#.#
...
.#.
5 5
.....
.....
.....
.....
.....
4 3
#..
.#.
#.#
...

*/