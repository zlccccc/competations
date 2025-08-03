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

vector<int> V;
inline int getid(int x) {
	return lower_bound(V.begin(), V.end(),x)-V.begin();
}
int pre[maxn],l[maxn],cnt[maxn],notok[maxn];
int A[maxn],mark[maxn],cut[maxn];
vector<pair<pair<int,pii>,int> > P;//pair<value,length(+-1),pos>
vector<int> ans;
int main() {
	freopen("fragmentation.in","r",stdin);
	freopen("fragmentation.out","w",stdout);
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) {
		scanf("%d",&A[i]);
		V.push_back(A[i]);
	} sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	FOR(i,1,n) A[i]=getid(A[i]);
	FOR(i,1,n) if (A[i]!=A[i-1]||i==1) cnt[A[i]]++;//blocks
	// FOR(i,1,n) printf("%d ",A[i]);
	l[0]=0;
	FOR(i,2,n) {
		if (A[i]==A[i-1]) {
			// printf("not_cut:%d\n",i);
			pre[i]=pre[i-1];
			continue;
		} if (A[i]==A[i-1]+1) {//>=2会产生pre
			if (cnt[A[i]]!=1) pre[i]=i;//切后面,x前必须要连上
			else pre[i]=pre[i-1];//cut_count=1
			l[i]=l[pre[i-1]]+1;
			P.push_back(make_pair(make_pair(-A[i],make_pair(-(l[i]&1),l[i])),i));
		} else {//must cut
			pre[i]=0; cut[i]=1;
		}
	} sort(P.begin(),P.end());
	// puts("init:ok");
	for (auto p:P) {
		int px=-p.first.first; int pos=p.second;
		// printf("check: %d; %d\n",pos,p.first.second);
		if (!notok[pos]&&!mark[px]) {
			// printf("remove: %d-%d; cnt=%d; pre=%d\n",pre[pos-1],pos,cnt[A[pos]],pre[pos-1]);
			mark[px]=1; notok[pre[pos-1]]=1;
			continue;
		} cut[pos]=1;
	} cut[n+1]=1;
	int now=0;
	FOR(i,1,n) {
		now++;
		if (cut[i+1]) {
			ans.push_back(now);
			now=0;
		}
	}
	printf("%d\n",(int)ans.size());
	for (int v:ans) printf("%d ",v);
}
/*
18
1 2 3 3 4 1 1 2 2 1 2 3 4 1 2 3 4 5
7
2 3 1 1 2 2 1
9
1 2 4 4 5 4 5 6 7
6
1 2 3 1 2 3
6
1 2 3 4 2 4
7
4 2 2 4 1 2 3
*/
