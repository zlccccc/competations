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
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=3e5+7;
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
int n,m,T;
int i,j;
char a[107][107];
string s;
int ans;
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		s="";
		FOR(i,1,n) scanf("%s",a[i]+1);
		FOR(i,1,n-1) if (a[1][i]!='.') s+=a[1][i];
		FOR(i,1,n-1) if (a[i][n]!='.') s+=a[i][n];
		FOR(i,1,n-1) if (a[n][n-i+1]!='.') s+=a[n][n-i+1];
		FOR(i,1,n-1) if (a[n-i+1][1]!='.') s+=a[n-i+1][1];
		if (s!="1122"&&s!="1221"&&s!="2211"&&s!="2112") puts("-1");
		else{
			int ans;
			int x1=0,x2=0,y1=0,y2=0;
			FOR(i,1,n){
				FOR(j,1,n) if (a[i][j]=='1'){
					if (x1==0) x1=i;
					else x2=i;
					if (y1==0) y1=j;
					else y2=j;
				}
			}
			int x3=0,x4=0,y3=0,y4=0;
			FOR(i,1,n){
				FOR(j,1,n) if (a[i][j]=='2'){
					if (x3==0) x3=i;
					else x4=i;
					if (y3==0) y3=j;
					else y4=j;
				}
			}
//			printf("%d %d %d %d\n",x1,y1,x2,y2);
//			printf("%d %d %d %d\n",x3,y3,x4,y4);
			ans=abs(x1-x2)+abs(x3-x4)+abs(y1-y2)+abs(y3-y4)+2;
			if (x1==x2&&x2==x3&&x3==x4&&(s=="1221"||s=="2112")) ans+=2;
			if (y1==y2&&y2==y3&&y3==y4&&(s=="1221"||s=="2112")) ans+=2;
			printf("%d\n",ans);
		}
	}
}
/*
*/ 
