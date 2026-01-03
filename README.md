# ⚔️ Pokémon Battle Simulator

![Bannière Pokémon Battle](pokemon-battle.png)

> Un simulateur de combats Pokémon en équipe automatisé, développé en C++. Ce projet illustre l'héritage, le polymorphisme et la gestion de collections.

## 📋 À propos du projet

Ce projet est une application console qui simule un tournoi entre deux dresseurs. Chaque joueur reçoit une équipe générée aléatoirement (entre 3 et 6 Pokémon) et s'affronte dans un combat au tour par tour entièrement automatisé.

Le moteur du jeu prend en compte les statistiques (PV, Attaque, Défense, Vitesse), le hasard, et surtout les **affinités de types** pour déterminer le vainqueur.

### ✨ Fonctionnalités implémentées
* **Système de Types (Pierre-Feuille-Ciseaux) :** Gestion complète des classes dérivées `FirePokemon`, `WaterPokemon` et `GrassPokemon`.
    * *Eau > Feu* (x2 dégâts)
    * *Feu > Plante* (x2 dégâts)
    * *Plante > Eau* (x2 dégâts)
* **Combat d'Équipe Automatisé :** La fonction `autoBattle` gère le déroulement du match et le remplacement automatique des Pokémon K.O.
* **Attaques Spécifiques :** Chaque type possède son propre set d'attaques stocké dans une `std::map` (ex: *Hydrocanon*, *Déflagration*, *Canon Graine*).
* **Interface Console Rythmée :** Utilisation de la bibliothèque Windows pour temporiser l'affichage (`Sleep`) et rendre le combat lisible en temps réel.

## 🛠️ Installation et Utilisation

⚠️ **Note de compatibilité :** Ce projet utilise `<windows.h>` pour la gestion du temps. Il est conçu pour fonctionner sous **Windows**.

### Prérequis
* Un environnement Windows.
* Un compilateur C++ (G++ via MinGW est recommandé).

### 🚀 Lancer la simulation

1.  **Cloner le dépôt** :
    ```bash
    git clone [https://github.com/Logibuilder/pokemon-battle.git](https://github.com/Logibuilder/pokemon-battle.git)
    cd pokemon-battle
    ```

2.  **Compiler le code source** :
    ```bash
    g++ pokemon.cpp -o pokemon.exe
    ```

3.  **Exécuter le programme** :
    ```bash
    .\pokemon.exe
    ```

## 💻 Architecture du Code

Ce projet met en pratique les concepts clés de la Programmation Orientée Objet (POO) en C++ :

* **Polymorphisme & Héritage :** La classe abstraite `Pokemon` définit l'interface, tandis que les classes filles implémentent les spécificités (comme `getType()`).
* **Pointeurs & Gestion Mémoire :** Utilisation de `Pokemon*` dans les listes pour manipuler les objets originaux et permettre le polymorphisme.
* **Collections STL :**
    * `std::list` : Pour gérer les équipes dynamiques des joueurs.
    * `std::map` : Pour associer les noms d'attaques à leur puissance.



## 👤 Auteur

**Assane KANE**
* Portfolio : [https://logibuilder.github.io/assane.kane/]

---
*Projet réalisé dans un but éducatif pour démontrer la maîtrise du C++ et de la POO.*
