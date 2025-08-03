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

int n,m,k;
vector<pair<int,LL> > edge[maxn];
vector<LL> have[maxn],V;
priority_queue<LL,vector<LL>,greater<LL> > Q;
void dfs(int x,int fa){
    have[x].push_back(0);
    for (auto now:edge[x]){
        int v=now.first;
        if (v==fa) continue;
        dfs(v,x);
        int i,j,jj;
        for (LL len:have[x]){
            j=0;
            while (j<have[v].size()){
                LL L=len+now.second+have[v][j];
                if (Q.size()<k){
                    Q.push(L);j++;
                }else if (Q.top()<L){
                    Q.pop();
                    Q.push(L);j++;
                }else break;
            }
        }i=0;j=0;jj=0;
        V.clear();
        V.swap(have[x]);
        REP(i,k){
            if (j==V.size()&&jj==have[v].size()) break;
            if (j==V.size()||jj!=have[v].size()&&V[j]<have[v][jj]+now.second) have[x].push_back(have[v][jj]+now.second),jj++;
            else have[x].push_back(V[j]),j++;
        }
    }
//    printf("%d: ",x);
//    for (LL v:have[x]) printf("%d ",v);puts("");
}vector<LL> ans;
int main(){
    scanf("%d%d",&n,&k);
    int i;
    REP(i,n-1){
        int u,v;LL len;
        scanf("%d%d%lld",&u,&v,&len);u++;v++;
        edge[u].push_back(make_pair(v,len));
        edge[v].push_back(make_pair(u,len));
    }dfs(1,0);
    while (Q.size())
        ans.push_back(Q.top()),Q.pop();
    rREP(i,ans.size()) printf("%lld\n",ans[i]);
}
/*
*/
