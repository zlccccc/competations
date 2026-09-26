#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}

struct node{
	LL num,pos,npos,numm;
};
bool cmp(node a,node b){
	return a.pos<b.pos;
}
bool cmp2(node a,node b){
	return a.npos<b.npos;
}
node a[N];
LL b;
LL n,m;
LL i,j;
LL l,r;
LL maxx;
int main()
{
	scanf("%I64d%I64d%I64d",&n,&l,&r);
	REP(i,n) scanf("%I64d",&a[i].num);
	REP(i,n) scanf("%I64d",&a[i].pos);
	REP(i,n) a[i].npos=i;
	sort(a,a+i,cmp);
	maxx=l-a[0].num;
	a[0].numm=l;
	REP(i,n){
		a[i].numm=max(maxx+a[i].num,l);
		maxx=a[i].numm-a[i].num;
		if (a[i].numm>r){
			printf("-1");
			return 0;
		}
		maxx++;
	}
	sort(a,a+i,cmp2);
	REP(i,n) printf("%I64d ",a[i].numm);
}
/*
*/
