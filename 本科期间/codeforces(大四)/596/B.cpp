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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

char str[maxn];
int val[maxn],pval[maxn],n;
pair<int,pii> more,ans_1;
int getans(int l,int r,int pans) {
	// printf("get: %d %d %d\n",l,r,pans);
	int i,ans=0; pval[l-1]=0;
	FOR(i,l,r) {
		if (str[i]=='(') pval[i]=1;
		else pval[i]=-1;
		pval[i]+=pval[i-1];
		// printf(" 2 solve %c(%d): %d\n",str[i],pans,pval[i]);
		if (pval[i]==pans) ans++;
	} return ans;
}
int cval[maxn];
pair<int,pii> check(int l,int r) {
	// printf("check: %d %d\n",l,r);
	pair<int,pii> ans,ret=make_pair(0,make_pair(1,1));
	if (l+1==r) return make_pair(0,make_pair(1,1));
	swap(str[l],str[r]);
	ans=make_pair(getans(l,r,-1),make_pair(l,r));
	if (ans.second.first>n) ans.second.first-=n;
	if (ans.second.second>n) ans.second.second-=n;
	swap(str[l],str[r]);
	ans_1=max(ans_1,ans);
	int lpos,i;
	FOR(i,l,r) {
		if (str[i]=='(') cval[i]=1;
		else cval[i]=-1;
		cval[i]+=cval[i-1];
		if (cval[i]==1&&str[i]==')') {//right
			swap(str[lpos],str[i]);
			ans=make_pair(getans(lpos,i,-1),make_pair(lpos,i));
			if (ans.second.first>n) ans.second.first-=n;
			if (ans.second.second>n) ans.second.second-=n;
			ret=max(ans,ret);
			swap(str[lpos],str[i]);
		}
		if (cval[i]==2&&str[i]=='(') lpos=i;
	}
	return ret;
}
int main() {
	more=ans_1=make_pair(0,make_pair(1,1));
	int i;
	scanf("%d",&n);
	scanf("%s",str+1);
	int pos=1;
	FOR(i,1,n) {
		if (str[i]=='(') val[i]=1;
		else val[i]=-1;
		val[i]+=val[i-1];
		if (val[i]<val[pos]) pos=i;
	} if (val[n]!=0) return 0*puts("0\n1 1\n");
	pos++;//last to first
	// printf("solving! pos=%d\n",pos);
	FOR(i,1,pos-1) str[n+i]=str[i];
	FOR(i,1,n) val[i]=0;
	int prev=pos,ans=0;
	FOR(i,1,n) {
		int p=pos+i-1;
		// printf("solve %c: %d\n",str[p],val[p]);
		if (str[p]=='(') val[p]=1;
		else val[p]=-1;
		val[p]+=val[p-1];
		if (val[p]==0) {
			more=max(more,check(prev,p));
			prev=p+1; ans++;
		}
	} more.first+=ans;
	ans_1=max(ans_1,more);
	printf("%d\n",ans_1.first);
	printf("%d %d\n",ans_1.second.first,ans_1.second.second);
}
/*
10
()()())(()

10
(()(()))()
*/