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

int i,j,k;
int u,v;
int n,m;
string pre[207],sub[207];
string s;
int ans[207];
int mark[207][1<<14|7];
string tostring(int x){
	string ret;
//	printf("%d  ",x);
	while (x!=1){
		char c='0'+(x&1);
		ret=c+ret;
		x/=2;
	}
//	cout<<x<<':'<<ret<<"\n";
	return ret;
}
int main(){
	cin>>n;
	FOR(i,1,n){
		cin>>s;
		pre[i]=sub[i]=s;
		ans[i]=2;//
		while (s.find(tostring(ans[i]))!=string::npos) mark[i][ans[i]]=1,ans[i]++;//没有的第一个pos 
	}
	cin>>m;
	FOR(i,n+1,n+m){
		cin>>u>>v;
		pre[i]=pre[u]+pre[v];
		sub[i]=sub[u]+sub[v];
		if (pre[i].length()>30) pre[i]=pre[i].substr(0,30);
		reverse(sub[i].begin(),sub[i].end());
		if (sub[i].length()>30) sub[i]=sub[i].substr(0,30);
		reverse(sub[i].begin(),sub[i].end());
		ans[i]=max(ans[u],ans[v]);
		s=sub[u]+pre[v];
		FOR(j,2,1<<14) if (mark[u][j]||mark[v][j]||s.find(tostring(j))!=string::npos) mark[i][j]=1;
		while (mark[i][ans[i]]) ans[i]++;
		int T=ans[i],A=0;
//		cout<<s<<"  "<<"\n";
//		cout<<s<<"  "<<pre[i]<<"  "<<sub[i]<<"\n";
//		printf("ans=%d\n",ans[i]);
		while (T) A++,T>>=1;
		printf("%d\n",A-2);
	}
}
/*
*/
