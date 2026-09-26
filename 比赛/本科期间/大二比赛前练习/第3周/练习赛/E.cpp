#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=500+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int nxt[maxn];
int cnt[maxn];
int Len[maxn];
void makenxt(char *a,int len){
	int i,j;
	nxt[0]=-1;
	Len[0]=0;
	FOR(i,1,len-1){
		j=nxt[i-1];
		while(j>=0&&(a[j+1]!=a[i])) j=nxt[j];
		if (a[i]==a[j+1]) nxt[i]=j+1,cnt[j+1]++;
		else nxt[i]=-1;
	}
}
bool kmp(char *s,char *a,int n,int m){
	int i,j=-1;
	REP(i,n){
		while (j>=0&&a[j+1]!=s[i]) j=nxt[j];
		if (s[i]==a[j+1]) j++;
		if (j==m-1) return 1;
	}
	return 0;
}
int i,T,len;
char a[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
		scanf("%s",a);
		len=strlen(a);
		makenxt(a,len);
		rREP(i,len) cnt[nxt[i]]+=cnt[i];
		i=len-1;
		int ans=0;
		while (i!=-1){
			i=nxt[i];
			int t=i+1;
			if (t*3<=len&&kmp(a+t,a,len-t*2,t)){
				ans=t;
				break;
			}
		}
		printf("%d\n",ans);
    }
    return 0;
}
/*
6
xy
abc
aaa
aaaaba
aaaaaa
aaxoaaaaa
*/
