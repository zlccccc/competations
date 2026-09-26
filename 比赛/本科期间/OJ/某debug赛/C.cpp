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
const LL maxn=1e5+7;
const double eps=0.000000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int score;
char a[100][100]={
"============",
"|          |",
"|          |",
"|          |",
"|          |",
"|          |",
"|          |",
"|          |",
"|          |",
"|          |",
"|          |",
"============"
};
int _x,_y;
void print(){
	if (a[_x][_y]=='*') {a[_x][_y]=' ';score++;}
	a[_x][_y]='M';
	printf("score:%d\n",score);
	int i;
	REP(i,12) printf("%s\n",a[i]);
	puts("");
	a[_x][_y]=' ';
}
int main(){
	scanf("%d%d",&_x,&_y);
	_x++;_y++;
	int T;
	scanf("%d",&T);
	print();
	char s[10];
	while (T--){
		scanf("%s",s);
		if (s[0]=='f'){
			int xx,yy;
			scanf("%d%d",&xx,&yy);
			xx++;yy++;
			if (xx>=1&&xx<=10&&yy>=1&&yy<=10&&a[xx][yy]!='*') a[xx][yy]='*';
		}else{
			int __x=_x,__y=_y;
			if (s[0]=='w') __x=_x-1,__y=_y;
			if (s[0]=='a') __x=_x,__y=_y-1;
			if (s[0]=='s') __x=_x+1,__y=_y;
			if (s[0]=='d') __x=_x,__y=_y+1;
			if (__x>=1&&__x<=10&&__y>=1&&__y<=10) _x=__x,_y=__y;
			print();
		}
	}
}
/*
*/
