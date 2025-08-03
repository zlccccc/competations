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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
 
struct SAM {
	const static int maxn=8e5+7;
	int next[maxn][26],fail[maxn],len[maxn],cnt,pos[maxn],Pos[maxn];
	void init() {
		cnt=0; fail[0]=-1; len[0]=0; pos[0]=0;
		memset(next[0],0,sizeof(next[0]));
	}
	int add(int p,int c,int id) {
		int np=++cnt; pos[np]=Pos[np]=id;
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
				fail[nq]=fail[q]; pos[nq]=pos[q]; Pos[nq]=0;
				fail[np]=fail[q]=nq;
				for (; p!=-1&&next[p][c]==q; p=fail[p]) next[p][c]=nq;
			}
		}
		return np;
	}
};
struct TRIE {
	SAM sam;
	const static int maxn=8e5+7;
	void init() {
		sam.init();
		tot=0; ToT=0; id[ToT]=0; val[0]=-1; //1:空
		memset(next[0],0,sizeof(next[0]));
	}
	// 1:trie上建树
	int id[maxn],ToT;//initial_id (i->trie)
	int next[maxn][26],last[maxn],tot;//on the trie
	int val[maxn];
	void Add(int i,int c) {
		int p=id[i]; ToT++;
		if (!next[p][c]) {
			next[p][c]=++tot; val[tot]=c;
			memset(next[tot],0,sizeof(next[tot]));
		} id[ToT]=next[p][c];
		// printf("id[%d]=%d\n",ToT,next[p][c]);
	}
	int Q[maxn],st,ed;
	void buildSAM() {
		st=ed=0; Q[ed++]=0;
		while (st!=ed) {
			int p=Q[st++]; int c;
			REP(c,26) if (next[p][c]) {
				int nxt=next[p][c];
				last[nxt]=sam.add(last[p],c,nxt);
				Q[ed++]=nxt;
			}
		}
	}
	int failtot;
	int in[maxn],out[maxn],dfstot;//(trie->dfsid)
	char a[maxn];
	void dfs_dfn(int x,int len=0) {
		debug("%d: %s\n",x,a);
		in[x]=++dfstot; int c;
		REP(c,26) if (next[x][c]) {
			a[len]=c+'a';
			dfs_dfn(next[x][c],len+1);
			a[len]=0;
		} out[x]=dfstot;
	}
	int ans[maxn];
	vector<int> edge[maxn];//fail
	vector<pair<int,int> > queries[maxn];
	void query(char str[],int idx,int idq) {
		int p=0,len=strlen(str),i;
		REP(i,len) {
			int c=str[i]-'a';
			// while (p&&!sam.next[p][c]) p=sam.fail[p];
			if (!sam.next[p][c]) return;
			p=sam.next[p][c];
		}
		debug("query: p=%d; id=%d\n",p,in[id[idx]]);
		queries[p].push_back(make_pair(in[id[idx]],idq));
	}
	struct node{
		int l,r,val;
	} T[maxn*21]; int tot_tree;
	int root[maxn];
	void update(int &x,int pos,int val,int L,int R) {
		if (!x) x=++tot_tree; T[x].val+=val;
		if (L==R) return;
		int mid=(L+R)/2;
		if (pos<=mid) update(T[x].l,pos,val,L,mid);
		if (mid<pos) update(T[x].r,pos,val,mid+1,R);
	}
	void merge(int &x,int y,int L,int R) {
		if (!x||!y) {x=x|y; return;}
		T[x].val=T[x].val+T[y].val;
		int mid=(L+R)/2;
		merge(T[x].l,T[y].l,L,mid);
		merge(T[x].r,T[y].r,mid+1,R);
	}
	int query(int x,int l,int r,int L,int R) {
		if (!x) return 0;
		if (l<=L&&R<=r) return T[x].val;
		int ret=0,mid=(L+R)/2;
		if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
		if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
		return ret;
	}
	int MAX=0;
	void linkfail() {
		int i; MAX=dfstot+1;
		FOR(i,1,sam.cnt) edge[sam.fail[i]].push_back(i);
		// printf("tot=%d;\n",tot); return;
		FOR(i,1,tot) {
			debug("update: %d : %d->%d\n",last[i],in[i],out[i]);
			update(root[last[i]],in[i],1,1,MAX);
			update(root[last[i]],out[i]+1,-1,1,MAX);
		}
	}
	void dfsfail(int x) {
		// printf("dfsfail: %d\n",x);
		for (int v:edge[x]) {
			dfsfail(v);
			merge(root[x],root[v],1,MAX);
		}
		for (auto now:queries[x]) {
			// printf("query: %d %d\n",now.second,now.first);
			ans[now.second]=query(root[x],1,now.first,1,MAX);
		}
	}
} trie;
char str[maxn];
int main() {
	trie.init();
	int q,i; scanf("%d",&q);
	FOR(i,1,q) {
		int op; scanf("%d",&op);
		if (op==1) {
			char s[2];
			scanf("%s",s);
			trie.Add(0,s[0]-'a');
		} else {
			int k; char s[2];
			scanf("%d",&k);
			scanf("%s",s);
			trie.Add(k,s[0]-'a');
		}
	} trie.buildSAM();
	trie.dfs_dfn(0);
	scanf("%d",&q);
	FOR(i,1,q) {
		int k; scanf("%d%s",&k,str);
		trie.query(str,k,i);
	}
	trie.linkfail();
	trie.dfsfail(0);
	FOR(i,1,q) printf("%d\n",trie.ans[i]);
}
/*
20
1 b
2 1 a
1 c
2 3 b
2 3 b
1 c
1 a
2 1 a
1 b
2 4 c
2 7 a
2 5 c
1 b
2 1 c
2 12 a
2 14 a
1 c
1 a
1 c
2 8 b
2
5 baa
4 abb
*/