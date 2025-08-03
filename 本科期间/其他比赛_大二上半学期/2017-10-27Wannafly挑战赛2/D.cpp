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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<pair<int,int> > edge[maxn];
#define MP make_pair
int tp[maxn],od[maxn],in[maxn];
LL s_l[maxn],r_t[maxn],pl[maxn],rp[maxn],len[maxn];
void solve(int l,int r,LL val){
//	printf("l=%d r=%d val=%d\n",l,r,val);
	if (l==r) {len[tp[l]]=val;return;}
	int mid=(l+r)/2,i,j;
	LL DL=val,DR=val;
	FOR(i,l,mid) DR=min(DR,s_l[tp[i]]+rp[i]);
	FOR(i,mid+1,r) DL=min(DL,pl[i]+r_t[tp[i]]);
	FOR(i,l,mid){
		for (auto &e:edge[tp[i]]){
			int j=od[e.first];
			if (mid+1<=j&&j<=r){
//				printf("solve:%d %d;(%d) (%d):%d\n",i,j,tp[i],tp[j],e.second); 
				rp[i]=min(rp[i],r_t[tp[j]]+e.second);
				pl[j]=min(pl[j],s_l[tp[i]]+e.second);
			}
		}
	}
	solve(l,mid,DL);
	solve(mid+1,r,DR);
}
int n,m,s,t;
vector<int> V;
int i,j,k;
int ans;
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	REP(i,m){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		edge[u].push_back(MP(v,len));
		in[v]++;
	}
	FOR(i,1,n) if (!in[i]) V.emplace_back(i);
	REP(i,V.size()){//sort
		tp[i+1]=V[i];od[V[i]]=i+1;
		for (auto &e:edge[V[i]]){
			in[e.first]--;
			if (!in[e.first]) V.emplace_back(e.first);
		}
	}
	FOR(i,1,n) len[i]=s_l[i]=r_t[i]=pl[i]=rp[i]=INFF;
	s_l[s]=r_t[t]=pl[od[s]]=rp[od[t]]=0;
	FOR(i,1,n)
		for (auto &e:edge[tp[i]])
			s_l[e.first]=min(s_l[e.first],s_l[tp[i]]+e.second);
	rFOR(i,1,n)
		for (auto &e:edge[tp[i]])
			r_t[tp[i]]=min(r_t[tp[i]],r_t[e.first]+e.second);
	solve(1,n,INFF);
//	FOR(i,1,n) printf("%-10d ",tp[i]);puts("-->topo");
//	FOR(i,1,n) printf("%-10d ",od[i]);puts("-->order");puts("");
//	FOR(i,1,n) printf("%-10d ",s_l[i]);puts("<--s_l");
//	FOR(i,1,n) printf("%-10d ",r_t[i]);puts("<--r_t");puts("");
//	FOR(i,1,n) printf("%-10d ",pl[i]);puts("<--pl");
//	FOR(i,1,n) printf("%-10d ",rp[i]);puts("<--rp");puts("");
	int q;
	scanf("%d",&q);
	while (q--){
		scanf("%d",&i);
//		printf("s-l:%d r-t:%d len:%d\n",s_l[i],r_t[i],len[i]);
		if (len[i]==INFF) puts("-1");
		else printf("%lld\n",len[i]);
	}
}
/*
*/
