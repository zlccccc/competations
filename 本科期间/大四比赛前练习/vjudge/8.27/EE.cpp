#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define drep(i, a, b) for (int i = a; i >= b; i--)
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
#define eps 1e-8
using namespace std;

//#define double long double
typedef pair<int, int> pii;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const ll INFF=INF;
/*
#ifdef DEBUG
	freopen("in", "r", stdin);
#endif
 */
//*******************************************************

const int maxn = 10005;

struct P {
	long double x, y; P() {}
	P(double _x, double _y) :
		x(_x), y(_y) {}

	long double distance(const P &b) {
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
} point[maxn];

long double leng[maxn];

const double pi = acos(-1);
long double calc(double x, int n) {
	long double ans = pi * x * x;
	REP(i, 1, n) {
		x = leng[i] - x;
		ans += pi * x * x;
	}
	x=leng[n]-x;
	return ans;
}
void print(double x,int n){
    printf("%.2f\n",x+eps);
    REP(i ,1, n){
        x=leng[i]-x;
        printf("%.2f\n",x+eps);
    }
}
//cons
// 点从0~n-1
// 边从1~n, 第i条边对应(i - 1, i)
int main() {
	int T;
	scanf("%d",&T);
	while (T--) {
		int n; scanf("%d", &n);
		REP(i, 0, n) {
		    double px,py;
            scanf("%lf%lf",&px,&py);
            point[i].x=px;
            point[i].y=py;
//		    scanf("%lf%lf", &point[i].x, &point[i].y);

		}

		rep(i, 1, n) {
			P a = point[i - 1], b = point[i % n];
			leng[i] = a.distance(b);
		}

		long double l = 0, r = min(leng[1], leng[n]);
//        if(n&1)
//		for(int )
		int s = 1; long double res = 0;
		REP(i, 1, n) {
			s *= -1;
			res = leng[i] - res;
			if (s == 1) {
				long double tmpr = min(leng[i], leng[i + 1]);
				l = max(l, -res);
				r = min(r, tmpr - res);
			}
			else {
				long double tmplen = min(leng[i], leng[i + 1]);
				l = max(l, res - tmplen);
				r = min(r, res);
			}
			// printf("%d: %f %f %f %f\n",i,l,r,leng[i],leng[i+1]);
		}

		if (n & 1) {//must
			long double ll = (leng[n] - res) / 2;
			l = max(l,ll);
			r = min(r,ll);
		} else {
			if (abs(leng[n]-res)>eps) {
				puts("IMPOSSIBLE"); continue;
			}
		}
        if (l - eps > r) { puts("IMPOSSIBLE"); continue; }
//        if(n&1){
//            if(l<-eps)puts("IMPO")
//        }
//		if()
//		cout<<l<<" "<<r<<"!!"<<endl;
        int cnt=120;
        long double ans=calc(l, n);
		while (cnt--) {
//			double mid = (l + r) / 2;
			long double midl = l + (r - l) / 3;
			long double midr = r - (r - l) / 3;


//			double ansmid = calc(mid, n);
			long double ansmidl = calc(midl, n);
			long double ansmidr = calc(midr, n);
//			cout<<l<<" "<<r<<" "<<ansmidl<<" "<<ansmidr<<endl;
			if(ansmidl<ansmidr)
                r=midr,ans=min(ans,ansmidl);
			else l=midl,ans=min(ans,ansmidr);
		}
        printf("%.2f\n",(double)ans+eps);
        print(l,n);
	}
}
/*
3
4
0 0
11 0
27 12
5 12
5
0 0
7 0
7 3
3 6
0 6
5
0 0
1 0
6 12
3 16
0 12
*/