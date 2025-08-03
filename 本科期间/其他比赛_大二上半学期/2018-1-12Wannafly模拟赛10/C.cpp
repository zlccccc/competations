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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct hash{
	int px[maxn],ix[maxn],val[maxn];
	void set(char a[],int n,int p){
		int i;int pinv=powMM(p*1ll,M-2);
		px[0]=ix[0]=1;val[0]=a[0];
		rep(i,1,n) px[i]=1ll*px[i-1]*p%M,ix[i]=1ll*ix[i-1]*pinv%M;
		rep(i,1,n) val[i]=(val[i-1]+1ll*a[i]*px[i])%M;
	}
	int get(int l,int r){
		return 1ll*ix[l-1]*(val[r]-val[l-1]+M)%M;
	}
}HA,RB;
void manacher(char A[],int p[],int len){
	int id=0,mx=0,i;
	rep(i,1,len){
		if (mx>i) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while (A[i+p[i]]==A[i-p[i]]) p[i]++;
		if (p[i]+i>mx) mx=p[i]+i,id=i;
	}
}
int n,i;
int s[maxn];
char a[maxn],b[maxn],A[maxn*2],B[maxn*2];
int PA[maxn*2],PB[maxn*2];//id
int len,ans;
int main(){
	scanf("%d",&n);
	scanf("%s%s",a,b+1);
	a[n]='(';b[0]=')';n++;
	A[len]='+';B[len]='-';len++;
	A[len]='%';B[len]='%';len++;
	REP(i,n){
		A[len]=a[i];B[len]=b[i];len++;
		A[len]='%'; B[len]='%'; len++;
	}A[len]='*';B[len]='/';len++;
	n=len;
	manacher(A,PA,len);
	manacher(B,PB,len);
	HA.set(A,n,19);
	reverse(B,B+n);
	RB.set(B,n,19);
//	REP(i,n) printf("%2d ",i);puts(" <-- i");
//	REP(i,n) printf("%2c ",A[i]);puts(" <-- A");
//	REP(i,n) printf("%2d ",PA[i]);puts("");
//	reverse(B,B+n);
//	REP(i,n) printf("%2c ",B[i]);puts(" <-- B");puts("");
//	reverse(B,B+n);
//	REP(i,n) printf("%2c ",B[i]);puts(" <-- RB");
//	REP(i,n) printf("%2d ",PB[i]);puts("");
	reverse(B,B+n);
	rep(i,1,n){
		//min(i-1-PA[i]+1,n-1-i-PA[i]+1)+1
		//PA和PB的判断相同 (只需一个最大即可)
		PA[i]=max(PA[i],PB[i]);
		int l=0,r=min(i-PA[i],n-1-i-PA[i])+1;//r:not
//		printf("check start    :    %d ; R=%d, PA=%d min(%d,%d)\n",i,r,PA[i],i-PA[i],n-1-i-PA[i]);
		while (l+1<r){
			int mid=(l+r)/2;
			int hash_A=HA.get(i-PA[i]-mid+1,i-PA[i]);
			int hash_B=RB.get(n-(i+PA[i]+mid),n-1-(i+PA[i]));
//			printf("%d - %d (%d) ::  %d - %d (%d)\n",i-PA[i]-mid+1,i-PA[i],hash_A,n-(i+PA[i]+mid),n-1-(i+PA[i]),hash_B);
			if (hash_A==hash_B) l=mid;
			else r=mid;
		}ans=max(ans,PA[i]+l);
//		printf("now=%d\n",PA[i]+l);
	}printf("%d\n",ans-1);
}
/*
8
aaaaaaaa
bbbaabaa
*/
