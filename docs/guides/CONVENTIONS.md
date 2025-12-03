[← Retour au README](../../README.md)

# Conventions du Projet

## Introduction

Ce document définit les règles de style, de structure et d'organisation utilisées dans ce projet.

Il vise à :

- garantir la cohérence du code entre les différents langages (C, C++ et Java),
- faciliter la lisibilité et la maintenance,
- simplifier la navigation dans l'arborescence du projet,
- assurer une documentation uniforme.

Ces conventions doivent être respectées par **tout contributeur** lors de l'écriture ou de la modification du code.

## Conventions d'écriture

### Style commun (tous les langages)

- Les **identifiants** (variables, fonctions, méthodes) sont écrits en **`camelCase`**.
- Les **types**, **classes**, **structures** et **énumérations sont nommés en **`PascalCase`**.
- Les **constantes** sont écrites en **`UPPER_SNAKE_CASE`**.
- Les **champs privés** d'une classe sont préfixés par **`_`**.
- Tous les identifiants (variables, fonctions/méthodes, classes, paramètres, champs…) doivent être **nommés en français**.

## C++

- Les **fichiers `.cpp` et `.h`** doivent être nommés en **`snake_case`**
- L’indentation utilise **4 espaces**.
- Les **accolades ouvrantes** sont placées **sur une nouvelle ligne**.

## Java

- Les **fichiers sources** doivent être nommés en **`PascalCase`** 
- L’indentation utilise **2 espaces**.
- Les **accolades ouvrantes restent sur la même ligne** (style K&R / Google).