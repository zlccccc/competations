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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char s[maxn]; 
int n,m;
int T;
char s1[]="AlvinZH",a1[]="hg, shg, awsl!";
char s2[]="ModricWang",a2[]="1080Ti!, wyr, silver!!!";
char s3[]="Bamboo",a3[]="this is 51's father";
char s4[]="ConnorZhong",a4[]="I am so weak";
char s5[]="BCPC",a5[]="I want to join in!";
void check(char *str,char *s,char *a){
	int len=strlen(s),i;
	REP(i,len) if (str[i]!=s[i]) return;
	printf("%s\n",a);
}
int main(){
	scanf("%d",&n);
	scanf("%s",s);
	int len=strlen(s);
	int i;
	REP(i,len){
		check(s+i,s1,a1);
		check(s+i,s2,a2);
		check(s+i,s3,a3);
		check(s+i,s4,a4);
		check(s+i,s5,a5);
	}
}
/*
*/
