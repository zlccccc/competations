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

namespace ACM{
	const int maxn=1e5+7;
	int next[maxn][26],len[maxn],tot;
	int fa[maxn],fail[maxn];
	void init(){
		tot=0; len[0]=0; fa[0]=0; fail[0]=0;
		memset(next[0],0,sizeof(next[0]));
	}
	void insert(char s[]) {
		int i,n=strlen(s),p=0;
		REP(i,n) {
			int c=s[i]-'a';
			if (!next[p][c]) {
				next[p][c]=++tot; len[tot]=len[p]+1;
				memset(next[tot],0,sizeof(next[tot]));
				fail[tot]=0; fa[tot]=0;
			} p=next[p][c];
		} fa[p]=p;
	}
	int Q[maxn],ST,ED;
	void buildAC() {
		ST=0; ED=-1; Q[++ED]=0;
		while (ST<=ED) {
			int p=Q[ST++],c;
			REP(c,26) {
				if (next[p][c]) {
					fail[next[p][c]]=p?next[fail[p]][c]:0;
					Q[++ED]=next[p][c];
				} else next[p][c]=p?next[fail[p]][c]:0;
			} if (!fa[p]) fa[p]=fa[fail[p]];
		}
	}
}
char str[maxn],ins[maxn];
vector<int> P[maxn];
vector<pii> queries[maxn];
int ans[maxn];
bitset<40100> Bit;
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,m,q,i;
		scanf("%d%d%d",&n,&m,&q);
		scanf("%s",str+1);
		ACM::init();
		FOR(i,1,m) {
			scanf("%s",ins);
			ACM::insert(ins);
		} ACM::buildAC();
		FOR(i,1,n) queries[i].clear();
		FOR(i,1,q) {
			int l,r;
			scanf("%d%d",&l,&r);
			queries[r-l+1].push_back(make_pair(l,i));
		}
		int p=0;
		FOR(i,1,n) {
			int c=str[i]-'a';
			p=ACM::next[p][c];
			P[i].clear();
			for (int k=ACM::fa[p];k;k=ACM::fa[ACM::fail[k]]) {
				P[ACM::len[k]].push_back(i-ACM::len[k]+1);
				// printf("not: %d->%d\n",i-ACM::len[k]+1,i);
			}
		} FOR(i,1,n+1) Bit.set(i,0);
		FOR(i,1,n) {
			Bit=Bit&(Bit>>1);
			Bit=Bit.flip();
			for (int v:P[i]) Bit.set(v,0);
			for (pii q:queries[i]) ans[q.second]=Bit[q.first]; 
			// int j;
			// FOR(j,1,n-i+1) printf("%d",(int)Bit[j]); puts("");
		}
		FOR(i,1,q) printf("%d\n",ans[i]);
	}
}
/*
2
10 4 10
zzzabcdzxx
a
z
dz
abcd
1 3
1 4
3 6
3 7
3 8
3 9
4 4
4 5
5 5
7 10

10 4 10
zzzabcdzxx
a
z
dz
abcd
1 3
1 4
3 6
3 7
3 8
3 9
4 4
4 5
5 5
7 10
*/