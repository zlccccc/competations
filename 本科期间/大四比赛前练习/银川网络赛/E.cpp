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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct node{
	int cnt;//value_count
	int val[3],son[4];
	node() {
		cnt=0;
		memset(val,0,sizeof(val));
		memset(son,0,sizeof(son));
	}
	void init(int v,int lson=0,int rson=0) {
		cnt=1; val[0]=v;
		son[0]=lson; son[1]=rson;
	}
}T[maxn]; int tot,root;
int insert(int &x,int val) {
	if (T[x].cnt==3) {//4-node; only_updated
		int left=++tot,right=++tot;
		T[left]=T[right]=node();
		T[left].init(T[x].val[0],T[x].son[0],T[x].son[1]);
		T[right].init(T[x].val[2],T[x].son[2],T[x].son[3]);
		T[x].init(T[x].val[1]);
		T[x].son[0]=left; T[x].son[1]=right;
		//root//TODO: root_notokay
		return x;//insert_pushup
	}
	while (1) {
		// printf("insert: %d\n",x);
		if (!x) {//only and only if x=root
			x=++tot; T[x]=node(); T[x].init(val);
			return 0;
		} else {//find the child
			int o,i; REP(o,T[x].cnt) if (T[x].val[o]>val) break;
			if (!T[x].son[0]) {//leaf
				rrep(i,o,T[x].cnt) T[x].val[i+1]=T[x].val[i];
				T[x].cnt++; T[x].val[o]=val;
				return 0;//insert
			} else {
				int son=insert(T[x].son[o],val);
				if (son) {
					rrep(i,o,T[x].cnt) {
						T[x].val[i+1]=T[x].val[i];
						T[x].son[i+2]=T[x].son[i+1];
					}
					T[x].cnt++; T[x].val[o]=T[son].val[0];
					T[x].son[o]=T[son].son[0];
					T[x].son[o+1]=T[son].son[1];
				} else return 0;//insert_okay
			}
		}
	} return 0;
}
void print(int x) {
	if (!x) return;
	// printf("%d : ",x);
	int i; REP(i,T[x].cnt) printf("%d%c",T[x].val[i]," \n"[i==T[x].cnt-1]);
	REP(i,T[x].cnt+1) print(T[x].son[i]);
} 
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		/*to solve the problem*/
		int n,i;
		scanf("%d",&n);
		root=0; tot=0;
		FOR(i,1,n) {
			int k; scanf("%d",&k);
			while (insert(root,k)){
				// print(root);
				// system("pause");
			}
			// print(root);
			// system("pause");
		}
		printf("Case #%d:\n",_);
		print(root);
	}
}
/*
3
4
1 2 3 4
4
4 3 2 1
17
6 3 5 7 1 10 2 9 4 8 11 12 13 14 15 16 17
*/