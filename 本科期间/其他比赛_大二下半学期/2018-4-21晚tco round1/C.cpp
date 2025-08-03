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
const LL maxn=1e6+7;
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

class Deadfish{
public:
    map<int,int> minimum;
    queue<int> Q;
    int shortestCode(int N){
        Q.push(0);
        minimum[0]=0;
        while (Q.size()){
            auto now=Q.front();Q.pop();
//            printf("now=%d, cnt=%d\n",now,minimum[now]);
            if (now==N) return minimum[now];
            if (!minimum.count(now+1)){
                minimum[now+1]=minimum[now]+1;
                Q.push(now+1);
            }if (!minimum.count(now-1)){
                minimum[now-1]=minimum[now]+1;
                Q.push(now-1);
            }if (now&&300000/now>now&&!minimum.count(now*now)){
                minimum[now*now]=minimum[now]+1;
                Q.push(now*now);
            }string s=to_string(now);
            sort(s.begin(),s.end(),greater<int>());
            int cur=stoi(s);
            if (cur<=300000&&!minimum.count(cur)){
                minimum[cur]=minimum[now]+1;
                Q.push(cur);
            }
        }return 0;
    }
}test;
int main() {
    int i,j,k;
    int T;
    printf("%d\n",test.shortestCode(3));
    printf("%d\n",test.shortestCode(5));
    printf("%d\n",test.shortestCode(15));
    printf("%d\n",test.shortestCode(61));
    printf("%d\n",test.shortestCode(200000));
    return 0;
}
/*
2 2 3 3
+-++++
*/
