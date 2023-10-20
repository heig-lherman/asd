# Enoncé 

Ce laboratoire reprend largement les principes du labo 1 : comparer différents algorithmes de tri, mais cette fois 
avec des algorithmes de tri efficaces : 

* le tri rapide
* le tri par base

Dans un premier temps, mettez en oeuvre le tris en respectant les prototypes suivants: 

~~~cpp 
// tri rapide

template<typename Iterator> 
Iterator partition(Iterator first, 
                   Iterator last);

template<typename Iterator> 
void tri_rapide(Iterator first, 
                Iterator last);
~~~ 

Ces fonctions doivent être capable de traiter tout type de donnée qui met en oeuvre `operator<`. La fonction 
`partition` retourne la position du pivot après partition. Elle suppose qui le pivot a été placé en dernière 
position avant qu'on l'appelle. 

La fonction `tri_rapide` se charge de choisir de la récursion et de choisir le pivot de manière aléatoire. Elle
met en oeuvre l'approche "semi-récursive" vue au cours qui remplace l'appel récursif sur la partition la plus grande
par une itération. 

Pour le tri par base, respectez l'interface suivant 

~~~cpp 
// tri par base 

template<typename Iterator, typename Fn>
void tri_comptage(Iterator first,  
                  Iterator last, 
                  Iterator output_first,  
                  Fn index_fn,  
                  size_t N);

template<typename Iterator, size_t NBITS>
void tri_par_base(Iterator first,  
                  Iterator last);
~~~

La fonction `tri_comptage` effectue un tri comptage de la plage d'éléments `[first,last)` et stocke le résultat dans 
le tableau commençant à `output_first`. La case de comptage d'un élément est déterminée par la fonction `index_fn` passée
en paramètre. Il y a `N` cases de comptage en tout. 

La fonction `tri_par_base` effectue le tri par base sur des entiers non signés, ce qui est vérifié avec le code suivant : 

~~~cpp 
    using T = typename Iterator::value_type;
    static_assert(std::is_unsigned<T>::value);
~~~ 

Elle le fait en divisant les `numeric_limits<T>::digits` bits de la représentation de ces nombres par groupes de 
de `NBITS` bits et en appelant la fonction `tri_comptage` autant de fois que nécessaire. 

Le foncteur suivant vous est fourni pour extraire certains bits d'un nombre de type T. 

~~~cpp 
template<typename T>
class SomeBits {
    size_t shift;
    T mask;
public:
    SomeBits(size_t nombreDeBits, size_t part)
            : shift(part * nombreDeBits),
              mask((T(1u) << nombreDeBits) - T(1u)) {

    }
    T operator()(T const& t) {
        return T(mask & (t >> shift));
    }
};
~~~ 

## Tests à effectuer et rapport 

En plus des fonctions ci-dessus, nous vous demandons de fournir 

* un programme vérifiant que chacune des 4 fonctions ci-dessus fonctionnent correctement. 
* un programme effectuant des tests de temps d'exécution (mais pas de compte d'opérations) comme au labo 1. 

Ce 2ème programme doit vous permettre d'écrire un court rapport comparant 

* le tri rapide
* le tri par base en divisant les `unsigned int` par groupes de 1, 2, 4, 8 ou 16 bits. 

Pour ces comparaisons, triez des `vector<unsigned int>` remplis aléatoirement, dont la taille varie de 
10 à 1'000'000 éléments. 

Produisez 1 fichier .csv et 1 graphique résumant ces différentes mesures et expliquez les résultats observés. 
