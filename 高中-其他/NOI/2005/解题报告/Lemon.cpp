/*
第22届全国青少年信息学奥林匹克竞赛
河南·郑州
第二试：月下柠檬树
C++源程序
作者：胡伟栋
声明：您可以对该源代码进行法律允许的任何操作，但作者对因错误使用该代码而引起的
      任何后果不负任何责任。
*/

#include <iostream>
#include <math.h>

using namespace std;

const char *inf = "lemon.in";
const char *ouf = "lemon.out";

#define real long double
#define pi 3.14159265359

const int maxSeg = 100000;
const int maxn = 5000;
const real zero = 1e-10;  //考虑实数误差

long ObjectUsed=0;

struct TPoint {
	real x, y;
};

enum TFigureType {FT_Line, FT_Cir};  

class TFigure {     //TFigure类型,由弧和线段两种组成
public:
	TFigure *next;
	TPoint p1, p2;  //弧或是线段的两个端点
	TFigureType ObjectType;  //ObjectType = {Cir or Line}
	virtual bool intersect(TFigure *X) { return false; };  //判断两个TFigure类型是否相交
	virtual TPoint intersector(TFigure *X) { TPoint tmp; tmp.x=0; tmp.y=0; return tmp; };  //求交点
	bool better(TFigure *X);  //取更靠外的 --->不是很好形容
	virtual real area() { return 0; };  //求该段围成的面积
	TFigure() { ++ObjectUsed; };  //记录TFigure用到的次数,没有实际用处
	virtual real YAt(real x) { return 0; };  //知道x,求该段的y坐标
	virtual TFigure *cut(real x) { return 0; };  //将该段割断成两块
};

class TLine: public TFigure {  //派生类--->线段
public:
	bool intersect(TFigure *X);
	TPoint intersector(TFigure *X);
	real area();
	real YAt(real x);
	TFigure *cut(real x);
	TLine();
};

class TCir: public TFigure {  //派生类--->弧
public:
	real x_c;
	real r;
	bool intersect(TFigure *X);
	TPoint intersector(TFigure *X);
	real area();
	real YAt(real x);
	TFigure *cut(real x);
	TLine *tangent(TCir *X);  //两端弧,返回其切线线段
	TCir();
	real getAngle(real x, real y);  //求（x,y）于圆心组成的线段与x轴的夹角
};

TFigure *cirRec=0, *lineRec=0;

TLine *CreateLine() {  //新建一条线段
	if (lineRec!=0) {
		TLine *tmp=(TLine *)lineRec;
		lineRec=lineRec->next;
		return tmp;
	} else
		return new TLine();
}

TCir *CreateCir() {  //新建一段弧
	if (cirRec!=0) {
		TCir *tmp=(TCir *)cirRec;
		cirRec=cirRec->next;
		return tmp;
	} else 
		return new TCir();
}
 
void Throw(TFigure *X) {  //丢掉尾巴
	if (X->ObjectType==FT_Line) {
		X->next=lineRec;
		lineRec=X;
	} else {
		X->next=cirRec;
		cirRec=X;
	}
}

bool TFigure::better(TFigure *X) {  //取更靠外的一段,返回y坐标
	real px=X->p2.x;
	if (p2.x<px) px=p2.x;
	px=(p1.x+px)/2;
	return YAt(px)>X->YAt(px);
}

real cross(const TPoint p0, const TPoint p1, const TPoint p2) {  //叉积
	return (p1.x - p0.x) * (p2.y - p0.y) -
		(p1.y - p0.y) * (p2.x - p0.x);
}

bool TLine::intersect(TFigure *X) {  //是否相交
	if (X->ObjectType==FT_Line) {
		return (cross(p1, X->p1, p2) * cross(p1, p2, X->p2) > zero) &&
			(cross(X->p1, p1, X->p2) * cross(X->p1, X->p2, p2) > zero);
	} else
		return X->intersect(this);
}

TPoint TLine::intersector(TFigure *X) {  //求交点
	if (X->ObjectType==FT_Line) {
		real A=cross(X->p1, p1, X->p2),
			B=cross(X->p1, X->p2, p2);
		A/=(A+B);
		TPoint tmp;
		tmp.x=(p2.x - p1.x) * A + p1.x;
		tmp.y=(p2.y - p1.y) * A + p1.y;
		return tmp;
	} else
		return X->intersector(this);
}

real TLine::area() {  //梯形面积
	return (p1.y + p2.y) * (p2.x - p1.x) / 2;  
}

TLine::TLine() {  //定义 objecttype是线
	ObjectType=FT_Line;
}

real TLine::YAt(real x) {  //求该直线 知道x 求y
	return (x - p1.x) / (p2.x - p1.x) * (p2.y - p1.y) + p1.y;
}

