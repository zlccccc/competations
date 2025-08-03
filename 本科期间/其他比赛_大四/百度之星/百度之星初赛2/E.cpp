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

namespace mincostflow {
    typedef int type;
    const type INF=0x3f3f3f3f;
    struct node {
        int to; type cap,cost; int next;
        node(int t=0,type c=0,type _c=0,int n=0):
            to(t),cap(c),cost(_c),next(n) {};
    } edge[maxn*2]; int tot;
    int head[maxn];
    void addedge(int from,int to,type cap,type cost,type rcap=0) {
        // printf("%d -> %d %d %d\n",from,to,cap,cost);
        edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
    }
    type dis[maxn];
    bool mark[maxn];
    void spfa(int s,int t,int n) {
        memset(dis+1,0x3f,n*sizeof(type));
        memset(mark+1,0,n*sizeof(bool));
        static int Q[maxn],ST,ED;
        dis[s]=0; ST=ED=0; Q[ED++]=s;
        while (ST!=ED) {
            int v=Q[ST]; mark[v]=0;
            if ((++ST)==maxn) ST=0;
            for (int i=head[v]; ~i; i=edge[i].next) {
                node &e=edge[i];
                if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
                    dis[e.to]=dis[v]+e.cost;
                    if (!mark[e.to]) {
                        if (ST==ED||dis[Q[ST]]<=dis[e.to]) {
                            Q[ED]=e.to,mark[e.to]=1;
                            if ((++ED)==maxn) ED=0;
                        } else {
                            if ((--ST)<0) ST+=maxn;
                            Q[ST]=e.to,mark[e.to]=1;
                        }
                    }
                }
            }
        }
    } int cur[maxn];
    type dfs(int x,int t,type flow) {
        if (x==t||!flow) return flow;
        type ret=0; mark[x]=1;
        for (int i=cur[x]; ~i; i=edge[i].next) if (!mark[edge[i].to]) {
                if (dis[x]+edge[i].cost==dis[edge[i].to]&&edge[i].cap) {
                    int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                    edge[i].cap-=f; edge[i^1].cap+=f;
                    ret+=f; flow-=f; cur[x]=i;
                    if (flow==0) break;
                }
            }
        mark[x]=0;
        return ret;
    }
    pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
        type ret=0,ans=0;
        while (flow) {
            spfa(s,t,n); if (dis[t]==INF) break;
            // 这样加当前弧优化会快, 我也不知道为啥
            memcpy(cur+1,head+1,n*sizeof(int));
            type len=dis[t],f;
            if ((f=dfs(s,t,flow))>0)//while也行
                ret+=f,ans+=len*f,flow-=f;
        } return make_pair(ret,ans);
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int));
        tot=0;
    }
} char str[27];
int cnt[28];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
    	int n; int i,j,k; int a,b,c;
    	scanf("%d%d%d%d",&n,&a,&b,&c);
        mincostflow::init(1+3+1+27);//S,T
        REP(i,27) cnt[i]=0;
        FOR(i,1,n) {
            scanf("%s",str);
            int t[4]; REP(k,3) t[str[k]-'0']=k; 
            int val=t[0]+t[1]*3+t[2]*9;//id
            cnt[val]++;
        } int S=1,T=1+3+27+1;
        mincostflow::addedge(S,2,a,0);
        mincostflow::addedge(S,3,b,0);
        mincostflow::addedge(S,4,c,0);
        FOR(i,0,2) FOR(j,0,2) FOR(k,0,2) {
            int val=i+j*3+k*9;
            int vid=val+1+1+3;
            if (!cnt[val]) continue;
            mincostflow::addedge(2,vid,INF,i);
            mincostflow::addedge(3,vid,INF,j);
            mincostflow::addedge(4,vid,INF,k);
            mincostflow::addedge(vid,T,cnt[val],0);
        } pii noww=mincostflow::mincostflow(S,T,1+3+1+27);
        // printf("%d %d\n",noww.first,noww.second);
        printf("%d\n",3*n-noww.second);
    }
}
/*
10000

*/