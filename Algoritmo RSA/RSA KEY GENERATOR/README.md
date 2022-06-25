El algoritmo RSA KEY GENERATOR produce el Sistema Criptografico RSA, donde: 

Clave Publica: P = {e,n} -> c= P(m) = m^e mod n, P(m): Funcion de cifrado.
Clave Privada: S = {d,n} -> m= S(c) = c^d mod n,  S(c): Funcion de descifrado.

El algoritmo recibe como entrada un numero k de bits y retorna las claves n, e y d.

Su funcionamiento se basa en los siguientes pasos: 
1. Generar dos primos aleatorios "p" y "q" tal que p != q. Cada uno de k/2 bits. 
   Esto lo hacemos gracias al algoritmo de Miller Rabin: esPrimoMR(N), que retorna un 
   booleano e indica si el numero N es primo o no. Ademas hacemos uso de la funcion 
   randomGen_Primos(b), que genera primos aleatorios de b bits, esta funcion se apoya de la
   funcion randomBits(b) que genera numeros aleatorios de b bits.
2. Calculamos "n" = pxq.
3. Calculamos la Funcion de Euler de n= phi(n).
   Por teorema, si p y q primos -> phi(n) = phi(p)xphi(q)= (p-1)x(q-1).
4. Calculamos aleatoriamente "e" E [2,n-1], tal que gcd(e,phi(n))= 1.
   Esto lo hacemos gracias a la funcion  randomGen_e(n, phi(n)), que nos genera el numero 
   aleatorio "e", esta funcion se apoya del algoritmo euclides(a,b), la cual nos asegura 
   que el gcd(e,phi(n)) sea igual a 1.
5. Hallamos d tal que "exd" sea congruente a 1 mod phi(n). 
   Esto lo hacemos gracias al algoritmo inversoMultiplicativo(a,n), la cual genera el inverso 
   del numero "a" mod "n", esta funcion se apoya del algoritmo extendido de euclides, que halla
   los coeficientes de Bezout "s" y "t", necesarios para encontrar el inverso multiplicativo.
7. Finalmente imprimimos el valor de n, e y d.