TFigure *TLine::cut(real x) {  //一条直线从x处切断变成两条，返回第二段的线段。
	TPoint p;
	p.x=x;
	p.y=YAt(x);
	TLine *tmp=CreateLine();
	tmp->p1 = p;
	tmp->p2 = p2;
	p2 = p;
	return tmp;
}

TLine *TCir::tangent(TCir *X) {  //tangent:切线,返回切线线段。
	if (X->x_c < x_c)
		return X->tangent(this);
	else {
		if ((X->x_c + X->r <= x_c + r) || (X->x_c - X->r <= x_c - r)) return 0;
		TLine *tmp=CreateLine();
		real _cos=(r - X->r) / (X->x_c - x_c),
			_sin=sqrt(1 - _cos * _cos);
		tmp->p1.x = _cos * r + x_c;
		tmp->p1.y = _sin * r;
		tmp->p2.x = _cos * X->r + X->x_c;
		tmp->p2.y = _sin * X->r;
		return tmp;
	}
}

real sqr(real x) {  //sqr：平方
	return x*x;
}

bool TCir::intersect(TFigure *X) {  //两弧是否相交
	if (X->ObjectType==FT_Line) { 
		real r2=r*r,
			tmp1=sqr(X->p1.x - x_c) + sqr(X->p1.y),
			tmp2=sqr(X->p2.x - x_c) + sqr(X->p2.y);
		if (!((tmp1 > r2 + zero) &&
			  (tmp2 < r2 - zero) ||
			  (tmp1 < r2 - zero) &&
			  (tmp2 > r2 + zero))) return false;
        TPoint p = intersector(X);
        return p.x>p1.x && p.x<p2.x && 
			p.x>=X->p1.x && p.x<=X->p2.x && 
			(p.y>=X->p1.y && p.y<=X->p2.y || 
			 p.y<=X->p1.y && p.y>=X->p2.y) &&
			p.x!=X->p1.x && p.x!=X->p2.x;
	} else {
		TCir *tmp=(TCir *)X;
		real tmp2=(tmp->x_c - x_c) * 2;
		if (tmp2==0) return false;
		real tmp1=(sqr(r) - sqr(tmp->r) + sqr(tmp->x_c) - sqr(x_c)) / tmp2;
		return (p1.x < tmp1 - zero) && 
			(p2.x > tmp1 + zero) &&
			(X->p1.x < tmp1 - zero) &&
			(X->p2.x > tmp1 + zero);
	}
}

