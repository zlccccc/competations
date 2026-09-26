#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2500+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

int n,m;
char a[maxn],b[maxn];
bool mark1,mark2; 
int i,j;
int main(){
	int T;
	scanf("%d",&T);
    while (T--){
    	scanf("%s%s",a,b);
    	mark1=mark2=0;
    	n=strlen(a);
    	m=strlen(b);
    	i=j=0;
    	REP(i,n){
    		while(b[j+1]=='*') j+=2;
			if (b[j]=='.'||a[i]==b[j]) j++;
    		while(b[j+1]=='*') j+=2;
		}
		if (j>=m) mark1=1;
//		printf("%d-%d  ",j,mark1);
		i=j=0;
		REP(j,m){
			while (i>0&&b[j]=='*'&&a[i]==a[i-1]&&i<n) i++; 
			if (b[j]=='.'||a[i]==b[j]) i++;
		}
		if (i>=n) mark2=1;
//		printf("%d-%d\n",i,mark2);
		if (mark1&&mark2) puts("yes");
		else puts("no");
	}
}
/*
10
dac
d.*a.
adc
....*
aaa
b*
abc
a.*

*/

