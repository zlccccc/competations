#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
 
#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;

ll A[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        int n,m,i,j,k;
        scanf("%d",&n);
        ll ans=0,idc=0,count=0,count2=0;
        FOR(i,1,n) scanf("%lld",&A[i]);
        FOR(i,2,n-1) {
            if (A[i]) ans+=(A[i]+1)/2,idc++;
            if (A[i]>=2) count++;
            if (A[i]>=2&&A[i]%2==0) count2++;
        } // 1 7 0 1: also okay
        if (!count&&idc) puts("-1"); // all 1
        else if (count==1&&count2==0&&idc==1) { // (ans==2&&!idc)
            if (ans==2||n==3) puts("-1"); // 1 3 0 1 or 1 5 0 1only one
            else printf("%lld\n",ans+1); // 
        } else printf("%lld\n",ans);
    }
}
/*
*/