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
#include <iomanip>
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

typedef pair<LL,LL> pll;
int T;
int n,m;
int i,j,k;
pll a[107],g[107];
pll f[107][107];
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%lld%lld",&a[i].first,&a[i].second);
        sort(a+1,a+1+n);reverse(a+1,a+1+n);
        FOR(i,1,n){
            LL all=0,cnt=0;
            FOR(j,i,n){
                all+=cnt*(a[j-1].first-a[j].first);
                cnt+=a[j].second;
                f[i][j]=make_pair(all,cnt);
            }
        }
        FOR(i,1,n) g[i]=f[1][i];
        m--;
        while (m--){
            rFOR(i,1,n)
                FOR(j,1,i-1)
                    g[i]=min(g[i],make_pair(g[j].first+f[j+1][i].first,max(g[j].second,f[j+1][i].second)));
        }printf("%lld %lld\n",g[n].first,g[n].second);
    }
}
/*
2
3 4
1 1
2 2
3 3

3 2
1 1
4 2
2 3
*/
