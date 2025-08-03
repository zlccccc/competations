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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q,i,j;
int t[maxn];
LL a[maxn],b[maxn],c[maxn],k;
vector<LL> H;
LL ans[maxn],now;
int cnt[maxn];
int L,R;
struct node{
	int l,r,id;
}Q[maxn];
int BLOCK[maxn];
int cmp(node a,node b){
	if (BLOCK[a.l]==BLOCK[b.l]) return a.r<b.r;
	return BLOCK[a.l]<BLOCK[b.l];
}
const int DIV=300;
inline int getid(LL x){
	return lower_bound(H.begin(),H.end(),x)-H.begin();
}
int main(){
	scanf("%d%I64d",&n,&k);n++;
	a[1]=0;b[1]=-k;c[1]=k;
	H.push_back(0);H.push_back(k);H.push_back(-k);
	FOR(i,2,n) scanf("%d",&t[i]);
	FOR(i,1,n) BLOCK[i]=i/DIV;
	FOR(i,2,n) {
		scanf("%I64d",&a[i]);
		if (t[i]==2) a[i]=-a[i];
		a[i]+=a[i-1];b[i]=a[i]-k;c[i]=a[i]+k;
		H.push_back(a[i]);H.push_back(b[i]);H.push_back(c[i]);
	}
	sort(H.begin(),H.end());H.erase(unique(H.begin(),H.end()),H.end());
	FOR(i,1,n) a[i]=getid(a[i]),b[i]=getid(b[i]),c[i]=getid(c[i]);
	scanf("%d",&q);
	REP(i,q) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i,Q[i].r++;
	sort(Q,Q+q,cmp);
	L=1;R=0;
	//a[R]-k==a[L-1](b);a[R]==a[L-1]+k(c);
	REP(i,q){
		while (R<Q[i].r) {R++;now+=cnt[b[R]];cnt[a[R]]++;}
		while (L>Q[i].l) {L--;now+=cnt[c[L]];cnt[a[L]]++;}
		while (R>Q[i].r) {cnt[a[R]]--;now-=cnt[b[R]];R--;}
		while (L<Q[i].l) {cnt[a[L]]--;now-=cnt[c[L]];L++;}
		ans[Q[i].id]=now;
	}
	REP(i,q) printf("%I64d\n",ans[i]);
}
/*
*/
