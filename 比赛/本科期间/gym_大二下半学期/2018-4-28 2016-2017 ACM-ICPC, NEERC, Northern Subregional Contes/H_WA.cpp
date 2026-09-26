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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct node{
    int x,y,l;
    node(int _x,int _y,int _l):x(_x),y(_y),l(_l){};
};
int n,m,q;
vector<node> have[67][67];
void init(){
    int i,j,k;
    FOR(i,1,60) {
        have[i][i].push_back(node(0,0,i));
        FOR(j,i+1,60){
            FOR(k,0,j){
                if (!have[i][j].size()||have[i][k].size()+have[i][j-k].size()<have[i][j].size()){
                    have[i][j].clear();
                    for (auto now:have[i][k]) have[i][j].push_back(now);
                    for (auto now:have[i][j-k]){
                        now.y+=k;
                        have[i][j].push_back(now);
                    }
                }
            }
            FOR(k,0,i){
                if (!have[i][j].size()||have[k][j].size()+have[i-k][j].size()<have[i][j].size()){
                    have[i][j].clear();
                    for (auto now:have[k][j]) have[i][j].push_back(now);
                    for (auto now:have[i-k][j]){
                        now.x+=k;
                        have[i][j].push_back(now);
                    }
                }
            }
            for (auto now:have[i][j]) {
                swap(now.x,now.y);
                have[j][i].push_back(now);
            }
        }
    }
}
int main() {
    int i,j,T;
    int w,h;
    freopen("hard.in","r",stdin);
    freopen("hard.out","w",stdout);
    init();
//    FOR(i,1,6)
//        FOR(j,1,6){
//            cerr<<i<<" "<<j<<"\n";
//            cerr<<"size="<<have[i][j].size()<<"\n";
//            for (auto now:have[i][j])
//                cerr<<now.x<<" "<<now.y<<" "<<now.l<<"\n";
//            cerr<<"\n";
//        }

    scanf("%d",&T);
    while (T--){
        int w,h;
        scanf("%d%d",&n,&m);
        printf("%d\n",have[n][m].size());
        for (auto now:have[n][m])
            printf("%d %d %d\n",now.x,now.y,now.l);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/
