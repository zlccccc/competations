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
const LL maxn=500+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
int T;
int n;
void read(bitset<1007> &S){
	char s[maxn];
	int num[maxn],len,i,j;
	scanf("%s",s);
	len=strlen(s);
	memset(num,0,sizeof(num));
	REP(i,len) num[i]=s[i]-'0';
	i=len-1;num[len-1]--;
	while (num[i]<0){
		num[i]+=10;
		num[i-1]--;
		i--;
	}
	S=0;
	REP(i,n){
//		printf("%d ",num[len-1]);
		if (num[len-1]%2==1) S[i]=1;
		else S[i]=0;
		REP(j,len){
			if (num[j]%2==1) num[j+1]+=10;
			num[j]=num[j]/2;
		}
	}
//	rREP(i,n) printf("%d",(int)S[i]);puts("");
}
bitset<1007> a,b,X,Y;
bool solve(){
	scanf("%d",&n);
	read(X);read(a);read(Y);read(b);
	int i,j;
//		printf("a:");rREP(j,n) printf("%d",(int)a[j]);puts("");
//		printf("b:");rREP(j,n) printf("%d",(int)b[j]);puts("");
//		printf("X:");rREP(j,n) printf("%d",(int)X[j]);puts("");
//		printf("Y:");rREP(j,n) printf("%d",(int)Y[j]);puts("");
	REP(i,n+1){
		bool ok=1;
//		REP(j,n) if ((a[j]^X[j])!=(b[j]^Y[j])){
//			ok=0;
//			break;
//		}
		if ((a^X)==(b^Y)) return 1;
//		if (ok) return 1;
		a[n]=a[0]^b[0];
		a>>=1;b>>=1;
	}
	return 0;
}
int main(){
	int x=0;
	scanf("%d",&T);
	while (T--){
		if (solve()) printf("Case %d: Yes\n",++x);
		else printf("Case %d: No\n",++x);
	}
}
/*
10
16 8161 31994 15230 13612
*/ 
