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
const LL M=1e9+7;
const LL maxn=2000+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
	int l,r,min;
	node(){l=r=0;min=INF;}
}T[maxn*200]; int tot=0;
int root[maxn*4];
void Update(int &x,int val,int r,int L,int R){
	if (!x) x=++tot,T[x]=node(); min_(T[x].min,r);
	if (L==R) return;
	int mid=(L+R)/2;
	if (val<=mid) Update(T[x].l,val,r,L,mid);
	else Update(T[x].r,val,r,mid+1,R);
}
void update(int x,int l,int r,int val,int L,int R){
	// printf("update: %d %d %d %d %d\n",x,l,r,L,R);
	if (l<=L&&R<=r) {Update(root[x],val,r,0,2000); return;}
	int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
}
int Query(int x,int pos,int L,int R){
	if (!x) return INF;
	if (R<=pos) return T[x].min;
	int ret=INF,mid=(L+R)/2;
	min_(ret,Query(T[x].l,pos,L,mid));
	if (mid<pos) min_(ret,Query(T[x].r,pos,mid+1,R));
	return ret;
}
int query(int x,int pos,int val,int L,int R){
	int ret=Query(root[x],val,0,2000);
	if (L==R) return ret;
	int mid=(L+R)/2;
	if (pos<=mid) min_(ret,query(x<<1,pos,val,L,mid));
	if (mid<pos) min_(ret,query(x<<1|1,pos,val,mid+1,R));
	return ret;
}
vector<pii> things[maxn];
bool solve(int x){
	tot=0; int i;
	FOR(i,1,(n+1)*4) root[i]=0;
	update(1,0,0,0,0,n);
	// printf("solve: %d\n",x);
	FOR(i,1,n){
		for (auto now:things[i]){
			int r=query(1,now.first-1,x-now.second,0,n);
			if (r+1<=i) {
				update(1,r+1,i,now.second,0,n);
				update(1,i,i,0,0,n);
			}
			// printf("solve_update: %d %d; %d\n",r+1,i,now.second);
		}
	}
	// printf("%d : %d\n",x,query(1,n,x,0,n));
	if (query(1,n,x,0,n)==n) return true;
	return false;
}
int TaskA() {
	int i;
	scanf("%d%d",&m,&n);
	FOR(i,1,n) things[i].clear();
	FOR(i,1,m){
		int l,r,val;
		scanf("%d%d%d",&l,&r,&val);
		things[r].push_back(make_pair(l,val));
	}
	int l,r;
	l=0;r=2000+7;
	while (l+1<r) {
		int mid=(l+r)/2;
		if (solve(mid)) r=mid;
		else l=mid;
	}if (r==2007) puts("-1");
	else printf("%d\n",r);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_T();
}
/*
2
2 4
1 2 2
3 4 5
1 4
1 3 1 
*/
