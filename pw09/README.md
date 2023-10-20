# ASD L8 - Arbre AVL

> Groupe B: [redacted]

----

Le but de ce laboratoire est de mettre en oeuvre la classe générique `avlTree` qui met en oeuvre 
un arbre binaire de recherche équilibré selon les principes expliqués au cours pour les arbres AVL.
Le fichier [avlTree.h](./src/avlTree.h) en fournit l'interface et ne doit pas être modifié. 

Pour chacune des méthodes déclarées vous devez fournir une mise en oeuvre à définir dans le fichier
[avlTreeImplementation.h](./src/avlTreeImplementation.h), ainsi que du code testant son bon 
fonctionnement. Vous pouvez utiliser le fichier [main.cpp](./src/main.cpp) à votre guise lors 
du développement. Cependant, les tests doivent être réalisés au format [catch2](https://github.com/catchorg/Catch2) dans le fichier 
[catch2_tests/avlTest.cpp](./src/catch2_tests/avlTest.cpp) dont des exemples vous sont fournis. 
Organisez vos tests avec un `TEST_CASE` par fonction à tester et une `SECTION` par test réalisé 
sur cette fonction. Pensez à tous les scaenarii qu'il est pertinent de tester pour chacune des
fonctions à réaliser. Il n'est pas nécessaire de tester les fonctions que vous écrivez mais qui ne 
font pas partie de l'interface d'[avlTree.h](./src/avlTree.h) demandé. 

La classe `avlTree` utilise la structure de noeud générique `avl::Node` définie dans le fichier
[avlNode.h](./src/avlNode.h). Vous ne devez pas modifier cette structure. 

Ce fichier déclare également des fonctions prenant ces `avl::Node` en paramètre et qui sont 
appelées par les méthodes d'`avlTree`. Les fonctions `insert_in_subtree` et `show_indented` vous
sont fournies à titre d'exemple. Les fonctions déclarées dans [avlNode.h](./src/avlNode.h) doivent
être définies dans [avlNodeImplementation.h](./src/avlNodeImplementation.h). Il est probable que
la plupart de ces fonctions à écrire soient récursives, mais il est aussi possible d'en écrire 
certaines itérativement si vous préférez. 

Idéalement, les définitions des méthodes dans [avlTreeImplementation.h](./src/avlTreeImplementation.h) 
devraient essentiellement êtres des appels à des fonctions définies dans définies dans 
[avlNodeImplementation.h](./src/avlNodeImplementation.h). L'immense majorité de ces méthodes
ne devraient faire qu'une ligne. 

Pour vous aider dans votre travail, nous fournissons 2 méthodes 

* `insert(Key const&)` insère la clé dans l'arbre binaire de recherche. Attention, elle met en oeuvre l'algorithme
de base sans équilibrage AVL et devra donc être modifiée par vos soins.
* `show_indented(ostream&)` affiche le contenu de l'arbre sous forme indentée, avec des `.` pour représenter 
les pointeurs nuls enfants de noeuds de degrés 1. Les enfants nuls des feuilles ne sont pas représentées. A titre 
  d'exemple, l'arbre binaire de recherche (non équilibré AVL) de lequel on a inséré les valeurs `3, 5, 2, 6, 8, 4, 6, 4, 1` 
  dans cet ordre est représenté sous la forme 
~~~
3
|_ 2
|  |_ 1
|  |_ .
|_ 5
   |_ 4
   |_ 6
      |_ .
      |_ 8
~~~

Le nom des méthodes est a priori suffisamment explicite pour que le comportement attendu n'aie pas besoin d'être 
documenté, mais si vous avez un doute sur ce qu'elles doivent réaliser n'hésitez pas à le demander à votre assistant. 

Pour les opérateurs d'entrée / sortie `operator<<` et `operator>>`, le format attendu est celui d'une liste imbriquée 
où tous les pointeurs nuls sont représentés par un `.`. A titre d'exemple la représentation de l'arbre ci-dessus serait 
`3(2(1(.,.),.),5(4(.,.),6(.,8(.,.))))`. La représentation d'un arbre vide serait un simple point, i.e. `.` Notez 
qu'`operator>>` peut supposer le flux d'entrée correct et ne doit pas vérifier que l'arbre lu est effectivement
équilibré AVL. Par contre il doit calculer les hauteurs des noeuds correctement. 

## Conseils

Il est probablement plus simple de mettre en oeuvre cette classe progressivement 
* d'abord écrire un arbre binaire de recherche sans équilibrage AVL
* puis ajouter le mise à jour de l'attribut `hauteur` des noeuds
* puis ajouter l'équilibrage par rotation AVL en sortie de récursion dans les méthodes où c'est pertinent

Prenez soin de dupliquer le moins possible de code. Découpez intelligemment votre code en fonctions. Notez que 
la structure de noeud permet souvent de traiter les cotés gauche et droit de manière identique via leurs indices 
LEFT et RIGHT. 

N'écrivez de commentaires que si le choix des noms et le découpage de votre code en fonctions ne permet pas de le 
comprendre aisément. Ce serait évidemment un mauvais signe. 

