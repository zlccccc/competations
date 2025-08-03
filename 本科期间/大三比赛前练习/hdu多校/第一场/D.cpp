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

#define DEBUG1
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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

int len[maxn*4];
void update(int x,int pos,int val,int L,int R){
	len[x]+=val;
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,val,L,mid);
	if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
}
int query(int x,int L,int R){
	if (L==R) return L;
	int mid=(L+R)/2;
	if (len[x<<1]!=mid-L+1) return query(x<<1,L,mid);
	return query(x<<1|1,mid+1,R);
}
int cnt[maxn],ans[maxn];
int L[maxn];
int TaskA() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) L[i]=i;
	FOR(i,1,m){
		int l,r;
		scanf("%d%d",&l,&r);
		min_(L[r],l);
	}rFOR(i,1,n-1) min_(L[i],L[i+1]);
	// FOR(i,1,n) printf("%d ",L[i]);puts("");
	int now=1;
	FOR(i,1,n){
		while (now<L[i]){
			cnt[ans[now]]--;
			if (!cnt[ans[now]]) update(1,ans[now],-1,1,n);
			now++;
		}ans[i]=query(1,1,n);
		if (!cnt[ans[i]]) update(1,ans[i],1,1,n);
		cnt[ans[i]]++;
	}while (now<=n){
		cnt[ans[now]]--;
		if (!cnt[ans[now]]) update(1,ans[now],-1,1,n);
		now++;
		while (now<L[i]){
			cnt[ans[now]]--;
			if (!cnt[ans[now]]) update(1,ans[now],-1,1,n);
			now++;
		}
	}
	FOR(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_T();
}
/*
2
5

*/
