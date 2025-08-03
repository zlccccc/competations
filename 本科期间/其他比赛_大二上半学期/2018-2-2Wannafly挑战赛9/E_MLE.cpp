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
const LL M1=998244353;
const LL M2=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const int len=20;
int n,m,i,j,k;
struct node{
    int n,d,next;
    node(){}
    node(int _n,int _d,int _next):n(_n),d(_d),next(_next){}
}edge[maxn*len*4];
int head[maxn*len],cnt;
inline void addedge(int u,int v,int len){
//    printf("addedge : %2d->%2d %3d\n",u,v,len);
    edge[cnt]=node(v,len,head[u]);
    head[u]=cnt++;
};
int dis[maxn*len];
bool vis[maxn*len];
void spfa(int s,int n){
    int i;
    FOR(i,0,n) dis[i]=INF;
    FOR(i,0,n) vis[i]=0;
    dis[s]=0;
    deque<int> Q;//slf need
    Q.push_back(s);
    while (!Q.empty()){
        int u=Q.front();Q.pop_front();
        vis[u]=0;//not lll
        for(i=head[u];i!=-1;i=edge[i].next){
            node &v=edge[i];
            if (dis[u]+v.d<dis[v.n]){
                dis[v.n]=dis[u]+v.d;
                if (!vis[v.n]){
                    vis[v.n]=1;
                    if (Q.empty()||dis[Q.front()]<dis[v.n]) Q.push_back(v.n);//slf
                    else Q.push_front(v.n);//slf
                }
            }
        }
//        FOR(i,0,n) printf("%d ",dis[i]);puts(" <-  dis");
    }
}
inline int getid(int x,int y){
    return x*len+y;
}
int main(){
    scanf("%d%d",&n,&m);
    int s,t;int all=(n+1)*len+2;
    FOR(i,1,all) head[i]=-1;
    s=(n+1)*len;t=(n+1)*len+1;
    REP(j,len) addedge(s,getid(0,j),0);
    FOR(i,1,n){
        REP(j,len){
            addedge(getid(i,j),getid(i-1,j),0);
            addedge(getid(i-1,j),getid(i,j),1);
        }
    }
    FOR(j,1,m){
        int op,l,r,x;
        scanf("%d%d%d%d",&op,&l,&r,&x);
        if (op==1){
            REP(i,len){
                if ((x>>i)&1) addedge(getid(r,i),getid(l-1,i),-1);
                else addedge(getid(l-1,i),getid(r,i),0);
            }
        }else{
            REP(i,len){
                if ((x>>i)&1) addedge(getid(r,i),getid(l-1,i),-(r-l+1));
                else addedge(getid(l-1,i),getid(r,i),r-l);
            }
        }
    }spfa(s,all);
//    FOR(i,1,n){
//        REP(j,len){
//            printf("%d",dis[getid(i,j)]-dis[getid(i-1,j)]);
//        }puts("");
//    }
    FOR(i,1,n){
        int now=0;
        REP(j,len) now|=(dis[getid(i,j)]-dis[getid(i-1,j)])<<j;
        printf("%d ",now);
    }
}
/*
2 3 5 8 13 6
1 1 2 3 4 5
*/
