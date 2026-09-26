#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
 
#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=3e5+107;
 
int A[maxn];
vector<int> H;
map<int,int> Count;
vector<int> B[maxn];
set<int> Used;
map<int,vector<int> > Remove;
int getid(int x) {return lower_bound(H.begin(),H.end(),x)-H.begin();}
bool mark[maxn];//could not use
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        for (int v:Used) B[v].clear();
        Used.clear(); H.clear();
        Remove.clear(); Count.clear();
        int n,m,i;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%d",&A[i]),Count[A[i]]++,H.push_back(A[i]);
        sort(H.begin(),H.end());
        H.erase(unique(H.begin(),H.end()),H.end());
        FOR(i,1,m) {
            int x,y;
            scanf("%d%d",&x,&y);
            Remove[x].push_back(y);
            Remove[y].push_back(x);
        }
        for (auto now:Count) {
            Remove[now.first].push_back(now.first);
            B[now.second].push_back(now.first);
            Used.insert(now.second);
        }
        for (int v:Used) {
            sort(B[v].begin(),B[v].end());
            int t; REP(t,(int)B[v].size()) B[v][t]=getid(B[v][t]);
            reverse(B[v].begin(),B[v].end());
        }
        ll ans=0;
        for (auto now:Count) {
            for (int k:Remove[now.first]) mark[getid(k)]=1;
            for (int v:Used) {
                for (int t:B[v]) 
                    if (!mark[t]) {
                        // printf("chk %d %d %d %d\n",now.first,now.second,H[t],v);
                        ans=max(ans,(ll)(v+now.second)*(H[t]+now.first));
                        break;
                    }
            }
            for (int k:Remove[now.first]) mark[getid(k)]=0;
        }
        printf("%lld\n",ans);
    }
}
/*
//swap A and B
*/

