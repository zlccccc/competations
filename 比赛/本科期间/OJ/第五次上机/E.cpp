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
const LL maxn=2007+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
int T,n,m; 
int a[maxn],p[maxn],h[maxn];
LL ans;
vector<int> edge[maxn];
bool used[maxn];
int matching[maxn];
bool dfs(int u){
    int v,i;
    REP(i,edge[u].size()){
        v=edge[u][i];
        if (!used[v]){
            used[v]=1;
            if (matching[v]==-1||dfs(matching[v])){
                matching[v]=u;
                matching[u]=v;
                return 1;
            }
        }
    }
    return 0;
}
int DFS(){
    int ans=0;
    int i,u;
    FOR(i,1,n*2) matching[i]=-1;
    FOR(u,1,n){
        if (matching[u]==-1){
        	FOR(i,1,n*2) used[i]=0;
            if (dfs(u)) ans++;
        }
    }
    return ans;
}
int A[maxn],L[maxn],P[maxn];
int _A[maxn],_L[maxn];
int main(){
    while (~scanf("%d",&n)){
        int i,j;
        FOR(i,1,n*2) edge[i].clear();
        FOR(i,1,n) scanf("%d%d%d",&A[i],&L[i],&P[i]);
        FOR(i,1,n) scanf("%d%d",&_A[i],&_L[i]);
        FOR(i,1,n){
            FOR(j,1,n){
                if ((A[i]>=_L[j]||P[i]==2||P[i]==3)
                   &&(_A[j]<L[i]||P[i]==1||P[i]==3)){
                        edge[i].push_back(j+n);
                        edge[j+n].push_back(i);
                }
            }
        }if (DFS()!=n) puts("NO");
        else puts("YES");
    }
}
