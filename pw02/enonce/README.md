Le but de ce laboratoire consiste à trouver toutes les solutions au jeu décrit dans la vidéo [https://youtu.be/bMBRjWbcn_I](https://youtu.be/bMBRjWbcn_I) et 
jouable sur [https://asd1-heigvd.github.io/ASD1-Labs/puzzle/](https://asd1-heigvd.github.io/ASD1-Labs/puzzle/). Vous 
pouvez également consulter les [slides de présentation](ASD-Labo2-Puzzle.pdf). 

Ces solutions selon écrites sous la forme d'une chaine de caractère contenant 9 fois le pattern "No " avec N un chiffre 
entre 1 et 9 codant la pièce à placer et o une lettre entre 'a' et 'd' codant l'orientation. Le site ci-dessus vous 
permet de visualiser le résultat.

Vous devez rendre 
* un programme dont les sources sont dans [src](../src) qui génère toutes les solutions, une par ligne. Ce programme 
  peut avoir la structure de votre choix, mais doit utiliser les fichiers pieces.h et pieces.cpp inchangés. 
* un court rapport au format markdown dans [rapport](../rapport) qui 
    * calcule de manière théorique le nombre de 
    permutations possible des 9 pièces pour former un carré, y compris les 4 rotations possibles pour chaque pièce 
    * compare ce calcul au nombre d'appels récursifs effectivement réalisés par votre algorithme. Idéalement votre 
  algorithme ne doit pas explorer les branches de l'arbre de récursion donc il est clair qu'elles ne mènent pas à une
  solution étant donné qu'au moins 2 pièces sont incompatibles parmi celles déjà posées.
    * compare vos résultats au texte commercial de Djeco : "des millions de possibilités et une seule solution"  
    
    
