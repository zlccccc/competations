
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
//加权不同子串个数;//START 

char a[maxn],b[maxn];
int cnt[maxn];
int i,j,n,m;
int len1,len2;
int toL,toR,ans;
int main(){
	scanf("%s%s",a,b);
	len1=strlen(a),len2=strlen(b);
	toL=toR=ans=1;
	REP(i,len2){
		if (b[i]=='U'){
			if (len1){
				ans++;
				if (a[--len1]=='L') toR++;
				else toL++;
			}
		}else if (b[i]=='L'){
			ans=(ans+toL)%M;
			toR=(toR+toL)%M;
		}else{
			ans=(ans+toR)%M;
			toL=(toR+toL)%M;
		}
	}
	printf("%d\n",ans);
}
/*
16->10000
*/
