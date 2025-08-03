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
inline ll powMM(ll a,ll b,ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct SAM{
	const static int maxn=2e5+7;
	int next[maxn][26],fail[maxn],len[maxn],cnt,last;
	void init(){
		cnt=0; fail[0]=-1; len[0]=0; last=0;
		memset(next[0],0,sizeof(next[0]));
	}
	void add(int c) {
		int p=last,np=++cnt;
		memset(next[np],0,sizeof(next[np]));
		len[np]=len[p]+1;
		for (;p!=-1&&!next[p][c]; p=fail[p]) next[p][c]=np;
		if (p==-1) fail[np]=0;
		else {
			int q=next[p][c];
			if (len[p]+1==len[q]) fail[np]=q;
			else {
				int nq=++cnt; len[nq]=len[p]+1;
				memcpy(next[nq],next[q],sizeof(next[q]));
				fail[nq]=fail[q];
				fail[np]=fail[q]=nq;
				for (;p!=-1&&next[p][c]==q; p=fail[p]) next[p][c]=nq;
			}
		} last=np;
	}
	void insert(char str[]) {
		int len=strlen(str),i;
		REP(i,len) add(str[i]-'a');
	}
	void solve(char str[],int L[]) {
		int l=0,p=0,length=strlen(str+1),i;
		FOR(i,1,length) {
			int c=str[i]-'a';
			while (p&&!next[p][c]) p=fail[p],l=len[p];
			if (next[p][c]) {
				p=next[p][c]; l++;
			} L[i]=l;
		}
	}

    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,fail[x],this->len[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
char str[maxn],que[maxn];
int L[maxn];
ll sum[maxn*4]; int lz[maxn*4];
void update(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		lz[x]++; sum[x]+=R-L+1;
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	sum[x]=sum[x<<1]+sum[x<<1|1]+(ll)lz[x]*(R-L+1);
}
ll query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2;
	ll ret=(ll)lz[x]*(min(r,R)-max(l,L)+1);
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	return ret;
}
ll ans[maxn];
vector<pair<int,int> > queries[maxn];
int main() {
	freopen("curse.in","r",stdin);
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		/*to solve the problem*/
		int n,i,q;
		scanf("%s%s",que+1,str);
		scanf("%d",&q);
		sam.init();
		sam.insert(str);
		// sam.dfs();
		sam.solve(que,L);
		n=strlen(que+1);
		// FOR(i,1,n) printf("%d ",L[i]);puts("");
		FOR(i,1,n) queries[i].clear();
		FOR(i,1,q) {
			int l,r; scanf("%d%d",&l,&r); 
			queries[r].push_back(make_pair(l,i));
		}
		FOR(i,1,n*4) sum[i]=lz[i]=0;
		FOR(i,1,n) {
			if (L[i]) update(1,i-L[i]+1,i,1,n);
			// if (L[i]) printf("update %d %d\n",i-L[i]+1,i);
			for (auto now:queries[i]) {
				ans[now.second]=query(1,now.first,i,1,n);
			}
		}
		printf("Case %d:\n",_);
		FOR(i,1,q) printf("%lld\n",ans[i]);
	}
}
/*
2
-2 3
-2 1

3
-3 3
-2 2
-1 1
*/