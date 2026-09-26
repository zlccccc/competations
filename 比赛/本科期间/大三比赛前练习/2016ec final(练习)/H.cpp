#include <bits/stdc++.h>
#include <utility>
#include <algorithm>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
typedef long long ll;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const int maxn=1e5+7;
const ll mod=1e9+7;
ll powMM(ll a,ll b,ll M=mod){
    ll ret=1;
    for (;b;b>>=1,a=a*a%M)
        if (b&1) ret=ret*a%M;
    return ret;
}
int n,m,k;
int main(){
    int _,T; scanf("%d",&T);
    FOR(_,1,T){
        ll ans=0; int i;
        scanf("%d%d%d",&n,&m,&k);
        FOR(i,2,k) ans=(ans+(powMM(k,(n-1)*(m-1))*powMM(i-1,n+m-2))%mod*n*m%mod)%mod;
        ans=(ans+powMM(k,n*m))%mod;
        printf("Case #%d: %lld\n",_,ans);
    }
}
