#include <cstdio>
#include <vector>

/*
  Name: (Heap��) 
  Copyright: 
  Author: wwt
  Date: 17/07/13
  Description: 
		��Ŀ¼�µ�ģ�����������©�������ʹ��
		Heap<����,��С,�ȽϺ���>: �����
		heap<����,�ȽϺ���>: vector��
		Heap_map<����,��С,int��Աָ��,�ȽϺ���>: �����+ӳ���
		heap_map<����,int��Աָ��,�ȽϺ���>: vector��+ӳ���
		���У�
		�ȽϺ���Ĭ��ʹ�� operator<
		�Զ���ȽϺ�������ӦΪ���� 
		int�ͳ�Աָ�������洢Ԫ���ڶ���λ�ã�Ĭ��ʹ�� &����::inh 
	ע�⣺
		��ģ�岻���׳��쳣
		��ͨ�Ķ�ֱ�Ӵ洢Ԫ�أ���Ҫ�����ڴ渴�ƣ����ڽϴ�����������ʹ�� 
		����ӳ���ĶѴ洢����ָ��
		����ӳ���ĶѲ�����push�����ָ��ͬһԪ�ص�ָ�� 
  Update: 09/08/13
		�Ľ��˱ȽϺ����������˺���ָ��İ汾�� 
		�����inh��Աָ�룬����˲��ܶ�ͬһ�ṹ�����heap_map�����⣬�Ӷ���������ѡ��"inh"��Ա����
		�����ʹ��"<"(С�ں�)��ΪĬ�ϱȽϺ��� 
	Update: 21/08/13
		�Ѵ���ӳ���ĶѵıȽϺ���������Ϊ���� 
*/

template<typename Type>
inline bool less(Type &a,Type &b){
	return a<b;
}

template<typename Type,unsigned maxsize,bool cmp(Type&,Type&)=less<Type> >
struct Heap{
	#define size_t unsigned
	Type data[maxsize+1]; size_t len;
	Heap():len(0){
	}
	Heap(const Type &x){
		data[len=1]=x;
	}
	Heap(Type* begin,Type* end):len(end-begin){
		for(Type* i=begin;i<end;i++) data[i-begin+1]=*i;
		for(size_t i=len>>1;i;i--)
			down(i);
	}
	Heap(Type begin,Type end){
		for(;begin<end;++begin) data[++len]=begin;
	}
	#define swap(i,j) {Type tmp=data[i];data[i]=data[j];data[j]=tmp;}
	void up(size_t i){
		for(size_t j;i>1&&cmp(data[j=i>>1],data[i]);i=j)
			swap(i,j);
	}
	void down(size_t i){
		for(size_t j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(data[j],data[j^1])) j^=1;
			if(!cmp(data[i],data[j])) break;
			swap(i,j);
		}
	}
	#undef swap
	void adjust(size_t i){
		up(i);
		down(i);
	}
	void push(const Type &x){
		data[++len]=x;
		up(len);
	}
	void pop(){
		data[1]=data[len--];
		down(1);
	}
	Type& top(){
		return data[1];
	}
	Type& operator[](const size_t i){
		return data[i];
	}
	bool empty(){
		return !len;
	}
	#undef size_t
};

template<typename Type,bool cmp(Type&,Type&)=less<Type> >
struct heap{
	#define size_t unsigned
	std::vector<Type> data;
	#define len (data.size()-1)
	heap(){ data.push_back(*new Type); }
	heap(const Type &x){ data.push_back(x); }
	heap(Type* begin,Type* end){
		data.push_back(*new Type);
		for(Type* i=begin;i<end;i++) data.push_back(*i);
		for(size_t i=len>>1;i;i--)
			down(i);
	}
	heap(Type begin,Type end){
		data.push_back(*new Type);
		for(;begin<end;++begin) data.push_back(begin);
	}
	#define swap(i,j) {Type tmp=data[i];data[i]=data[j];data[j]=tmp;}
	void up(size_t i){
		for(size_t j;i>1&&cmp(data[j=i>>1],data[i]);i=j)
			swap(i,j);
	}
	void down(size_t i){
		for(size_t j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(data[j],data[j^1])) j^=1;
			if(!cmp(data[i],data[j])) break;
			swap(i,j);
		}
	}
	#undef swap
	void adjust(size_t i){
		up(i);
		down(i);
	}
	void push(const Type &x){
		data.push_back(x);
		up(len);
	}
	void pop(){
		data[1]=data[len];
		data.pop_back();
		down(1);
	}
	Type& top(){
		return data[1];
	}
	Type& operator[](size_t i){
		return data[i];
	}
	bool empty(){
		return !len;
	}
	size_t size(){
		return len;
	}
	#undef len
	#undef size_t
};

