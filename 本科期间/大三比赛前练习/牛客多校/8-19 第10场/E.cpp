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
const LL M=998244353;
const LL maxn=1e6+7;
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

// 对于每个子集, 绑定一下一个排列, 那么只有一个位置是不固定的~
// 贡献是gcd*(cnt^(m-1))
// 每个方案的贡献是gcd/m
// 构造容斥系数使得\sum_{i|k}p[i]+p[k]=k, 乘一下就行了
int p[maxn];//容斥系数
vector<int> P[maxn];
int A[maxn],ans[maxn];
int cnt[maxn];
int main() {
	int T,i,j,k;
	FOR(i,1,100000) p[i]=i;
	FOR(i,1,100000) {
		for (j=i+i;j<=100000;j+=i){
			add_(p[j],M-p[i]);
			P[j].push_back(i);
		} P[i].push_back(i);
	}
	// FOR(i,1,100000) printf("%d(%d) ",i,p[i]);
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		FOR(i,1,100000) cnt[i]=0;
		FOR(i,1,n) scanf("%d",&k),cnt[k]++;
		FOR(i,1,100000) for (j=i+i;j<=100000;j+=i) cnt[i]+=cnt[j];
		int Ans=0;
		FOR(i,1,m){
			ans[i]=0; int invi=powMM((ll)i,M-2);
			for (auto now:P[i]) if (p[now]){
				add_(ans[i],(ll)p[now]*(powMM(i+1,cnt[now])+M-1)%M);
			}
			// printf("%d : %d\n",i,ans[i]);
			mul_(ans[i],invi);
			Ans^=ans[i];
		} printf("%d\n",Ans);
	}
}
/*
*/
