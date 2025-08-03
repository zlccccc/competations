#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=3e7;
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


LL a,b,c;
string s;
priority_queue<LL> USB,PS2;
LL n,m;
LL i,j,k;
LL sum;
LL val;
LL num;
int main()
{
	scanf("%I64d%I64d%I64d",&a,&b,&c);
	scanf("%I64d",&m);
	REP(i,m){
		cin>>val>>s;
		if (s=="USB") USB.push(-val);
		else PS2.push(-val);
	}
	REP(i,a) if (!USB.empty()){
		num++;
		sum+=-USB.top(); 
		USB.pop();
	}
	REP(i,b) if (!PS2.empty()){
		num++;
		sum+=-PS2.top(); 
		PS2.pop();
	}
	REP(i,c) if (!(USB.empty()&&PS2.empty())) 
	if (PS2.empty()||(!USB.empty()&&-USB.top()<-PS2.top())){
		num++;
		sum+=-USB.top(); 
		USB.pop();
	}
	else{
		num++;
		sum+=-PS2.top(); 
		PS2.pop();
	}
	printf("%I64d %I64d",num,sum);
	return 0;
}
/*
2 0 2
4
5 USB
6 PS/2
3 PS/2
7 PS/2
*/
