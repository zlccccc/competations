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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=5e5+7;
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

struct node{
	int l,r; ll cnt; 
	node(){l=r=0;cnt=0;}
}T[maxn*10]; int tot;
inline void ADD(ll &x,ll y){
	x=min(x+y,INFF);
}
void update(int &x,int pos,ll val,int L,int R){
	if (!x) x=++tot,T[tot]=node();
	ADD(T[x].cnt,val);
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,pos,val,L,mid);
	else update(T[x].r,pos,val,mid+1,R);
}
ll query(int x,int l,int r,int L,int R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].cnt;
	ll ret=0; int mid=(L+R)/2;
	if (l<=mid) ADD(ret,query(T[x].l,l,r,L,mid));
	if (mid<r) ADD(ret,query(T[x].r,l,r,mid+1,R));
	return ret;
}
int root;
ll F[maxn];
int A[maxn];
vector<int> ans;
vector<int> V;
inline int getid(int x){return lower_bound(V.begin(),V.end(),x)-V.begin()+1;}
int TaskA() {
	int i; ll k;
	scanf("%d%lld",&n,&k);
	FOR(i,1,n) scanf("%d",&A[i]),V.push_back(A[i]);
	sort(V.begin(),V.end()); V.erase(unique(V.begin(),V.end()),V.end());
	FOR(i,1,n) A[i]=getid(A[i]);
	root=tot=0; int START=0;
	rFOR(i,1,n){
		F[i]=query(root,A[i]+1,INF,1,INF); ADD(F[i],1);//start from this
		update(root,A[i],F[i],1,INF);
	}
	// FOR(i,1,n) printf("%lld ",F[i]); puts("");
	ans.clear();
	FOR(i,1,n){
		if (A[i]>START){
			if (k>F[i]) k-=F[i];
			else {
				ans.push_back(i);
				k--; if (!k) break;
				START=A[i];
			}
		}
	}
	if (k) return 0*puts("-1");
	printf("%d\n",(int)ans.size());
	REP(i,(int)ans.size()) printf("%d%c",ans[i]," \n"[i==(int)ans.size()-1]);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
3 1 1 2 3 
3 2 1 2 3 
3 3 1 2 3 
3 4 1 2 3 
3 5 1 2 3 
3 6 1 2 3 
3 7 1 2 3 
4 1
1 2 3 4
*/
