// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

namespace mincostflow {
    typedef ll type;
    const type INF=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap,cost; int next;
        node(int t=0,type c=0,type _c=0,int n=0):
            to(t),cap(c),cost(_c),next(n) {};
    } edge[maxn*2]; int tot;
    int head[maxn];
    int addedge(int from,int to,type cap,type cost,type rcap=0) { //cost初始值不能有负环
        // printf("mincostflow addedge %d %d %d %d\n",from,to,cap,cost);
        if (!cap) return 0; // init了俩空的edge
        edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
        return tot-2;
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
        tot=2;
    }
}
namespace pipeflow {
    typedef int type;
    int eid[maxn],sgn[maxn],etot;
    type in[maxn],out[maxn],flow[maxn];
    ll all=0;
    int s_s,t_t;//S,T
    int addedge(int u,int v,int low,int high,int cost) {
        // printf("addedge %d %d %d %d %d\n",u,v,low,high,cost);
        if (cost<0) {
            eid[etot]=mincostflow::addedge(v,u,high-low,-cost);
            out[u]+=high; in[v]+=high; sgn[etot]=-1; flow[etot++]=high;
            all+=(ll)-cost*high;
        } else  {
            eid[etot]=mincostflow::addedge(u,v,high-low,cost);
            out[u]+=low; in[v]+=low; sgn[etot]=1; flow[etot++]=low;
            all+=(ll)cost*low;
        }
        return etot-1;
    }
    void init(int n) {
        s_s=n+1,t_t=n+2; etot=0;
        memset(in+1,0,n*sizeof(type));
        memset(out+1,0,n*sizeof(type));
        mincostflow::init(n+2);
    }
    bool solve(int n) {
        int sum=0,i;
        FOR_(i,1,n) {
            sum+=max(0,in[i]-out[i]);
            if (in[i]>out[i]) mincostflow::addedge(s_s,i,in[i]-out[i],0);
            if (in[i]<out[i]) mincostflow::addedge(i,t_t,out[i]-in[i],0);
        }
        // FOR_(i,1,n) printf("%d(%d) ",in[i],out[i]); puts("<- solve");
        auto res=mincostflow::mincostflow(s_s,t_t,n+2); all+=res.second;
        if (res.first!=sum) return 0;
        REP_(i,etot) flow[i]+=mincostflow::edge[eid[i]^1].cap*sgn[i];//more
        // REP(i,etot) printf("%d ",flow[i]); puts("<- flow");
        return 1;
    }
}

int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    pipeflow::init(n);
    int res=0;
    FOR_(i,1,m) {
        int u,v,c,f;
        scanf("%d%d%d%d",&u,&v,&c,&f);
        if (f<=c) {
            pipeflow::addedge(u,v,f,f,0);  // 已经流了f
            pipeflow::addedge(v,u,0,f,1);  // 流量小于f
            pipeflow::addedge(u,v,0,c-f,1);  // 流量大于f
            pipeflow::addedge(u,v,0,INF,2);
        } else {  // c<f
            pipeflow::addedge(u,v,c,c,0);    // 已经流了c
            pipeflow::addedge(v,u,0,c,1);    // 流量小于c
            pipeflow::addedge(u,v,0,f-c,0);  // c->f
            pipeflow::addedge(u,v,0,INF,2);  // 流量大于f
            res+=f-c;
        }
    }
    pipeflow::addedge(n,1,0,INF,0);
    pipeflow::solve(n);
    printf("%lld\n",res+pipeflow::all);
}
/*
*/