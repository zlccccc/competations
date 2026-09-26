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
const LL maxn=5e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
struct node{
	int A[2][2];
	node(int a00=1,int a01=0,int a10=0,int a11=0){
		A[0][0]=a00;
		A[0][1]=a01;
		A[1][0]=a10;
		A[1][1]=a11;
	}
	node operator*(node &A)const{
		node ret;
		ret.A[0][0]=a.A[0][0]*A[0][0]+a.A[0][1]*A[1][0];
		ret.A[0][1]=a.A[0][0]*A[0][1]+a.A[0][1]*A[1][1];
		ret.A[1][0]=a.A[1][0]*A[0][0]+a.A[1][1]*A[1][0];
		ret.A[1][1]=a.A[1][0]*A[0][1]+a.A[1][1]*A[1][1];
		return ret;
	}
};
node pow(node a,node b){
	node ret;
	while (b){
		if (b&1) ret=ret*a;
		a=a*a;
		b>>=1;
	}
	return ret;
}
int ans;
node mul;
int main(){
	scanf("%d",&n);
	node ans;
	ans.A[0][0]=ans.A[0][1]=1;
	ans.A[1][0]=ans.A[1][1]=0;
	mul.A[0][0]=;
	
	while (~scanf("%d%d",&n,&m)){
		
	}
}
/*
*/ 
