#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
typedef pair<long long,long long> pii;
const int MAX=1e5+5;
#define pb push_back
#define mp make_pair
typedef long long ll;
int n;
int bfs(){
	int i,ans=0;
	set<pair<int,int> > S,nxt; S.insert(make_pair(0,0));
	FOR(i,0,100){
		int _nxt=S.size()-14*i*i+6*i; 
		printf("%d : %d(%d)\n",i,(int)_nxt-ans,_nxt+14*i*i-6*i);
		ans=_nxt;
		for (auto now:S){
			nxt.insert(now);
			nxt.insert(make_pair(now.first-2,now.second-1));
			nxt.insert(make_pair(now.first-2,now.second+1));
			nxt.insert(make_pair(now.first-1,now.second-2));
			nxt.insert(make_pair(now.first-1,now.second+2));
			nxt.insert(make_pair(now.first+1,now.second-2));
			nxt.insert(make_pair(now.first+1,now.second+2));
			nxt.insert(make_pair(now.first+2,now.second-1));
			nxt.insert(make_pair(now.first+2,now.second+1));
		} for (auto now:nxt) S.insert(now);
	} return 0;
}
int main() {
	// bfs();
    int _t,T; scanf("%d",&T);
    FOR(_t,1,T) {
    	unsigned long long n;
        scanf("%llu",&n); unsigned long long ans;
        if (n==0) ans=1;
        else if (n==1) ans=9;
        else if (n==2) ans=41;
        else if (n==3) ans=109;
        else if (n==4) ans=205;
        else ans=14*n*n-6*n+5;
        printf("Case #%d: %llu\n",_t,ans);
    }
}
/*
*/
