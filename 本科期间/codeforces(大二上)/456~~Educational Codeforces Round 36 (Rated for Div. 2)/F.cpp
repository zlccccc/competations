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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<LL,int> pli;
int n,m;
int i,j,k;
pli A[maxn];
int fa[maxn],size[maxn];
vector<int> edge[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}bool mark[maxn];
LL query(){
    FOR(i,1,n) fa[i]=i,size[i]=1,mark[i]=0;//small->bigger merge!
    sort(A+1,A+1+n);
    LL ans=0;
    FOR(i,1,n){
//        printf("%lld(%d) ",A[i].first,A[i].second);
        int u=A[i].second;mark[u]=1;
        for (int v:edge[u]) if (mark[v]){
            int x=getfa(u),y=getfa(v);
            if (x==y) continue;
            ans+=A[i].first*size[y]*size[x];
            fa[x]=y;size[y]+=size[x];
        }
    }return ans;
}
LL ans;
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%I64d",&A[i].first),A[i].second=i;
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }ans=query();
//    printf("%I64d  ",ans);
    FOR(i,1,n) A[i].first=-A[i].first;
    ans+=query();
    printf("%I64d\n",ans);
}
/*
*/
