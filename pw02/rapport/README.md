# Rapport

### Quantité théorique de permutations

Sachant que nous avons 9 pièces à placer, il y a ![formula](https://render.githubusercontent.com/render/math?math=9!)
façons de les arranger dans un puzzle de 3 par 3.

Chaque pièce pouvant avoir 4 rotations différentes, nous avons
alors ![formula](https://render.githubusercontent.com/render/math?math=4^9)
façon de tourner l'ensemble des 9 pièces.

Donc, il y a ![formula](https://render.githubusercontent.com/render/math?math=4^9\cdot9!=95126814720) façons d'arranger
les pièces du puzzle. Si on ignore les rotations du même arrangement, en divisant le nombre de permutations total par 4,
on aurait ![formula](https://render.githubusercontent.com/render/math?math=4^8\cdot9!=23781703680) permutations
possibles en tout.

Cependant, ce nombre représenterait le nombre de solutions uniquement si les pièces n'avaient aucune restriction pour
être posées les unes à côté des autres. Dans notre cas, seules les pièces avec des faces correspondantes peuvent se
retrouver côte à côte, réduisant grandement le nombre de solutions totales.

### Solutions du puzzle

Notre programme calcule toutes les solutions possibles, sans regrouper les différentes rotations d'un même arrangement.
Donc chaque arrangement donne lieu à quatre solutions qui sont des rotations autour de la case centrale du puzzle.

On trouve donc les 8 solutions suivantes :

```
9b 3c 8c 2c 6c 7c 4c 5b 1d 
8d 7d 1a 3d 6d 5c 9c 2d 4d 
7d 2d 1b 3d 4a 9d 5d 8a 6a 
6c 8c 5b 9b 4c 3b 1d 2b 7b 
5c 3c 7c 8d 4d 2c 6d 9c 1a 
4b 2b 9a 5a 6b 3b 1c 7b 8b 
1b 5d 4a 7a 6a 2a 8a 3a 9d 
1c 9a 6b 2a 4b 8b 7a 3a 5a 
```

Si on ignore les solutions qui sont de simples rotations d'un même arrangement, on peut garder les deux solutions
suivantes :

```
1c 9a 6b 2a 4b 8b 7a 3a 5a
1b 5d 4a 7a 6a 2a 8a 3a 9d
```

### Appels de la fonction récursive

La fonction récursive principale de notre programme est appelée 2819 fois en total pour trouver les 8 solutions
présentées ci-dessus.

On notera que ce nombre est d'un ordre de grandeur bien plus petit que le nombre de permutations. En effet, grâce aux
verifications effectuées dans le code, de nombreuses branches de l'arbre des possibilités ne sont pas traitées, car
menant à des solutions invalides. Notre code possède les caractéristiques suivantes :

- Le programme parcourt le puzzle dans l'ordre présenté ci-dessous, en recommençant à la première colonne quand on passe
  à la ligne suivante. L'ordre des valeurs dans une solution suit donc ce sens, dans un vecteur unidimensionnel.

```
 [1] [2] [3]
 [4] [5] [6]
 [7] [8] [9]
```

- Nous vérifions en premier temps si la pièce contient l'arrosoir inverse, comme ce dessin est incompatible avec tout
  autre côté, il est important de vérifier au plus vite si la position de l'arrosoir est valide (donc sur un des côtés
  extérieurs du puzzle).
- Ensuite, si le puzzle est vide, la pièce est placée sans autres vérifications.
- Dans le cas ou des pièces ont déjà été placées :
    - Les pièces précédentes sont comparées afin que les côtés adjacents soient compatibles
    - Les pièces en positions 4,5,7 et 8 sont comparées respectivement avec les pièces 2,3,5 et 6, car dans le cas où il
      y aurait deux symboles de la même catégorie (par exemple, deux parties d'arrosoir), il n'y aura aucune pièce
      compatible par la position suivante.

On notera aussi, selon le listing suivant, que ces vérifications permettent un temps d'exécution raisonnable (15 ms) :

```
❯ time ./src/cmake-build-debug/L2-recursivite 
9b 3c 8c 2c 6c 7c 4c 5b 1d 
8d 7d 1a 3d 6d 5c 9c 2d 4d 
7d 2d 1b 3d 4a 9d 5d 8a 6a 
6c 8c 5b 9b 4c 3b 1d 2b 7b 
5c 3c 7c 8d 4d 2c 6d 9c 1a 
4b 2b 9a 5a 6b 3b 1c 7b 8b 
1b 5d 4a 7a 6a 2a 8a 3a 9d 
1c 9a 6b 2a 4b 8b 7a 3a 5a 

Nombre d'appels de la fonction recursive : 2819
________________________________________________________
Executed in   14.48 millis    fish           external
   usr time   11.74 millis    0.00 micros   11.74 millis
   sys time    2.85 millis  888.00 micros    1.96 millis
```

### Le slogan original du puzzle

> Des millions de possibilités et une seule solution.

Le slogan initial est très vendeur et annonce directement la couleur de ce puzzle : malgré un très grand nombre
d'arrangements possible, ceux-ci ne sont presque jamais solution du puzzle. Cependant, suite aux résultats que nous
avons présentés ci-dessus, il est clair qu'il est principalement commercial et ne cherche pas à être mathématiquement
précis.

Premièrement, les possibilités pour ce puzzle se comptent en milliard. Ensuite, la solution ne sera jamais unique, à
cause des rotations d'un même arrangement. Pour correspondre à la réalité, il faudrait plutôt présenter le puzzle comme
suit :

> Des milliards de possibilités et seulement huit solutions.

Comme mentionné auparavant, chaque solution du puzzle engendre 3 autres solutions au travers d'une simple rotation
autour de la pièce centrale, ce qui permettrait de dire, en restant mathématiquement correct :

> Des milliards de possibilités et seulement deux solutions.

Ce dernier slogan reste bien plus vendeur que le précédent, mettant en avant le peu de possibilités réellement
solutions, tout en restant mathématiquement correct.