#include<iostream>
#include<math.h>
#include<vector>
#include<stdlib.h>
#include<ctime>
#include<random>
#include<algorithm>
#define ULL unsigned long long int
#define LL long long int

using namespace std;
ULL multMod(ULL, ULL, ULL);
ULL powMod(ULL, ULL, ULL);
bool esPrimoMR(ULL);
ULL randomBits(int);
ULL randomMessage();
ULL randomGen_Primos(int);
void RSA_KEY_GENERATOR(int);
ULL euclides(ULL, ULL);
ULL inversoMultiplicativo(ULL,ULL);
ULL randomGen_e(ULL, ULL);
ULL cifrar(ULL);
ULL descifrar(ULL);
void enmarca(int n);
void imprimeEspacios(int);
void imprimirTabla(vector<vector<string>>);
ULL _n,_e,_d;

int main(){
	int k= 64;
	RSA_KEY_GENERATOR(64);
	cout<<".:GENERANDO CLAVE:."<<endl;
	cout<<"Clave Publica : P = {e, n}"<<endl;
	cout<<"Clave Privada : S = {d, n}"<<endl;
	cout<<"e: "<<_e<<endl;
	cout<<"d: "<<_d<<endl;
	cout<<"n: "<<_n<<endl;
	vector<vector<string>> v(10,vector<string>(3));
	cout<<"\n.:IMPRIMIENDO TABLA:.\n"<<endl;
	for(int i= 0; i< 10; i++){
		ULL m= randomMessage();
		v[i][0]= to_string(m);
		ULL c= cifrar(m); 
		v[i][1]= to_string(c);
		v[i][2]= to_string(descifrar(c));
	}
	imprimirTabla(v);
	system("pause");
	return 0;
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

//Prueba de primalidad 
bool esPrimoMR(ULL N){
	//N>3 es impar. Respuesta 100% seguro si 37 <N< 2^64, si se toman 12 bases primas
	ULL N1  = N-1;
	int primo[12] = {2,3,5,7,11,13,17,19, 23, 29, 31, 37};  //Valor de confianza f= 8
	int s = 0; 
	ULL a,r,y;
	ULL j;
	
	while(N1%2 == 0){ //n-1 = 2^s r
		N1 = N1/2;
		s++;
	}
	r = N1;
	N1 = N - 1;
	for(int i=0;i<=11;i++){
		a = primo[i];
		y = powMod(a,r,N);//a^r mod N
		if(y != 1 && y!= N1){
			j = 1;
			while(j<=s-1 && y!= N1){ // y != n-1
				y = powMod(y,2,N);       //y = y^2 mod N
				//Si N es primo y N|ab -----> o N divide a "a" o N divide a "b"
				if(y == 1){      // si X^2 es congruente Y^2 mod N  y  X no es congruente (+-Y) mod N -----> N es compuesto
					return false;  // si a^(2^j r) es congruente 1 mod N y a^(2^(j-1) r) no es congruente a (+-1) mod N
								   // entonces N es compuesto, ya que para pasar a j, antes j-1 debio ser distindo de 1 y N1=-1
				}
				j++;	
			}
			if(y != N1){  //Falta comprobar el ultimo caso, que es para 2^(s-1) r
				return false;  //a es testigo fuerte de no-primalidad de n
			}
		}
	}
	return true; //si pasa todos los test
	//si N es compuesto, N es pseudoprimo fuerte en la base "a" y al entero "a" se le llama: embaucador fuerte
}	

//Genera un numero aleatorio de b bits
ULL randomBits(int b){
	ULL MIN= 0,MAX;
	if(b==64){
		MAX= 18446744073709551615;
	}
	else{
		MAX= pow(2,b)-1; 
	}
	static mt19937 eng(time(NULL)); //motor, semilla= time(NULL) //distribucion
	static uniform_int_distribution<ULL> distr(MIN, MAX);
	ULL n= distr(eng); //Genera un numero aleatorio entre 0 y 2^b - 1
	ULL m= pow(2,b-1); //mascara
	n= n|m; //compuerta OR
	return n;
}

//Genera un numero primo aleatorio de b bits
ULL randomGen_Primos(int b){
	ULL n= randomBits(b);
	n+= (6- n%6); //n es un multiplo de 6
	while(!esPrimoMR(n-1) && !esPrimoMR(n+1)){ //el grado de confianza es 12= {2,3,5,7,11,13,17,19,23,29,31,37}
		n+= 6; //numeros primos de forma multiplosDe6 +-1
	}
	if(esPrimoMR(n-1)){
		return n-1;
	}
	else{
		return n+1;
	}
}

//Funcion para calcular el mcd de a y b
ULL euclides(ULL a, ULL b){
	while(b!=0){
		ULL aux= a;
		a= b, b= aux%b;
	}
	return a;
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

//Genera la n, e y d
void RSA_KEY_GENERATOR(int k){
	//Paso 1 Generar dos primos p y q, tal que p != q. Cada uno de k/2 bits.
	ULL p= randomGen_Primos(k/2);
	ULL q= randomGen_Primos(k/2);;
	while(p==q){
		q= randomGen_Primos(k/2);	
	}
	//Paso 2 Calcular n= pxq
	_n= p*q;
	//Paso 3 Calcular la funcion de Euler de n= phi(p)*phi(q)
	ULL phi_de_n= (p-1)*(q-1);
	//Paso 4 Generar aleatoriamente e E [2,n-1], tal que gcd(e,phi_de_n)= 1
	_e= randomGen_e(_n, phi_de_n);
	//Paso 5 Hallar d= inverso multiplicativo de e
	_d= inversoMultiplicativo(_e, phi_de_n);
	//Paso 6 return {n,e,d}
}

//Funcion para generar m aleatorio m E [2,n-1]
ULL randomMessage(){
	ULL MIN= 2, MAX= _n-1, m;
	static mt19937 eng(time(NULL)); //motor, semilla= time(NULL) 
	static uniform_int_distribution<ULL> distr(MIN, MAX); //distribucion
	m= distr(eng);
	return m;
}

//Funcion para cifrar mensaje
ULL cifrar(ULL m){
	return powMod(m,_e,_n);
}

//Funcion para descifrar mensaje
ULL descifrar(ULL c){
	return powMod(c,_d,_n);
}

//Funcion que enmarca
void enmarca(int n){
	cout<<"+";
	for(int i= 0; i< n; i++){
		if((i+1)%(n/3)==0){
			cout<<"+";
		}
		else{
			cout<<"-";
		}
	}
}
//Funcion que Imprime espacios
void imprimeEspacios(int n){
	for(int i= 0; i< n; i++){
		cout<<" ";
	}
}
//Funcion para imprimir tabla
void imprimirTabla(vector<vector<string>> v){
	enmarca(96); cout<<"\n";
	cout<<"| m= mensaje"; imprimeEspacios(20);
	cout<<"| c= P(m)= mensaje cifrado"; imprimeEspacios(6);
	cout<<"| m'= S(c)= mensaje descifrado"; imprimeEspacios(2); cout<<"|\n";
	for(int i= 0; i< 10; i++){
		enmarca(96); cout<<"\n";
		string m= v[i][0], c= v[i][1], _m= v[i][2];
		cout<<"| "<<m;  imprimeEspacios(30-m.size());
		cout<<"| "<<c;  imprimeEspacios(30-c.size());
		cout<<"| "<<_m; imprimeEspacios(30-_m.size()); cout<<"|\n";
	}
	enmarca(96); cout<<"\n";
}
