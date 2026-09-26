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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

vector<LL> V;
inline LL getid(LL x){return lower_bound(V.begin(),V.end(),x)-V.begin();};
int mark[(3*maxn)<<2],lazy[(3*maxn)<<2];
inline void pushup(int x){
	if (mark[x<<1]==mark[x<<1|1]) mark[x]=mark[x<<1];
	else if (mark[x<<1]!=1||mark[x<<1|1]!=1) mark[x]=2;//have 0&1
	else mark[x]=1;
}
inline void pushdown(int x){
	if (lazy[x]!=-1){
		if (lazy[x]==2) {//reverse
			if (lazy[x<<1]==2) lazy[x<<1]=-1;
			else if (lazy[x<<1]==-1) lazy[x<<1]=2;
			else lazy[x<<1]^=1;
			if (lazy[x<<1|1]==2) lazy[x<<1|1]=-1;
			else if (lazy[x<<1|1]==-1) lazy[x<<1|1]=2;
			else lazy[x<<1|1]^=1;
			if (mark[x<<1]!=2) mark[x<<1]^=1;
			if (mark[x<<1|1]!=2) mark[x<<1|1]^=1;
			lazy[x]=-1;
		}else{
			mark[x<<1]=mark[x<<1|1]=lazy[x];
			lazy[x<<1]=lazy[x<<1|1]=lazy[x];
			lazy[x]=-1;
		}
	}
}
void update(int x,int l,int r,int L,int R,int val){
//	printf("%d->%d:%d\n",L,R,val);
	if (l<=L&&R<=r){
		if (val!=2) lazy[x]=mark[x]=val;
		else{
			if (L!=R) pushdown(x);
			if (mark[x]!=2) mark[x]=mark[x]^1;
			if (lazy[x]==val) lazy[x]=-1;
			else lazy[x]=2;
		}
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,L,mid,val);
	if (r>mid) update(x<<1|1,l,r,mid+1,R,val);
	pushup(x);
}
int query(int x,int L,int R){
//	printf("%d->%d:%d   %d      le::%d ri::%d\n",L,R,mark[x],lazy[x],mark[x<<1],mark[x<<1|1]);
	if (L==R) return L;
	int mid=(L+R)/2,ret;
	pushdown(x);
	if (mark[x<<1]!=1) ret=query(x<<1,L,mid);
	else ret=query(x<<1|1,mid+1,R);
	pushup(x);
	return ret;
}
LL Q[maxn],L[maxn],R[maxn];
int n,m;
int i,j;
int k,l,r;
int main(){
	scanf("%d",&n);
	REP(i,n){
		scanf("%d%I64d%I64d",&Q[i],&L[i],&R[i]);
		V.push_back(L[i]);
		V.push_back(R[i]);
		V.push_back(R[i]+1);
	}
	V.push_back(1);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	fill(lazy,lazy+V.size()*4,-1);
//	REP(i,V.size()) printf("%d ",V[i]);puts("");
	REP(i,n){
		k=Q[i];l=getid(L[i])+1;r=getid(R[i])+1;
//		printf("change:%d %d %d\n",k,l,r);
		if (k==1)
			update(1,l,r,1,V.size(),1);
		if (k==2)
			update(1,l,r,1,V.size(),0);
		if (k==3)
			update(1,l,r,1,V.size(),2);
//		printf("%I64d\n",query(1,1,V.size()));
		printf("%I64d\n",V[query(1,1,V.size())-1]);
	}
}
/*
*/
