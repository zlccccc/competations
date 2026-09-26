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
const LL M=998244353;
const LL maxn=200000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//分块_状态直接记录转移,比滚动要慢
int SIZE;
struct node{
    int u,v,id;
    node(){};
    node(int _u,int _v,int _id):u(_u),v(_v),id(_id){};
}to[maxn],re[maxn],queries[maxn];
int ID[maxn],BID[maxn],LE[maxn],MAXSIZE;
bool ok[maxn];
bool cmp1(node A,node B){
    if (A.u!=B.u) return A.u<B.u;
    if (A.v!=B.v) return A.v<B.v;
    return A.id<B.id;
}bool cmp2(node A,node B){
    if (A.v!=B.v) return A.v<B.v;
    if (A.u!=B.u) return A.u<B.u;
    return A.id<B.id;
}
int fa[20000007],size[20000007];LL now[1007];
LL Ans[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int FA[maxn],SZ[maxn],PID[maxn];
inline int getFA(int x){
    if (FA[x]==x) return x;
    return FA[x]=getFA(FA[x]);
}
inline int getid(int x,int y){return x*MAXSIZE+y;}
inline void update(int u,int k,int pid){
    if (PID[u]!=pid){
        int f=getfa(getid(u,k));f/=MAXSIZE;
        if (PID[f]!=pid){
            FA[f]=f;
            PID[f]=pid;
            SZ[f]=size[getid(f,k)];
        }PID[u]=pid;FA[u]=f;
    }
}
void addedge(int k,LL &now,node e,int pid=0){
    if (pid){
        update(e.u,k,pid);update(e.v,k,pid);
        int x=getFA(e.u),y=getFA(e.v);
        if (x==y) return;FA[x]=y;
        now+=2ll*SZ[x]*SZ[y];
        SZ[y]+=SZ[x];
    }else{
        int u=getid(e.u,k),v=getid(e.v,k);
        int x=getfa(u),y=getfa(v);
        if (x==y) return;fa[x]=y;
        now+=2ll*size[x]*size[y];
        size[y]+=size[x];
    }
}int tot=0;
int main(){
    int T;
//    int time0=clock();
    scanf("%d",&T);
    while (T--){
        int n,m,q,i,j,k;
        scanf("%d%d%d",&n,&m,&q);
        if (q==0) SIZE=m;else SIZE=m/sqrt(q);
        if (!SIZE) SIZE++;
        FOR(i,1,m){
            int u,v;ok[i]=0;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            to[i]=node(u,v,i);
            re[i]=node(u,v,i);
        }sort(to+1,to+m+1,cmp2);
        sort(re+1,re+m+1,cmp1);
        MAXSIZE=0;
        FOR(i,1,m){
            ID[re[i].id]=i;
            BID[i]=i/SIZE;
            MAXSIZE=max(MAXSIZE,BID[i]);
            if (LE[BID[i]]==0||LE[BID[i]]>re[i].u)
                LE[BID[i]]=re[i].u;
        }MAXSIZE++;LE[MAXSIZE]=n;
        FOR(k,0,MAXSIZE) now[k]=0;
        FOR(i,1,(n+1)*MAXSIZE){
            size[i]=1;
            fa[i]=i;
        }
        FOR(i,1,q){
            int u,v;
            scanf("%d%d",&u,&v);
            if (u>v) swap(u,v);
            queries[i]=node(u,v,i);
        }sort(queries+1,queries+q+1,cmp2);
        j=1;
        FOR(i,1,q){
            for (;j<=m&&to[j].v<=queries[i].v;j++){
                FOR(k,0,BID[ID[to[j].id]]-1)
                    addedge(k,now[k],to[j]);
                ok[ID[to[j].id]]=1;
//                printf("OK : %d\n",ID[to[j].id]);
            }
            for (k=MAXSIZE;k&&LE[k]>=queries[i].u;k--);
            int id=k;k++;k*=SIZE;k--;k=min(k,m);
            LL ans=now[id];tot++;
            for (;k&&re[k].u>=queries[i].u;k--) if (ok[k])
                addedge(id,ans,re[k],tot);
            Ans[queries[i].id]=ans/2;
        }
        FOR(i,1,q) printf("%lld\n",Ans[i]);
    }
//    printf("%d\n",clock()-time0);
}
/*
*/