template<typename Type,unsigned maxsize,bool cmp(Type&,Type&)=less<Type>,int Type::* inh=&Type::inh>
struct Heap_map{
	#define size_t unsigned
	typedef Type* tp;
	tp data[maxsize+1]; size_t len;
	Heap_map():len(0){
	}
	Heap_map(tp x){
		data[x->*inh=len=1]=x;
	}
	Heap_map(tp* begin,tp* end):len(end-begin){
		for(tp* i=begin;i<end;i++) data[i->*inh=i-begin]=*i;
		for(size_t i=len>>1;i;i--)
			down(i);
	}
	Heap_map(tp begin,tp end){
		for(tp i=begin;i<end;++i) data[i->*inh=++len]=begin;
	}
	#define swap(i,j) {\
		tp tmp=data[i];data[i]=data[j];data[j]=tmp;\
		data[i]->*inh=i; data[j]->*inh=j;\
	}
	void up(size_t i){
		for(size_t j;i>1&&cmp(*data[j=i>>1],*data[i]);i=j)
			swap(i,j);
	}
	void up(const tp x){ up(x->*inh); }
	void down(size_t i){
		for(size_t j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(*data[j],*data[j^1])) j^=1;
			if(!cmp(*data[i],*data[j])) break;
			swap(i,j);
		}
	}
	void down(const tp x){ down(x->*inh); }
	#undef swap
	void adjust(size_t i){
		up(i);
		down(i);
	}
	void adjust(const tp x){ adjust(x->*inh); }
	void replace(const tp x,const tp y){
		data[y->*inh=x->*inh]=y; x->*inh=0;
		adjust(y->*inh);
	}
	void push(tp x){
		data[x->*inh=++len]=x;
		up(len);
	}
	void pop(){
		data[1]->*inh=0;
		(data[1]=data[len--])->*inh=1;
		down(1);
	}
	tp& top(){
		return data[1];
	}
	tp& operator[](const size_t i){
		return data[i];
	}
	bool empty(){
		return !len;
	}
	#undef size_t
};

template<typename Type,bool cmp(Type&,Type&)=less<Type>,int Type::* inh=&Type::inh>
struct heap_map{
	#define size_t unsigned
	typedef Type* tp;
	std::vector<tp> data;
	#define len (data.size()-1)
	heap_map(){ data.push_back(*new tp); }
	heap_map(tp x){ data.push_back(x); x->*inh=len; }
	heap_map(tp* begin,tp* end){
		data.push_back(*new tp);
		for(tp* i=begin;i<end;i++) data.push_back(*i),i->*inh=i-begin+1;
		for(size_t i=len>>1;i;i--)
			down(i);
	}
	heap_map(tp begin,tp end){
		data.push_back(*new tp);
		for(tp i=begin;i<end;++i) i->*inh=i-begin+1,data.push_back(i);
	}
	#define swap(i,j) {\
		tp tmp=data[i];data[i]=data[j];data[j]=tmp;\
		data[i]->*inh=i; data[j]->*inh=j;\
	}
	void up(size_t i){
		for(size_t j;i>1&&cmp(*data[j=i>>1],*data[i]);i=j)
			swap(i,j);
	}
	void up(tp x){ up(x->*inh); }
	void down(size_t i){
		for(size_t j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(*data[j],*data[j^1])) j^=1;
			if(!cmp(*data[i],*data[j])) break;
			swap(i,j);
		}
	}
	void down(tp x){ down(x->*inh); }
	#undef swap
	void adjust(size_t i){
		up(i);
		down(i);
	}
	void adjust(tp x){ adjust(x->*inh); }
	void replace(const tp x,const tp y){
		data[y->*inh=x->*inh]=y; x->*inh=0;
		adjust(y->*inh);
	}
	void push(const tp x){
		data.push_back(x);
		up(x->*inh=len);
	}
	void pop(){
		data[1]->*inh=0;
		(data[1]=data[len])->*inh=1;
		data.pop_back();
		down(1);
	}
	tp& top(){
		return data[1];
	}
	tp& operator[](size_t i){
		return data[i];
	}
	bool empty(){
		return !len;
	}
	size_t size(){
		return len;
	}
	#undef len
	#undef size_t
};
inline bool mini(int &a,const int b){
	return b<a?(a=b,true):false;
}
inline void read(int &a){
	char c; while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}

const int N=1000001,M=10000000;
struct node;
struct edge{
	node *ed; edge *next; int w;
} E[M],*newE=E;
struct node{
	edge *son; int inh,dist;
	inline void addedge(node* ed,int w){
		*newE=(edge){ed,son,w}; son=newE++;
	}
} V[N];
inline bool cmp(node &a,node &b){
	return a.dist>b.dist;
}
Heap_map<node,N,cmp> h;
int n,m,t; long long rxa,rxc,rya,ryc,rp;
int main(){
	scanf("%u%u\n%u%u%u%u%u%u",
		&n,&m,&t,&rxa,&rxc,&rya,&ryc,&rp);
	long long x=0,y=0; int a,b,w;
	for(int i=0;i<t;i++){
		x=(x*rxa+rxc)%rp;
		y=(y*rya+ryc)%rp;
		a=x%n+1;
		b=y%n+1;
		if(a<b) V[a].addedge(V+b,100000000-100*a);
	}
	for(int i=t;i<m;i++){
		read(a),read(b),read(w);
		V[a].addedge(V+b,w);
	}
	for(node* v=V+1;v<=V+n;v++) v->dist=0x7f7f7f7f;
	V[1].dist=0;
	h.push(V+1);
	while(!h.empty()){
		node *u=h.top(); h.pop();
		if(u==V+n){
			printf("%u\n",V[n].dist);
			return 0;
		}
		for(edge* e=u->son;e;e=e->next)
			if(mini(e->ed->dist,u->dist+e->w))
				if(e->ed->inh)
					h.up(e->ed->inh);
				else
					h.push(e->ed);
	}
}
