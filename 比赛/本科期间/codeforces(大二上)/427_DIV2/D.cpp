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
#define MP make_pair
typedef pair<int,int> pii;
int n;
vector<pii> edge[maxn];
bool mark[maxn];
stack<pii> S;
pii circle[maxn];
int cnt;
void predfs(int x){
	mark[x]=1;
	for (auto y:edge[x]) if (S.empty()||y!=S.top()){
		if (cnt) return;
		if (mark[y.first]){
			while (1){
				circle[++cnt]=S.top();
				if (S.top().first==y.first) break;
				S.pop();
			}circle[++cnt]=MP(x,y.second);
			return;
		}
		S.push(MP(x,y.second));
		predfs(y.first);
		if (cnt) return;
		if (S.size()&&S.top().first==x) S.pop();
	}
}
LL len[maxn],Len[maxn];
LL preans,ans;
void DFS(int x){
	mark[x]=1;
	Len[x]=len[x]=0;
	for(auto y:edge[x]) if (!mark[y.first]){
		DFS(y.first);
		if (Len[x]<len[y.first]+y.second) Len[x]=len[y.first]+y.second;
		if (len[x]<Len[x]) swap(len[x],Len[x]);
	}
	if (len[x]&&Len[x]) preans=max(preans,len[x]+Len[x]);
}
LL pre[maxn],suf[maxn],prelen[maxn],suflen[maxn];
LL maxlen,nowlen;
int main(){
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		edge[u].push_back(MP(v,len));
		edge[v].push_back(MP(u,len));
	}
	predfs(1);
	FOR(i,1,n) mark[i]=0;
	FOR(i,1,cnt) mark[circle[i].first]=1;
	FOR(i,1,cnt) DFS(circle[i].first);
	FOR(i,0,cnt) circle[i].second=circle[i+1].second;swap(circle[cnt].second,circle[0].second);
	maxlen=nowlen=0;
	FOR(i,1,cnt){
		nowlen+=circle[i-1].second;
		LL lenlen=nowlen+len[circle[i].first];
		pre[i]=max(pre[i-1],lenlen);
		prelen[i]=max(prelen[i-1],maxlen+lenlen);
		maxlen=max(maxlen,len[circle[i].first]-nowlen);//add
	}
	maxlen=nowlen=0;
	rFOR(i,1,cnt){
		nowlen+=circle[i].second;
		LL lenlen=nowlen+len[circle[i].first];
		suf[i]=max(suf[i+1],lenlen);
		suflen[i]=max(suflen[i+1],maxlen+lenlen);
		maxlen=max(maxlen,len[circle[i].first]-nowlen);//add
	}
	ans=INFF;
	FOR(i,1,cnt) ans=min(ans,max(pre[i]+suf[i+1],max(prelen[i],suflen[i+1])));
	printf("%I64d\n",max(ans,preans));
}
/*
*/
