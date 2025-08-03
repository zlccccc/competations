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
const LL maxn=1e4+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

namespace mincostflow {
    typedef ll type;
    const type INF=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap,cost; int rev;
        node(int t=0,type c=0,type _c=0,int n=0):
            to(t),cap(c),cost(_c),rev(n) {};
    }; vector<node> edge[maxn];
    void addedge(int from,int to,type cap,type cost,type rcap=0) {
        edge[from].push_back(node(to,cap,cost,edge[to].size()));
        edge[to].push_back(node(from,rcap,-cost,edge[from].size()-1));
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
            for (node &e:edge[v]) {
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
        int i;
        rep(i,cur[x],(int)edge[x].size()) {
            node &e=edge[x][i];
            if (!mark[e.to]&&e.cap) {
                if (dis[x]+e.cost==dis[e.to]) {
                    int f=dfs(e.to,t,min(flow,e.cap));
                    e.cap-=f; edge[e.to][e.rev].cap+=f;
                    ret+=f; flow-=f; cur[x]=i;
                    if (flow==0) break;
                }
            }
        } mark[x]=0;
        return ret;
    }
    pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
        type ret=0,ans=0;
        while (flow) {
            spfa(s,t,n); if (dis[t]==INF) break;
            // printf("dis=%lld\n",dis[t]); int i;
            // FOR(i,1,n) printf("%lld ",dis[i]); puts("<- dis");
            // 这样加当前弧优化会快, 我也不知道为啥
            memset(cur+1,0,n*sizeof(int));
            type len=dis[t],f;
            while ((f=dfs(s,t,flow))>0)//while也行
                ret+=f,ans+=len*f,flow-=f;
        } return make_pair(ret,ans);
    }
    void init(int n) {
        int i; FOR(i,1,n) edge[i].clear();
    }
}

bool prime[1000007];
array<int,3> A[1000007],B[1000007];
ll ans[1000007],Ans;
int main() {
    int n,i;
    FOR(i,1,1e6) prime[i]=1;
    prime[1]=0;
    FOR(i,2,1e6) if (prime[i]) {
        // printf("%d ",i);
        for (int j=i+i;j<=1e6;j+=i) prime[j]=0;
    }
    vector<int> chk;
    FOR(i,1,10000) if (i*(i-1)<=1e6) {
        if (prime[i&(i>>1)]) {
            chk.push_back(i); //,printf("%d %d\n",i,i&(i>>1));
            // printf("%d:%d\n",i,i*(i-1));
        }
    }
    // for (int v:chk) for (int k:chk) if (v%(k*(k-1))==0) printf("check %d %d(k*(k-1)=%d)\n",v,k,k*(k-1));
    // printf("%d ",chk.size()); puts("<- chk");
    // for (int v:chk) printf("%d ",v); puts("<- chk");
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d%d",&A[i][0],&A[i][1],&A[i][2]),Ans+=(ll)A[i][1]*A[i][1];
    sort(A+1,A+1+n);
    FOR(i,1,n) B[i]=A[i];
    memset(ans,0x3f,sizeof(ans));
    function<ll(int)> getvalue=[&](int j) {
        return (ll)A[j][1]*A[j][1]-(ll)(A[j][1]-A[j][2])*(A[j][1]-A[j][2]);
    };
    function<void(set<int>,set<int>)> solve=[&](set<int> banS,set<int> banT) {
        int i,S=n+n+1,T=n+n+2;
        FOR(i,1,n) A[i]=B[i];
        mincostflow::init(n+n+2);
        rFOR(i,1,n) if (prime[A[i][0]&(A[i][0]>>1)]) {
            if (banS.count(A[i][0])) continue;
            mincostflow::addedge(S,i,1,0);
            int j;
            FOR(j,i+1,n) if (A[j][0]%(A[i][0]*(A[i][0]-1))==0) {
                if (banT.count(A[j][0])) continue;
                if (A[j][2]<=A[j][1]) {
                    mincostflow::addedge(n+j,T,1,-((ll)A[j][1]*A[j][1]-(ll)(A[j][1]-A[j][2])*(A[j][1]-A[j][2])));
                    A[j][1]-=A[j][2];
                }
                mincostflow::addedge(i,j+n,1,0);
                // printf("edge %d -> %d\n",i,j);
            }
        }
        // FOR(i,1,n) mincostflow::addedge(i+n,T,1,0);
        ll nowans=0; i=0;
        while (1) {
            pll res=mincostflow::mincostflow(S,T,n+n+2,1);
            // printf("solve %lld %lld\n",res.first,res.second);
            if (res.first==0) break; i++;
            nowans-=res.second; min_(ans[i],Ans-nowans);
        }
        // rep(i,1,(int)nowans.size()) printf("%lld ",Ans-nowans[i]); puts("<- solve");
    };
    solve({},{150,294}); // 6 in S: 150 not int T
    solve({150},{294});
    solve({294},{150});
    solve({150,294},{});
    FOR(i,1,n) {
        if (ans[i]==INFF) printf("-1\n");
        else printf("%lld\n",ans[i]);
    }
}
/*
*/