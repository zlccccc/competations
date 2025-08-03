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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i,j;
typedef pair<int,int> pii;
pii a[maxn],b[maxn][16];
int Log[maxn];
int ans[maxn];
int pos1,pos2,pos3;//divide
int val1,val2,val3;
pii query(int l,int r){
	int log=Log[r-l+1];
	return max(b[l][log],b[r-(1<<log)+1][log]);
}
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i].first),a[i].second=i+1;
	sort(a,a+n);
	b[0][0]=make_pair(a[0].first,0);
	rep(i,1,n) b[i][0]=make_pair(a[i].first-a[i-1].first,i);
	REP(i,15)
		REP(j,n) b[j][i+1]=max(b[j][i],b[j+(1<<i)][i]);
	Log[0]=-1;
	FOR(i,1,n) if (!(i&(i-1))) Log[i]=Log[i-1]+1;else Log[i]=Log[i-1];
	//-1....1....2....3
	rREP(i,n){//pos3
		rREP(j,i){//pos2
			int len3=n-i,len2=i-j;
			if (len3>2*len2||len2>2*len3) continue;
			int minlen=max(1,(max(len2,len3)+1)/2);
			int maxlen=min(j,min(len2,len3)*2);
			if (minlen>maxlen) continue;
			pii k=query(j-maxlen,j-minlen);
			if (a[i].first-a[i-1].first<val3) continue;
			if (a[i].first-a[i-1].first==val3&&a[j].first-a[j-1].first<val2) continue;
			if (a[i].first-a[i-1].first==val3&&a[j].first-a[j-1].first==val2&&k.first<val1) continue;
			val1=k.first;val2=a[j].first-a[j-1].first;val3=a[i].first-a[i-1].first;
			pos1=k.second;pos2=j;pos3=i;
		}
	}
	REP(i,pos1) ans[a[i].second]=-1;
	rep(i,pos1,pos2) ans[a[i].second]=3;
	rep(i,pos2,pos3) ans[a[i].second]=2;
	rep(i,pos3,n) ans[a[i].second]=1;
	FOR(i,1,n) printf("%d ",ans[i]);
}
/*
*/
