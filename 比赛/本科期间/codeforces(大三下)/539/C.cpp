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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct node {
	int l,r;
	int lpos,rm,value;//rm:maxi
	ll maxused,used;//lpos+(v-used)/value
	node():lpos(0),rm(0),value(0),maxused(0),used(0) {l=r=0;};
} T[maxn*50]; int tot;
void merge(node &ret,node A,node B) {//避免l,r被改
	if (!A.lpos) {
		ret.lpos=B.lpos; ret.rm=B.rm;
		ret.value=B.value;
		ret.maxused=B.maxused; ret.used=B.used;
		return;
	} if (!B.lpos) {
		ret.lpos=A.lpos; ret.rm=A.rm;
		ret.value=A.value;
		ret.maxused=A.maxused; ret.used=A.used;
		return;
	} ret.maxused=max(A.maxused,A.used+(ll)(B.rm-A.lpos)*A.value+B.maxused);
	ret.lpos=B.lpos; ret.value=B.value; ret.rm=A.rm;
	ret.used=A.used+(ll)(B.rm-A.lpos)*A.value+B.used;
} int root;
int op,t,s,l,r,v;
void update(int &x,int L,int R) {//starttime
	if (!x) x=++tot;
	if (L==R) {//lpos:start_time(position)
		if (op==1) T[x].lpos=T[x].rm=t,T[x].value=s;
		else T[x].lpos=T[x].rm=0,T[x].value=0;
		return;
	} int mid=(L+R)/2;
	if (t<=mid) update(T[x].l,L,mid);
	else update(T[x].r,mid+1,R);
	merge(T[x],T[T[x].l],T[T[x].r]);
	// printf("update : %d %d   %d %d %lld %lld _l=%d %d; used=%lld\n"
	// 	,L,R,T[x].lpos,T[x].value,T[x].maxused,T[x].used,T[T[x].l].lpos,T[T[x].r].lpos,T[T[x].l].used);
} double ans;
node now;
void query(int x,int L,int R) {//(l,R]时间段内
	if (ans>=0) return;
	if (l<=L&&R<=r) {
		if (T[x].lpos) {
			if (now.used+(ll)(T[x].rm-now.lpos)*now.value>=v) { //merge_R
				if (now.value<=0) ans=now.lpos;
				else ans=now.lpos+1.*(v-now.used)/now.value;
				return;
			}
			node tmp;
			merge(tmp,now,T[x]);
			// printf("check: (%d-%d) now=%d %d %lld %lld; chk=%lld: v=%d\n",
			//        L,R,tmp.lpos,tmp.value,tmp.maxused,tmp.used,tmp.used+(ll)(R-tmp.lpos)*tmp.value,v);
			if (tmp.maxused>=v) {//not
				// printf("query: %d %d: okay\n",L,R);
				int mid=(L+R)/2;
				query(T[x].l,L,mid);
				query(T[x].r,mid+1,R);
				if (ans>=0) return;
				puts("-100");
			} else {
				now=tmp;
			}
		}
		if (now.used+(ll)(R-now.lpos)*now.value>=v) { //last=R
			if (now.value<=0) ans=now.lpos;
			else ans=now.lpos+1.*(v-now.used)/now.value;
		} return;
	} int mid=(L+R)/2;
	if (l<=mid) query(T[x].l,L,mid);
	if (mid<r) query(T[x].r,mid+1,R);
}
int main() {
	int q,i;
	scanf("%d",&q);
	FOR(i,1,q) {
		scanf("%d",&op);
		if (op==1) {
			scanf("%d%d",&t,&s); s=-s;
			update(root,1,1000000000);
		} else if (op==2) {
			scanf("%d",&t);
			update(root,1,1000000000);
		} else {
			scanf("%d%d%d",&l,&r,&v);
			ans=-1; now=node(); now.lpos=l;
			query(root,1,1000000000);
			if (ans>r) puts("-10000");
			// printf("query %d %d %lld %lld\n",now.lpos,now.value,now.maxused,now.used);
			printf("%.10f\n",ans);
		}
		// now=T[1];
		// printf("_i: %d %d %lld %lld\n",now.lpos,now.value,now.maxused,now.used);
	}

}
/*
10
1 1 1000000000
1 2 1000000000
1 3 1000000000
1 4 1000000000
1 500 1000000000
1 322 1000000000
1 500000000 -1000000000
3 1 1000000000 1
3 1 1000000000 1000000000
3 100 1000000000 1
*/