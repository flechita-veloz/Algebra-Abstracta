//Prueba de primalidad Miller Rabin
//Usualmente se combina con el test de Lucas
#include<iostream>
#include<math.h>
#include<vector>
#include<stdlib.h>
#include<ctime>
#include<random>
#include<algorithm>
#define ULL unsigned long long int

using namespace std;
ULL powMod(ULL, ULL, ULL);
bool esPrimoMR(ULL);
ULL ramdomBits(int);
ULL randomGen_Primos(int);

int main(){
	int b, n;
	cout<<"Digite el numero de bits que desea que los primos tengan: ";
	cin>>b;
	cout<<"Digite el numero de primos aleatorios que desea imprimir: ";
	cin>>n;
	vector<ULL> v;
	cout<<".:Generando numeros primos:."<<endl;
	for(int i= 0; i< n; i++){ 
		auto num= randomGen_Primos(b); //Generando n numeros primos aleatorios de b bytes
		if(find(v.begin(), v.end(), num) == v.end()){
			cout<<num<<", ";
			v.push_back(num);
		}
		else{
			i--;
		}
	}
	cout<<"\n";
	system("pause");
	return 0;
}

//funcion de multiplicacion modular para evitar overflow
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


//funcion de exponenciacion modular
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

//Si N compuesto pasa los test ---> N es pseudoprimo fuerte y ai son embaucadores fuertes
//La probabilidad de equivocarnos al decir que n es primo es inferior a 1/4^k  k: cantidad de ai

ULL randomBits(int b){
	ULL MIN= 0, MAX;
	if(b== 64){
		MAX= 18446744073709551615;
	}
	else{
		MAX= pow(2,b)-1; 
	}
	static mt19937 eng(time(NULL)); //motor, semilla= time(NULL)
	static uniform_int_distribution<ULL> distr(MIN, MAX); //distribucion
	ULL n= distr(eng); //Genera un numero aleatorio entre 0 y 2^b - 1
	ULL m= pow(2,b-1); //mascara
	n= n|m; //compuerta OR
	return n;
}

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
