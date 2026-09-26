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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//卡常太严重,加了各种挂过去的
char buffer[12000000],write[7000000],*buf=buffer,*ed=write;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
int pp[20];
void print(LL x){
    if (!x) *ed++='0';
    else {
        int now=0,i;
        while (x) pp[now++]=x%10,x/=10;
        while (now) *ed++=pp[--now]+48;
    }*ed++='\n';
}
int in[maxn],out[maxn];
vector<int> edge[maxn];
int fa[maxn][20],tot;
int dep[maxn];
void dfs(int x,int f,int d){
    int i;
    fa[x][0]=f;in[x]=++tot;dep[x]=d;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]) if (v!=f) dfs(v,x,d+1);
    out[x]=tot;
}
int lca(int x,int y){
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int getnthfa(int x,int k){
    int i;
    rREP(i,20) if ((k>>i)&1) x=fa[x][i];
    return x;
}
struct query{
    int l,r,id,seg;
    query(){};
    query(int _l,int _r,int _id,int _seg):l(_l),r(_r),id(_id),seg(_seg){};
}Q[maxn*9*5],F[maxn*9*5];
int CNT1[maxn],CNT2[maxn];
int cnt;
int SIZE;
int n,m,i,j;
inline void addquery(int l,int r,int id,int seg){
    if (l==0||r==0) return;
//    printf("ADD: %d %d,id=%d, seg=%d\n",l,r,id,seg);
    Q[cnt++]=query(l,r,id,seg);
}
inline void addquery(int l,int r,int L,int R,int id){
//    printf("addquery: %d-%d; %d-%d; %d\n",l,r,L,R,id);
    if (l>r||L>R) return;
    addquery(r,R,id,1);
    addquery(l-1,R,id,-1);
    addquery(r,L-1,id,-1);
    addquery(l-1,L-1,id,1);
}
int a[maxn],b[maxn];
struct node{int A,B;} P[maxn],*p[maxn],**L,**R;
LL ans[maxn*5],now;
int root;
int main(){
    int time0=clock();int time1=time0;
    fread(buffer,1,12000000,stdin);
    read(n);read(m);
    FOR(i,1,n) read(a[i]),b[i-1]=a[i];
    sort(b,b+n);//t=unique(b,b+n)-b;
    FOR(i,1,n) a[i]=lower_bound(b,b+n,a[i])-b;
//    printf("lower-bound: %d\n",clock()-time0);time0=clock();
    FOR(i,1,n-1){
        int u,v;
        read(u);read(v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
//    printf("read: %d\n",clock()-time0);time0=clock();
    dfs(1,0,1);root=1;
    FOR(i,1,m){
        int op;
        read(op);
        if (op==1) read(root),ans[i]=-1;
        else {
            int x,y;
            read(x);read(y);
            if (x==root&&y==root){
                addquery(n,n,i,1);
            }else if (x==root||y==root){
                if (y==root) swap(x,y);
                if (in[y]<=in[root]&&in[root]<=out[y]){
                    int v=getnthfa(root,dep[root]-dep[y]-1);
                    addquery(1,n,1,in[v]-1,i);
                    addquery(1,n,out[v]+1,n,i);
                }else{
                    addquery(1,n,in[y],out[y],i);
                }
            }else{
                if (in[x]<=in[root]&&in[root]<=out[x]){
                    int u=getnthfa(root,dep[root]-dep[x]-1);
                    if (in[y]<=in[root]&&in[root]<=out[y]){
                        int v=getnthfa(root,dep[root]-dep[y]-1);
                        addquery(1,in[u]-1,1,in[v]-1,i);
                        addquery(out[u]+1,n,1,in[v]-1,i);
                        addquery(1,in[u]-1,out[v]+1,n,i);
                        addquery(out[u]+1,n,out[v]+1,n,i);
                    }else{
                        addquery(1,in[u]-1,in[y],out[y],i);
                        addquery(out[u]+1,n,in[y],out[y],i);
                    }
                }else{
                    if (in[y]<=in[root]&&in[root]<=out[y]){
                        int v=getnthfa(root,dep[root]-dep[y]-1);
                        addquery(in[x],out[x],1,in[v]-1,i);
                        addquery(in[x],out[x],out[v]+1,n,i);
                    }else{
                        addquery(in[x],out[x],in[y],out[y],i);
                    }
                }
            }
        }
    }
    SIZE=n/sqrt(cnt)*5;if (!SIZE) SIZE=1;
//    printf("SIZE=%d %d\n",SIZE,cnt);
//    printf("add-query-time:%d\n",clock()-time0);time0=clock();
    REP(i,cnt) CNT1[Q[i].r/SIZE]++,CNT2[Q[i].l]++;
    FOR(i,1,n) CNT1[i]+=CNT1[i-1],CNT2[i]+=CNT2[i-1];
    REP(i,cnt) F[--CNT2[Q[i].l]]=Q[i];
    REP(i,cnt) Q[--CNT1[F[i].r/SIZE]]=F[i];
    FOR(i,1,n) p[in[i]]=&P[a[i]];
//    printf("sort-time : %d\n",clock()-time0);time0=clock();
    L=R=p;
    REP(i,cnt){
        auto x=Q[i];node **l=x.l+p,**r=x.r+p;
        while (L<l){L++;node *T=*L;now+=T->B;T->A++;}
        while (R<r){R++;node *T=*R;now+=T->A;T->B++;}
        while (L>l){node *T=*L;now-=T->B;T->A--;L--;}
        while (R>r){node *T=*R;now-=T->A;T->B--;R--;}
//        printf("Q: %d~%d, id=%d, now=%lld; seg=%d\n",L,R,x.id,now,x.seg);
        ans[x.id]+=now*x.seg;
//        if (x.seg>0) ans[x.id]+=now;else ans[x.id]-=now;
    }
    printf("block-time : %d\n",clock()-time0);time0=clock();
    FOR(i,1,m) if (~ans[i]) print(ans[i]);
    fwrite(write,1,ed-write,stdout);
    printf("printf time : %d\n",clock()-time1);
    return 0;
}
/*
5 5
1 2 3 4 5
1 2
1 3
3 4
3 5
2 4 5
2 1 5
2 3 5
1 5
2 4 5
*/
