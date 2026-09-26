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


int nxt[maxn][26],fail[maxn],num[maxn];
int nowpos,maxpos;
int cnt;
queue<int> Q;
void insert(char *str){
	int len=strlen(str),now=0,i;
	REP(i,len){
		int k=str[i]-'a';
		if (!nxt[now][k]) nxt[now][k]=cnt++;
		now=nxt[now][k]; 
	}
	num[now]++;
}
inline void buildAC(){
	fail[0]=-1;
	Q.push(0);
	int i;
	while (Q.size()){
		int x=Q.front();Q.pop();
		REP(i,26) if (nxt[x][i]){
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
inline int match(char *str){
	int len=strlen(str),now=0;
	int i,ret=0;
	REP(i,len){
		int k=str[i]-'a';
		while (now&&!nxt[now][k]) now=fail[now];
		now=nxt[now][k];
		if (now==-1) now=0;
		int tmp=now;
		while (tmp){
			if (num[tmp]==-1) break;
			ret+=num[tmp];
			num[tmp]=-1;
			tmp=fail[tmp];
		}
	}
	return ret;
}
char a[maxn],c[maxn];
int solve(){
	int n;
	int i,j;
	int nowlen=0,maxlen=0;cnt=1;
	scanf("%d",&n);
	REP(i,n){
		scanf("%s",a);
		insert(a);
//		printf("ins:%s\n",a);
		nowlen=strlen(a);
		if (nowlen>maxlen){
			maxlen=nowlen;
			REP(j,nowlen+1) c[j]=a[j];
		}
	}
	buildAC();
	if (match(c)==n) printf("%s\n",c);
	else puts("No");
//	printf("MATCH ::%s : %d\n",c,match(c));
	REP(i,cnt+1) memset(nxt[i],0,sizeof(nxt[i])),fail[i]=num[i]=0;
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
