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
const LL maxn=2e5+107;
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
 
vector<int> edge[maxn];
namespace ACM {
	const int maxn=2e5+7;
	int nxt[maxn][26],fail[maxn],len[maxn],tot;
	ll cnt[maxn];
	void init() {
		tot=0; len[0]=0; fail[0]=0; cnt[0]=0;
		memset(nxt[0],0,sizeof(nxt[0]));
	}
	int insert(char s[]) {
		int i,n=strlen(s),p=0;
		REP(i,n) {
			int c=s[i]-'a';
			if (!nxt[p][c]) {
				nxt[p][c]=++tot; len[tot]=len[p]+1; fail[tot]=0;
				memset(nxt[tot],0,sizeof(nxt[tot])); cnt[tot]=0;
			} p=nxt[p][c];
		} cnt[p]++;
		return p;
	}
	void buildAC() {
		static int Q[maxn],ST,ED;
		ST=0; ED=-1; Q[++ED]=0;
		while (ST<=ED) {
			int p=Q[ST++],c;
			cnt[p]+=cnt[fail[p]];
			REP(c,26) {
				if (nxt[p][c]) {
					fail[nxt[p][c]]=p?nxt[fail[p]][c]:0;
					Q[++ED]=nxt[p][c];
				} else nxt[p][c]=p?nxt[fail[p]][c]:0;
			}
		}
	}
	void dfs(int p=0,int l=0) {
		static char s[maxn];
		printf("%-20s  p=%d(fail=%d;len=%d) cnt=%lld\n",s,p,fail[p],len[p],cnt[p]);
		int c;
		REP(c,26) if (nxt[p][c]){
			if (nxt[p][c]&&len[p]+1==len[nxt[p][c]]) {
				s[l]=c+'a'; dfs(nxt[p][c],l+1); s[l]=0;
			}
		}
	}
}
ll C[maxn],D[maxn];
int id[maxn];
char so[maxn];
char pool[maxn*3],*st=pool;
char *str[maxn];
ll ANS1,ANS2;
void ADDANS(ll x) {
	ANS2+=x; ANS1+=ANS2/10000000000ll;
	ANS2%=10000000000ll;
}
void PRINTANS(){
	if (ANS1) printf("%lld%010lld",ANS1,ANS2);
	else printf("%lld",ANS2);
}
int main() {
	int n,i;
	scanf("%s",so);
	int len=strlen(so);
	scanf("%d",&n);
	ACM::init();
	REP(i,n) {
		str[i]=st;
		scanf("%s",str[i]);
		int l=strlen(str[i]);
		ACM::insert(str[i]);
		reverse(str[i],str[i]+l);
		st+=l+2;
	} ACM::buildAC();
	// ACM::dfs();
	int p=0;
	REP(i,len) {
		int c=so[i]-'a';
		p=ACM::nxt[p][c];
		C[i]=ACM::cnt[p];
	}
 
	ACM::init();
	REP(i,n) {
		int l=strlen(str[i]);
		ACM::insert(str[i]);
		reverse(str[i],str[i]+l);
	} ACM::buildAC();
	// ACM::dfs();
	p=0;
	rREP(i,len) {
		int c=so[i]-'a';
		p=ACM::nxt[p][c];
		D[i]=ACM::cnt[p];
	}
	// REP(i,len) printf("%d %d\n",C[i],D[i]);
	REP(i,len-1) ADDANS((ll)C[i]*D[i+1]);
	PRINTANS();
}
/*
*/