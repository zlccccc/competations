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
const LL maxn=1e5+107;
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

int A[maxn],S[maxn];
int r[maxn];//nowr
vector<pair<int,int> > V[maxn];//could
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,s,i;
		scanf("%d",&n); s=0;
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(i,1,n) S[i]=0,s+=A[i];
		FOR(i,1,n) {
			r[i]=i; int l=i;
			if (S[i]<=s){
				// while (r[l]<=n&&!A[r[l]]) r[l]++;
				while (r[l]<=n) {
					S[l]+=A[r[l]];
					if (S[l]) V[S[l]].push_back(make_pair(l,r[l]));
					r[l]++;
					// while (r[l]<=n&&A[r[l]]==0) {
					// 	S[l]+=A[r[l]];
					// 	if (S[l]) V[S[l]].push_back(make_pair(l,r[l]));
					// 	r[l]++;
					// }//insert
				}
			}
		} ll ans1=0,ans2=0;
		FOR(i,1,s) if (V[i].size()){
			// nth_element(V[i].begin(), V[i].begin()+(V[i].size()-1)/2, V[i].end());
			pii nxt=V[i][(V[i].size()-1)/2];
			add_(ans1,powMM(233,i)*nxt.first%M);
			add_(ans2,powMM(233,i)*nxt.second%M);
			printf("%d: %d %d\n",i,nxt.first,nxt.second);
			// for (auto now:V[i]) printf("%d %d\n",now.first,now.second);
			// for (auto now:V[i]) {
			// 	int l=now.first;
			// 	if (S[l]==i) {
			// 		if (r[l]<=n) {
			// 			S[l]+=A[r[l]];
			// 			if (S[l]) V[S[l]].push_back(make_pair(l,r[l]));
			// 			r[l]++;
			// 			while (r[l]<=n&&A[r[l]]==0) {
			// 				S[l]+=A[r[l]];
			// 				if (S[l]) V[S[l]].push_back(make_pair(l,r[l]));
			// 				r[l]++;
			// 			}//insert
			// 		}
			// 	}
			// } 
			V[i].clear();
		}
		printf("%lld %lld\n",ans1,ans2);
	}
}
/*
3
4
2 1 1 2
4
0 1 0 0
6
2 3 2 3 2 1
*/