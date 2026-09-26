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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll* a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int n,m,k;
int i,j;
priority_queue<int> remain,could;//remain:max; could:min
vector<pair<int,int> > edges;
int D[maxn];
int ans[maxn],top;
vector<int> edge[maxn];
void addnode(int x){
    ans[++top]=x;
    for (int v:edge[x]){
        D[v]--;
        if (!D[v]) could.push(-v);
    }
}
int main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        D[v]++;
    }
    FOR(i,1,n) if (!D[i]) could.push(-i);
    while (could.size()||remain.size()){
        if (!could.size()){
            int noww=remain.top();
            remain.pop();
            edges.push_back(make_pair(ans[top],noww));
            addnode(noww);
//            printf("add_remain %d\n",noww);
            continue;
        }
        if (!k||(could.size()==1&&(!remain.size()||-could.top()>remain.top()))){
            int now=-could.top();
            could.pop();
            addnode(now);
//            printf("add_now %d\n",now);
            continue;
        }
        {//first
//            printf("could -> remain  %d;\n",-could.top());
            remain.push(-could.top());
            could.pop();k--;
            continue;
        }
    }
    FOR(i,1,n) printf("%d ",ans[i]);puts("");
    printf("%d\n",edges.size());
    for (auto now:edges) printf("%d %d\n",now.first,now.second);
}
/*
4 2 3
4 1
1 2

5 3 2
1 4
4 2
1 3

5 3 3
1 4
4 2
1 3
*/
