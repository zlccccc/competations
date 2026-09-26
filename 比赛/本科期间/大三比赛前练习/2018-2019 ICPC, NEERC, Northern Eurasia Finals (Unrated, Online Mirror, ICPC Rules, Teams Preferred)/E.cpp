#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
const int inf=0x3f3f3f3f;
const int maxn=1e5+7;
typedef long long ll;

vector<string> ans;
int main(){
	int n,i;
	char x,y; x=y=0;
	scanf("%d",&n);
	if (n==63) 
		return 0*puts("a1 a2 a3 a4 a5 a6 a7 a8 b8 b7 b6 b5 b4 b3 b2 b1 c1 c2 c3 c4 c5 c6 c7 c8 d8 d7 d6 d5 d4 d3 d2 d1 e1 e2 e3 e4 e5 e6 e7 e8 f8 f7 f6 f5 f4 f3 f2 f1 g1 g2 g3 g4 g5 g6 g8 g7 h7 h6 h5 h4 h3 h2 h1 h8");
	FOR(i,0,n){
		if ((x==7||y==7)&&n-i==1){
			string s=""; s+=(x+'a'); s+=(y+'1');
			ans.push_back(s);
			ans.push_back("h8");
			break;
		} else if (x!=7&&y!=7&&n-i==2) {
			string s=""; s+=(x+'a'); s+=(y+'1');
			ans.push_back(s);
			x=7;
			s=""; s+=(x+'a'); s+=(y+'1');
			ans.push_back(s);
			ans.push_back("h8");
			break;
		} string s=""; s+=(x+'a'); s+=(y+'1');
		ans.push_back(s);
		// cout<<s<<"\n";
		if (!(x&1)) {if ((y<7&&x<6)||(x==6&&y<6)) y++; else x++;}
		else {if (y!=0) y--; else x++;}
	}
	if (*ans.rbegin()=="h8"){
		for (string now:ans) cout<<now<<" ";
		return 0;
	}
	ans.clear(); x=y=0;
	FOR(i,0,n){
		if ((x==7||y==7)&&n-i==1){
			string s=""; s+=(x+'a'); s+=(y+'1');
			ans.push_back(s);
			ans.push_back("h8");
			break;
		} else if (x!=7&&y!=7&&n-i==2) {
			string s=""; s+=(x+'a'); s+=(y+'1');
			ans.push_back(s);
			x=7;
			s=""; s+=(x+'a'); s+=(y+'1');
			ans.push_back(s);
			ans.push_back("h8");
			break;
		} string s=""; s+=(x+'a'); s+=(y+'1');
		ans.push_back(s);
		// cout<<s<<"\n";
		if (!(x&1)) {if (y<6) y++; else x++;}
		else {if (y!=0) y--; else x++;}
	}
	if (*ans.rbegin()=="h8"){
		for (string now:ans) cout<<now<<" ";
		return 0;
	}
}

