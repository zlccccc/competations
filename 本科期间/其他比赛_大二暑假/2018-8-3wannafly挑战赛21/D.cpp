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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=10000+7;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<ll> Ans,ans;
ll S[maxn],P[maxn];
map<ll,ll> now,nxt;
inline int getid(ll x){
	int ret=lower_bound(S+1,S+1+n,x)-S;
	if (ret<=n&&S[ret]==x) return ret;
	return -1;
}
pair<ll,ll> H[maxn];
pii pre[107][maxn];
int solve(int T){
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%lld",&H[i].first);
	FOR(i,1,n) scanf("%lld",&H[i].second);
	sort(H+1,H+1+n);
	FOR(i,1,n) S[i]=H[i].first,P[i]=H[i].second;
	ll MIN=-S[1]; P[1]--;
	FOR(i,1,n) S[i]+=MIN;
	now.clear(); now[0]++;
	Ans.clear(); ans.clear();
	FOR(i,1,n){
		while (P[i]){
			// printf("i=%d P=%lld\n",i,P[i]);
			// for (auto x:now) printf("%lld(%lld) ",x.first,x.second);puts("");
			Ans.push_back(S[i]);
			for (auto x:now){
				P[getid(x.first+S[i])]-=x.second;
				nxt[x.first+S[i]]+=x.second;
				nxt[x.first]+=x.second;
			} swap(nxt,now); nxt.clear();
		}
	}
	// for (int v:Ans) printf("%lld ",S[v]);puts("");
	FOR(i,1,n) pre[0][i]=make_pair(0,0); pre[0][1]=make_pair(0,1);
	REP(i,(int)Ans.size()){
		FOR(j,1,n) pre[i+1][j]=pre[i][j];
		rFOR(j,1,n) if (pre[i][j]!=make_pair(0,0)){
			int nxtid=getid(S[j]+Ans[i]);
			if (nxtid!=-1) pre[i+1][nxtid]=make_pair(i,j);
		}
	} int last=getid(MIN); i=Ans.size();
	while (last!=1){
		auto nxt=pre[i][last];
		ans.push_back(-(S[last]-S[nxt.second]));
		last=nxt.second; i=nxt.first;
	}last=ans.size()-1;
	REP(i,(int)Ans.size()){
		if (last!=-1&&ans[last]+Ans[i]==0) last--;
		else ans.push_back(Ans[i]);
	}
	printf("Case #%d:",T);
	for (ll now:ans) printf(" %lld",now);puts("");
	return 0;
}
int main() {
	int T,i;
	scanf("%d",&T);
	FOR(i,1,T) solve(i);
}
/*
*/
