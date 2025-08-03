#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue> 
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
vector<int>a[N];
char s[N]; 
int i,j,k;
bool mark;
int main(){
	cin>>n;
	REP(i,n){
		scanf("%s",&s);
		a[i].push_back(0);
		for (j=0;s[j]!='\0';j++) {a[i][0]++; a[i].push_back(s[j]);}
	}
	rREP(i,n-1){
		k=1; mark=0;
		for (k=1;k<=a[i+1][0]&&k<=a[i][0]&&a[i+1][k]>=a[i][k];k++){
			if (a[i+1][k]>a[i][k]) {mark=1; break;}
		}
		if (mark) continue;
		a[i][0]=k-1;
	}
	REP(i,n){
		FOR(j,1,a[i][0]) printf("%c",a[i][j]);
		puts("");
	}
}
/*
*/
