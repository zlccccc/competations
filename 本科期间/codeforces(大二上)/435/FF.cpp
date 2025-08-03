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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char a[maxn];
int S[maxn],L[maxn];
struct node{
	LL max;
	int lpos,rpos;
	vector<int> L,R;
}T[maxn<<2];
node merge(const node &A,const node &B){
	node ret;
	ret.L=A.L;
	ret.R=B.R;
	ret.max=max(A.max,B.max);
	ret.lpos=A.lpos;ret.rpos=B.rpos;
	LL i,len=min(A.R.size(),B.L.size());
	REP(i,len){
		if (a[S[A.rpos]+i]==a[S[B.lpos]+i]){
			ret.max=max(ret.max,(i+1)*(B.L[i]-A.R[i]+1));
			if (B.L[i]==B.rpos) ret.R[i]=A.R[i];
			if (A.R[i]==A.lpos) ret.L[i]=B.L[i];
		}else break;
	}
	return ret;
}
void build(int x,int l,int r){
	if (l==r){
		T[x].lpos=l;T[x].rpos=r;
		T[x].L.resize(L[l],l);
		T[x].R.resize(L[r],r);
		T[x].max=L[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r){
	int L=T[x].lpos,R=T[x].rpos;
//	printf("%d %d %d,%d %d\n",x,l,r,L,R);
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2;
	if (r>mid&&mid>=l) return merge(query(x<<1,l,r),query(x<<1|1,l,r));
	if (mid>=l) return query(x<<1,l,r);
	if (r>mid) return query(x<<1|1,l,r);
}
void update(int x,int pos){
	int l=T[x].lpos,r=T[x].rpos;
//	printf("%d %d %d,%d\n",x,l,r,pos);
	if (l==r){
		T[x].L.resize(L[l],l);
		T[x].R.resize(L[r],r);
		T[x].max=L[l];
		return;
	}
	int mid=(l+r)/2;
	if (mid>=pos) update(x<<1,pos);
	else update(x<<1|1,pos);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
int n,m;
int k;
int now;
int main(){
	scanf("%d%d",&n,&m);
	int i;
	FOR(i,1,n){
		scanf("%s",a+now);
		S[i]=now;L[i]=strlen(a+now);now+=L[i];
	}
	build(1,1,n);
	while (m--){
		scanf("%d",&k);
		if (k==1){
			int l,r;
			scanf("%d%d",&l,&r);
//			node now=query(1,l,r);
//			REP(i,now.L.size()) printf("%d ",now.L[i]);puts("");
//			REP(i,now.R.size()) printf("%d ",now.R[i]);puts("");
			printf("%I64d\n",query(1,l,r).max);
		}else{
			int pos;
			scanf("%d",&pos);
			scanf("%s",a+now);
			S[pos]=now;L[pos]=strlen(a+now);now+=L[pos];
			update(1,pos);
		}
	}
}
/*
10 20
qn jhulkujid wkcexecmdkm bak xrkjwqdyu ossvo cl mbyx xnagta gzay
1 1 5
2 3 wkc
1 3 6
2 1 qnwvjal
2 1 qnwvncksizgza
2 4 bh
1 3 6
1 7 10

*/
