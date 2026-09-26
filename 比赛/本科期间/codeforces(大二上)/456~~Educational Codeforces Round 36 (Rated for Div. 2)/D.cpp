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
#include <bitset>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,int> pii;
vector<int> edge[maxn];
int n,m,q;
int i,j,k,t;
pii S[maxn];int top;
int mark[maxn],instack[maxn],flag;
int U,V;
void dfs(int x,int id){
//    printf("%d ",x);
    if (mark[x]==id&&instack[x]) flag=1;
    if (flag||mark[x]) return;
    mark[x]=id;instack[x]=1;
    for (int v:edge[x]){
        if (U==x&&V==v) continue;
        if (id<=n) S[top++]=make_pair(x,v);
        dfs(v,id);if (flag) return;
        if (id<=n) top--;
    }instack[x]=0;
}
int id;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
    }FOR(i,1,n) if (!flag&&!mark[i]) dfs(i,i);
    id=n+1;
    if (!flag) return 0*puts("YES");
    while(top--){
//        printf("%d %d\n",S[top].first,S[top].second);
        U=S[top].first;V=S[top].second;
        flag=0;FOR(i,1,n) mark[i]=0;
        FOR(i,1,n) if (!flag&&!mark[i]) dfs(i,id++);
        if (!flag) return 0*puts("YES");
    }puts("NO");
}
/*
*/
