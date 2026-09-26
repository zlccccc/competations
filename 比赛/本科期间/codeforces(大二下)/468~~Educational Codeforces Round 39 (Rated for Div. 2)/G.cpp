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

int T;
int n,m;
int i,j,k;
int ans;
int a[maxn],L[maxn];
int add;
int b[maxn],tot;
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]),a[i]-=i;
//    FOR(i,1,n) printf("%d ",a[i]);puts("");
    FOR(i,1,n){
        int now=upper_bound(b,b+tot,a[i])-b;
        b[now]=a[i];if (now==tot) tot++;
        L[i]=now+1;
    }tot=0;ans=n-tot-1;
//    FOR(i,1,n) printf("%d ",L[i]);puts("");
    rFOR(i,1,n){
        int id=upper_bound(b,b+tot,-a[i]+1)-b;
        ans=min(ans,n-(id+L[i]+1));
        if (i+1<=n){
            int now=upper_bound(b,b+tot,-a[i+1])-b;
            b[now]=-a[i+1];if (now==tot) tot++;
        }
    }ans=max(ans,0);
    printf("%d\n",ans);
}
/*
5
1 2 8 3 4
*/
