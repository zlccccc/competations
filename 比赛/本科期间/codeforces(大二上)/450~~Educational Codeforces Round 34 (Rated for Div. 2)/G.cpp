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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<pair<int,int> > edge[maxn];
LL T[maxn],lazy[maxn],now[maxn];
void update(int x,int l,int r,LL val,int L,int R){
    if (l<=L&&R<=r){
        T[x]+=val;
        lazy[x]+=val;
        return;
    }
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    T[x]=min(T[x<<1],T[x<<1|1])+lazy[x];
//    if (x==1) printf("update: x=%d   l,r=%d %d   L,R=%d %d,  val=%d   T=%d\n",x,l,r,L,R,val,T[x]);
}
int n,m,q;
int i,j,k;
int a[maxn],b[maxn];
int main(){
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n-1) scanf("%d%d",&a[i],&b[i+1]);
    FOR(i,1,m){
        int u,v,len;
        scanf("%d%d%d",&u,&v,&k);//v=v-1+1
        edge[u].push_back(make_pair(v,k));
    }FOR(i,2,n) update(1,i,i,b[i],1,n);
    FOR(i,1,n){
        for (auto now:edge[i])
            update(1,1,now.first,now.second,1,n);
        now[i]=T[1];
//        printf("i(%d):%d ; sum=%d\n",i,now[i],a[i]+now[i]);
    }FOR(i,1,n<<2) T[i]=lazy[i]=0;
    FOR(i,1,n) update(1,i,i,a[i]+now[i],1,n);
    printf("%I64d\n",T[1]);
    while (q--){
        int x,y;
        scanf("%d%d",&x,&y);
        update(1,x,x,y-a[x],1,n);
        a[x]=y;
        printf("%I64d\n",T[1]);
    }
}
/*
*/
