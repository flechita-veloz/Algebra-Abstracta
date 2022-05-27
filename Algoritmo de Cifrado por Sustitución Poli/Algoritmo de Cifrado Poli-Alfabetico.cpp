#include<iostream>
#include<stdlib.h>
using namespace std;

char abecedario[27];
void llenarAlfabeto();
void cifrar(string, string);
void descifrar(string, string);

int main(){
	string message, key;
	bool band=0;
	cout<<".:Si desea cifrar una palabra ingrese 1:.\n";
	cout<<".:Si desea descifrar una palabra ingrese 0:.\n";
	cin>>band;
	system("cls");
	cout<<"Ingrese la clave por favor: ";
	cin>>key;
	llenarAlfabeto();
	if(band){
		cout<<".:Inicilizando cifrado:."<<endl;
		cout<<"Por favor ingrese el mensaje a cifrar: ";
		cin>>message;
		cifrar(message, key);
	}
	else{
		cout<<".:Inicalizando descifrado:."<<endl;
		cout<<"Por favor ingrese el mensaje a descifrar: ";
		cin>>message;
		descifrar(message, key);
	}
	return 0;
}

//Funcion modulo
int mod(int a, int b){
	return (a%b+b)%b;
}

//llenamos nuestro alfabeto
void llenarAlfabeto(){
	for(char l= 'A'; l<= 'Z'; l++){
		if(l<'O'){
			abecedario[l-'A']= l;
		}
		else if(l=='O'){
			abecedario[l-'A']= '@';
			abecedario[l-'A'+1]= l;
		}
		else{
			abecedario[l-'A'+1]= l;
		}
	}
}

void cifrar(string message, string key){
	int d= key.size(), tam= message.size();
	char new_message[tam];
	for(int i=0; i< tam; i++){
		int mi, ki;
		(message[i]=='@') ? mi= 14:mi= message[i]-'A';
		(key[(i%d)]== '@') ? ki= 14:ki= key[(i%d)]-'A';
		if(message[i]>= 'O'){
			mi++;//Por la letra enie=@
		}
		if(key[(i%d)]>= 'O'){
			ki++;//Por la letra enie=@
		}
		new_message[i]= abecedario[mod(mi+ki,27)];
	}
	cout<<".:Imprimiendo palabra cifrada:.\n";
	cout<<new_message<<endl;
}

void descifrar(string message, string key){
	int d= key.size(), tam= message.size();
	char new_message[tam];
	for(int i=0; i< tam; i++){
		int emi, ki;
		(message[i]=='@') ? emi= 14:emi= message[i]-'A';
		(key[(i%d)]== '@') ? ki= 14:ki= key[(i%d)]-'A';
		if(message[i]>= 'O'){
			emi++;//Por la letra enie=@
		}
		if(key[(i%d)]>= 'O'){
			ki++;//Por la letra enie=@
		}
		new_message[i]= abecedario[mod(emi-ki, 27)];
	}
	cout<<".:Imprimiendo palabra descifrada:.\n";
	cout<<new_message<<endl;
}
