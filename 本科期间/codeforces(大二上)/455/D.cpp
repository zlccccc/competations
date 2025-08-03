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

int n,i,j;
char a[maxn];
vector<int> check,erase; 
int ans;
int suf[maxn],pre[maxn];
bool mark[maxn];
int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	a[0]=a[1];a[n+1]=a[n];
	FOR(i,1,n) check.push_back(i),pre[i]=i-1,suf[i]=i+1;suf[n]=0;
	while (check.size()){
		erase.clear();
		for (int v:check){
			if (!mark[v]&&pre[v]&&a[pre[v]]!=a[v])
				erase.push_back(v),mark[v]=1;
			if (!mark[v]&&suf[v]&&a[suf[v]]!=a[v])
				erase.push_back(v),mark[v]=1;
		}check.clear();
		for (int v:erase){
			suf[pre[v]]=suf[v];
			pre[suf[v]]=pre[v];
		}for (int v:erase){
//			printf("erase %d\n",v);
			if (suf[v]&&!mark[suf[v]]) check.push_back(suf[v]);
			if (pre[v]&&!mark[pre[v]]) check.push_back(pre[v]);
		}if (erase.size()) ans++;
//		for (int v:check) printf("%d ",v);puts("");
	}printf("%d\n",ans);
}
/*
*/
