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

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

 // "1234567"
vector<string> Str={
    "1110111", // 0
    "0010010", // 1
    "1011101", // 2
    "1011011", // 3
    "0111010", // 4
    "1101011", // 5
    "1101111", // 6
    "1010010", // 7
    "1111111", // 8
    "1111011"  // 9
};

int f[10][10],g[10][10];
void init() {
    REP_(i,10) {
        REP_(j,10) {
            REP_(k,Str[i].size()) {
                if (Str[i][k]=='1'&&Str[j][k]=='0') f[i][j]++;
                if (Str[i][k]=='0'&&Str[j][k]=='1') g[i][j]++;
            }
        }
    }
    REP_(i,10) {
        REP_(j,10) printf("(%d,%d) ",f[i][j],g[i][j]); puts("");
    }
}
int check(string str) {
    int ret=0,cur=0;
    int op=1,start=0;
    for (;start<str.size();start++) {
        char &c=str[start];
        if (c=='+') break;
        if (c=='-') {op=-1; break;}
        cur=cur*10+c-'0';
    } start++;
    ret+=cur; cur=0;
    for (;start<str.size();start++) {
        char &c=str[start];
        if (c=='=') break;
        cur=cur*10+c-'0';
    } start++;
    if (op==1) ret+=cur; else ret-=cur; cur=0;
    for (;start<str.size();start++) {
        char &c=str[start];
        cur=cur*10+c-'0';
    }
    ret-=cur; cur=0;
    return ret;
}
struct node {
    string s;
    int x,y;
    node(string s,int x,int y) :s(s),x(x),y(y) {};
    node(const node &oth) {s=oth.s; x=oth.x; y=oth.y;};
};
int solve() {
    string str; int k;
    vector<node> S[11];
    set<string> solved;
    cin>>str>>k;  // 先修改加减
    S[0].push_back({str,0,0});
    bool res=0;
    int cnt=0;
    FOR_(i,0,10) {
        for (auto &cur:S[i]) {
            cnt++;
            if (solved.count(cur.s)) continue;
            solved.insert(cur.s);
            // cout<<cur.s<<" "<<cur.x<<" "<<cur.y<<" "<<check(cur.s)<<endl;
            if (cur.x==cur.y&&check(cur.s)==0) {
                res=1; break;
            }
            for (int i=0;i<cur.s.size();i++) {
                // printf("i=%d\n",i);
                if ('0'<=cur.s[i]&&cur.s[i]<='9') {
                    int x=cur.s[i]-'0';
                    REP_(y,10) if (x!=y&&cur.x+f[x][y]<=k&&cur.y+g[x][y]<=k) {
                        if (y==0&&(i==0||!('0'<=cur.s[i-1]&&cur.s[i-1]<='9'))) continue;
                        node nxt=cur;
                        // printf("x,y=%d %d\n",x,y);
                        nxt.s[i]=y+'0';
                        nxt.x+=f[x][y]; nxt.y+=g[x][y];
                        if (!solved.count(nxt.s))
                            S[nxt.x+nxt.y].push_back(nxt);
                    }
                } else if (cur.s[i]=='=') continue;
                else if (cur.s[i]=='+') {
                    node nxt=cur;
                    nxt.s[i]='-'; nxt.x++;
                    if (nxt.x<=k&&!solved.count(nxt.s))
                        S[nxt.x+nxt.y].push_back(nxt);
                    // cout<<nxt.s<<" "<<nxt.x<<" "<<nxt.y<<" "<<check(nxt.s)<<endl;
                } else if (cur.s[i]=='-') {
                    node nxt=cur;
                    nxt.s[i]='+'; nxt.y++;
                    if (nxt.y<=k&&!solved.count(nxt.s))
                        S[nxt.x+nxt.y].push_back(nxt);
                }
            }
        }
    }
    printf("cnt=%d\n",cnt);
    if (res) puts("YES");
    else puts("NO");
    return 0;
}
int main() {
    init();
    int T; T=1;
    scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
1
1+1=999
4
*/