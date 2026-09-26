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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//无解的条件:完全图
typedef pair<int,int> pii;
int n,m;
set<int> edge[maxn];
void upd(vector<int> &A,vector<int> &B){
    if (!A.size()||A.size()>B.size()) A.swap(B);
}
vector<int> ans;
queue<int> Q;
int vis[maxn];
void bfs(){
    Q.push(1);
    while (Q.size()){
        int x=Q.front();Q.pop();
        for (int v:edge[x]) if (!vis[v]&&v!=1){
            vis[v]=x; Q.push(v);
        }
    }if (vis[n])
        for (int now=n;now;now=vis[now])
            ans.push_back(now);
    reverse(ans.begin(),ans.end());
}
void check4(){
    vector<int> now;
    for(int x:edge[1]){
        for (int u:edge[x]) if (u!=1&&!edge[u].count(1)){
            now=vector<int>{1,x,u,1,n};
            upd(ans,now);
            return;
        }
    }
}
bool visited[maxn];
int y_y;
void dfs(int x){
    visited[x]=1;
    if (edge[x].size()<edge[y_y].size()) y_y=x;
    for (int v:edge[x]){
        if (!visited[v]) dfs(v);
    }
}
void check5(){
    int i;//1->min_d
    vector<int> now;
    vector<int> ini;
    for (int v:edge[1]) ini.push_back(v);
    FOR(i,2,n) {
        if (edge[1].count(i)){
            edge[1].erase(i);
            edge[i].erase(1);
        }else{
            edge[1].insert(i);
            edge[i].insert(1);
        }
    }
    for (int y:ini) if (!visited[y]){
//        printf("y=%d\n",y);
        y_y=y;dfs(y);y=y_y;
        for (int x:edge[y]){
            for (int u:edge[x]) if (u!=y&&!edge[u].count(y)){
                now=vector<int>{1,y,x,u,y,n};
                upd(ans,now);
                return;
            }
        }
    }
}
int main() {
    int i;
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].insert(v);
        edge[v].insert(u);
    }bfs();check4();check5();
    if (!ans.size()) return 0*puts("-1");
    printf("%d\n",ans.size()-1);
    for (int v:ans) printf("%d ",v);
    return 0;
}
/*
6 9
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
*/
