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

char s[]="What are you doing at the end of the world? Are you busy? Will you save us?";
char a[]="What are you doing while sending \"";
char b[]="\"? Are you busy? Will you send \"";
char c[]="\"?";
LL len[maxn];
LL lens,lena,lenb,lenc;
char solve(LL x,LL pos){
	if (len[x]<pos) return '.';
	if (x==0) return s[pos-1];
	if (pos<=lena) return a[pos-1]; 
	pos-=lena;
	if (pos<=len[x-1]) return solve(x-1,pos);
	pos-=len[x-1];
	if (pos<=lenb) return b[pos-1];
	pos-=lenb;
	if (pos<=len[x-1]) return solve(x-1,pos);
	pos-=len[x-1];
	if (pos<=lenc) return c[pos-1];
	return '.';
}
LL n,k;
int T;
int main(){
	int i;
	lens=strlen(s);lena=strlen(a);
	lenb=strlen(b);lenc=strlen(c);
	len[0]=lens;
	FOR(i,1,200000) len[i]=min((LL)2e18,lena+lenb+lenc+2*len[i-1]);
//	FOR(i,1,1000) printf("%d-%lld\n",i,len[i]);
//	FOR(i,1,1000) printf("%c",solve(2,i));
	scanf("%d",&T);
	while (T--){
		scanf("%I64d%I64d",&n,&k);
		printf("%c",solve(n,k));
	}
}
/*
*/
