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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
    int n,d,gcd;
    node(){};
    node(int _n,int _d,int _gcd):n( _n),d(_d),gcd(_gcd){};
    const bool operator <(const node &A)const{
        if (d!=A.d) return d>A.d;
        return gcd>A.gcd;
    }
};
priority_queue<node> Q;
int T;
int n,m;
int GCD[507][507];
int dis[1007][507];//pos;gcd
vector<node> edge[1007];
void dij(int s){
    int i,j,k;
    FOR(i,1,n) FOR(j,0,500) dis[i][j]=INF*2;
    FOR(j,1,500) dis[s][j]=0,Q.push(node(s,0,j));
    while (Q.size()){
        node x=Q.top();Q.pop();
        if (dis[x.n][x.gcd]!=x.d) continue;
        for (node &y:edge[x.n]) if (y.d%x.gcd==0){
            for (k=x.gcd;k<=500;k+=x.gcd){
                if (dis[y.n][k]>x.d+y.d/x.gcd){
                    dis[y.n][k]=x.d+y.d/x.gcd;
                    Q.push(node(y.n,dis[y.n][k],k));
                }
            }
        }
    }FOR(i,1,n) FOR(j,1,500) dis[i][0]=min(dis[i][0],dis[i][j]);
}
int main(){
    int i,j;
    FOR(i,1,500) FOR(j,1,500) GCD[i][j]=gcd(i,j);
    while (~scanf("%d%d",&n,&m)){
        FOR(i,1,n) edge[i].clear();
        FOR(i,1,m){
            int u,v,d;
            scanf("%d%d%d",&u,&v,&d);
            edge[u].push_back(node(v,d,d));
            edge[v].push_back(node(u,d,d));
        }dij(n);
//        FOR(i,0,10){
//            printf("(i)%-6d:  ",i);
//            FOR(j,1,n) printf("%-10d ",dis[j][i]);puts("");
//        }
        int p,q;
        scanf("%d",&q);
        while (q--){
            scanf("%d",&p);
            printf("%d\n",dis[p][0]);
        }
    }
}
/*
*/
