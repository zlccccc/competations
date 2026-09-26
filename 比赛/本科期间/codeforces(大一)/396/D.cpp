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


int n,m,q;
int f[N];
int opp[N];
int i,j,k;
string s,s1,s2;
int t;
map<string,int> pos;
void Union(int,int);
int getfather(int);
int relation(int,int);
int i1,i2;
bool mark;
int main()
{
	cin>>n>>m>>q;
	FOR(i,n){
		cin>>s;
		pos.insert(pair<string,int>(s,i));
		f[i]=i;
		f[i+n]=i+n;
	}
	REP(i,m){
		mark=false;
		cin>>k>>s1>>s2;
		i1=pos[s1]; i2=pos[s2];
/*
		getfather(i1); getfather(i2);
		FOR(j,2*n) printf("%d ",f[j]);
		printf("\n");
		FOR(j,2*n) printf("%d ",opp[j]);
		printf("\n");
*/
		t=relation(i1,i2);
		if (k==1&&t==2) printf("NO\n");
		else if (k==2&&t==1) printf("NO\n");
		else if (k==2&&t==2) printf("YES\n");
		else if (k==1&&t==1) printf("YES\n");
		else {
			printf("YES\n");
			if (k==1){
				Union(i1,i2);
				Union(i1+n,i2+n);
			}
			else {
				Union(i1,i2+n);
				Union(i2,i1+n);
			}
		}
	}
	REP(i,q){
		cin>>s1>>s2;
		cout<<relation(pos[s1],pos[s2])<<'\n';
	}
}
int getfather(int i1){
	if (f[i1]==i1) return i1;
	return f[i1]=getfather(f[i1]);
}
int relation(int i1,int i2){
	int ii1=getfather(i1),ii2=getfather(i2);
	int ii3=getfather(i1+n),ii4=getfather(i2+n);
	if (ii1==ii2) return 1;
	if (ii1==ii4||ii2==ii3) return 2;
	return 3;
}
void Union(int i1,int i2){
	int ii1=getfather(i1),ii2=getfather(i2);
	f[ii1]=ii2;
}
/*
3 3 4
hate love like
1 love like
2 love hate
1 hate like
love like
love hate
like hate
hate like
8 6 5
hi welcome hello ihateyou goaway dog cat rat
1 hi welcome
1 ihateyou goaway
2 hello ihateyou
2 hi goaway
2 hi hello
1 hi hello
dog cat
dog hi
hi hello
ihateyou goaway
welcome ihateyou
*/
