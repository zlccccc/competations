    #include <cstdio>  
    #include <cstring>  
    #include <algorithm>  
    #include <vector>
    #include <cmath>
    using namespace std;  
      
    /***********����*************/  
      
    const double EPS=0.000001;  
      
    typedef struct Point_3D {  
        double x, y, z;  
        Point_3D(double xx = 0, double yy = 0, double zz = 0): x(xx), y(yy), z(zz) {}  
      
        bool operator == (const Point_3D& A) const {  
            return x==A.x && y==A.y && z==A.z;  
        }  
    }Vector_3D;  
      
    Point_3D read_Point_3D() {  
        double x,y,z;  
        scanf("%lf%lf%lf",&x,&y,&z);  
        return Point_3D(x,y,z);  
    }  
      
    Vector_3D operator + (const Vector_3D & A, const Vector_3D & B) {  
        return Vector_3D(A.x + B.x, A.y + B.y, A.z + B.z);  
    }  
      
    Vector_3D operator - (const Point_3D & A, const Point_3D & B) {  
        return Vector_3D(A.x - B.x, A.y - B.y, A.z - B.z);  
    }  
      
    Vector_3D operator * (const Vector_3D & A, double p) {  
        return Vector_3D(A.x * p, A.y * p, A.z * p);  
    }  
      
    Vector_3D operator / (const Vector_3D & A, double p) {  
        return Vector_3D(A.x / p, A.y / p, A.z / p);  
    }  
      
    double Dot(const Vector_3D & A, const Vector_3D & B) {  
        return A.x * B.x + A.y * B.y + A.z * B.z;  
    }  
      
    double Length(const Vector_3D & A) {  
        return sqrt(Dot(A, A));  
    }  
      
    double Angle(const Vector_3D & A, const Vector_3D & B) {  
        return acos(Dot(A, B) / Length(A) / Length(B));  
    }  
      
    Vector_3D Cross(const Vector_3D & A, const Vector_3D & B) {  
        return Vector_3D(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);  
    }  
      
    double Area2(const Point_3D & A, const Point_3D & B, const Point_3D & C) {  
        return Length(Cross(B - A, C - A));  
    }  
      
    double Volume6(const Point_3D & A, const Point_3D & B, const Point_3D & C, const Point_3D & D) {  
        return Dot(D - A, Cross(B - A, C - A));  
    }  
      
    // �����������  
    Point_3D Centroid(const Point_3D & A, const Point_3D & B, const Point_3D & C, const Point_3D & D) {  
        return (A + B + C + D) / 4.0;  
    }  
      
    /************������*************/  
    // ��p��ƽ��p0-n�ľ��롣n����Ϊ��λ����  
    double DistanceToPlane(const Point_3D & p, const Point_3D & p0, const Vector_3D & n)  
    {  
        return fabs(Dot(p - p0, n)); // �����ȡ����ֵ���õ������������  
    }  
      
    // ��p��ƽ��p0-n�ϵ�ͶӰ��n����Ϊ��λ����  
    Point_3D GetPlaneProjection(const Point_3D & p, const Point_3D & p0, const Vector_3D & n)  
    {  
        return p - n * Dot(p - p0, n);  
    }  
    //ֱ��p1-p2 ��ƽ��p0-n�Ľ���  
    Point_3D LinePlaneIntersection(Point_3D p1, Point_3D p2, Point_3D p0, Vector_3D n)  
    {  
        Vector_3D v= p2 - p1;  
        double t = (Dot(n, p0 - p1) / Dot(n, p2 - p1)); //��ĸΪ0��ֱ����ƽ��ƽ�л���ƽ����  
        return p1 + v * t; //������߶� �ж�t�Ƿ���0~1֮��  
    }  
    // ��P��ֱ��AB�ľ���  
    double DistanceToLine(const Point_3D & P, const Point_3D & A, const Point_3D & B)  
    {  
        Vector_3D v1 = B - A, v2 = P - A;  
        return Length(Cross(v1, v2)) / Length(v1);  
    }  
    //�㵽�߶εľ���  
    double DistanceToSeg(Point_3D p, Point_3D a, Point_3D b)  
    {  
        if(a == b)  
        {  
            return Length(p - a);  
        }  
      
        Vector_3D v1 = b - a, v2 = p - a, v3 = p - b;  
      
        if(Dot(v1, v2) + EPS < 0)  
        {  
            return Length(v2);  
        }  
        else  
        {  
            if(Dot(v1, v3) - EPS > 0)  
            {  
                return Length(v3);  
            }  
            else  
            {  
                return Length(Cross(v1, v2)) / Length(v1);  
            }  
        }  
    }  
    //������ֱ�� p1+s*u��p2+t*v�Ĺ����߶�Ӧ��s ���ƽ��|�غϣ�����false  
    bool LineDistance3D(Point_3D p1, Vector_3D u, Point_3D p2, Vector_3D v, double & s)  
    {  
        double b = Dot(u, u) * Dot(v, v) - Dot(u, v) * Dot(u, v);  
      
        if(abs(b) <= EPS)  
        {  
            return false;  
        }  
      
        double a = Dot(u, v) * Dot(v, p1 - p2) - Dot(v, v) * Dot(u, p1 - p2);  
        s = a / b;  
        return true;  
    }  
    // p1��p2�Ƿ����߶�a-b��ͬ��  
    bool SameSide(const Point_3D & p1, const Point_3D & p2, const Point_3D & a, const Point_3D & b)  
    {  
        return Dot(Cross(b - a, p1 - a), Cross(b - a, p2 - a)) - EPS >= 0;  
    }  
    // ��P��������P0, P1, P2��  
    bool PointInTri(const Point_3D & P, const Point_3D & P0, const Point_3D & P1, const Point_3D & P2)  
    {  
        return SameSide(P, P0, P1, P2) && SameSide(P, P1, P0, P2) && SameSide(P, P2, P0, P1);  
    }  
    // ������P0P1P2�Ƿ���߶�AB�ཻ  
    bool TriSegIntersection(const Point_3D & P0, const Point_3D & P1, const Point_3D & P2, const Point_3D & A, const Point_3D & B, Point_3D & P)  
    {  
        Vector_3D n = Cross(P1 - P0, P2 - P0);  
      
        if(abs(Dot(n, B - A)) <= EPS)  
        {  
            return false;    // �߶�A-B��ƽ��P0P1P2ƽ�л���  
        }  
        else   // ƽ��A��ֱ��P1-P2��Ωһ����  
        {  
            double t = Dot(n, P0 - A) / Dot(n, B - A);  
      
            if(t + EPS < 0 || t - 1 - EPS > 0)  
            {  
                return false;    // �����߶�AB��  
            }  
      
            P = A + (B - A) * t; // ����  
            return PointInTri(P, P0, P1, P2);  
        }  
    }  
    vector<Point_3D> now[20];
    int mark[20];
    Point_3D eye;
    Point_3D noww;
    int n;
    int i,j,k,ii,jj,kk,tt;
    int main() {  
        scanf("%d",&n);getchar();
		for (int i=1;i<=n;i++){
			int t;
			scanf("%d",&t);
			char c=getchar();
			while (c!='\n'&&c!=EOF){
				double x,y,z;
				c=getchar();
				while (c==' ') c=getchar();if (c=='\n'||c==EOF) break; 
				scanf("%lf%lf%lf",&x,&y,&z);
				x+=c-'0';
				now[i].push_back(Point_3D(x,y,z));
			}if (c==EOF) break;
		}
		double x,y,z;
		scanf("%lf%lf%lf",&x,&y,&z);
		eye=Point_3D(x,y,z);
		for(i=1;i<=n;i++){
			for (j=0;j<now[i].size();j++){
				int cnt=1;
				for(ii=1;ii<=n;ii++) if (i!=ii){
					for (tt=0;tt<now[ii].size();tt++){
						for (jj=tt+1;jj<now[ii].size();jj++){
							for (kk=jj+1;kk<now[ii].size();kk++){
								if (TriSegIntersection(now[ii][tt],now[ii][jj],now[ii][kk],now[i][j],eye,noww)) cnt=0;
							}
						}
					}
				}
				mark[i]+=cnt;
			}
		}
		for(int i=1;i<=n;i++) if (mark[i]==now[i].size()) printf("%d\n",i);
//		for(int i=1;i<=n;i++) printf("%d ",mark[i]);
    }
    /*
    */
