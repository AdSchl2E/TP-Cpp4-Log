# TP C++ n°4 : Analyse de logs apache

Cette application permet de lire et d'analyser un fichier de logs apache.


## Fonctionnalités

Utilisation : ./analog [-e] [-t hour] [-g dotFile] [-u localURL] [-h] [-r] [-v] <file.log>

Par défaut l'application affiche dans le terminal la liste des 10 documents les plus consultés par ordre décroissant de popularité.

Plusieurs options sont proposées : 

[-e] : exclut la liste d'extensions suivantes : .js, .css, .jpg, .gif, .png, .ico, .ics, .doc, .docx, .pdf, .xml, .zip et .txt.

[-t hour] : seuls les hits qui sont dans le créneau horaire correspondant à l’intervalle [heure, heure+1[ sont pris en compte.

[-g dotFile] : produit un fichier au format GraphViz du graphe analysé

[-u localURL] : permet de spécifier l'url locale (**intranet-if.insa-lyon.fr** par défaut)

[-h] : affiche l'aide dans le terminal

[-r] : permet de prendre en compte les redirections 

[-v] : mode verbose

<file.log> : le fichier à analyser, chaque ligne doit avoir la structure suivante qui suit

**192.168.0.0 - - [08/Sep/2012 :11:16:02 +0200] "GET /temps/4IF16.html HTTP/1.1" 200 12106 "http://intranet-if.insa-lyon.fr/temps/4IF15.html"**
**"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1"**


## Framework de test

Un total de 10 tests ont été mis en place pour tester les différentes fonctionnalités.
Les détails de ces tests peuvent être retrouvés dans les dossiers correspondants et seront montrés lors du lancement du framework.
Pour le faire marcher, il suffit de lancer `./mktest.sh` dans le dossier **Tests** après avoir compilé l'exécutable.
Le fichier Makefile permet de lancer la compilation sans étapes supplémentaires.


## Classes utilisées

Il a été choisi de créer deux classes pour répondre au besoin : 

La classe **ReadFile**, qui permet de gérer l'ouverture d'un fichier log et d'extraire les informations contenues dans chaque ligne;
et la classe **StatLog**, qui permet de créer un graphe (sous la forme d'un fichier dot) ainsi qu'un top 10 des pages les plus visitées,
à partir du fichier log manipulé avec la classe **ReadFile**.

Chacune des classes est pensée pour être réutilisable et peut ếtre adaptée pour éventuellement créer d'autres applications.