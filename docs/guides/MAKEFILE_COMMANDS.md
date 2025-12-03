[← Retour au README](../../README.md)

# Guide des Commandes Makefile

## Introduction

Ce document présente les principales commandes Make utilisées pour compiler, exécuter et nettoyer la partie C++ du projet.

## Commandes Makefile

### C++

- `make build-cpp`        : Compile entièrement la partie C++.
- `make run-cpp`          : Compile si nécessaire puis exécute l’application.
- `make run-tests-cpp`    : Compile si nécessaire puis exécute les tests C++.
- `make doc-cpp`          : Génère la documentation Doxygen.

### Java

- `make build-java`       : Compile tout le code Java (sources + tests).
- `make run-java`         : Compile uniquement les sources puis exécute la classe principale.
- `make run-tests-java`   : Compile tout puis exécute l’ensemble des tests JUnit.
- `make doc-java`         : Génère la documentation Javadoc pour le code Java.

### Formatage du Code

- `make format-cpp`       : Formate automatiquement tous les fichiers C++ avec **clang-format**.
- `make format-java`      : Formate automatiquement tous les fichiers Java avec **google-java-format**.

### Nettoyage

- `make clean`            : Supprime l’ensemble des fichiers de build.
- `make clean-doc`        : Supprime toutes les documentations générées.
- `make clean-all`        : Nettoie toutes les sorties de compilation et de documentation.
