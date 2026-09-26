#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
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

int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int ans=0;
int n,m,k;
queue<pair<int,int> > Q;
vector<pair<int,pair<int,int> > > link;
int id[2007][2007],len[2007][2007];
char R[2007][2007],D[2007][2007];
void spand(int x,int y,int i,int l){
    assert(1<=x&&x<=n);
    assert(1<=y&&y<=m);
    if (id[x][y]==i) return;
    if (!id[x][y]){
        id[x][y]=i;
        len[x][y]=l;
        Q.push(make_pair(x,y));
        return;
    }
//    printf("pos: %d %d; i=%d ",x,y,i);
//    printf("link %d-%d ans=%d\n",u,v,l+len[x][y]);
    link.push_back(make_pair(l+len[x][y],make_pair(i,id[x][y])));
}
int main() {
    int i,j;
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n) scanf("%s",R[i]+1);
    FOR(i,1,n-1) scanf("%s",D[i]+1);
    FOR(i,1,k) fa[i]=i;
    FOR(i,1,k){
        int x,y;
        scanf("%d%d",&x,&y);
        if (id[x][y]) continue;
        assert(1<=x&&x<=n);
        assert(1<=y&&y<=m);
        Q.push(make_pair(x,y));
        id[x][y]=i;
    }while (Q.size()){
        auto now=Q.front();Q.pop();
        int x=now.first,y=now.second;
        assert(1<=x&&x<=n);
        assert(1<=y&&y<=m);
        if (x!=n&&D[x][y]!='1') spand(x+1,y,id[x][y],len[x][y]+1);
        if (x!=1&&D[x-1][y]!='1') spand(x-1,y,id[x][y],len[x][y]+1);
        if (y!=m&&R[x][y]!='1') spand(x,y+1,id[x][y],len[x][y]+1);
        if (y!=1&&R[x][y-1]!='1') spand(x,y-1,id[x][y],len[x][y]+1);
    }sort(link.begin(),link.end());
    for (auto now:link){
        int x=now.second.second,y=now.second.first;
        x=getfa(x);y=getfa(y);
        if (x==y) continue;
        fa[x]=y; ans+=now.first;
    }
    int cnt=0;
    FOR(i,1,k) cnt+=(getfa(i)==i);
    assert(cnt==1);
    printf("%d\n",ans);
//    FOR(i,0,n+1){
//        FOR(j,0,m+1){
//            printf("%-2d",id[i][j]);
//        }puts("");
//    }puts("");
//    FOR(i,0,n+1){
//        FOR(j,0,m+1){
//            printf("%-2d",len[i][j]);
//        }puts("");
//    }
    return 0;
}
/*
*/
