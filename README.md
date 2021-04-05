# Encodage de Parachute

## Introduction

Notre projet consiste à réaliser un logiciel permettant d’encoder un message sur un parachute, comme vu sur le parachute utilisé lors de l'atterrissage du rover Perseverance. Ce logiciel est muni de différentes fonctionnalités et a été codé à l’aide de la bibliothèque Qt et du logiciel Qt Creator.

## Conception

Le logiciel a été conçu en suivant le patron d'architecture MVP (Modèle-Vue-Présentation). Le modèle s’occupe de la conversion du message textuel en un tableau de bits. La vue concerne le parachute, l’affichage binaire et le widget de couleur. Dans notre cas, le MainWindow est la présentation.

Les interactions entre les différents composants se font à l’aide des “connect” qui permet de lier un signal à un slot pour gérer un événement. Nous avons pris le soin de bien mettre le modificateur d’accès adapté (public ou privé) pour les différents attributs et méthodes.

Le projet possède aussi une arborescence adaptée avec des dossiers pour les fichiers d'entête, les fichiers sources et les icônes.


## Fonctionnalités

Nous avons implémenté diverses fonctionnalités:

- Dessin du parachute  
- Dessin de la vue binaire  
- Ajout des sliders et spinbox pour régler le nombre de secteurs/pistes  
- Traduction automatique  
- Sauvegarde et ouverture  
- Disque central vide  
- Changement de caractère de référence  
- Choix des couleurs et couleur primaire aléatoire  
- Incrémentation des sliders de 7 en 7 ou de 10 en 10  
- Affichage de blocs de 10 trapèzes  
- Mode sombre  
- Animation au lancement  

## Installation

Exécuter les commandes suivantes dans la racine du projet:
	
	qmake
	make

Pour lancer le logiciel, faire:

	./ParachuteEncoder

Pour nettoyer le répertoire, faire:

	make clean
	

## Conclusion

Pour conclure, la réalisation du projet avec Qt Creator était à la fois facile, avec le Qt Designer pour faire l’interface et les différents outils de génération de fichier, et difficile avec le système de contrôle de version git inclus dans ce logiciel qui est des fois capricieux.

Ce projet nous a tout de même permis de consolider nos connaissances et d’apprendre plus sur Qt en découvrant de nouveaux widgets comme QPropertyAnimation pour animer les propriétés des widgets.


