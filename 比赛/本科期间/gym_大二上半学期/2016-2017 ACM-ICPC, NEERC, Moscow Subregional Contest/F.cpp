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
const double eps=2e-3;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char nxt[maxn];
string solve(char *a,int len){
	string ret;
	if (len==0) return "!";
	int i=0,j;
	while(i<len){
		j=i;
		while (j+1<len&&nxt[a[j]]==a[j+1]) j++;
		if (j-i>=2){
			if (a[i]=='0') ret+='!';
			else if (a[i]=='A') ret+=':';
			else if (a[i]=='a') ret+='[';
			else ret+=a[i];
			ret+='-';
			ret+=a[j];
		}else{
			ret+=a[i];
			if (i!=j) ret+=a[j];
		}i=j+1;
//		cout<<ret<<"\n";
	}
	return ret;
}
int m,i,j,k;
char a[maxn],b[maxn];
char c[maxn],S[maxn];
int len,tot;
int main(){
	c[tot++]=' ';
	FOR(i,'0','9') c[tot++]=i;
	FOR(i,'A','Z') c[tot++]=i;
	FOR(i,'a','z') c[tot++]=i;
	REP(i,tot) nxt[c[i]]=c[i+1];
	gets(a);
	int len=strlen(a);
	sort(a,a+len);
	len=unique(a,a+len)-a;
	string A="%["+solve(a,len)+"]";
	i=0;j=0;len=0;
	REP(i,tot){
		if (a[j]==c[i]) j++;
		else b[len++]=c[i];
	}
//	printf("A:%s\nB:%s\n",a,b);
	string B="%[^"+solve(b,len)+"]";
//	cout<<A<<";"<<B<<"\n";
	if (B=="%[^]") cout<<A;
	else if (A=="%[]") cout<<B;
	else if (A.length()<B.length()) cout<<A;
	else if (A.length()>B.length()) cout<<B;
	else if (A<B) cout<<A;
	else cout<<B;
}
/*

*/
