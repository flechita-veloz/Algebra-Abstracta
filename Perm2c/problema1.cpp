#include<iostream>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<ctime>
#include<random>
#define ULL unsigned long long int
#define LL long long int
#define endl "\n"

using namespace std;
ULL multMod(ULL, ULL, ULL);
ULL powMod(ULL, ULL, ULL);
ULL randomGen_e(ULL, ULL);
ULL inversoMultiplicativo(ULL, ULL);
ULL euclides(ULL, ULL);
ULL phi(ULL);

ULL solve(ULL e, ULL n, ULL c){
	ULL x,_m,_c,d, invx,m, phi_de_n;
	//paso 1: Generamos un entero x E [2,n-1] (coprimo con n)
	//y calculamos su inversa
	x= randomGen_e(n,n);
	invx= inversoMultiplicativo(x,n); 
	
	//paso 2: Calculamos _c= c*x^e mod n
	_c= powMod(x,e,n);
	_c= multMod(c,_c,n);
	
	//paso 3: Calculamos phi(n)
	phi_de_n= phi(n);
	
	//paso 4: Calculamos d
	d= inversoMultiplicativo(e,phi_de_n);
	
	//paso 5: Calculamos _m= S(_c), donde S() es la funcion de
	//descifrado
	_m= powMod(_c,d,n);
	
	//paso 6: Hallamos m= S(c)= _m*invx mod n
	m= multMod(invx,_m,n);
	return m;
}

int main(){
	ULL e,n,c,m;
	cout<<"Ingrese la clave Publica e: "<<endl;
	cin>>e;
	cout<<"Ingrese la clave Publica n: "<<endl;
	cin>>n;
	cout<<"Ingrese el mensaje cifrado c: "<<endl;
	cin>>c;
	m= solve(e,n,c);
	cout<<"El mensaje es: "<<m<<endl;
	return 0;
}

//Funcion para calcular el mcd de a y b
ULL euclides(ULL a, ULL b){
	while(b!=0){
		ULL aux= a;
		a= b, b= aux%b;
	}
	return a;
}

//Funcion de multiplicacion modular para evitar overflow
ULL multMod(ULL a, ULL b, ULL mod){
	ULL c= min(a,b)%mod;
	ULL d= max(a,b)%mod;
	ULL res= 0;
	while(c>0){
		if(c&1){
			if(res> mod-d){ //res+d> mod
				res= res-mod+d; //si hay overflow
			}
			else{ //si no hay overflow
				res= res+d;
			}
			res%=mod; 
		}
		c/=2;
		if(d> mod-d){ //2d> mod
			d= d-mod+d; //si hay overflow
		}
		else{ //si no hay overflow
			d= d+d;
		}
		d%=mod;
	}
	return res;
}

//Funcion de exponenciacion modular
ULL powMod(ULL a, ULL exp, ULL mod){
	ULL ans= 1, c= a%mod;
	while(exp>0){
		if(exp&1){
			ans= multMod(ans,c,mod);
		}
		c= multMod(c,c,mod);
		exp/= 2;
	}
	return ans;
}

//Funcion para hallar e
ULL randomGen_e(ULL n, ULL phi_de_n){
	bool coprimos= false;
	ULL MIN= 2, MAX= n-1, e;	
	static mt19937 eng(time(NULL)); //motor, semilla= time(NULL) 
	static uniform_int_distribution<ULL> distr(MIN, MAX); //distribucion
	while(!coprimos){
		e= distr(eng);
		e= e-1*(e%2==0);//Solo probamos con e impares
		if(euclides(e,phi_de_n)==1){
			coprimos= true;
		}
	}
	return e;
}

//Funcion para halla el inverso multiplicativo de a mod n
ULL inversoMultiplicativo(ULL a, ULL n){
	//Inicio de Algoritmo Iterativo Extendido de Euclides
	LL uk,vk,uk_1,uk_2,vk_1,vk_2,q, r;
	
	ULL c = a , d = n;
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
	//Fin del Algoritmo Iterativo Extendido de Euclides
	if(c==1){
		LL s= uk_2; // 's' y 't' coeficientes de Bezout
		if(s < 0){
			return s + n; //Solución general x = x0 + b/mcd(a,b) * k
		}
		else{
			return s;
		}
	}
	else{
		cout<<"El numero "<<a<<" no tiene inverso"<<endl;
		exit(1);
	}
}

//Funcion phi
ULL phi(ULL n){
	ULL p,q;
	for(ULL i= 6; i< sqrt(n); i+=6){
		if(euclides(i-1,n)!=1){
			p= i-1;
			break;
		}
		if(euclides(i+1,n)!=1){
			p= i+1;
			break;
		}
	}
	q= n/p;
	return (p-1)*(q-1);
}
