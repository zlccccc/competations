#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=20007;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a*=a) ret=1ll*ret*a%M; return ret;}


namespace maxflow {
    typedef int type;
    const type INF=0x3f3f3f3f;
    struct node {
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
    } edge[maxn*50];
    int head[maxn],tot;
    void addedge(int from,int to,type cap,type rcap=0) {
        edge[tot]=node(to,cap,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
    }
    int dep[maxn],cur[maxn];//当前弧优化
    bool bfs(int s,int t,int n) {
        static int Q[maxn],ST,ED;
        memset(dep+1,0,n*sizeof(int));
        ST=0; ED=-1;
        Q[++ED]=s; dep[s]=1;
        while (ST<=ED) {
            int u=Q[ST++];
            for (int i=head[u]; i!=-1; i=edge[i].next) {
                int v=edge[i].to;
                if (!dep[v]&&edge[i].cap) {
                    Q[++ED]=v; dep[v]=dep[u]+1;
                }
            }
        } return (dep[t]!=0);
    }
    type dfs(int x,const int &t,type flow=INF) {
        if (x==t||flow==0) return flow;
        type ret=0;
        for (int i=cur[x]; i!=-1; i=edge[i].next) {
            if (dep[x]+1==dep[edge[i].to]&&edge[i].cap){
                type f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                edge[i].cap-=f; edge[i^1].cap+=f;
                ret+=f; flow-=f; cur[x]=i;
                if (flow==0) break;
            }
        } if (!ret) dep[x]=0;
        return ret;
    }
    type maxflow(int s,int t,int n) {
        type ret=0;
        while (bfs(s,t,n)) {
            type f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while ((f=dfs(s,t))>0) ret+=f;
        } return ret;
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int)); tot=0;
    }
}

struct node{
	int u,v,len;
}e[maxn];
int main() {
	int n,m;
	while (~scanf("%d%d",&n,&m)) {
		int ans=INF; int i,j,o;
		FOR(i,1,m) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].len);
		FOR(i,2,4) FOR(j,i+1,4) {
			int x,y;
			FOR(x,2,n-1) FOR(y,x+1,n-1) {
				maxflow::init(n);
				maxflow::addedge(1,i,INF);
				maxflow::addedge(1,j,INF);
				maxflow::addedge(x,n,INF);
				maxflow::addedge(y,n,INF);
				FOR(o,1,m) {
					maxflow::addedge(e[o].u,e[o].v,e[o].len);
				}
				int now=maxflow::maxflow(1,n,n);
				ans=min(ans,now);
				// printf("%d %d %d %d: %d\n",i,j,x,y,now);
			}
		}
		FOR(i,2,4) FOR(j,i+1,4) {
			int x,y;
			FOR(x,2,n-1) FOR(y,x+1,n-1) {
				maxflow::init(n);
				maxflow::addedge(1,x,INF);
				maxflow::addedge(1,y,INF);
				maxflow::addedge(i,n,INF);
				maxflow::addedge(j,n,INF);
				FOR(o,1,m) {
					maxflow::addedge(e[o].u,e[o].v,e[o].len);
				}
				int now=maxflow::maxflow(1,n,n);
				ans=min(ans,now);
				// printf("%d %d %d %d: %d\n",i,j,x,y,now);
			}
		}
		printf("%d\n",ans);
	}
}
