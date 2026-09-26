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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=5e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

struct Ptree{
	int next[maxn][10];
	int fail[maxn];
	int cnt[maxn];
	int len[maxn];
	int S[maxn];
	int last;
	int n,tot;
	int newnode(int l){
		memset(next[tot],0,sizeof(next[tot]));
		cnt[tot]=0;
		len[tot]=l;
		return tot++;
	}
	void init(){
		tot=0;
		newnode(0);
		newnode(-1);
		last=n=0;
		S[n]=-1;
		fail[0]=1;
	}
	int getfail(int x){
		while (S[n-len[x]-1]!=S[n]) x=fail[x];
		return x;
	}
	void add(int c){
		c-='a';
		S[++n]=c;
		int cur=getfail(last);
		if (!next[cur][c]){
			int now=newnode(len[cur]+2);
			fail[now]=next[getfail(fail[cur])][c];
			next[cur][c]=now;
		}
		last=next[cur][c];
		cnt[last]++;
	}
	void count(){
		int i;
		rREP(i,tot) cnt[fail[i]]+=cnt[i];
	}
}T;

int n,m;
int i;
char s[maxn];
int ans;
int main(){
	scanf("%s",s);
	int len=strlen(s);
	T.init();
	REP(i,len) T.add(s[i]);
	T.count();
	ans=0;
	rrep(i,2,T.tot) ans=(ans+1ll*T.cnt[i]*(T.cnt[i]-1)/2)%M;
	printf("%d\n",ans);
}
