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

int A[maxn];
int S[maxn],tmp[maxn],top;
int lef[maxn],R[maxn],L[maxn];//rightv
int rig[maxn],pre[maxn],pretop[maxn];//changes
pii ans[maxn];
vector<int> toR[maxn];
priority_queue<pii,vector<pii>,greater<pii> > Q;
int main() {
	int T,_;
	int i;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n;
		scanf("%d",&n);
		FOR(i,1,n) scanf("%d",&A[i]);
		S[top=0]=0;
		FOR(i,1,n) {
			int pos=lower_bound(S+1,S+top+1,i,[&](int i,int j) {return A[i]<A[j];})-S;
			S[pos]=i; L[i]=S[pos-1]; lef[i]=pos;
			top=max(pos,top);//(contain this)
		} S[top=0]=n+1; A[0]=-1;
		rFOR(i,1,n) {
			int pos=lower_bound(S+1,S+top+1,i,[&](int i,int j) {return A[i]>A[j];})-S;
			pre[i]=S[pos]; rig[i]=pos; pretop[i]=top;
			S[pos]=i; R[i]=S[pos-1];//right
			top=max(pos,top);
		} int base=top;
		int k=0;//i+1 to x:okay
		FOR(i,1,n) if (lef[i]+rig[i]-1==base) {
			ans[i]=make_pair(base,A[L[i]]+1);
			if (i<k) ans[i]=make_pair(base,0);
			k=max(k,R[i]);
		} else ans[i]=make_pair(base,0);
		k=INF;
		rFOR(i,1,n) if (lef[i]+rig[i]-1==base) {
			if (i>k) ans[i]=make_pair(base,0);
			k=min(k,L[i]);
		} pretop[0]=top;
		FOR(i,1,top) tmp[i]=S[i];
		while (Q.size()) Q.pop();
		Q.push(make_pair(0,1));
		FOR(i,1,n) {
			top=pretop[i]; S[rig[i]]=pre[i];//right;
			while (Q.size()) {
				auto x=Q.top(); A[0]=x.first;
				int pos=lower_bound(S+1,S+top+1,0,[&](int i,int j) {return A[i]>A[j];})-S;
				// printf("Q: i=%d; %d : %d+%d\n",i,A[0],x.second,pos);
				if (pos+x.second-1<base) Q.pop();
				else break;
			} if (Q.size()) ans[i]=min(ans[i],make_pair(base,Q.top().first));
			Q.push(make_pair(A[i]+1,lef[i]+1));
			// printf("push %d %d\n",A[i]+1,lef[i]+1);
		} top=pretop[0];
		FOR(i,1,top) S[i]=tmp[i]; 
		while (Q.size()) Q.pop();
		Q.push(make_pair(0,1));
		FOR(i,1,n) {
			top=pretop[i]; S[rig[i]]=pre[i];//right;
			while (Q.size()) {
				auto x=Q.top(); A[0]=x.first;
				int pos=lower_bound(S+1,S+top+1,0,[&](int i,int j) {return A[i]>A[j];})-S;
				// printf("Q: i=%d; %d : %d+%d\n",i,A[0],x.second,pos);
				if (pos+x.second-1<=base) Q.pop();
				else break;
			} if (Q.size()) ans[i]=make_pair(base+1,Q.top().first);
			Q.push(make_pair(A[i]+1,lef[i]+1));
			// printf("push %d %d\n",A[i]+1,lef[i]+1);
		}
		// FOR(i,1,n) printf("%d ",lef[i]); puts(" lef");
		// FOR(i,1,n) printf("%d ",rig[i]); puts(" rig");
		// FOR(i,1,n) printf("%d ",L[i]); puts("  <- L");
		FOR(i,1,n) printf("%d %d\n",ans[i].first,ans[i].second);
	}
}
/*
100
5
0 2 5 8 71
*/