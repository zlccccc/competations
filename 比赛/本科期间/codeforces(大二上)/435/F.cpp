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
int lcp[maxn];
struct node{
	LL max;
	int lpos,rpos;
	vector<pair<int,int> > L,R;//µÝ¼õµÄ 
}T[maxn<<2];
node merge(const node &A,const node &B){
	node ret;
	ret.max=max(A.max,B.max);
	ret.lpos=A.lpos;ret.rpos=B.rpos;
	int i,j,pos=A.rpos;
	j=B.L.size()-1;
	rREP(i,A.R.size()){
		while(j>=0&&B.L[j].first<A.R[i].first) j--;
		if (j<0) break;
		ret.max=max(ret.max,1ll*min(min(A.R[i].first,B.L[j].first),lcp[pos])*(B.L[j].second-A.R[i].second+1));
	}
	i=A.R.size()-1;
	rREP(j,B.L.size()){
		while(i>=0&&B.L[j].first>A.R[i].first) i--;
		if (i<0) break;
		ret.max=max(ret.max,1ll*min(min(A.R[i].first,B.L[j].first),lcp[pos])*(B.L[j].second-A.R[i].second+1));
	}
	ret.L=A.L;
	for (auto now:B.L){
		now.first=min(lcp[pos],now.first);
		if (now.first>=ret.L.back().first) ret.L.back().second=now.second;
		else ret.L.push_back(now);
	}
	ret.R=B.R;
	for (auto now:A.R){
		now.first=min(lcp[pos],now.first);
		if (now.first>=ret.R.back().first) ret.R.back().second=now.second;
		else ret.R.push_back(now);
	}
	return ret;
}
void build(int x,int l,int r){
	if (l==r){
		T[x].lpos=l;T[x].rpos=r;lcp[l]=0;
		while (lcp[l]<L[l]&&lcp[l]<L[l+1]&&a[S[l]+lcp[l]]==a[S[l+1]+lcp[l]]) lcp[l]++;//x,x+1
		T[x].L.clear();T[x].R.clear();
		T[x].L.push_back(make_pair(L[l],l));
		T[x].R.push_back(make_pair(L[r],r));
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
		lcp[l]=0;
		while (lcp[l]<L[l]&&lcp[l]<L[l+1]&&a[S[l]+lcp[l]]==a[S[l+1]+lcp[l]]) lcp[l]++;//x,x+1
		T[x].L.clear();T[x].R.clear();
		T[x].L.push_back(make_pair(L[l],l));
		T[x].R.push_back(make_pair(L[r],r));
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
			node now=query(1,l,r);
//			FOR(i,1,n) printf("%d ",lcp[i]);puts("");
//			REP(i,now.L.size()) printf("%d,%d ",now.L[i].first,now.L[i].second);puts("");
//			REP(i,now.R.size()) printf("%d,%d ",now.R[i].first,now.R[i].second);puts("");
			printf("%I64d\n",query(1,l,r).max);
		}else{
			int pos;
			scanf("%d",&pos);
			scanf("%s",a+now);
			S[pos]=now;L[pos]=strlen(a+now);now+=L[pos];
			update(1,pos);
			if (pos!=1) update(1,pos-1);
		}
	}
}
/*
*/