TPoint TCir::intersector(TFigure *X) {  //两段弧交点
	if (X->ObjectType==FT_Line) {
		real a=sqr(X->p2.x - X->p1.x) + sqr(X->p2.y - X->p1.y),
			b=2 * ((X->p1.x - x_c) * (X->p2.x - X->p1.x) + (X->p1.y) * (X->p2.y - X->p1.y)),
			c=sqr(X->p1.x - x_c) + sqr(X->p1.y) - sqr(r),
			lambda=(-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
		if ((lambda < 0) || (lambda > 1))
			lambda=(-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
		TPoint tmp;
		tmp.x = X->p1.x + (X->p2.x - X->p1.x) * lambda;
		tmp.y = X->p1.y + (X->p2.y - X->p1.y) * lambda;
		return tmp;
	} else {
		TCir *ctmp=(TCir *)X;
		TPoint tmp;
		tmp.x=(sqr(r) - sqr(ctmp->r) + sqr(ctmp->x_c) - sqr(x_c)) / (2 * (ctmp->x_c - x_c));
		tmp.y=sqrt(sqr(r) - sqr(x_c - tmp.x));
		return tmp;
	}
}

real TCir::getAngle(real x, real y) {  //（x,y）于圆心夹角
	x-=x_c;
	if (x==0) return pi/2;
	if (y==0) {
		if (x>0) return 0; else return pi;
	} else {
		real tmp=atan(y/x);
		return (tmp<0)?(tmp+pi):tmp;
	}
}

real TCir::area() {  //求弧线梯形面积
	return (sqr(r) * (getAngle(p1.x, p1.y) - getAngle(p2.x, p2.y)) + (p2.x - x_c) * p2.y - (p1.x - x_c) * p1.y) / 2;
}

TCir::TCir() {  //定义 objecttype是圆
	ObjectType=FT_Cir;
}

real TCir::YAt(real x) {  //圆上x坐标上的点 y坐标
	return sqrt(sqr(r) - sqr(x_c - x));
}

TFigure *TCir::cut(real x) {  //弧 分成两段，返回第二段
	TPoint p;
	p.x = x;
	p.y = YAt(x);
	TCir *tmp=CreateCir();
	tmp->p1 = p;
	tmp->p2 = p2;
	tmp->x_c = x_c;
	tmp->r = r;
	p2 = p;
	return tmp;
}

class THeap {  //堆,处理每次操作的段的次序问题
private:
	long th;
	TFigure *q[maxSeg+1];  
public:
	THeap() { th=0; };
	void Push(TFigure *X);
	TFigure *Top() { return q[1]; };
	TFigure *Pop();
	bool null() { return th==0; };
};

long HeapUsed=0,HeapPushed=0;

void THeap::Push(TFigure *X) {  //加入元素，向上调整,以p1.x(即左边的端点的x坐标)的值为比较对象
	++HeapPushed;
	long i=++th,j=i>>1;
	while ((j>0)&&(q[j]->p1.x > X->p1.x)) {
		q[i]=q[j];
		i=j;
		j>>=1;
	}
	q[i]=X;
}

TFigure *THeap::Pop() {  //堆中删除堆顶元素,以p1.x(即左边的端点的x坐标)的值为比较对象
	TFigure *result=q[1],
		*X=q[th--];
	long i=1,j=2;
	if ((j < th) && (q[j + 1]->p1.x < q[j]->p1.x)) ++j;
	while ((j <= th) && (q[j]->p1.x < X->p1.x)) {
		q[i]=q[j];
		i=j;
		j<<=1;
		if ((j < th) && (q[j + 1]->p1.x < q[j]->p1.x)) ++j;
	}
	q[i]=X;
	return result;
}

long n;
real alpha;
TCir *tmpCir[maxn+1];

void init() {  //初始化，建立n个弧
	FILE *f=fopen(inf, "rt");
	fscanf(f, "%d%lf", &n, &alpha);
	long i;
	for (i=0;i<=n;++i)
		tmpCir[i]=CreateCir();
	real h;
	fscanf(f, "%lf", &h);
	real tmp=0,
		_cot=cos(alpha) / sin(alpha);
	for (i=0;i<n;++i) {
		fscanf(f, "%lf", &h);
		tmpCir[i]->x_c = tmp;
		tmp+=h * _cot;
	}
	tmpCir[n]->x_c = tmp;
	for (i=0;i<n;++i)
		fscanf(f, "%lf", &tmpCir[i]->r);
	tmpCir[n]->r = 0;
	for (i=0;i<=n;++i) {
		tmpCir[i]->p1.x = tmpCir[i]->x_c - tmpCir[i]->r;  //弧的左端点
		tmpCir[i]->p1.y = 0;
		tmpCir[i]->p2.x = tmpCir[i]->x_c + tmpCir[i]->r;  //弧的有端点
		tmpCir[i]->p2.y = 0;
	}
	fclose(f);
}

THeap heap;  

void segPrepare() {   //把弧和切线全部进堆
	long i;
	for (i=0;i<n;++i)
		heap.Push(tmpCir[i]);   //加入弧
	for (i=0;i<n;++i) {
		TFigure *tmp=tmpCir[i]->tangent(tmpCir[i+1]);  //加入切线
		if (tmp!=0)
			heap.Push(tmp);
	}
}

real ans;
long count;

void process() {  
	segPrepare();
	ans=0;
	while (!heap.null()) {  
		++count;  
		TFigure *cur=heap.Pop();  //cur取出,堆顶元素.
		while (!heap.null()) {
			TFigure *next=heap.Top();  //当前的堆顶元素,即cur的下一个
			if (next->p1.x > cur->p1.x + zero) {  
				if (next->p1.x < cur->p2.x - zero)  
					heap.Push(cur->cut(next->p1.x));  //从next->p1.x的地方割断,成为新的一段插入堆中
				break;
			} else {  //处理cur和next的起始点的x坐标相同的情况
				next=heap.Pop();  
				if (cur->intersect(next)) {  
					TPoint p=cur->intersector(next); 
					TFigure *a=cur->cut(p.x),  
						*b=next->cut(p.x);
					if (a->better(b)) {
						heap.Push(a);
						Throw(b);
					} else {
						heap.Push(b);
						Throw(a);
					};
				} else if (cur->p2.x < next->p2.x - zero)
					heap.Push(next->cut(cur->p2.x));
				else if (next->p2.x < cur->p2.x - zero)
					heap.Push(cur->cut(next->p2.x));
				if (next->better(cur)) {
					Throw(cur);
					cur=next;
				} else
					Throw(next);
			}
		}
		ans+=cur->area();  //加入cur这段围成的面积
		Throw(cur);  //扔掉 cur
	}
	ans*=2;
}

void print() {  //打印ans
	FILE *f=fopen(ouf, "wt");
	fprintf(f, "%0.2lf", ans);
	fclose(f);
}

int main() {  //主程序
	init();
	process();
	print();
	return 0;
}