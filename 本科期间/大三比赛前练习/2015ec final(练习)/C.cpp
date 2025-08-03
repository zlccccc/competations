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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
// char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int sa[maxn],mala[maxn],rnk[maxn];
char str[maxn],s[maxn*2];
int p[maxn*2];
void manacher(){
	int i; 
	s[0]='+'; s[1]='%';
	REP(i,n+1) {
		s[i*2+2]=str[i];
		s[i*2+3]='%';
	} int len=n*2+2,id=0,mx=0;
	FOR(i,1,len-1){
		if (mx>i) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while (s[i+p[i]]==s[i-p[i]]) p[i]++;
		if (p[i]+i>mx) mx=p[i]+i,id=i;
	} FOR(i,1,len-1) p[i]--;
}
set<int> S[maxn];//edge
int fa[maxn*2];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
inline void merge(int u,int v){
	int x=getfa(u),y=getfa(v);
	if (x==y) return; else fa[x]=y;
	if (S[x].size()>S[y].size()) swap(x,y);
	for (auto now:S[x]) S[y].insert(now);
}
int solve(){
	int i;
	REP(i,n) rnk[sa[i]]=i; rnk[n]=-1;
	str[sa[0]]='a';
	REP(i,n) S[i].clear();
	REP(i,n) fa[i]=i;
	REP(i,n*2-1) {
		if (mala[i]==0) continue;
		int l=(i-mala[i]+1)/2,r=(i+mala[i]-1)/2;
		merge(l,r);
		l--; r++;
		if (l<0||r>=n) continue;//make not same
		if (getfa(l)==getfa(r)) return 0*puts("Wrong calculation!");
		S[getfa(l)].insert(r);
		S[getfa(r)].insert(l);
	}
	// REP(i,n) printf("%d ",rnk[i]); puts("");
	REP(i,n-1) {
		// printf("%d : %d(%d) %d(%d)  %d\n",i,sa[i],rnk[sa[i]+1],sa[i+1],rnk[sa[i+1]+1],mala[sa[i]+sa[i+1]]);
		if (rnk[sa[i]+1]<rnk[sa[i+1]+1]&&//first
			!S[getfa(sa[i])].count(sa[i+1])) {//could_same
			str[sa[i+1]]=str[sa[i]];
			merge(sa[i],sa[i+1]);
		} else {
			str[sa[i+1]]=str[sa[i]]+1;
		}
	} str[n]=0;
	REP(i,n) if (str[i]>'z') return 0*puts("Wrong calculation!");
	manacher();
	// REP(i,n*2+2) printf("%d ",p[i]);
	// puts(str);
	REP(i,n*2-1) if (p[i+2]!=mala[i]) return 0*puts("Wrong calculation!");
	return 0*puts(str);
}
int main() {
	// scanf("%s",str); n=strlen(str); manacher();
	// int i; FOR(i,1,n*2+2) printf("%d ",p[i]);
	int T,_t; scanf("%d",&T);
	FOR(_t,1,T) {
		int i;
		scanf("%d",&n);
		REP(i,n) scanf("%d",&sa[i]);
		REP(i,n*2-1) scanf("%d",&mala[i]);
		printf("Case #%d: ",_t);
		solve();
	}
}
/*
10
3
2 0 1
1 0 3 0 1
3
2 0 1
1 2 3 2 1
5
4 3 2 1 0
1 2 3 4 5 4 3 2 1

5
2 0 4 3 1
1 0 3 0 1 0 1 2 1
*/
