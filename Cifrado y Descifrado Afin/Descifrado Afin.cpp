#include<bits/stdc++.h>

using namespace std;

vector<char> letras(27);
void abecedario();
int inversoMultiplicativo(int a,int b);
int euclidesExtendido(int, int);
int sgn(int);
int mod(int, int);
int s; //Coeficiente de Bezout para el inverso multiplicativo
void cifradoAfin(int a, int b, string palabra);
void descifradoAfin(int a, int b, string palabra);

int main(){
	int a;
	string palabra = "SLBCMVRBSHZBT@SRQVVMSZBVH@BVRQVLALHZBT@SRQVWQAXLZW@AQFQV";
	abecedario();
	cout<<"Desencriptando la palabra SLBCMVRBSHZBT@SRQVVMSZBVH@BVRQVLALHZBT@SRQVWQAXLZW@AQFQV"<<endl;
	while(a!=26){
		if(euclidesExtendido(a,27)==1){//si tiene inversa mod 27
			int inv= inversoMultiplicativo(a,27);
			for(int b=0; b<27; b++){
				descifradoAfin(a, b, palabra);
			}
		}
		a++;
	}
	return 0;
}

//Llenando el vector con letras
void abecedario(){
	for(char l= 'A'; l<='Z'; l++){
		if(l=='O'){
			letras[l-'A']='@';
			letras[l-'A'+1]=l;
		}
		else if(l>'O'){
			letras[l-'A'+1] = l;
		}
		else{
			letras[l-'A'] = l;
		}
	}
}

//Funcion modulo
int mod(int a, int b){
	return (a%b+b)%b;
}

// Alg descifrado Afin
void descifradoAfin(int a, int b, string palabra){
	string nueva_palabra = "";
	int inv = inversoMultiplicativo(a, 27);
	for(int i=0; i< palabra.size(); i++){
		int compensar=0; //Por la letra @=enie
		if(palabra[i]>='O'){
			compensar=1;
		}
		int pos = (inv* ((palabra[i]-'A'+ compensar)-b));
		if(palabra[i]=='@'){
			pos = (inv* (14-b));
		}
		pos = mod(pos, 27);
		nueva_palabra += letras[pos];
	}
	bool band= false;
	if(nueva_palabra == "NOEXISTENPREGUNTASSINRESPUESTASOLOPREGUNTASMALFORMULADAS"){
		band= true;
	}
	if(band){
		cout<<"-------------------------------------------------------------------------"<<endl;
	}
	cout<<"Posible palabra: "<<nueva_palabra<<endl;;
	if(band){
		cout<<"-------------------------------------------------------------------------"<<endl;
	}
}

//Funcion signo
int sgn(int x){
	if(x>=0){
		x = 1;
	}
	else{
		x=-1;
	}
	return x;
}

//Alg Euclides Extendido
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

//Alg para hallar el inverso de un numero
int inversoMultiplicativo(int a,int n){
	if(n<=0){
		return -1;
	}
	int k=1; 
	while(s < 0){
		s = s + n*k; //Solución general x = x0 + b/mcd(a,b) * k
		k++;
	}
	return s%n;
}


