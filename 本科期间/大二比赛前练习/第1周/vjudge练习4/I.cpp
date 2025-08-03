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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		b>>=1;
		a=a*a%M;
	}
	return ret;
}
map<int,int> MP;
int cnt;//³åÍ»¸öÊý 
char a[maxn];
LL hsh[maxn];
int m,l,len;
int i,j;
int ans;
int main(){
	while (~scanf("%d%d",&m,&l)){
		scanf("%s",a);
		len=strlen(a);
		REP(i,len) a[i]-='a';
		hsh[0]=0;ans=0;
		REP(i,l){
			hsh[0]=(hsh[0]*29+a[i])%M;
		}
		FOR(i,1,len-l){
			hsh[i]=(hsh[i-1]*29%M+a[i+l-1]-a[i-1]*powMM(29,l)%M+M)%M;
		}
//		REP(i,len-l+1) printf("%d ",hsh[i]);puts("");
		ans=0;
		REP(i,min(l,len-l*m+1)){
			MP.clear();cnt=0;
			for(j=0;j<m;j++){
				if (MP[hsh[i+j*l]]!=0) cnt++;
				MP[hsh[i+j*l]]++;
//				printf("add:%d,cnt=%d\n",i+j*l,cnt);
			}
//			printf("ANS++");
			if (cnt==0) ans++;
			for(;i+j*l<=len-l;j++){
				MP[hsh[i+(j-m)*l]]--;
				if (MP[hsh[i+(j-m)*l]]!=0) cnt--;
//				printf("del:%d,cnt=%d\n",i+(j-m)*l,cnt);
				if (MP[hsh[i+j*l]]!=0) cnt++;
				MP[hsh[i+j*l]]++;
//				printf("add:%d,cnt=%d\n",i+j*l,cnt);
//				printf("ANS++");
				if (cnt==0) ans++;
			}
		}
		printf("%d\n",ans);
	}
}
/*
2 4
aaaaaaaaaa
2 4
aaabaaababa
2 3
abcabdabbacc
*/
