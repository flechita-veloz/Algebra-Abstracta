El algoritmo "Genera Primos aleatorios", genera numeros primos aleatorios con la ayuda de la prueba de Miller Rabin y una funcion para generar numeros aleatorios de diferente cantidad de bits.
Para este algoritmo utilizamos un valor de confianza igual a 12, https://oeis.org/A014233 dice: "la primacía de los números<2^64 se puede determinar afirmando una pseudoprimalidad fuerte a todas las bases principales≤ 37". 
La referencia es el artículo reciente "Strong pseudoprimes to doce prime bases" de Sorenson y Webster.

Para su ejecucion: 
1. Ingrese el numero de bits que se desea que tengan los numeros primos.
2. Ingrese el numero de primos aleatorios que desea generar.
Finalmente el programa retornara la cantidad de numeros primos deseada en un tiempo aceptable.
