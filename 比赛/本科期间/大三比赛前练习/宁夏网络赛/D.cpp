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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
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

struct node{
	int l,r,xl,xr;
};
LL A[maxn];
LL pre[maxn],dp[maxn];
int cnt[maxn];
queue<node> Q;
void Solve(int n){
	int i;
	Q.push(node{1,n,1,n});
	while (Q.size()){
		node F=Q.front();Q.pop();
		int l=F.l,r=F.r,L=F.xl,R=F.xr;
		int m=(l+r)/2,M=L;
//		printf("l,m,r,L,R: %d %d %d %d %d\n",l,m,r,L,R);
		LL &now=dp[m];
		FOR(i,L,min(m,R)){
		    LL sum=(A[m]-A[i])*(A[m]-A[i]);
			if (now>sum+pre[i-1]) now=sum+pre[i-1],M=i;
		}
		if (l<m) Q.push(node{l,m-1,L,M});
		if (r>m) Q.push(node{m+1,r,M,R});
	}
}
bool mark[maxn];
void solve(){
    int i,j;
    int n,m,cnt;cnt=0;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,n) if (!mark[A[i]]) A[++cnt]=A[i];
    sort(A+1,A+1+cnt);
    n=unique(A+1,A+1+cnt)-A-1;
    FOR(i,1,n) pre[i]=dp[i]=INFF;pre[0]=0;
//    FOR(i,1,n) printf("%lld ",A[i]);puts("");
    while(m--){
//        FOR(i,1,n) dp[i]=INFF;
        Solve(n);
//        rFOR(i,1,n)
//            FOR(j,1,i)
//                dp[i]=min(dp[i],pre[j-1]+(A[j]-A[i])*(A[j]-A[i]));
//        FOR(i,1,n) printf("%lld ",dp[i]);puts("");
        FOR(i,1,n) pre[i]=dp[i];
    }printf("%lld\n",dp[n]);
}
int p[maxn],tot;
const int MAX=1e6;
void init(){
    tot=0;int i,j;
    FOR(i,2,MAX){
        if (!mark[i]) p[tot++]=i;
        REP(j,tot){
            if (i*p[j]>MAX) break;
            mark[i*p[j]]=1;
            if (i%p[j]==0) break;
        }
    }
}
int main() {
    int i,j,k;
    init();
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
*/
