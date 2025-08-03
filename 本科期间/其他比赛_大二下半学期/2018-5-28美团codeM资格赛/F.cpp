#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2000+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}


//拆点后可以S向入连边,出向T连边,然后入和出就可以保持动态平衡
//注意观察特殊性质
struct node {
    int to,cap,cost,rev;
    node(int t=0,int c=0,int n=0,int r=0):
        to(t),cap(c),cost(n),rev(r) {}
};
vector<node> edge[maxn];
void addedge(int from,int to,int cap,int cost) {
//    printf("%d -> %d  %d %d\n",from,to,cap,cost);
    edge[from].push_back(node(to,cap,cost,edge[to].size()));
    edge[to].push_back(node(from,0,cost,edge[from].size()-1));
}
int dis[maxn];
bool mark[maxn];
int pre_v[maxn],pre_e[maxn];
deque<int> Q;
pair<int,int> mincostflow(int s,int t,int f) {
    int ret=0,d,_f=f;
    int i,v;
    while (f) {
        memset(dis,0x3f,sizeof(dis));
        memset(mark,0,sizeof(mark));
        while (Q.size()) Q.pop_front();
        Q.push_back(s);
        dis[s]=0;
        while (Q.size()) {
            v=Q.front();
            mark[v]=0;
            Q.pop_front();
            REP(i,(int)edge[v].size()) {
                node &e=edge[v][i];
                if (e.cap>0&&dis[e.to]>max(dis[v],e.cost)) {
                    dis[e.to]=max(dis[v],e.cost);
                    pre_v[e.to]=v;
                    pre_e[e.to]=i;
                    if (!mark[e.to]) {
                        if (Q.empty()||dis[Q.front()]<dis[e.to])
                            Q.push_back(e.to);
                        else Q.push_front(e.to);
                        mark[e.to]=1;
                    }
                }
            }
        }
        if (dis[t]==INF) break;
        d=f;
        for (v=t; v!=s; v=pre_v[v])
            d=min(d,edge[pre_v[v]][pre_e[v]].cap);
        f-=d;
        ret=dis[t];
        for (v=t; v!=s; v=pre_v[v]) {
            node &e=edge[pre_v[v]][pre_e[v]];
            e.cap-=d;
            edge[v][e.rev].cap+=d;
        }
        if (d==0) break;
    }
    return make_pair(_f-f,ret);
}

int n,m;
struct E_E{
    int u,v,len;
}e[maxn*200];
int ans[maxn];
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].len);
    int flow=0,s=n*2+1,t=n*2+2,S=n*2+3;
    FOR(i,1,n) addedge(s,i,1,0),addedge(i+n,t,1,0);
    FOR(i,1,n) ans[i]=INF;
    FOR(i,1,m) addedge(e[i].u,e[i].v+n,1,e[i].len);
    FOR(i,1,n){
        addedge(S,s,1,0);
        auto now=mincostflow(S,t,1);
        if (now.first)
            ans[i]=min(ans[i],now.second);
//        printf("%d:%d ",i,now.second);
    }
    FOR(i,1,n) {
        if (ans[i]==INF) printf("-1");
        else printf("%d",ans[i]);
        putchar(" \n"[i==n]);
    }
    return 0;
}
/*
*/
