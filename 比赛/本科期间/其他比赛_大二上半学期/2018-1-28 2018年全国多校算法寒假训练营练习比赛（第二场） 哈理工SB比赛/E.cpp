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

int n,m,i;
vector<int> edge[maxn];
int minweight=INF,id;
int SIZE[maxn];
void dfs(int x,int fa,int n){
    SIZE[x]++;int weight=0;
    for (int v:edge[x]) if (v!=fa){
        dfs(v,x,n);
        SIZE[x]+=SIZE[v];
        weight=max(weight,SIZE[v]);
    }weight=max(weight,n-SIZE[x]);
    if (weight<minweight) minweight=weight,id=x;
    else if (weight==minweight)id=min(id,x);
}
int main(){
    scanf("%d",&n);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }dfs(1,0,n);
    printf("%d %d\n",id,minweight);
}
/*
*/
