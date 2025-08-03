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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,k;
int i,j;
set<int> could,edge[maxn];
vector<int> ans;
queue<int> Q;
vector<int> nxt;
int main(){
    scanf("%d%d",&n,&m);
    while (m--){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].insert(v);
        edge[v].insert(u);
    }FOR(i,1,n) could.insert(i);
    FOR(i,1,n) if (could.find(i)!=could.end()){
        Q.push(i);could.erase(i);int now=1;
        while (Q.size()){
            int u=Q.front();Q.pop();
            nxt.clear();
            for (int v:could) if (edge[u].find(v)==edge[u].end()){
                now++;
                nxt.push_back(v);
                Q.push(v);
            }for (int v:nxt) could.erase(v);
        }ans.push_back(now);
    }printf("%d\n",ans.size());
    sort(ans.begin(),ans.end());
    for (int x:ans) printf("%d ",x);
}
/*
*/
