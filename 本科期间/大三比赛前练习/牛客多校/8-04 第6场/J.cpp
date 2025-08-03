#include <sstream>
#include <fstream>
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
typedef unsigned int UI;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e7+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];

unsigned x,y,z;
unsigned tang(){
    unsigned t;
    x^=(x<<16);
    x^=(x>>5);
    x^=(x<<1);
    t=x;x=y;y=z;
    z=t^x^y;
    return z;
}
UI a[maxn];
void initialize() {}
int main() {
	int T,t;
	scanf("%d",&T);
	FOR(t,1,T){
		int i,j;
		scanf("%d%u%u%u",&n,&x,&y,&z);
		FOR(i,1,n) a[i]=tang();
		// FOR(i,1,n) printf("%u ",a[i]);puts("");
		nth_element(a+1,a+1+max(0,n-1000000),a+1+n);
		int cnt=max(0,n-1000000)+1;
		FOR(i,cnt,n) a[i-cnt+1]=a[i];
		n=min(n,1000000);
		ull ans=0;
		sort(a+1,a+1+n);
		rFOR(i,1,n) rFOR(j,i+1,n){
			if ((ull)a[i]*a[j]<=ans) break;
			// printf("%u %u : %llu\n",a[i],a[j],(ull)a[i]*a[j]/gcd(a[i],a[j]));
			ans=max(ans,(ull)a[i]*a[j]/gcd(a[i],a[j]));
		}
		printf("Case #%d: %llu\n",t,ans);
	}
}
/*

*/
