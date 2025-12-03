[← Retour au README](../../README.md)

# Prérequis du Projet

## Introduction
Ce document présente les outils nécessaires pour développer, compiler, tester et documenter le projet.  
Les instructions sont organisées par plateforme afin de simplifier l'installation pour chaque contributeur.

## Outils Généraux

- Git  
- Un terminal compatible POSIX  
  - Linux / macOS : terminal natif  
  - Windows : Git Bash recommandé  
- Un éditeur/IDE (VS Code, CLion, IntelliJ, etc.)

## Environnement C++

### Linux (Ubuntu/Debian)

#### Installation du compilateur C++

```bash
sudo apt update  
sudo apt install build-essential
```

#### Installation de CMake

```bash
sudo apt install cmake
```

#### Installation de Doxygen (optionnel)
```bash
sudo apt install doxygen graphviz
```

GoogleTest est automatiquement téléchargé par CMake : aucune installation manuelle n’est requise.

---

### Windows (Git Bash + MSYS2)
L’environnement recommandé pour Windows est MSYS2, qui fournit gcc, cmake et make compatibles avec Git Bash.

---

#### 1. Installer MSYS2

Télécharger : https://www.msys2.org/

---

#### 2. Mettre MSYS2 à jour

Ouvrir *MSYS2 MinGW64* puis exécuter :  

```bash
pacman -Syu
```

Relancer si demandé, puis :  

```bash
pacman -Syu
```

---

#### 3. Installer le compilateur C++ (MinGW-w64)

```bash
pacman -S mingw-w64-x86_64-gcc
```

---

#### 4. Installer CMake

```bash
pacman -S mingw-w64-x86_64-cmake
```

---

#### 5. Installer Make

```bash
pacman -S make
```

---

#### 6. Installer Doxygen (optionnel)

```bash
pacman -S doxygen graphviz
```

Git Bash utilisera automatiquement les outils installés par MSYS2.

## Environnement Java

La partie Java nécessite uniquement le **Java Development Kit (JDK)**, comprenant **`javac`**, **`java`** et **`javadoc`**.

### Linux (Ubuntu/Debian)

#### Installation de OpenJDK

```bash
sudo apt install default-jdk
```

### Installation de Javadoc (inclus dans le JDK)

Aucune installation supplémentaire n'est nécessaire.

---

### Windows

---

#### 1. Installer le JDK

Télécharger Open JDK.

### 2. Installer Javadoc

Aucune installation supplémentaire n'est nécessaire.

## Documentation

- Doxygen pour la partie C++  
- Javadoc pour la partie Java