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

int n;
string A;
string S[]={"algorithm","bitset","cctype","cerrno","clocale","cmath","complex","cstdio","cstdlib","cstring","ctime","deque","exception","fstream","functional","limits","list","map","iomanip","ios","iosfwd","iostream","istream","ostream","queue","set","sstream","stack","stdexcept","streambuf","string","utility","vector","cwchar","cwctype"};
int main() {
    int i,j,k;
    int T,cnt=0;
//    while (cin>>A) cout<<"\""+A.substr(0,A.length()-1)+"\",",cnt++;
//    printf("%d\n",cnt);
//    REP(i,35) cout<<S[i];
    scanf("%d",&T);
    while (T--){
        cin>>A;
        bool mark=0;
        REP(i,35) if (A==S[i]) mark=1;
        if (mark) puts("Qian");
        else puts("Kun");
    }
    return 0;
}
/*
2 2 3 3
+-++++
*/
