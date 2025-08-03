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
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
vector<int> Q[maxn];
int pre[maxn];
int l1[maxn],l2[maxn];
int MAX[maxn<<2];
void update(int x,int pos,int val,int L,int R){
	MAX[x]=max(MAX[x],pos);
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,val,L,mid);
	if (mid<pos) update(x<<1|1,pos,val,mid+1,R); 
}
int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return MAX[x];
	int ret=0,mid=(L+R)/2;
	if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
	if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
	return ret;
}
LL ans;
int main(){
	scanf("%d",&n);
	FOR(i,2,n) scanf("%d%*d",&pre[i]);
	scanf("%d",&m);
	REP(i,m){
		int l,r;
		scanf("%d%d",&l,&r);l++;r++;
		Q[r].push_back(l);
	}
	FOR(i,2,n){
		for(int j=i,len=0;j;j=pre[j],len++){
			if (l1[j]==len-1) l1[j]++;
			else if (l2[j]==len-1) l2[j]++;
			else continue;
			update(1,i,l1[j]+l2[j],1,n);
		}
		for (int x:Q[i]){
			printf("%d-%d : %d\n",x,i,query(1,x,i,1,n));
			ans+=query(1,x,i,1,n);
		}
	}
	printf("%lld\n",ans);
}
/*
*/
