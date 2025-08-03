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
const LL maxn=1e7+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int nxt[maxn][2],fail[maxn],mark[maxn];
int S[807],T[807];
int E[807][807];
int pos[maxn];
int cnt,tot;
queue<int> Q;
void insert(char *str,int id){
	int now=0,len=strlen(str),i;
	S[id]=tot;
	REP(i,len){
		int k=str[i]-'a';
		if (!nxt[now][k]) nxt[now][k]=++cnt;
		now=nxt[now][k];
		pos[tot++]=now;
	}
	if (mark[now]) E[id][mark[now]]=1;
	mark[now]=id;
	T[id]=tot;
}
int F[maxn];//pre
void buildAC(){
	fail[0]=-1;
	Q.push(0);
	int i;
	while (Q.size()){
		int x=Q.front();Q.pop();
		if (fail[x]==-1||fail[x]==0||mark[fail[x]]) F[x]=fail[x];
		else F[x]=F[fail[x]];
		REP(i,2) if (nxt[x][i]){
			if (x==0) fail[nxt[x][i]]=0;
			else{
				int p=fail[x];
				while (p!=-1&&!nxt[p][i]) p=fail[p];
				if (p!=-1) fail[nxt[x][i]]=nxt[p][i];
				else fail[nxt[x][i]]=0;
			}
			Q.push(nxt[x][i]);
		}
	}
}
int match[1607];
bool used[1607];
vector<int> edge[1607];
bool dfs(int u){
	for (int v:edge[u]){
		if (!used[v]){
			used[v]=1;
			if (!match[v]||dfs(match[v])){
				match[v]=u;
				match[u]=v;
				return 1;
			}
		}
	}
	return 0;
}
bool use[1607],tag[1607];
void check(int u){
	if (use[u]) return;
	use[u]=1;
	for (int v:edge[u]) if (!use[v]){
		use[v]=1;
		check(match[v]);
	}
}
int n,m;
int i,j,k;
char a[maxn];
int ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%s",a);
		insert(a,i);
	}
	buildAC();
	FOR(i,1,n){
		rep(j,S[i],T[i]){
			for (k=pos[j];F[k]!=-1;k=F[k]){
				if (mark[k]!=0){
					if (E[i][mark[k]]) break;
					E[i][mark[k]]=1;
				}
			}
		}
	}
	FOR(k,1,n)
		FOR(i,1,n)
			FOR(j,1,n) E[i][j]|=E[i][k]&&E[k][j];
	FOR(i,1,n) E[i][i]=0;
	FOR(i,1,n){
		FOR(j,1,n) if (E[i][j]){
			edge[i].push_back(j+n);
			edge[j+n].push_back(i);
		}
	}
	ans=n;
	FOR(i,1,n) if (!match[i]){
		memset(used,0,sizeof(used));
		if (dfs(i)) ans--;
		else tag[i]=1;
	}
	printf("%d\n",ans);
	FOR(i,1,n) if (tag[i]) check(i);
//	FOR(i,1,n) printf("%2d ",match[i]);puts("");
//	FOR(i,1,n) printf("%2d ",match[i+n]);puts("");
//	FOR(i,1,n*2) printf("%d",use[i]);puts(""); 
	FOR(i,1,n) if (use[i]&&!use[i+n]) printf("%d ",i);
}
/*
*/
