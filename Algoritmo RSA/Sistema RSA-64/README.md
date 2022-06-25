Sea "m" nuestro mensaje a cifrar:
Clave Publica: P = {e,n} -> c= P(m) = m^e mod n, P(m): Función de cifrado. 
Clave Privada: S = {d,n} -> m= S(c) = c^d mod n, S(c): Función de descifrado.

El Algoritmo "Sistema RSA- 64" genera una tabla de tres columnas y 10 filas para diferentes
valores de "m" E [2,n-1], y muestra su respectivo cifrado= P(m)= c y descifrado= S(c) = m'.
Para eso hace uso del algoritmo "RSA_KEY_GENERATOR(k)" con un valor de k= 64 bits, la cual
produce las claves "n", "e" y "d". 
El objetivo es mostrar que los valores de m y m' son iguales.
