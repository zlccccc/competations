#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
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

typedef pair<int,int> pii;
int n,k;
int i,j;
int up[maxn],dn[maxn];//->,<-
bool mark[maxn];
vector<int> have[maxn];
set<int> ans;
int all;
pii MAX[maxn*4];
void build(int x,int L,int R){
    if (L==R) {MAX[x]=make_pair(up[L]+dn[L],L);return;}
    int mid=(L+R)/2;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
void update(int x,int pos,int L,int R){
    if (L==R) {MAX[x]=make_pair(up[L]+dn[L],L);return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    else update(x<<1|1,pos,mid+1,R);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n){
        ans.insert(i);
        for (j=i+i;j<=n;j+=i){
            up[i]++;dn[j]++;
            have[j].push_back(i);
        }all+=up[i]+dn[i];
    }up[1]=dn[1]=0;
    build(1,1,n);
//    printf("all=%d\n",all);
    all/=2;mark[1]=1;
    if (k>all) return 0*puts("No");
    while (all>k){
        auto now=MAX[1];int x=now.second;
        up[x]=dn[x]=0;update(1,x,1,n);
//        printf("%d %d\n",all,now.first);
        mark[x]=1;
        if (all-now.first<k) continue;
        all-=now.first;
//        printf("erase : %d\n",x);
        for (int t:have[x]){
            if (mark[t]) continue;
            up[t]--;
            update(1,t,1,n);
        }for (int t=x+x;t<=n;t+=x){
            if (mark[t]) continue;
            dn[t]--;
            update(1,t,1,n);
        }ans.erase(x);
    }
//    printf("all=%d %d\n",all,k);
    puts("Yes");
    printf("%d\n",ans.size());
    for (int v:ans) printf("%d ",v);
}
/*
300000 1
*/
