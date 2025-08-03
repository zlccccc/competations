#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
const int MAX=105;
const double eps=1e-6;
const double pi=acos(-1);
int sgn(double x){
    if(fabs(x)<eps)return 0;
    if(x<0)return -1;
    return 1;
}
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    double dis(Point z){
        return hypot(x-z.x,y-z.y);
    }
};
struct circle{
    Point p;
    double r;
    circle(){}
    circle(Point _p,double _r){
        p=_p;r=_r;
    }
    circle(double x,double y,double _r){
        p=Point(x,y);r=_r;
    }
    int relationcircle(circle v){
        double d=p.dis(v.p);
        if(sgn(d-r-v.r)>0)return 5;
        if(sgn(d-r-v.r)==0)return 4;
        double l=fabs(r-v.r);
        if(sgn(d-r-v.r)<0&&sgn(d-l)>0)return 3;
        if(sgn(d-l)==0)return 2;
        if(sgn(d-l)<0)return 1;
    }
    double areacircle(circle v){
        int rel=relationcircle(v);
        if(rel>=4)return 0.0;
        else if(rel<=2)return min(v.r*v.r*pi,r*r*pi);
        double d=p.dis(v.p);
        double hf=(r+v.r+d)/2.0;
        double ss=2*sqrt(hf*(hf-r)*(hf-v.r)*(hf-d));
        double a1=acos((r*r+d*d-v.r*v.r)/(2.0*r*d));
        a1=a1*r*r;
        double a2=acos((v.r*v.r+d*d-r*r)/(2.0*v.r*d));
        a2=a2*v.r*v.r;
        return a1+a2-ss;
    }
};
int t;
int n,R,r;
int dis;
struct node{
    int x,y,id;
    double dis;
    bool operator<(const node &z)const{
        return dis>z.dis;
    }
}a[MAX];
bool cmp(node a,node b){
    return a.id<b.id;
}
int lim,cnt;
vector<node>an;
#define pb push_back
int main(){
    scanf("%d",&t);
    while(t--){

        an.clear();
        scanf("%d%d%d",&n,&R,&r);
        circle tem=circle(0,0,R-r);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i].x,&a[i].y);a[i].id=i;
            circle z=circle(a[i].x,a[i].y,r);
            a[i].dis=z.areacircle(tem);
            //a[i].dis=a[i].x*a[i].x+a[i].y*a[i].y;
        }
        sort(a+1,a+1+n);
        //if(R<2*r||(a[1].dis>=lim)){
            an.pb(a[1]);
            for(int i=2;i<=n&&abs(a[i].dis-a[1].dis)<eps;i++)an.pb(a[i]);
            sort(an.begin(),an.end(),cmp);
        //}
//        else{
//            int cnt=0;
//            for(int i=1;i<=n;i++){
//                if(a[i].dis>lim)break;
//                an.pb(a[i]);
//            }
//            sort(an.begin(),an.end(),cmp);
//        }
        bool st=0;
        printf("%d\n",an.size());
        for(node u:an){
            if(st)printf(" ");
            //cout<<"!"<<u.dis<<endl;
            printf("%d",u.id);st=1;
        }
        printf("\n");

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

1
1
5 5
10 10

3
3 5 5
3 4
-4 3
2 1

4 6 6
3 4
-4 3
1 5
-3 4
*/
