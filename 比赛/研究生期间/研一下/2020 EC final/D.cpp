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

int dist[5007][5007];
vector<int> edge[5007];
int more[5007];
double get(int v,int cost) {
    if (!v) return 0;
    if (!cost) return v;
    int base=cost/v,mor=cost%v;
    return mor/(1.+base+1)+(v-mor)/(1.+base);
}
double get(int a,int b,int costa,int costb){
    double ret=2*get(a,costa)+get(b,costb);
    // printf("%d %d %d %d: %f\n",a,b,costa,costb,ret);
    return ret;
}
int main() {
    int n,m,k,i,j;
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    } int s1,s2,t1,t2;
    scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
    memset(dist,0x3f,sizeof(dist));
    FOR(i,1,n) {
        int dis=0;
        vector<int> now,nxt;
        now.push_back(i);
        dist[i][i]=0;
        while(now.size()) {
            dis++;
            for (int u:now) for (int v:edge[u]) 
                if (dist[i][v]==INF) dist[i][v]=dis,nxt.push_back(v);
            now.swap(nxt); nxt.clear();
        }
    }
    // FOR(i,1,n) {
    //     FOR(j,1,m) printf("%d ",dist[i][j]); puts("");
    // }
    memset(more,0x3f,sizeof(more));
    more[0]=dist[s1][t1]+dist[s2][t2];
    FOR(i,1,n) FOR(j,1,n) if (dist[i][j]!=INF) {
        more[dist[i][j]]=min((ll)more[dist[i][j]],(ll)dist[s1][i]+dist[s2][i]+dist[j][t1]+dist[j][t2]);
        more[dist[i][j]]=min((ll)more[dist[i][j]],(ll)dist[s1][i]+dist[t2][i]+dist[j][t1]+dist[j][s2]);
    }
    FOR(i,1,n) more[i]=min(more[i-1],more[i]);
    // FOR(i,0,n) printf("%d ",more[i]); puts("<<- more");
    double ans=INF;
    FOR(i,0,n) {
        int l=0,r=k;
        while (r-l>5) {
            int d=(r-l)/3;
            int dl=l+d,dr=r-d;
            double xl=get(i,more[i],dl,k-dl);
            double xr=get(i,more[i],dr,k-dr);
            if (xl>xr) l=dl;
            else r=dr;
        } FOR(j,l,r) ans=min(ans,get(i,more[i],j,k-j));
        // printf("%d(%d): %f, now=%f\n",i,more[i],l,get(i,more[i],l,k-l));
    } printf("%.12f\n",ans);
}
/*
*/