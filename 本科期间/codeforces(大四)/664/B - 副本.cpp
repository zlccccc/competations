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
const LL maxn=2e5+107;
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

// 最后一定是环
// 所以每个点一定有入度
int limit=6;
int maxi=21;
bitset<720> cnt[1<<21|7];//bitset
int decode(int x[]) {//okay[i]
    int ret=0,l=0; int i;
    for (i=1;i<=limit;i++) {ret|=1<<(l+x[i]-1); l+=i;}
    return ret;
}
ll ans=0;
int id[maxn];
int okay[20],now[20];
int LIMIT;
void dfs(const int &mark,int k,const int &end,int val) {// k:position
    int i;
    if (k>end) {
        // printf("maxi=%d %d  %d   %d val=%d\n",maxi,((1<<maxi)-1)^id[val],limit,id[val],val);
        // printf("dfs mark=%d ; end=%d: val=%d; decode=",mark,end,val); pr2(decode(now),maxi); pr2(LIMIT,maxi); pr2(((1<<maxi)-1)^id[val],LIMIT); puts("<<LIMIT");
        if (mark==1) cnt[decode(now)].set(val);//initialize
        if (mark==2) id[val]=0;
        if (mark==3) id[val]&=LIMIT;//count
        if (mark==4) ans-=cnt[id[val]];//count
        if (mark!=3||LIMIT!=(1<<limit)-1) {
            FOR(i,1,end) printf("%d ",now[i]);
            printf("dfs mark=%d ; end=%d: val=%d; val=%d decode=%d  ",mark,end,val,id[val],decode(now)); pr2(decode(now),maxi);
            pr2(LIMIT,maxi); printf(" <<<limit "); pr2(id[val],maxi); puts("fin");
        }
        return;
    }
    FOR(i,1,k) if (!((okay[k]>>i)&1)) {
        now[k]=i;
        dfs(mark,k+1,end,val*k+i-1);
    }
}
int val[maxn][20];
vector<pair<int,int> > edge[maxn];//dis=k:okay
int main() {
    int n,m,k;
    int i,j;
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,m) {
        int u,v,w; scanf("%d%d%d",&u,&v,&w);
        edge[u].push_back(make_pair(w,v));
    }
    limit=min(limit,k);
    maxi=limit*(limit+1)/2;
    // printf("maxi=%d\n",maxi);
    FOR(i,1,k) okay[i]=0;
    dfs(1,1,limit,0);//initialize
    REP(i,maxi) {
        REP(j,(1<<maxi)) if ((j>>i)&1) cnt[j]=cnt[j]|cnt[j^(1<<i)];
    }
    dfs(2,limit+1,k,0);
    FOR(i,1,n) {
        sort(edge[i].begin(), edge[i].end());
        int t=edge[i].size();
        REP(j,t) val[edge[i][j].second][t]|=1<<(j+1);//kth
    }
    FOR(i,1,n) {
        FOR(j,1,9) okay[j]=val[i][j];
        {
            LIMIT=0; int k=0;
            FOR(j,1,limit) LIMIT=LIMIT|((val[i][j]>>1)<<k),k+=j;
            printf("i=%d\n",i);
            printf("LIMIT=%d ",LIMIT); pr2(LIMIT,maxi); puts("");
        }
        dfs(3,limit+1,k,0);
    }
    FOR(i,1,k) okay[i]=0;
    ans=1;
    FOR(i,1,k) ans=ans*i;
    dfs(4,limit+1,k,0);
    printf("%lld\n",ans);
}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/