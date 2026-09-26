#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e6;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline double min(double a,double b) {return a>b?b:a;}
inline int max(int a,int b) {return a<b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline double max(double a,double b) {return a<b?b:a;}
inline int abs(int a,int b) {return a>0?a:-a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}



LL n,m;
LL a[256];
string s;
LL num[N];
LL num2[N];
LL maxsub;
LL i,j,k;
LL p1,p2,p3;
int main()
{
	cin>>n;
	cin>>s;
	REP(i,26) scanf("%I64d",&a['a'+i]);
	p2=1;
	REP(i,n){
		j=i;maxsub=a[s[i]];
		num2[i]=INF;
		while(j>=0){
			maxsub=min(maxsub,a[s[j]]);
			if (i-j+1>maxsub) break;
//			cout<<j<<" /"<<maxsub<<"/   ";
			if (j>0) {num[i]=(num[i]+num[j-1])%M; num2[i]=min(num2[i],num2[j-1]+1);}
			else {num[i]++; num2[i]=1;}
			p2=max(i-j+1,p2);
			j--;
		}
//		cout<<num[i]<<"\n";
	}
	p1=num[n-1];
	p3=num2[n-1];
	printf("%I64d\n%I64d\n%I64d\n",p1,p2,p3);
}
/*
*/
