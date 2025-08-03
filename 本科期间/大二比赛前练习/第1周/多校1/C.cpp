#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const double eps=0.0000001;
const LL gcd(LL a,LL b){return b?gcd(b,a%b):a;};
using namespace std;
int n;
vector<int> edge[maxn];
LL subnum[maxn];
LL delnum[maxn];
void dfs1(int u,int fa){
    subnum[u]=1;
    for (int v:edge[u]) if (v!=fa){
        dfs1(v,u);
        subnum[u]+=subnum[v];
    }
//    printf("subnum %d -> %d\n",u,subnum[u]);
}
LL allnum[maxn];
int color[maxn];
LL dfs2(int u,int fa){//up
    LL ret=0;
    LL oriDnum=delnum[color[u]];
    LL subOKnum=0;
    for (int v:edge[u]) if (v!=fa){
        LL num1=delnum[color[u]];
        ret+=dfs2(v,u);
        LL num2=delnum[color[u]];
        ret+=(subnum[v]-(num2-num1))*(subOKnum+1);
        subOKnum+=subnum[v]-(num2-num1);
    }
//    printf("%d %d-->ret1=%d\n",u,fa,ret);
    LL remain=subnum[u]-(delnum[color[u]]-oriDnum);//²îÖµ Ê£ÏÂµÄ 
    delnum[color[u]]=oriDnum+subnum[u];//DEL
    ret+=(remain)*(allnum[color[u]]-remain);//up
    allnum[color[u]]-=remain;
//    printf("%d %d-->ret2=%d,,remain=%d\n",u,fa,ret,remain);
    return ret;
}
LL solve(int n){
    int i;
    FOR(i,1,n) scanf("%d",&color[i]);
    FOR(i,1,n) edge[i].clear();
    REP(i,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    memset(subnum,0,sizeof(subnum));
    dfs1(1,0);
    FOR(i,1,n) allnum[i]=n;
    memset(delnum,0,sizeof(delnum));//color
    LL ret=dfs2(1,0);
    return ret;
}
int main(){
    int x=0;
    while (~scanf("%d",&n)){
        printf("Case #%d: %lld\n",++x,solve(n));
    }
}
/*
*/
