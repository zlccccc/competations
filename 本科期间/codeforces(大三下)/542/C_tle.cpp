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
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

//16*4=64; (len<<4)|now
struct SAM {
	int next[maxn][64];
	int fail[maxn],len[maxn];
	int cnt;
	void init() {
		cnt=0; fail[0]=-1; len[0]=0;
		memset(next[0],0,sizeof(next[0]));
	}
	void add(int last,int c,int &nxt) {
		int np=++cnt,p=last;
		memset(next[np],0,sizeof(next[np]));
		len[np]=len[p]+1;
		for (; p!=-1&&!next[p][c]; p=fail[p]) next[p][c]=np;
		if (p==-1) fail[np]=0;
		else {
			int q=next[p][c];
			if (len[p]+1==len[q]) fail[np]=q;
			else {
				int nq=++cnt; len[nq]=len[p]+1;
				memcpy(next[nq],next[q],sizeof(next[q]));
				fail[nq]=fail[q];
				fail[np]=fail[q]=nq;
				for (; p!=-1&&next[p][c]==q; p=fail[p]) next[p][c]=nq;
			}
		} nxt=np;
	}

	int S[maxn],K[maxn],C[maxn];
	int solve(){
		int i;
		FOR(i,0,cnt) S[i]=K[i]=C[i]=0;
		FOR(i,0,cnt) S[len[i]]++;
		FOR(i,0,cnt) S[i]+=S[i-1];
		FOR(i,0,cnt) K[S[len[i]]--]=i;
		rFOR(i,0,cnt) {
			if (i) C[i]=1; int c;
			REP(c,64) if (next[i][c])
				add_(C[i],C[next[i][c]]);
		} return C[0];
	}

	void print() {
		int i;
		FOR(i,1,cnt) {
		}
	}
	int a[maxn];
	void dfs(int x=0,int len=0) {
		int i;
		printf("%-3d(fail:%-3d,len=%-2d):",x,fail[x],this->len[x]);
		REP(i,len) {pr2(a[i],a[i]/16+1);} puts("");
		REP(i,64) {
			if (next[x][i]) {
				a[len]=i;
				dfs(next[x][i],len+1);
				a[len]=0;
			}
		}
	}
} sam;
//substring...我怎么还以为是subsquence
int n,m,q;
char str[maxn];
set<int> no={3,5,14,15};//len=4
int nxt[maxn][4][16],last[maxn],tot;
bool couldstart[maxn][4][16],islast[maxn];
int main() {
	int _;
	scanf("%d",&n);
	tot=1;
	sam.init();
	REP(_,n) {
		int i,l,k;
		scanf("%s",str);
		int now=str[0]-'0'; islast[0]=1;
		rFOR(i,0,tot) {//start_id
			rREP(l,3) REP(k,16) {
				if (nxt[i][l][k]&&couldstart[i][l][k]){
					int x=(k<<1)|now; couldstart[i][l][k]=0;
					if (l+1==3&&no.count(x)) continue;
					if (!nxt[i][l+1][x]) sam.add(last[i],((l+1)<<4)|x,last[nxt[i][l+1][x]=++tot]);
					islast[nxt[i][l+1][x]]=1; couldstart[i][l+1][x]=1;
					// printf("add: %d -%d ",i,l+1); pr2(x,l+1+1); puts("");
				}
			} if (islast[i]){
				islast[i]=0;
				// if (!nxt[i][0][now]) printf("add(: %d - ",i); pr2(now,1); puts("");
				if (!nxt[i][0][now]) sam.add(last[i],now,last[nxt[i][0][now]=++tot]);
				islast[nxt[i][0][now]]=1; couldstart[i][0][now]=1;
			}
		}

		printf("%d\n",sam.solve());
		sam.dfs();
	}
}
/*
3
1
1
1
*/