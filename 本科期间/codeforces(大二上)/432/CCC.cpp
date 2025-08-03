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
//±ØÐë¹þÏ£ 
int calc(vector<int> now){
	set<int> mex;
	int MX=0,i;
	for (int val:now) MX=max(MX,val);
//	for (int val:now) printf("%d ",val);puts("");
	FOR(i,1,MX){
		vector<int> down;
		for (int val:now){
			if (val==i) continue;
			if (val>i) down.push_back(val-i);
			else down.push_back(val);
		}
		mex.insert(calc(down));
	}
	int ret=0;
	while (mex.count(ret)) ret++;
//	for (int val:now) printf("%d ",val);printf(", ret=%d",ret);puts("");
	return ret;
}
int n,k;
int i,j;
int ans;
vector<int> val[maxn];
int cnt;
map<int,int> MP;//val,pos
int main(){
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d",&k); 
		for(j=2;j*j<=k;j++){
			int tot=0;
			while (k%j==0) k/=j,tot++;
			if (tot){
				if (!MP.count(j)) MP[j]=++cnt;
				val[MP[j]].push_back(tot);
			}
		}if (k!=1){
			if (!MP.count(k)) MP[k]=++cnt;
			val[MP[k]].push_back(1);
		}
	} 
//	FOR(i,1,100000) sort(val[i].begin(),val[i].end()),val[i].erase(unique(val[i].begin(),val[i].end()),val[i].end()); 
	FOR(i,1,cnt) if (val[i].size()) ans^=calc(val[i]);
//	printf("%d\n",ans);
	if (ans) puts("Mojtaba");
	else puts("Arpa");
}
/*
*/
