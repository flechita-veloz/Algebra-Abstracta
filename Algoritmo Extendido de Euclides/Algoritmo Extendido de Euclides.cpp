#include<iostream>
#include<conio.h>

using namespace std;


int sgn(int);
int valorAbsoluto(int);
void euclidesExtendido(int, int);


int main(){
	int a,b;
	cout<<".:Algoritmo extendido de Euclides:.\n";
	cout<<"Digite el valor del primer numero: ";cin>>a;
	cout<<"Digite el valor del segundo numero: ";cin>>b;
	
	euclidesExtendido(a,b);
	
	getch();
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

int valorAbsoluto(int x){
	x *= sgn(x);
	return x;
}

void euclidesExtendido(int a, int b){ //mcd(-8,22)
	int c,d,c1,c2,d1,d2,q,r1,r2,s,t,r;
	
	c = valorAbsoluto(a) , d = valorAbsoluto(b);
	c1= 1 , c2= 0; //Primera combinaci�n lineal de a
	d1= 0 , d2 = 1;  //Primera combinaci�n lineal de b
	
	//Si d > c : el ciclo while se repite una vez m�s para ordenarlo as�(c,d)
	while(d != 0){
		q = c/d,        r = c- q*d;    //  22 = 8(2) + 6      8 = 6(1) + 2
									  //  2 = 8 - 6(1)       2 = 8 - (22 - 8(2))(1)
		//Resta de coeficientes de c y d       					
		// 8(1) - (22(1) + 8(-2))(1)   
		r1 = c1- q*d1,   r2 = c2- q*d2;   //  1- (-2)(1)      0- (1)(1);
		
		//Intercambio de variable   mcd(c,d) = mcd(r,d)
		c = d ,   c1 = d1 ,     c2 = d2;
		d = r ,   d1 = r1 ,     d2 = r2;
	}//c>d siempre
	// 's' y 't' coeficientes de B�zout
	s= c1/sgn(a)*sgn(c), t = c2/sgn(b)*sgn(c);
	
	cout<<"\nEl maximo comun divisor del par ingresado es: "<<valorAbsoluto(c)<<endl;
	cout<<"<.:Coeficientes de B�zout:."<<endl;
	cout<<"El valor de 's' es: "<<s<<endl;
	cout<<"El valor de 't' es: "<<t<<endl;
}

/* Validez del algoritmo -> En todo ciclo while se tiene

	c = c1 |a| + c2 |b|            (2.1)
	d = d1 |a| + d2 |b|
	
	Al final, cuando d = 0, obtenemos s y t usando los datos en  (2.1).
	
	Como |x| = x/sgn(x) = x � sgn(x), entonces
	
	|c| = c1/sgn(c)*|a| + c2 / sgn(c)*|b|
		
		= c1/sgn(c).sgn(a)  *  a + c2/sgn(c).sgn(b)  *   b
		          s                       t
*/

