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
#include <bitset>
#include <utility>
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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//TMD为啥W能是负数啊...
struct segtree{
    int A[maxn*4];
    void update(int x,int l,int r,int val,int L,int R){
        if (l<=L&&R<=r) {A[x]=max(A[x],val);return;}
        int mid=(L+R)/2;
        if (l<=mid) update(x<<1,l,r,val,L,mid);
        if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    }int query(int x,int pos,int L,int R){
        if (L==R) return A[x];
        int mid=(L+R)/2;
        if (pos<=mid) return max(A[x],query(x<<1,pos,L,mid));
        else return max(A[x],query(x<<1|1,pos,mid+1,R));
    }
}in,out;
struct node{
    int to,len,next;
    node(){};
    node(int _to,int _len,int _next):to(_to),len(_len),next(_next){};
}edge[maxn*2];
int head[maxn],etot;
void addedge(int u,int v,int len){
    edge[++etot]=node(v,len,head[u]);head[u]=etot;
}//dfs
int sz[maxn],fa[maxn],son[maxn],top[maxn],id[maxn],dep[maxn],len[maxn];
int tot,eid[maxn];
void dfs1(int u,int from,int depth,int length){
    int v,i,mx=-1;
    sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;len[u]=length;
    for (i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if (v==from) continue;
        eid[(i+1)/2]=v;
        dfs1(v,u,depth+1,length+edge[i].len);
        sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}void dfs2(int u,int x){
    int v,i;
    top[u]=x;id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if (v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}typedef pair<int,int> pii;
vector<pii> should;
int getInside(int x,int y){
    int ret=len[x]+len[y];
    while (top[x]!=top[y]){
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        should.push_back(make_pair(id[top[x]],id[x]));
        x=fa[top[x]];
    }if (dep[x]>dep[y]) swap(x,y);
    if (x!=y&&son[x]) should.push_back(make_pair(id[son[x]],id[y]));
    ret-=len[x]*2;
    return ret;
}int n;
int update(int x,int y){
    should.clear();
    int length=getInside(x,y);
    sort(should.begin(),should.end());
//    printf("UPD:%d %d; length=%d\n",x,y,length);
//    for (auto now:should) printf("%d-%d ",now.first,now.second);puts("");
    int nowpos=1;
    for (auto now:should){
        if (nowpos<=now.first-1){
            out.update(1,nowpos,now.first-1,length,1,n);
//            printf("update out: %d %d (%d)\n",nowpos,now.first-1,length);
        }
        in.update(1,now.first,now.second,length,1,n);
//        printf("update in: %d %d (%d)\n",now.first,now.second,length);
        nowpos=now.second+1;
    }if (nowpos<=n) {
        out.update(1,nowpos,n,length,1,n);
//        printf("update out: %d %d (%d)\n",nowpos,n,length);
    }
    return length;
}
int q;
int i,j,k;
int main(){
    while (~scanf("%d%d",&n,&q)){
        tot=etot=0;
        FOR(i,1,n) head[i]=-1;
        FOR(i,1,4*n) in.A[i]=out.A[i]=-INF;
        REP(i,n-1){
            int u,v,l;
            scanf("%d%d%d",&u,&v,&l);
            addedge(u,v,l);
            addedge(v,u,l);
        }dfs1(1,0,0,0);dfs2(1,1);
//        FOR(i,1,n) printf("%2d ",i);puts("  <- i");
//        FOR(i,1,n) printf("%2d ",fa[i]);puts("  <- fa");
//        FOR(i,1,n) printf("%2d ",top[i]);puts("  <- top");
//        FOR(i,1,n) printf("%2d ",id[i]);puts("  <- id");
//        FOR(i,1,n) printf("%2d ",dep[i]);puts("  <- dep");
//        FOR(i,1,n) printf("%2d ",len[i]);puts("  <- len");
        while (q--){
            int op,x,y;
            scanf("%d%d%d",&op,&x,&y);
            if (op==1){
                if (x==y) continue;
                int ans=update(x,y);//MDZZ
                printf("%d\n",ans);
            }else{
                int ans=max(in.query(1,id[eid[x]],1,n)+y-edge[x*2].len,out.query(1,id[eid[x]],1,n));
                ans=max(ans,0);
                printf("%d\n",ans);
            }
        }
    }
}
/*
*/
