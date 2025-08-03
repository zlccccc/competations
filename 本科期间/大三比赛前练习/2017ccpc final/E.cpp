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
int main() {
    int _t,T; scanf("%d",&T);
    FOR(_t,1,T) {
        scanf("%d",&n);
        int ans=0,x,i;
        FOR(i,1,n) scanf("%d",&x),ans+=x+(x+9)/10;
        printf("Case #%d: %d\n",_t,ans);
    }
}
/*
2
3 10 5
3 4
3 5
3 6
3 10 4
-7 -6
4 5
5 4
*/