
# Hive

Sujet : https://moodle.utc.fr/pluginfile.php/260046/mod_resource/content/5/LO21_Projet_A24_Hive.pdf
Règles : https://www.regledujeu.fr/hive/

## by Abel B, Valentin C, Juliette C, Florian H et Léonard V

## Les classes

### Case
- case.cpp
- case.h
Les cases sont représentées sous forme d'une liste chaînées avec 6 maillons par case (hexagone = six côtés donc six maillons). Une case remplie doit toujours être entourée de 6 cases alentours au cas où elles viendraient à être utilisées ! Les fonctions pour créer les cases sont assez explicites.

### Insecte
- insecte.cpp
- insecte.h

Classe mère des classes comme Araignée, Abeille, Fourmi, ... qui héritent de cette dernière. Elle a pour but de définit un insecte de manière générale avec les attributs généraux à tous les insectes. (Le concept d'héritage a pas encore été vu en cours mais il est pas très compliqué).


===========================

A LIRE A LA FIN, c'est du détail :

La classe est remplie de syntaxes de mots-clefs un peu bizarres (virtual, const à la fin d'une fonction, "= 0", je vais essayer d'expliquer.)
- virtual sert à indiquer que la fonction peut-être redéfinie quand on en hérite. Par exemple, la classe "abeille" va redéfinir la fonction "get_moves_possibles" pour obtenir la liste des mouvements possibles, puisqu'elle a son propre système de mouvement (comme tous les insectes).

- const, sert à dire que la fonction modifie pas la classe (ce qui permet d'utiliser la fonction dans un objet même s'il est constant.)

- = 0, sert à dire que toute classe qui hérite de cette fonction est OBLIGEE de la définir. Par exemple, pour get_moves_possibles, chaque type d'insecte est obligé de définir cette fonction pour obtenir sa liste des mouvements possibles pour un plateau donné.

Il y a peut-être plein de mots-celfs un peu bizarres mais ils sont souvent un peu anecdotiques et le code marcherait sans, hésitez pas à google un max / à demander sur le groupe.

============================

### Abeille, Araignée, Fourmi, Scarabé, Sauterelle, Moustique, Coccinelle
- abeille.cpp
- abeille.h
- araignee.cpp
- araignee.h
- fourmi.cpp
- fourmi.h
- scarabe.cpp
- scarabe.h
- sauterelle.cpp
- sauterelle.h
- moustique.cpp
- moustique.h
- coccinelle.cpp
- coccinelle.h

Fichiers qui gèrent les sous-classes de Insecte.

L'abeille se déplace d'une case par une case maximum, et elle doit être placée au bout du 4ème tour inclus maximum. Si elle est encerclée, le jeu se termine.

L'araignée se déplace par 3 cases exactement.

La fourmi se déplace sur les contours du jeu.

Le scarabé se déplace de 1 en 1 même par dessus les pièces (dans ce cas là les pièces en dessous sont bloquées).

La sauterelle je sais plus

Le moustique se déplace sur les cases sur lesquelles les pièces adjacentes peuvent aller

La coccinelle je sais plus

### Partie
- partie.cpp
- partie.h

La partie est gérée par un objet de type Partie. Celle-ci gère les tours des joueurs et les variables joueurs. Elle contient un plateau.

### Plateau
- plateau.cpp
- plateau.H
Celle-ci gère le plateau (donc placement de la première clase et création / suppression des cases). Elle devrait pas être trop compliquée mais attention à bien gérer la mémoire quoi.

### Joueur
- joueur.cpp
- joueur.h
Classe pour les joueurs.

### MainWindow
- mainwindow.cpp
- mainwindow.h
- maindinow.ui
Classe créée par Qt Creator qui est la fenêtre principale. Le fichier ".ui" sert à design la fenêtre principale (ça sera vu en TD sûrement sinon go tuto YouTube).

## Les énumérations

Les énumérations sont un type très simple en C++, ils servent à faire correspondre un nombre à un nom. Par exemple, dans le fichier teams.h, on crée une énumération avec NOIR et BLANC. Le compilateur va alors décider que NOIR = 1 et BLANC = 2, et on va pouvoir créer des variables de type Equipe qui vont pouvoir valoir soit NOIR soit BLANC (mais pas autre chose, c'est tout l'intérêt). C'est pas essentiel mais c'est plus clair comme ça et ça évite d'avoir à décider arbitrairement de nombres pour représenter des choses comme des couleurs.

Y a [cette page](https://www.learncpp.com/cpp-tutorial/unscoped-enumerations/) et [cette page](https://www.learncpp.com/cpp-tutorial/unscoped-enumerator-integral-conversions/) qui expliquent ce que c'est, et si c'est pas clair y a plein d'explications sur youtube / internet. Le mot-clef "class" que j'ajoute après "enum" n'a pas grand chose à voir avec le vrai mot-clef "class", il permet juste d'interdire les conversions d'un nombre entier vers une équipe/un type d'insecte/une direction, c'est expliqué sur [cette page](https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/).

- teams.h pour les équipes (NOIR ou BLANC)

- types.h pour le type d'un insecte (ARAIGNEE, SCARABE, ... ainsi que NULL au cas où). On pourrait directement utiliser le type de la classe pour identifier un insecte mais c'est super relou et incompréhensible comme syntaxe, alors autant utiliser une variable "type" de type TypeInsecte pour identifier une race d'insecte.

- directions.h qui définit six directions, HAUT_DROIT, DROITE, BAS_DROIT, HAUT_GAUCHE, GAUCHE, BAS_GAUCHE.

Les variables du style "DIRECTION_ALL" servent à lister toutes les directions possibles histoire de pouvoir boucler sur toutes les directions sans avoir à les lister une par une (sinon relou et en plus si on ajoute une direction / change un nom de direction faut tout changer).

## Le .pro

Le fichier .pro sert est automatiquement généré par Qt Creator, et la plupart du temps il n'y a pas besoin d'y toucher. Il permet de lister les fichiers à compiler pour le compilateur, son contenu est très facilement compréhensible. Quand on crée un nouveau fichier avec Qt Creator, il ajoute automatiquement ce fichier à la liste des fichiers à compiler. Par contre, quand on supprime un fichier / le renomme, il faut le faire manuellement. Il y a d'autres infos dans le fichier .pro, genre la version de C++ à utiliser, le nom du projet, et on peut ajouter d'autres Informations comme la version désirée d'une librairie (#include <...>) à utiliser, où même un chemin d'accès pour une librairie qui ne serait pas conventionnellement installée, bref ça peut aller loin. Mais Qt Creator se charge de tout.

## Le .gitignore

/!\ Commme le nom du fichier commence par un "." il est peut-être caché par Windows/Linux par défaut.

Le fichier .gitignore sert à dire quels sont les fichiers à ignorer pour GitHub. Le gros dossier à ignorer, c'est le dossier "build" qui se crée quand on compile le projet. Pour l'instant ce serait cool de le laisser dans le .gitignore pour par que les fichiers compilés se retrouvent sur le github (ça prend de la place pour rien).

# Informations

## Conventions de nommage

Je suis chaud qu'on utilise les noms avec des minuscules et des underscores pour les variables et les fonctions, genre "premiere_case, insecte_actuel" et pour les types on met des majuscules, donc pour déclarer une variable de type insecte "Insecte mon_insecte;".
Après on peut ptet utiliser autre chose comme vous voulez, ça m'est égal.

## Pour compiler

Installez Qt Creator, téléchargez le fichier (grâce à un git clone idéalement), et compilez le projet depuis l'IDE.

## TO-DO LIST

- Le rapport pour cette semaine
- Les déplacements pour chaque insecte
- L'interface graphique mdr
- La classe "Joueur"
- La classe "Partie"
- ... Bien plus
