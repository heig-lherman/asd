# Evaluation d'expressions

Le but de ce laboratoire est d'évaluer des expressions arithmétiques entières avec 2 approches 

* l'algorithme de Dijkstra à 2 piles vu au cours
* une approche récursive

Ils sont à mettre en oeuvre dans les fichiers [evaluator.cpp](src/evaluator.cpp) et [evaluator_recursive.cpp](src/evaluator_recursive.cpp)

Les 2 doivent passer le même codecheck : [https://codecheck.io/files/2105171211aco95yh2osm9zfvi3n3ix46eu](https://codecheck.io/files/2105171211aco95yh2osm9zfvi3n3ix46eu)

Les expressions testées et leurs valeurs sont disponibles dans le fichier [output.txt](./output.txt). 

Les résultats de vos codechecks doivent être sauvés dans le répertoire [zips](./zips).

Pour information, les solutions "officielles" utilisent les éléments suivants de la STL, mais vous n'êtes pas obligés de 
faire de même. 

* [std::stack](http://www.cplusplus.com/reference/stack/stack/)
* [std::string](http://www.cplusplus.com/reference/string/)
    * [string::find](http://www.cplusplus.com/reference/string/string/find/)
* [&lt;cctype&gt;](http://www.cplusplus.com/reference/cctype/)
    * [isblank](http://www.cplusplus.com/reference/cctype/isblank/)
    * [isdigit](http://www.cplusplus.com/reference/cctype/isdigit/)
* [std::istringstream](http://www.cplusplus.com/reference/sstream/istringstream/)
    * [istream::get](http://www.cplusplus.com/reference/istream/istream/get/)
    * [istream::putback](http://www.cplusplus.com/reference/istream/istream/putback/)