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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int n,len;
char s[maxn],a[maxn],b[maxn];
char toward[255];
bool used[255],okay;
void dfs(int pos,bool issmaller,bool isbetter) {
	// printf("dfs: %d %d %d\n",pos,issmaller,isbetter);
	if (okay) return;
	int i,j;
	if (pos==len) {
		okay=1; puts("YES");
		REP(i,n) if (!toward[i+'a']) {
			REP(j,n) if (!used[j+'a']) {
				toward[i+'a']=j+'a'; used[j+'a']=1;
				break;
				// printf("used=%d:%d\n",i,j);
			}
		} puts(toward+'a');
		return;
	}
	if (toward[(int)s[pos]]) {
		if ((issmaller||toward[(int)s[pos]]<=a[pos])&&
		        (isbetter||b[pos]<=toward[(int)s[pos]]))
			dfs(pos+1,issmaller||toward[(int)s[pos]]<a[pos],isbetter||toward[(int)s[pos]]>b[pos]);
	} else {
		rep(i,'a','a'+n) if (!used[i]) {
			toward[(int)s[pos]]=i; used[i]=1;
			if ((issmaller||toward[(int)s[pos]]<=a[pos])&&
			        (isbetter||b[pos]<=toward[(int)s[pos]]))
				dfs(pos+1,issmaller||toward[(int)s[pos]]<a[pos],isbetter||toward[(int)s[pos]]>b[pos]);
			if (okay) return;
			toward[(int)s[pos]]=0; used[i]=0;
		}
	}
}
void solve() {
	int i;
	scanf("%d",&n);
	scanf("%s%s%s",s,b,a);//emmmm
	REP(i,n+1) toward[i+'a']=used[i+'a']=0;
	len=strlen(s);
	okay=0; dfs(0,0,0);
	if (!okay) puts("NO");
}
int main() {
	int T,_; scanf("%d",&T);
	FOR(_,1,T) solve();
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