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
const LL maxn=1e3+107;
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

char str[207];
char s[407];
bool solve(int x,int y) {
	int n=y-x+1,i,j,l;
	FOR(i,x,y) s[i-x+1]=str[i];
	FOR(i,1,n) s[i+n]=s[i];
	i=1; j=2;
	while (i<=n&&j<=n) {
		REP(l,n) if (s[i+l]!=s[j+l]) break;
		if (l==n) break;
		if (s[i+l]>s[j+l]) swap(i,j);
		j=max(j+l+1,i+1);
	} return (i==1);
}
int Cnt[maxn],Pre[maxn];
bool mark[maxn];
int main(){
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		scanf("%s",str+1);
		int len=strlen(str+1),i,j;
		FOR(i,1,len) {
			Cnt[i]=len+1;
			FOR(j,1,i) {
				if (Cnt[j-1]+1<Cnt[i]&&solve(j,i)) {
					Cnt[i]=Cnt[j-1]+1;
					Pre[i]=j-1;
				}
			} mark[i]=0;
		}
		// FOR(i,1,len) printf("%d ",Pre[i]); puts(" <- pre");
		// printf("%d\n",Cnt[len]);
		for (int k=len;k;k=Pre[k]) mark[k]=1;
		FOR(i,1,len) {
			printf("%c",str[i]);
			if (mark[i]) {
				Cnt[len]--;
				if (Cnt[len]) printf(" ");
				else puts("");
			}
		}
	}
}