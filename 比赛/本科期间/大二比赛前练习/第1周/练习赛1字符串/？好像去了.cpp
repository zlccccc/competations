//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=800000+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b){return a>0?a:-a;}

int a[maxn][27];
vector<int> pos[maxn][2];
int cnt;
void insert(char str[],int mark,int k){
	int len=strlen(str),now=0;
	int i;
	REP(i,len){
		if (!a[now][str[i]-'a']) a[now][str[i]-'a']=++cnt;
		now=a[now][str[i]-'a'];
	}
	pos[now][mark].push_back(k);
}
LL all;
vector<pair<int,int> > ans;
bool mark[maxn][2];
queue<int> ret0,ret1;
void dfs(int now,int len){
	int i,j;
	queue<int> S0,S1;
	REP(j,27) if (a[now][j]){
		dfs(a[now][j],len+1);
		while (ret0.size()) S0.push(ret0.front()),ret0.pop();
		while (ret1.size()) S1.push(ret1.front()),ret1.pop();
	}
	for (int t:pos[now][0]) S0.push(t);
	for (int t:pos[now][1]) S1.push(t);
	while (S0.size()&&S1.size()){
//		printf("%d %d----%d\n",S0.top(),S1.top(),len);
		ans.push_back(make_pair(S0.front(),S1.front()));
		mark[S0.front()][0]=1;mark[S1.front()][1]=1;
		all+=len;
		S0.pop();S1.pop();
	}
	while (S0.size()) ret0.push(S0.front()),S0.pop();
	while (S1.size()) ret1.push(S1.front()),S1.pop();
}
int n;
char str[maxn];
int main(){
	scanf("%d",&n);
	int i;
	FOR(i,1,n){
		scanf("%s",str);
		insert(str,0,i);
	}
	FOR(i,1,n){
		scanf("%s",str);
		insert(str,1,i);
	}
	dfs(0,0);
	printf("%lld\n",all);
	REP(i,ans.size())
		printf("%d %d\n",ans[i].first,ans[i].second);
}
