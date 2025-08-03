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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL poww(LL a,LL b,LL m){
	LL ret=1;a%=m; 
	for (;b;b>>=1ll,a=a*a%m)
		if (b&1) ret=ret*a%m;
	return ret;
}
struct node{
	int l,r;LL val;
	node(int _l,int _r,LL _val):l(_l),r(_r),val(_val){}
};
vector<node> now,pre;
int n,m;
LL seed,vmax;
int T;
int rnd(){
	int ret=seed;
	seed=(seed*7+13)%M;
	return ret;
}
int tot;
priority_queue<pair<LL,int> > Q;
int main(){
	int i;
	scanf("%d%d%I64d%I64d",&n,&m,&seed,&vmax);
	FOR(i,1,n){
		now.push_back(node(i,i,rnd()%vmax+1));
	}FOR(i,1,m){
//		for (auto t:now) printf("%d-%d:%d ",t.l,t.r,t.val);puts("");
		int op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1,x,y;
		if (l>r) swap(l,r);
		if (op==3) x=rnd()%(r-l+1)+1;
		else x=rnd()%vmax+1;
		if (op==4) y=rnd()%vmax+1;
//		printf("q:%d:%d-%d  x,y=%d %d\n",op,l,r,x,y);
		if (op==1){
			pre.swap(now);now.clear();
			for (auto &t:pre){
				int L=max(t.l,l),R=min(r,t.r);
				if (L>R) {now.push_back(t);continue;}
				if (t.l<=L-1) now.push_back(node(t.l,L-1,t.val));
				now.push_back(node(L,R,t.val+x));
				if (R+1<=t.r) now.push_back(node(R+1,t.r,t.val));
			}
		}if (op==2){
			pre.swap(now);now.clear();
			for (auto &t:pre){
				int L=max(t.l,l),R=min(r,t.r);
				if (L>R) {now.push_back(t);continue;}
				if (t.l<=L-1) now.push_back(node(t.l,L-1,t.val));
				now.push_back(node(L,R,x));
				if (R+1<=t.r) now.push_back(node(R+1,t.r,t.val));
			}pre.swap(now);now.clear();int i=0;
			while(i<pre.size()){
				int L=pre[i].l;LL val=pre[i].val;
				while (i<pre.size()&&val==pre[i].val) i++;
				int R=pre[i-1].r;
//				printf("12345 %d %d %d\n",L,R,val);
				now.push_back(node(L,R,val));
			}
		}if (op==3){
			while (Q.size()) Q.pop();
			for (auto &t:now){
				int L=max(t.l,l),R=min(r,t.r);
				if (L>R) continue;
//				printf("2:push_%d %d %d\n",L,R,t.val);
				Q.push(make_pair(-t.val,R-L+1));
			}while (Q.size()){
				auto now=Q.top();Q.pop();
//				printf("3:%d %d\n",now.first,now.second);
				x-=now.second;
				if (x<=0){printf("%I64d\n",-now.first);break;}
			}
		}if (op==4){
			LL ans=0;
			for (auto &t:now){
				int L=max(t.l,l),R=min(r,t.r);
				if (L>R) continue;
				(ans+=(R-L+1)*poww(t.val,x,y))%=y;
//				printf("%d %d %d %d;ans=%d  ; +=%d\n",R-L+1,t.val,x,y,ans,poww(t.val,x,y));
			}printf("%I64d\n",ans);
		}
	}
}
/*
*/
