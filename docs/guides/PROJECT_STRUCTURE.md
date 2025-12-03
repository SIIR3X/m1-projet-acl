[← Retour au README](../../README.md)

# Structure du projet

## Introduction

Ce document présent l'organisation générale du projet.
L'objectif est d'offrir une vue d'ensemble claire pour faciliter la navigation, le développement et la maintenance.
Chaque dossier a un rôle précis et doit être utilisé conformément à la structure décrite ci-dessous.

## Arborescence du projet

Voici la structure actuelle du dépôt :

```bash
.
├── CMakeLists.txt               → CMake racine
├── Makefile                     → Automatisation (build, tests, docs, etc.)
├── README.md                    → Présentation générale du projet
├── LICENSE                      → Licence du projet
│
├── code/                        → Code source du projet
│   ├── cpp/                     → Partie C++
│   │   ├── CMakeLists.txt       → Configuration CMake pour la partie C++
│   │   ├── Doxyfile             → Configuration Doxygen (doc C++)
│   │   ├── include/             → Headers C++
│   │   ├── src/                 → Sources C++ (dont main.cpp)
│   │   └── tests/               → Tests unitaires C++ (GoogleTest)
│   │
│   └── java/                    → Partie Java (packages, classes, futurs tests Java)
│
├── data/                        → Données utilisées par le projet
│   └── 13_fichiers_JSON/        → Fichiers JSON fournis (par régions)
│
├── docs/                        → Documentation générée et guides
│   ├── cpp/                     → Documentation générée pour la partie C++
│   ├── java/                    → Documentation générée pour la partie Java
│   └── guides/                  → Documents internes
│       ├── COMPILATION.md       → Guide de compilation (C++ / Java)
│       ├── CONVENTIONS.md       → Conventions d’écriture et style
│       └── PROJECT_STRUCTURE.md → Document décrivant la structure du projet
│
├── sujet/                       → Documents d’énoncé et de présentation du projet
│   ├── 25-26_Projet_commun_ACL_presentation_aux_etudiants.pdf
│   ├── Sujet_projet_commun_algo_ACL_Minich.pdf
│   └── Sujet_projet_commun_algo_partie_ACL_25_26.doc.pdf
```