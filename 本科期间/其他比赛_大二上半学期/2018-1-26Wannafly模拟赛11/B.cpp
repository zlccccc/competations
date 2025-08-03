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
#include <bitset>
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
const LL M=998244353;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i;
string a[maxn];
vector<pair<int,int> > T[maxn];
int id[maxn],tot;
inline void insert(string str,int ID){
    int len=str.length(),now=0;
    int i;
    REP(i,len){
        int c=str[i]-'a';int NXT=0;
        for (auto x:T[now]) if (x.first==c) NXT=x.second;
        if (NXT==0) T[now].push_back(make_pair(c,++tot)),NXT=tot;
        now=NXT;
    }
    id[now]=ID;
}
struct relation{
    bitset<27> f[27];
};
bool mark[maxn];
int ans;
void dfs(int x,relation A){
    int i,j,k,cnt=0;
    if (id[x]) {mark[id[x]]=1;ans++;return;}
    cnt=T[x].size();
//    printf("x=%d,cnt=%d\n",x,cnt);
    if (cnt==1){
        for (auto now:T[x]) dfs(now.second,A);
    }else{
        vector<pair<int,int> > have;
        for (auto now:T[x]) have.push_back(now);
//        printf("%d\n",have.size());
        for (auto v:have){
            relation next=A;
            for (auto u:have) if (u.first!=v.first) next.f[v.first][u.first]=1;
            REP(i,26)
                REP(j,26) if (next.f[i][j])
                    REP(k,26) if (next.f[j][k]) next.f[i][k]=1;
            bool mark=0;
            REP(i,26) REP(j,26) if (next.f[i][j]&&next.f[j][i]) mark=1;
            if (mark) continue;
            dfs(v.second,next);
        }
    }
}
int main(){
    scanf("%d",&n);
    FOR(i,1,n) cin>>a[i];
    FOR(i,1,n) insert(a[i],i);
    dfs(0,relation());
    cout<<ans<<"\n";
    FOR(i,1,n) if (mark[i]) cout<<a[i]<<"\n";
}
/*
*/
