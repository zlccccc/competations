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
const LL maxn=3e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

int nxt[maxn][27],fail[maxn];
int from[maxn],cnt;
void insert(char str[]){
	int len=strlen(str),now=0,i;
	REP(i,len){
		if (!nxt[now][str[i]-'a']){
			nxt[now][str[i]-'a']=++cnt;
			from[cnt]=now;
		}
		now=nxt[now][str[i]-'a'];
	}
}
void buildAC(){
	fail[0]=-1;
	queue<int> Q;
	Q.push(0);
	int i;
	while (!Q.empty()){
		int x=Q.front();Q.pop();
		REP(i,27) if (nxt[x][i]){
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
int num[maxn],sum[maxn];
LL calc(){
	queue<int> Q;
	int i;
	FOR(i,1,cnt) sum[i]=1;
	memset(num,0,sizeof(num));
	FOR(i,1,cnt) if (fail[i]!=-1) num[fail[i]]++;
	FOR(i,1,cnt) if (num[i]==0) Q.push(i);
	while (Q.size()){
		int t=Q.front();Q.pop();
		sum[fail[t]]+=sum[t];num[fail[t]]--;
		if (num[fail[t]]==0) Q.push(fail[t]);
	}
//	printf("cnt-->%d\n",cnt);
	LL ans=1ll*cnt*cnt;
	FOR(i,1,cnt){
		int p=i,mark=fail[i];
		while (mark) p=from[p],mark=from[mark];
//		printf("%d %d\n",p,sum[p]-1);
		if (fail[i]) ans-=sum[p]-1;
	}
	return ans;
}
char a[10007][37];
void solve(int n){
	cnt=0;
	memset(nxt,0,sizeof(nxt));
	memset(from,0,sizeof(from));
	int i; 
	REP(i,n){
		scanf("%s",&a[i]);
		insert(a[i]);
	}
	buildAC();
	printf("%lld\n",calc());
}
int main(){
	int n;
	while (~scanf("%d",&n)&&n) solve(n);
}
/*
*/
