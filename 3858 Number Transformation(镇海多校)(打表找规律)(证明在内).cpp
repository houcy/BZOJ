/*
x'=((x-1)/i+1)*i
let x=i*y
y'=(y*(i-1)-1)/i+1
  =(y*i-y-1)/i+1
  =y+(-y-1)/i+1
��sqrt()�κ�y<sqrt(),��Խ��ԽС 
��i>=sqrt()����Խ��Խ��
��(-y-1)/i+1=0
y���� 
*/
#include <cstdio>
typedef long long ll;
const int t=2e5;
ll x,k;
int main(){
	for(int Case=1;scanf("%lld%lld",&x,&k),x||k;Case++){
		for(int i=1;i<=k&&i<=t;i++)
			x=((x-1)/i+1)*i;
		printf("Case #%d: %lld\n",Case,k>t?x/t*k:x);
	}
}
