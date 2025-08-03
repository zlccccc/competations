#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
string a[N];
string b[N];
bool mark[N];
set<string> s1,s2;
string s,ss;
int i,ii,j,jj,k;
int main(){
	scanf("%d",&n);
	REP(i,n){
        cin>>s>>ss;
        a[i]=s.substr(0,3);
        b[i]=s.substr(0,2)+ss[0];
        if (s1.count(a[i])) s2.insert(a[i]);
        s1.insert(a[i]);
    }
    s1.clear();
    REP(i,n){
        if (!s1.count(b[i])){
            s1.insert(b[i]);
            a[i]=b[i];
        }
        else{
            if (s1.count(a[i])||s2.count(a[i])) {
                puts("NO");
                return 0;
            }
            s1.insert(a[i]);
        }
    }
    puts("YES");
    REP(i,n) cout<<a[i]<<'\n';
}
/*
*/
