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
const LL maxn=250000+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

bool flag;//could
int S[maxn];
priority_queue<int> Q;
vector<pair<int,int> > edge[maxn];
int size[maxn],root,minw;
void dfs1(int u,int from,int n){
    int i,v,weight=0;
    size[u]=1;
    REP(i,edge[u].size()){
        v=edge[u][i].first;
        if (v==from||mark[v]) continue;
        dfs1(v,u,n);
        size[u]+=size[v];
        weight=max(weight,size[v]);
    }weight=max(weight,n-size[u]);
    if (weight<minw) {root=u;minw=weight;}
}vector<int> length[maxn][2];
int nowroot,seg;
void dfs2(int u,int from,int depth){
    int i,v;
    size[u]=1;
    length[v].push_back(depth);
    REP(i,edge[u].size()){
        v=edge[u][i].first;
        if (v==from||mark[v]) continue;
        dfs2(v,u,depth+edge[u][i].second);
        size[u]+=size[v];
    }
}int calc(int root,int len){
    length[root].clear();
    nowroot=root;
    dfs2(root,0,len);
    sort(length[root][seg].begin(),length[root][seg].end());
}int ans;
void dfs3(int u){
    int i,v,l,r;
    seg=1;ans+=calc(u,0);seg=2;
    mark[u]=1;
    REP(i,edge[u].size()){
        v=edge[u][i].first;
        if (mark[v]) continue;
        ans-=calc(v,edge[u][i].second);
        minw=size[v];//зЂвт
        dfs1(v,0,size[v]);
        dfs3(root);
    }
}LL Solve(int mid){
    LL ret=0;
    FOR(i,1,n){
        int l,r;
        for (l=0,r=length[i][0].size()-1;l<r;){
            if (length[i][0][l]+length[i][0][r]<=k) ret+=r-l,l++;
            else r--;
        }
        for (l=0,r=length[i][1].size()-1;l<r;){
            if (length[i][1][l]+length[i][1][r]<=k) ret+=l-r,l++;
            else r--;
        }
    }return ret;
}vector<int> Ans;
LL solve(int k){
    dfs1(1,0,n);
    l=0;r=1e11;
    while (l+1<r){
        int mid=(l+r)/2;
        if (Solve(mid)>=k) l=mid;
        else r=mid;
    }
}
int main(){
    scanf("%d%d")
}
/*
*/
