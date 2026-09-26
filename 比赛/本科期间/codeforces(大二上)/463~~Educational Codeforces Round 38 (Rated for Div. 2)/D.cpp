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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//woc板子错了
struct node{
    int n;LL d;
    node(){}
    node(int _n,LL _d):n(_n),d(_d){};
    const bool operator <(const node &A)const {
        if (d!=A.d) return d>A.d;//注意!!! 否则为未优化的bellmanford
        return n>A.n;
    }
};
vector<node> edge[maxn];
priority_queue<node> Q;
LL dis[maxn];
int n,m;
void dij(int s,int n){
    int i;
    FOR(i,1,n) dis[i]=INFF;
    dis[s]=0;
    Q.push(node(s,0));
    while (Q.size()){
        node x=Q.top();Q.pop();
        if (dis[x.n]!=x.d) continue;
        for (node y:edge[x.n]){
            if (dis[y.n]>x.d+y.d){
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
}
int i,j,k;
int main(){
    scanf("%d%d",&n,&m);
    int s=n+1;
    while (m--){
        int u,v;LL w;
        scanf("%d%d%I64d",&u,&v,&w);
        edge[u].push_back(node(v,w*2));
        edge[v].push_back(node(u,w*2));
    }FOR(i,1,n){
        LL a;
        scanf("%I64d",&a);
        edge[s].push_back(node(i,a));
    }dij(s,n+1);
    FOR(i,1,n) printf("%I64d ",dis[i]);
}
/*
4 2
1 2 4
2 3 7
6 20 1 25
*/
