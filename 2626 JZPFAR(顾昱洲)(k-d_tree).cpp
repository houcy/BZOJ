#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define Type int
#define kD 2
#define SIZE 100001
inline void maxi(Type &a,const Type b){if (a<b) a=b;}
inline void mini(Type &a,const Type b){if (a>b) a=b;}
inline double sqr(const double a){return a*a;}
struct point{
	Type p[kD];
	void read(){
		for (int i=0;i<kD;++i) scanf("%d",p+i);
	}
	void operator = (const point& x){
		memcpy(this,&x,sizeof(point));
	}
};
point p,Base[SIZE],*base[SIZE];
struct kd_tree{
	point *x,min,max; unsigned split; kd_tree* c[2];
	kd_tree(point* _x,unsigned _split,kd_tree* _l,kd_tree* _r):
		split(_split),x(_x){
		max=*_x;
		min=*_x;
		if (c[0]=_l)
			for (int i=0;i<kD;++i)
				maxi(max.p[i],c[0]->max.p[i]),
				mini(min.p[i],c[0]->min.p[i]);
		if (c[1]=_r)
			for (int i=0;i<kD;++i)
				maxi(max.p[i],c[1]->max.p[i]),
				mini(min.p[i],c[1]->min.p[i]);
	}
};
unsigned fd;
inline bool cmp(const point* a,const point* b){
	return a->p[fd]<b->p[fd];
}
kd_tree* build(point** begin,point** end){
	if (end-begin<=0) return NULL;
	++fd==kD?fd=0:0; int d=fd;
	point** mid=begin+(end-begin)/2;
	std::nth_element(begin,mid,end,cmp);
	return new kd_tree(*mid,d,build(begin,mid),build(mid+1,end));
}
double dist(point &p,point &q){
	double ret=0;
	for (int i=0;i<kD;++i)
		ret+=sqr(p.p[i]-q.p[i]);
	return ret;
}
double dist(const point &p,const kd_tree* rec){
	double ret=0;
	for (int i=0;i<kD;++i)
		if (p.p[i]<(rec->min.p[i]+rec->max.p[i])/2)
		     ret+=sqr(rec->max.p[i]-p.p[i]);
		else ret+=sqr(p.p[i]-rec->min.p[i]);
	return ret;
}
#define sizeK 22
int K;
struct ansdata{
	point* p; double d;
	bool operator () (const ansdata &a,const ansdata &b){
		return a.d>b.d||a.d==b.d&&a.p<b.p;
	}
	void operator = (const ansdata &b){
		memcpy(this,&b,sizeof(ansdata));
	}
} ans[sizeK],newa;
int anssum;
void nth_farthest(kd_tree* This){
	if (!This||anssum==K&&dist(p,This)<ans[K-1].d) return;
	newa=(ansdata){This->x,dist(p,*This->x)};
	ansdata *start=std::upper_bound(ans,ans+anssum,newa,ansdata());
	if(anssum<K) ++anssum;
	ansdata* i;
	for(i=ans+anssum-1;i>start;--i) *i=*(i-1);
	*start=newa;
	fd=This->split;
	bool goright=This->x->p[fd]>p.p[fd];
	nth_farthest(This->c[goright]);
	nth_farthest(This->c[!goright]);
}
int main(){
	int N,M; scanf("%d",&N);
	for (int i=1;i<=N;++i) Base[i].read(),base[i]=Base+i;
	fd=kD-1;
	kd_tree *flat=build(base+1,base+N+1);
	scanf("%d",&M);
	while (M--){
		scanf("%d%d%d",p.p,p.p+1,&K);
		anssum=0;nth_farthest(flat),printf("%d\n",ans[K-1].p-Base);
	}
}
