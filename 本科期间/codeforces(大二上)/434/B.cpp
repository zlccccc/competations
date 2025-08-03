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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char a[maxn][20];
int n,cnt;
char pre;
bool mark;
int nxt[maxn][20];
int num[maxn];
void insert(char *str,int ii){
//	printf("ins:%s\n",str);
	int len=strlen(str),now=0,i;
	REP(i,len){
		int k=str[i]-'0';
		if (!nxt[now][k]) nxt[now][k]=++cnt;
		now=nxt[now][k];
		if (!num[now]) num[now]=ii;
		else if (num[now]!=ii) num[now]=INF;
	}
}
int stpos,stlen;
void check(char *str,int ii,int pos){
	int len=strlen(str),now=0,i;
	REP(i,len){
		int k=str[i]-'0';
		now=nxt[now][k];
		if (num[now]==ii){
			if (i+1<stlen) stpos=pos,stlen=i+1;
			return;
		}
	}
}
int main(){
	int n,i,j;
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%s",a[i]);
		REP(j,9) insert(a[i]+j,i);
	}
	FOR(i,1,n){
		stlen=10;stpos=0;
		REP(j,9) check(a[i]+j,i,j);
//		printf("%d,%d\n",stpos,stlen);
		REP(j,stlen) putchar(a[i][stpos+j]);puts("");
	}
}
/*
*/
