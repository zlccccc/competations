#include <cstdio>
#include <cstring>
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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

int sum[maxn];
int lazy[maxn];
LL query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return sum[x];
	LL ret=0;
	int mid=(L+R)/2;
	if (mid>=l) ret=query
}
LL update(int x,int l,int r,int L,int R){
}
int i,j,k,now;
int ans[maxn];
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		printf("%d\n",ans[i]);
	}
}
/*
*/

