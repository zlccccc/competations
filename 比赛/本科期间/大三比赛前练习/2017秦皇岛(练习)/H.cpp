#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
const int maxn=3000+7;
const int maxm=4e6+7;
char str[maxn];
namespace maxflow{
    typedef int type;
    const type INF=0x3f3f3f3f;
    struct node{
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n){}
    }edge[maxm*2];
    int head[maxn],tot;
    void addedge(int from,int to,type cap=0,type rcap=0){
       // printf("%d->%d :%d\n",from,to,cap);
        edge[tot]=node(to,cap,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
    }
    int dep[maxn],cur[maxn];
    bool bfs(int s,int t,int n){
       // printf("s=%d t=%d n=%d\n",s,t,n);
        static int Q[maxn],ST,ED;
        memset(dep+1,0,n*sizeof(int));
        ST=0; ED=-1;
        Q[++ED]=s; dep[s]=1;
        while (ST<=ED){
            int u=Q[ST++];
            for (int i=head[u];~i;i=edge[i].next){
                int v=edge[i].to;
                if (!dep[v]&&edge[i].cap){
                    Q[++ED]=v; dep[v]=dep[u]+1;
                }
            }
        }return dep[t]!=0;
    }
    type dfs(int x,const int &t,type flow=INF){
        if (x==t||flow==0) return flow;
        type ret=0;
        for (int i=cur[x];i!=-1;i=edge[i].next){
            if (dep[x]+1==dep[edge[i].to]&&edge[i].cap){
                type f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                //printf(" dfs: %d->%d %d cap=%d\n",x,edge[i].to,f,edge[i].cap);
                edge[i].cap-=f; edge[i^1].cap+=f;
                ret+=f; flow-=f; cur[x]=i;
                if (!flow) break;
            }
        } if (!ret) dep[x]=0;
        return ret;
    }
    type maxflow(int s,int t,int n){
        type ret=0;
        while (bfs(s,t,n)){
            type f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while ((f=dfs(s,t))>0) ret+=f;
//            printf("  ret=%d %d %d dep=%d\n",ret,s,t,dep[t]);
        } return ret;
    }
    void init(int n){
        memset(head+1,0xff,n*sizeof(int)); tot=0;
    }
}
const int MAX=2e6+7;
bool no[MAX];
int A[maxn];
int main(){
    int t,i,j;
    scanf("%d",&t);
    FOR(i,2,2000000) if (!no[i]){
        for (j=i+i;j<=2000000;j+=i) no[j]=1;
    }
    while(t--){
        int n,k;
        scanf("%d%d",&n,&k);
        FOR(i,1,n) scanf("%d",&A[i]);
        maxflow::init(n+3);
        int s=n+2,t=n+3,pos_1=n+1;
        int cnt_1=0,all=0;
        FOR(i,1,n){
            if (A[i]==1) cnt_1++;
            else if (A[i]&1) {
                maxflow::addedge(s,i,1);
                FOR(j,1,n) if (i!=j&&!no[A[i]+A[j]]) {
                    //printf("%d-%d\n",i,j);
                    maxflow::addedge(i,j,1);
                }
            } else maxflow::addedge(i,t,1);
        }
        FOR(i,1,n) {
            bool mask=0;
            FOR(j,1,n) if (i!=j&&!no[A[i]+A[j]]) mask=1;
            all+=mask;
        }
        int mflow=maxflow::maxflow(s,t,n+3);
        FOR(i,1,n) if (A[i]!=1&&!no[A[i]+1]) maxflow::addedge(pos_1,i,n);
        //printf("init? all=%d mflow=%d cnt1=%d  %d-%d\n",all,mflow,cnt_1,s,t);
        maxflow::addedge(s,pos_1,cnt_1);
        int f=maxflow::maxflow(s,t,n+3);
        mflow+=f; cnt_1-=f;
//        while (cnt_1) {
//            maxflow::addedge(s,pos_1,1);
//            int f=maxflow::maxflow(s,t,n+3);
//            mflow+=f;//f: more
//            if (!f) break;
//            cnt_1--;
//        }
        mflow+=cnt_1/2;
        //printf("okay? all=%d mflow=%d(done) cnt1=%d  %d-%d\n",all,mflow,cnt_1,s,t);
        mflow=min(mflow,k);//cnt
        int ans=mflow*2+min(all-mflow*2,k-mflow);
        printf("%d\n",ans);
    }
}
/*
4
4 2
2 3 4 5
5 3
3 4 12 3 6
6 3
1 3 6 8 1 1
1 0
1
*/
