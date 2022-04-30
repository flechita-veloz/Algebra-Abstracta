#include<iostream>
#include<stdlib.h>
#include<math.h>

using namespace std;

void inversoMultiplicativo(int a,int b);
int euclidesExtendido(int, int);
int sgn(int);
int s; //Coeficiente de Bezout para el inverso multiplicativo

int main(){
	float a=0,n=0;
	cout<<"Digite un numero para hallar su inverso multiplicativo: ";cin>>a;
	int _a= int(a);
	while(a - float(_a) != 0){
		float aux;
		cout<<"Por favor digite un numero entero: ";cin>>aux;
		a = aux;
		_a = int(aux);
	}
	cout<<"Digite su modulo: ";cin>>n;
	int _n= int(n);
	while(n - float(_n) != 0 || n<=0){
		float aux;
		cout<<"Por favor digite un modulo entero positivo: ";cin>>aux;
		n = aux;
		_n = int(aux);
	}
	inversoMultiplicativo(_a,_n);
	return 0;
}

int sgn(int x){
	if(x>=0){
		x = 1;
	}
	else{
		x=-1;
	}
	return x;
}

int euclidesExtendido(int a, int b){ 
	int c,d,uk,vk,uk_1,uk_2,vk_1,vk_2,q, r;
	
	c = abs(a) , d = abs(b);
	uk_2= 1 , vk_2= 0;  
	uk_1= 0 , vk_1 = 1; 

	while(d != 0){
		q = c/d,        r = c- q*d;   
		//rk = a(uk) + b(vk)
		//uk = uk-2 - qk.uk-1	vk = vk-2 - qk.vk-1
		uk = uk_2- q*uk_1,   vk = vk_2- q*vk_1;  
		
		//intercambio
		c = d ,   uk_2 = uk_1 ,   vk_2 = vk_1; 
		d = r ,   uk_1 = uk   ,   vk_1 = vk;  
	}
	// 's' y 't' coeficientes de Bezout
	s= uk_2*sgn(a);
	return c;
}

void inversoMultiplicativo(int a,int n){
	int d;
	d = euclidesExtendido(a,n);
	if(d == 1){
		int k=1; 
		while(s < 0){
			s = s + n*k; //Solución general x = x0 + b/mcd(a,b) * k
			k++;
		}
		cout<<".:Felicidades:."<<endl;
		cout<<"El inverso multiplicativo del numero "<<a<<" es "<<s%n<<endl; //rem(s,m)
	}
	else{
		cout<<"El numero "<<a<<" no tiene inverso";
	}
}

