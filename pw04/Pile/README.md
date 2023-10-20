# Pile<C>

Le but de cet exercice est de passer le codeckeck suivant : [https://codecheck.io/files/2104121353e4vqkbekgens3idg4z5s3rfvt](https://codecheck.io/files/2104121353e4vqkbekgens3idg4z5s3rfvt)

Dans cet exercice nous mettons en oeuvre une pile dont la capacité est fixée dynamiquement à la
    construction et la taille varie selon les appels à push et pop. Le code c++ de cet exercice 
est fourni dans ce répertoire. Le seul fichier à modifier est `pile_impl.h`. 

Le constructeur doit allouer
    la mémoire nécessaire pour stocker n éléments de type T,
    mais sans construire ces éléments,
    la pile étant à l'origine vide.

Le destructeur devra à la fois détruire les éléments
présents et libérer la mémoire allouée par le constructeur.

La méthode push doit construire un élément par construisant
    par déplacement l'objet passé en paramètre à la
    bonne addresse mémoire. 

 pop doit détruire l'élément au sommet sans libérer de mémoire.

 push et pop doivent gérer la valeur de l'attribut  taille et offrir des garanties fortes. 

 En cas d'impossibilité d'effectuer l'opération
    demandée, toutes ces méthodes lèvent une exception std::out_of_range("...")
    où  "..." est le nom de la méthode. 

 Le constructeur de copie effectue une copie de la Pile reçue en paramètre
    avec la même capacité que celle-ci. 

 L'opérateur d'affectation par copie doit se comporter comme suit: si la taille
    de la Pile à copier est inférieure ou égale à la capacité
    courante de la pile, on ne réalloue pas de mémoire.
    Par contre, si la capacité actuelle est trop faible, on
    réalloue. 

 Dans le cas où il y a réutilisation de la capacité
    actuelle, il faut offrir une garantie faible en cas
    d'exception. Dans le cas où on réalloue, il faut offrir
    la garantie forte

 La méthode swap échange le contenu des 2 piles en offrant une garantie noexcept.
Elle doit vous aider à mettre en oeuvre un des cas de l'opérateur d'affectation. 