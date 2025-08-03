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

bitset<20001> mark;
ll A[maxn],B[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        ll all,ans=0; int i,n;
        scanf("%d",&n);
        all=0;
        FOR(i,1,n) scanf("%lld",&A[i]);
        FOR(i,1,n) scanf("%lld",&B[i]);
        //sum^2=\sum 2*aiaj
        mark.reset(); mark.set(0);
        FOR(i,1,n) ans+=A[i]*A[i]*(n-2),all+=A[i];//should: n-3
        FOR(i,1,n) ans+=B[i]*B[i]*(n-2),all+=B[i];//should: n-3
        FOR(i,1,n) mark=(mark<<A[i])|(mark<<B[i]);
        ll Ans=INFF;
        // *(n-2)
        // printf("%lld; all=%lld\n",ans,all);
        FOR(i,0,all) if (mark[i]) {
            Ans=min(Ans,ans+i*i+(all-i)*(all-i));
            // printf("i=%d; %lld\n",i,ans+i*i+(all-i)*(all-i));
        }
        printf("%lld\n",Ans);
    }
}
/*
//swap A and B
*/