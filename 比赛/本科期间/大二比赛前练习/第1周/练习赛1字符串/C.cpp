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

int n;
int i,j,k,t;
bitset<1007> pos[17],ans;
char s[maxn];
int main(){
	scanf("%d",&n);
	REP(i,n){
		scanf("%d",&k);
		REP(j,k){
			scanf("%d",&t);
			pos[t].set(i);
		}
	}
	getchar();
	gets(s);
	int len=strlen(s);
	REP(i,len){
		ans<<=1;
		ans.set(0);
		ans=ans&pos[s[i]-'0'];
		if (ans[n-1]==1){
			char cc=s[i+1];
			s[i+1]='\0';
			puts(s+i-n+1);
			s[i+1]=cc;
		}
	}
}
