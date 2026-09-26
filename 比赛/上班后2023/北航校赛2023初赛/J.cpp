// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

void check(string s,vector<pair<string,string>> vec, bool out=false) {
    string inis=s;
    for (auto &p:vec) {
        int x=s.find(p.first);
        while (x!=s.npos) {
            s.replace(x,p.first.size(),p.second);
            x=s.find(p.first);
        }
        if (out) cout<<s<<endl;
    }
    if (out) exit(0);
    set<char> S;
    for (char c:inis) S.insert(c);
    if (s.size()!=1||s[0]-'0'!=S.size()) {
        cout<<inis<<" "<<s<<"\n";
        check(inis,vec,true);
    }
    // cout<<inis<<" "<<s<<endl;
}

int main() {
    vector<pair<string,string>> vec;
        vec.push_back({"ba","ab"});
        vec.push_back({"ca","ac"});
        vec.push_back({"cb","bc"});

        vec.push_back({"aa","a"});
        vec.push_back({"bb","b"});
        vec.push_back({"cc","c"});

    vec.push_back({"abc","3"});
    // vec.push_back({"cab","3"});
    vec.push_back({"bac","3"});
    vec.push_back({"bca","3"});
    // vec.push_back({"cba","3"});
    // vec.push_back({"acb","3"});

        vec.push_back({"a","1"});
        vec.push_back({"b","1"});
        vec.push_back({"c","1"});

    vec.push_back({"33","3"});
    vec.push_back({"13","3"});
    vec.push_back({"31","3"});

        vec.push_back({"11","2"});


    cout<<vec.size()<<endl;
    for (auto &p:vec) cout<<"replace(\""<<p.first<<"\","<<"\""<<p.second<<"\")"<<endl;

    // for (int l=1;l<=10;l++) {
    //     for (int i=0;i<pow(3,l);i++) {
    //         string str;
    //         for (int k=0,t=i;k<l;k++) str+='a'+t%3,t/=3;
    //         check(str,vec);
    //     }
    // }
    return 0;
}
/*
*/