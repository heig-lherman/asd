# ASD2022-L5 Buffer circulaire de capacité variable

Le but de ce laboratoire est de mettre en oeuvre un buffer circulaire de capacité variable sous la forme d'une classe générique ArrayDeque<T>

Pour tester cette classe, nous vous fournissons 4 codechecks de difficulté croissante. Notez cependant qu'il s'agit ici d'un seul exercice, le même code final devant être capable de passer les 4 codechecks.  

* [Buffer Circulaire (1)](https://codecheck.io/files/2104260833a69wz83ptbn5rt1m1o9mdgi98) spécifie la capacité 
  du buffer à la construction, et il n'est donc pas nécessaire d'avoir codé l'augmentation de capacité pour le 
  passer. 
* [Buffer Circulaire (2)](https://codecheck.io/files/2104260838dzzrkmsyltbns00m7ylp0f8q0)
  reprend le même test mais en stockant des objets de type de la classe C utilisée dans le 
  laboratoire sur l'allocation dynamique de mémoire affiche quels constructeurs, 
  `operator=` et destructeurs sont appelés. Allocation de la mémoire et construction des 
  éléments sont faites séparément, de même que destruction et libération. Pour rappel, 
    * il faut réserver la mémoire nécessaire pour stocker `capacité` éléments avec `operator new`
    * quand on écrit dans un emplacement mémoire actuellement non utilisé, il faut construire l'élément avec le `new` en place. 
    * quand on écrit dans un emplacement mémoire actuellement utilisé, il faut affecter avec l'opérateur `=`. 
    * quand on n'utilise plus un emplacement mémoire, il faut détruire l'élément qui s'y trouvait en appelant explicitement le destructeur, codecheck ne connaissant malheureusement pas `std::destroy_at`. 
    * quand on n'utilise plus de mémoire, il faut la libérer avec `operator delete`.
* [Buffer Circulaire (3)](https://codecheck.io/files/2104260839ci3p47azayry7cxu4mz90ku7s) 
  modifie le test en commençant avec un buffer de capacité nulle. Ensuite, il utilise 
  la stratégie de doublement si nécessaire vue au cours pour augmenter au fur et à mesure 
  la capacité. Il ajoute également une nouvelle méthode: `shrink_to_fit`, qui doit se 
  comporter comme celle de `std::vector`.
* [Buffer Circulaire (4)](https://codecheck.io/files/2104260840ca196gxe4wqd4k8h1kj84b79w)
  reprend tout d'abord le même test mais en stockant des objets qui affichent quels 
  constructeurs, `operator=` et destructeurs sont appelés. Ensuite, il vérifie les 
  garanties offertes par les différentes méthodes et par le constructeur de copie 
  quand la copie de certains éléments lève des exceptions. Toutes les méthodes doivent 
  offrir des garanties fortes et le constructeur de copie la garantie faible. 

Le code de ces 4 codechecks est disponible dans le répertoire [src](./src). Modifiez uniquement le fichier [ArrayDeque.h](./src/ArrayDeque.h). La sortie attendue de chacun des ces tests est disponible dans le répertoire [txt](./txt). 

Sauvegardez les fichiers zip générés par codecheck dans le répertoire [zips](./zips).

Pour vous aider, vous pouvez voir ou revoir les capsules vidéos suivantes, issues du cours d'ASD1 de 2020 : 

* [4.2 - Tableaux de taille fixe](https://tinyurl.com/yc88dntx) pour la gestion des garanties
  en cas d'exception
* [4.4 - Buffer circulaire](https://tinyurl.com/y9fb3bmm) pour le type de donnée buffer circulaire,
  mais présenté avec une capacité fixe
* [4.5 - Tableaux de capacité variable](https://tinyurl.com/yctdn646) pour la gestion de la 
capacité variable
