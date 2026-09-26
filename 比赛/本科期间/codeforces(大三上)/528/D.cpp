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
const LL maxn=4e5+107;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

inline int lowbit(int x) {return x&-x;}
int n,q;
int C[3][maxn],D[3][maxn];//D:rev
int get(int px,int py){//
	int len=0,l=1,ret=0;
	while (l<=n) l<<=1; l>>=1;
	for (;l;l>>=1) if (C[px][len+l]+C[py][len+l]==l)
		ret+=C[px][len+l],len+=l;
	// printf("get %d-%d: %d; ret_first=%d\n",px,py,len,ret);
	int tmpret=ret,tmpl=len;
	len=0,l=1;
	while (l<=n) l<<=1; l>>=1;
	for (;l;l>>=1) if (C[px][len+l]==l)
		ret-=C[px][len+l],len+=l;
	if (len!=n&&tmpl==n) ret=tmpret; 
	// printf("get %d-%d: %d; ret_first2=     %d\n",px,py,len,ret);
	return ret;
}
int get2(int px,int py){
	int len=0,l=1,ret=0;
	while (l<=n) l<<=1; l>>=1;
	for (;l;l>>=1) if (D[px][len+l]+D[py][len+l]==l)
		ret+=D[px][len+l],len+=l;
	// printf("get2 %d-%d: %d; ret_first=%d\n",px,py,len,ret);
	int tmpl=len; len=0,l=1;
	while (l<=n) l<<=1; l>>=1;
	for (;l;l>>=1) if (D[px][len+l]==l)
		ret-=D[px][len+l],len+=l;
	// printf("get2 %d-%d: %d; ret_first2=     %d\n",px,py,len,ret);
	if (tmpl==n) return 0;
	else return ret;
}
inline void add(int x,int p,int val){
	int ini=x;
	for (;x<=n;x+=lowbit(x)) C[p][x]+=val;
	x=n-ini+1;
	for (;x<=n;x+=lowbit(x)) D[p][x]+=val;
}
map<char,int> MP;
int query(){
	return get(0,1)+get2(0,1)+get(1,2)+get2(1,2)+get(2,0)+get2(2,0);
}
char str[maxn];
int main() {
	int i;
	MP['R']=0; MP['P']=1; MP['S']=2;
	scanf("%d%d",&n,&q);
	scanf("%s",str+1);
	FOR(i,1,n) add(i,MP[str[i]],1);
	printf("%d\n",n-query());
	FOR(i,1,q){
		int x; char s[3];
		scanf("%d%s",&x,s);
		add(x,MP[str[x]],-1); str[x]=s[0];
		add(x,MP[str[x]],1);
		// puts(str+1);
		printf("%d\n",n-query());//no
	}
}
/*
3
4
bbcb
aada
aada
3
abc
bbb
bbb
4
bbcba
aadac
aadad

*/