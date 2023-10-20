# Allocations en C++

Le but de cet exercice est de passer le codecheck suivant : 

[https://codecheck.io/files/2104121332d4y630pc13cyzg9rbr4bqjnnm](https://codecheck.io/files/2104121332d4y630pc13cyzg9rbr4bqjnnm)

Le code C++ de ce codecheck est disponible dans ce répertoire. Le seul fichier qui doit 
être modifié est le fichier main.cpp, et ce uniquement entre les 6 paires de commentaires 

~~~cpp 
// AJOUTEZ VOTRE CODE ICI ...

// ... FIN DE VOTRE CODE
~~~

Dans cet exercice, vous devez choisir où et comment créer et éventuellement détruire des variables de type C. Cette class C affiche quand ses objets sont construits et détruits. Elle reçoit un entier en paramètre 
du constructeur. Cet entier est affiché à la construction et à la destruction. Vous ne pouvez utiliser aucune fonction d'affichage (cout, cerr, printf, ...). Enfin, vous n'avez malheureusement pas accès à std::destroy_at ce codecheck n'acceptant pas encore le C++17.

Le résultat final doit afficher la sortie suivante et ne pas souffrir de fuite de mémoire. Essayez 
d'utiliser toujours la méthode la plus simple quand plusieurs sont disponibles. Plus spécifiquement, 
utilisez de préférence, mais seulement si c'est possible,

1. variable automatique
2. variable statique
3. new 
4. new[]
5. la combinaison de ::operator new et new() 

N'utilisez pas de variable globale de type C.

N'oubliez pas de détruire tout objet construit et de libérer toute mémoire allouée si c'est votre responsabilité.

~~~
enter main
ic(1)
enter f0
ic(2) ic(3)
leave f0
d(3)
enter f0
ic(4)
leave f0
d(4)
enter f1
ic(5)
leave f1

enter f2
ic(6) ic(7)
leave f2

enter f3
ic(8)
leave f3
d(7) d(6) d(5)
enter f4
ic(9) ic(10)
leave f4
d(8)
enter f4
ic(11)
leave f4
d(9) d(10) d(11)
leave main
d(1) d(2)
~~~

N'hésitez pas à revoir les videos suivantes pour vous inspirer

* [X.1 - new & delete](https://youtu.be/h4v9GbVMbZc)
* [X.2 - ::operator new et new()](https://youtu.be/yjfcEBcw4wE)
