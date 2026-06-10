# Organisation du projet Enigma Simulator

Ce document décrit l'organisation des fichiers du projet **Enigma Simulator**, leur rôle, ainsi que les règles générales à respecter pour garder un code clair, maintenable et évolutif.

Le projet a pour objectif de simuler une machine Enigma de manière réaliste, avec une architecture propre permettant plusieurs interfaces :

- une application console ;
- une version Arduino ;
- éventuellement une interface web ;
- un moteur Enigma réutilisable dans plusieurs contextes.

L'idée principale est de séparer clairement :

- le moteur de chiffrement Enigma ;
- l'interface utilisateur ;
- les fichiers de configuration ;
- les tests ;
- la documentation ;
- les scripts d'aide au développement.

---

## 1. Structure générale du dépôt

```text
enigma-simulator/
│
├── README.md
├── LICENSE
├── .gitignore
├── Makefile
├── CMakeLists.txt
│
├── docs/
│   ├── architecture.md
│   ├── enigma-rules.md
│   ├── usage-cli.md
│   ├── build.md
│   └── tests.md
│
├── config/
│   ├── rotors/
│   │   └── historical_rotors.ini
│   │
│   └── examples/
│       ├── enigma_m3_default.ini
│       └── enigma_m3_realistic.ini
│
├── include/
│   └── enigma/
│       ├── enigma.h
│       ├── machine.h
│       ├── rotor.h
│       ├── reflector.h
│       ├── plugboard.h
│       ├── config.h
│       ├── input.h
│       └── error.h
│
├── src/
│   └── enigma/
│       ├── enigma.c
│       ├── machine.c
│       ├── rotor.c
│       ├── reflector.c
│       ├── plugboard.c
│       ├── config.c
│       ├── input.c
│       └── error.c
│
├── apps/
│   ├── cli/
│   │   └── main.c
│   │
│   ├── arduino/
│   │   ├── README.md
│   │   └── enigma_arduino.ino
│   │
│   └── web/
│       └── README.md
│
├── tests/
│   ├── test_input.c
│   ├── test_rotor.c
│   ├── test_plugboard.c
│   ├── test_machine.c
│   └── test_enigma_vectors.c
│
└── scripts/
    ├── run_tests.sh
    └── format_check.sh
```

---

## 2. Principe d'architecture

Le projet doit être organisé autour d'une règle principale :

> Le moteur Enigma doit être indépendant de l'interface utilisateur.

Cela signifie que le code responsable du chiffrement ne doit pas dépendre de la console, d'Arduino, d'une page web ou d'un affichage particulier.

Le moteur Enigma doit pouvoir être utilisé par plusieurs applications différentes.

```text
Application console
        |
        v
Moteur Enigma
        ^
        |
Application Arduino
        ^
        |
Interface web
```

La console, Arduino et le web ne sont que des interfaces autour du même moteur.

---


## 3. Dossier `docs/`

Le dossier `docs/` contient la documentation technique du projet.

---

### `docs/architecture.md`

Document décrivant l'organisation globale du projet.

Il explique :

- la structure des dossiers ;
- le rôle des principaux fichiers ;
- la séparation entre moteur Enigma et interfaces ;
- les choix d'architecture ;
- les règles de développement.

Ce document est celui que vous êtes en train de lire.

---

### `docs/enigma-rules.md`

Document décrivant le fonctionnement théorique de la machine Enigma.

Il devra expliquer :

- le rôle du clavier ;
- le rôle du plugboard ;
- le rôle des rotors ;
- le rôle du réflecteur ;
- le trajet d'une lettre ;
- la rotation des rotors ;
- le double-stepping ;
- les caractères supportés.

Ce fichier servira de référence pour vérifier que le code respecte bien le fonctionnement réel d'une machine Enigma.

---

### `docs/usage-cli.md`

Document expliquant comment utiliser l'application console.

Il contient :

- les commandes disponibles ;
- les modes d'utilisation ;
- le mode lettre par lettre ;
- le mode phrase complète ;
- les options de configuration ;
- des exemples d'entrée et de sortie.

---

### `docs/build.md`

Document expliquant comment compiler le projet.

Il contient les instructions pour :

- Linux ;
- macOS ;
- Windows.

---

### `docs/tests.md`

Document expliquant comment lancer et comprendre les tests.

Il devra expliquer :

---

## 5. Dossier `config/`

Le dossier `config/` contient les fichiers de configuration utilisés par le simulateur.

Ces fichiers permettent de séparer les réglages du code source.


---

### `config/rotors/`

Ce dossier contient les définitions des rotors et réflecteurs historiques.

Exemple :

```text
config/rotors/historical_rotors.ini
```

Ce fichier contient:

```ini
[rotor_I]
wiring=EKMFLGDQVZNTOWYHXUSPAIBRCJ
notch=Q

[rotor_II]
wiring=AJDKSIRUXBLHWTMCQGZNPYFVOE
notch=E

[reflector_B]
wiring=YRUHQSLDPXNGOKMIEBFZCWVJAT
```

Ces données décrivent les composants disponibles, mais pas forcément la configuration active de la machine.

---

### `config/examples/`

Ce dossier contient des exemples de configuration complète.

Exemple :

```text
config/examples/enigma_m3_default.ini
```

Un fichier de configuration complète contient :

```ini
[machine]
rotors=I,II,III
reflector=B

[settings]
positions=A,A,A
rings=A,A,A

[plugboard]
pairs=AV BS CG DL FU HZ IN KM OW RX
```

Ce type de fichier décrit une machine prête à être utilisée.

---

## 4. Dossier `include/enigma/`

Le dossier `include/enigma/` contient les fichiers d'en-tête `.h`.

---

### `include/enigma/enigma.h`

Fichier d'en-tête principal du moteur.

Il pourra inclure les autres headers importants pour simplifier l'utilisation du moteur.

Exemple :

```c
#include "enigma/machine.h"
#include "enigma/config.h"
#include "enigma/error.h"
```

Ce fichier peut servir de point d'entrée public pour utiliser le moteur Enigma.

---

### `include/enigma/machine.h`

Déclare la structure représentant une machine Enigma complète.

Il pourra contenir :

- la structure `EnigmaMachine` ;
- les fonctions d'initialisation ;
- les fonctions de chiffrement ;
- les fonctions de remise à zéro de la machine.

Exemples de fonctions possibles :

```c
int enigma_machine_init(EnigmaMachine *machine, const EnigmaConfig *config);
bool enigma_encrypt_char(EnigmaMachine *machine, char input, char *output);
```

---

### `include/enigma/rotor.h`

Déclare la structure représentant un rotor.

Il pourra contenir :

- le câblage du rotor ;
- la position courante ;
- le ring setting ;
- l'encoche de rotation ;
- les fonctions de chiffrement aller et retour.

---

### `include/enigma/reflector.h`

Déclare la structure représentant le réflecteur.

Le réflecteur renvoie le signal vers les rotors en sens inverse.

Contrairement aux rotors, il ne tourne pas.

---

### `include/enigma/plugboard.h`

Déclare la structure représentant le plugboard.

Le plugboard est le tableau de connexions situé à l'avant de la machine.

Il permet d'échanger certaines lettres par paires.

Exemple :

```text
A <-> V
B <-> S
```

---

### `include/enigma/config.h`

Déclare les structures et fonctions liées à la configuration.

Il pourra contenir :

- la structure `EnigmaConfig` ;
- les fonctions de chargement de fichier ;
- les fonctions de validation de configuration.

---

### `include/enigma/input.h`

Déclare les fonctions de validation et de normalisation des entrées utilisateur.

Son rôle est de gérer les caractères acceptés par Enigma.

Règles prévues :

- les lettres minuscules sont converties en majuscules ;
- seules les lettres de A à Z sont acceptées ;
- les espaces sont ignorés ;
- les chiffres sont ignorés ;
- les accents sont ignorés ;
- la ponctuation est ignorée.

---

### `include/enigma/error.h`

Déclare les codes d'erreur utilisés dans le projet.

Cela permet d'éviter de retourner des valeurs magiques comme `-1`, `0`, `1` sans signification claire.

Exemple possible :

```c
typedef enum
{
    ENIGMA_OK = 0,
    ENIGMA_ERROR_INVALID_ARGUMENT,
    ENIGMA_ERROR_INVALID_CONFIG,
    ENIGMA_ERROR_FILE_NOT_FOUND
} EnigmaStatus;
```

---

## 5. Dossier `src/enigma/`

Le dossier `src/enigma/` contient les fichiers `.c`.

Ces fichiers contiennent l'implémentation réelle des fonctions déclarées dans les fichiers `.h`.

---

### `src/enigma/enigma.c`

Fichier pouvant contenir des fonctions de haut niveau du moteur Enigma.

Il peut servir à regrouper des fonctions pratiques, par exemple le chiffrement complet d'un texte.

---

### `src/enigma/machine.c`

Contient la logique d'une machine Enigma complète.

Il devra gérer :

- la rotation des rotors ;
- le passage dans le plugboard ;
- le passage dans les rotors à l'aller ;
- le passage dans le réflecteur ;
- le passage dans les rotors au retour ;
- le second passage dans le plugboard ;
- le chiffrement d'une lettre ;
- le double-stepping.

C'est un des fichiers les plus importants du projet.

---

### `src/enigma/rotor.c`

Contient la logique d'un rotor.

Il devra gérer :

- le câblage interne ;
- la conversion d'une lettre en index ;
- la conversion d'un index en lettre ;
- la position du rotor ;
- le ring setting ;
- le passage du signal en sens aller ;
- le passage du signal en sens retour ;
- la détection de l'encoche.

---

### `src/enigma/reflector.c`

Contient la logique du réflecteur.

Le réflecteur est plus simple qu'un rotor car il ne tourne pas.

Il doit cependant être validé correctement, car son câblage doit être cohérent.

---

### `src/enigma/plugboard.c`

Contient la logique du plugboard.

Il devra gérer :

- l'initialisation sans paires ;
- l'ajout de paires ;
- la validation des paires ;
- l'échange des lettres ;
- la détection des conflits.

Exemple de conflit :

```text
AB AC
```

Ici, la lettre `A` est utilisée dans deux paires différentes. Cette configuration doit être refusée.

---

### `src/enigma/config.c`

Contient la logique de chargement et validation des fichiers de configuration.

Il devra transformer un fichier de configuration en structure C utilisable par le moteur.

Le moteur Enigma ne doit pas lire directement les fichiers.

C'est le rôle du module `config`.

---

### `src/enigma/input.c`

Contient la logique de validation des entrées utilisateur.

Il devra proposer des fonctions pour :

- savoir si un caractère est accepté ;
- convertir une lettre minuscule en majuscule ;
- nettoyer une phrase complète ;
- ignorer les caractères non supportés.

Exemple :

```text
Entrée : Bonjour Quentin ! 123
Sortie : BONJOURQUENTIN
```

---

### `src/enigma/error.c`

Contient éventuellement des fonctions liées aux erreurs.

Exemple :

```c
const char *enigma_status_to_string(EnigmaStatus status);
```

Cette fonction permettrait de transformer un code d'erreur en message lisible.

---

## 8. Dossier `apps/`

Le dossier `apps/` contient les différentes applications utilisant le moteur Enigma.

Chaque application doit rester séparée du moteur.

---

### `apps/cli/`

Application console du projet.

Elle sera la première application développée.

---

### `apps/cli/main.c`

Point d'entrée du programme console.

Son rôle est de :

- afficher le menu ;
- lire les choix utilisateur ;
- lire une lettre ou une phrase ;
- charger une configuration ;
- appeler le moteur Enigma ;
- afficher le résultat.

Le fichier `main.c` ne doit pas contenir la logique interne d'Enigma.

Il ne doit pas gérer directement :

- le câblage des rotors ;
- le plugboard ;
- le réflecteur ;
- le double-stepping.

Il doit seulement coordonner les appels aux autres modules.

---

### `apps/arduino/`

Dossier réservé à une future version Arduino.

Le moteur Enigma devra rester suffisamment indépendant pour être réutilisé ici.

La version Arduino n'utilisera peut-être pas les fichiers `.ini`.

Elle pourra initialiser la configuration directement dans le code.

---

### `apps/web/`

Dossier réservé à une future version web.

---

## 9. Dossier `tests/`

Le dossier `tests/` contient les tests du projet.

Les tests permettent de vérifier automatiquement que le programme fonctionne correctement.

---

### `tests/test_input.c`

Teste la validation des entrées utilisateur.

Exemples à tester :

- `a` devient `A` ;
- `Z` reste `Z` ;
- `1` est ignoré ;
- `!` est ignoré ;
- une phrase complète est nettoyée correctement.

---

### `tests/test_rotor.c`

Teste le fonctionnement d'un rotor seul.

Il devra vérifier :

- le passage aller ;
- le passage retour ;
- la position du rotor ;
- le ring setting ;
- la détection de l'encoche.

---

### `tests/test_plugboard.c`

Teste le plugboard.

Il devra vérifier :

- une lettre non branchée reste identique ;
- une paire échange correctement deux lettres ;
- une configuration invalide est refusée ;
- une lettre ne peut pas être utilisée dans deux paires différentes.

---

### `tests/test_machine.c`

Teste la machine complète.

Il devra vérifier :

- le chiffrement d'une lettre ;
- la rotation des rotors ;
- le passage complet dans tous les composants ;
- le comportement avec des caractères invalides.

---

### `tests/test_enigma_vectors.c`

Teste le simulateur avec des résultats connus.

Ce fichier est important pour vérifier que le simulateur donne les mêmes résultats qu'une vraie configuration Enigma.

On y placera des tests de validation historique.

---

## 6. Dossier `scripts/`

Le dossier `scripts/` contient des scripts d'aide au développement.

Ces scripts ne font pas partie du moteur Enigma.

---

### `scripts/run_tests.sh`

Script permettant de lancer tous les tests plus facilement.
# 11. Gestion de l'état de la machine

Les positions des rotors, les réglages et l'état courant de la machine ne doivent pas être stockés dans des variables globales modifiables.

La bonne approche est de stocker l'état dans une structure.

Exemple conceptuel :

```c
typedef struct
{
    Rotor left;
    Rotor middle;
    Rotor right;
    Reflector reflector;
    Plugboard plugboard;
} EnigmaMachine;
```

Ainsi, plusieurs machines pourraient exister en même temps si nécessaire.

Cela rend aussi le code plus facile à tester.

---

## 12. Variables globales

Les variables globales modifiables doivent être évitées.

Mauvaise idée :

```c
int current_rotor_position = 0;
```

Bonne idée :

```c
typedef struct
{
    int position;
} Rotor;
```

Les constantes globales sont acceptables si elles représentent des données fixes.

Exemple :

```c
static const char ROTOR_I_WIRING[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
```

Règle générale :

```text
Constantes historiques : autorisées
État courant de la machine : dans une structure
Réglages utilisateur : dans une structure de configuration
Variables de saisie : locales dans l'application
```

---

## 13. Gestion des entrées utilisateur

Le simulateur doit accepter uniquement les lettres de A à Z.

Les règles prévues sont :

- les minuscules sont converties en majuscules ;
- les lettres de A à Z sont acceptées ;
- les autres caractères sont ignorés ;
- les caractères ignorés ne doivent pas faire tourner les rotors.

Exemple :

```text
Entrée utilisateur :
Bonjour Quentin ! 123

Texte réellement traité :
BONJOURQUENTIN
```

Cette logique sera placée dans le module `input`.

---

## 14. Objectif du premier jalon

Le premier jalon du projet ne doit pas encore implémenter toute la machine Enigma.

Il doit simplement permettre de valider la structure du projet.

Objectifs :

- créer l'arborescence ;
- compiler un premier programme ;
- afficher un menu console ;
- permettre la saisie lettre par lettre ;
- permettre la saisie d'une phrase complète ;
- nettoyer les entrées utilisateur ;
- ajouter les premiers tests du module `input`.

Ce premier jalon permettra de vérifier que le projet est bien organisé avant d'ajouter la logique complexe des rotors.

---

## 15. Règles de développement

Quelques règles à respecter pendant le développement :

1. Le fichier `main.c` ne doit pas contenir la logique Enigma.
2. Le moteur Enigma ne doit pas dépendre de l'application console.
3. Les variables globales modifiables doivent être évitées.# 11. Gestion de l'état de la machine

Les positions des rotors, les réglages et l'état courant de la machine ne doivent pas être stockés dans des variables globales modifiables.

La bonne approche est de stocker l'état dans une structure.

Exemple conceptuel :

```c
typedef struct
{
    Rotor left;
    Rotor middle;
    Rotor right;
    Reflector reflector;
    Plugboard plugboard;
} EnigmaMachine;
```

Ainsi, plusieurs machines pourraient exister en même temps si nécessaire.

Cela rend aussi le code plus facile à tester.

---

## 12. Variables globales

Les variables globales modifiables doivent être évitées.

Mauvaise idée :

```c
int current_rotor_position = 0;
```

Bonne idée :

```c
typedef struct
{
    int position;
} Rotor;
```

Les constantes globales sont acceptables si elles représentent des données fixes.

Exemple :

```c
static const char ROTOR_I_WIRING[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
```

Règle générale :

```text
Constantes historiques : autorisées
État courant de la machine : dans une structure
Réglages utilisateur : dans une structure de configuration
Variables de saisie : locales dans l'application
```

---

## 13. Gestion des entrées utilisateur

Le simulateur doit accepter uniquement les lettres de A à Z.

Les règles prévues sont :

- les minuscules sont converties en majuscules ;
- les lettres de A à Z sont acceptées ;
- les autres caractères sont ignorés ;
- les caractères ignorés ne doivent pas faire tourner les rotors.

Exemple :

```text
Entrée utilisateur :
Bonjour Quentin ! 123

Texte réellement traité :
BONJOURQUENTIN
```

Cette logique sera placée dans le module `input`.

---

## 14. Objectif du premier jalon

Le premier jalon du projet ne doit pas encore implémenter toute la machine Enigma.

Il doit simplement permettre de valider la structure du projet.

Objectifs :

- créer l'arborescence ;
- compiler un premier programme ;
- afficher un menu console ;
- permettre la saisie lettre par lettre ;
- permettre la saisie d'une phrase complète ;
- nettoyer les entrées utilisateur ;
- ajouter les premiers tests du module `input`.

Ce premier jalon permettra de vérifier que le projet est bien organisé avant d'ajouter la logique complexe des rotors.

---

## 15. Règles de développement

Quelques règles à respecter pendant le développement :

1. Le fichier `main.c` ne doit pas contenir la logique Enigma.
2. Le moteur Enigma ne doit pas dépendre de l'application console.
3. Les variables globales modifiables doivent être évitées.
4. Chaque module doit avoir un rôle clair.
5. Les fichiers `.h` déclarent les fonctions.
6. Les fichiers `.c` implémentent les fonctions.
7. Les tests doivent être ajoutés progressivement.
8. La documentation doit évoluer en même temps que le code.
9. Le projet doit rester portable entre Windows, Linux et macOS.
10. Le code doit rester compréhensible pour un développeur débutant, mais organisé proprement.

---

## 16. Évolution prévue

Le projet évoluera progressivement.

Ordre conseillé :

```text
1. Structure du dépôt
2. Application console minimale
3. Module input
4. Tests du module input
5. Module rotor
6. Tests du module rotor
7. Module reflector# 11. Gestion de l'état de la machine

Les positions des rotors, les réglages et l'état courant de la machine ne doivent pas être stockés dans des variables globales modifiables.

La bonne approche est de stocker l'état dans une structure.

Exemple conceptuel :

```c
typedef struct
{
    Rotor left;
    Rotor middle;
    Rotor right;
    Reflector reflector;
    Plugboard plugboard;
} EnigmaMachine;
```

Ainsi, plusieurs machines pourraient exister en même temps si nécessaire.

Cela rend aussi le code plus facile à tester.

---

## 12. Variables globales

Les variables globales modifiables doivent être évitées.

Mauvaise idée :

```c
int current_rotor_position = 0;
```

Bonne idée :

```c
typedef struct
{
    int position;
} Rotor;
```

Les constantes globales sont acceptables si elles représentent des données fixes.

Exemple :

```c
static const char ROTOR_I_WIRING[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
```

Règle générale :

```text
Constantes historiques : autorisées
État courant de la machine : dans une structure
Réglages utilisateur : dans une structure de configuration
Variables de saisie : locales dans l'application
```

---

## 13. Gestion des entrées utilisateur

Le simulateur doit accepter uniquement les lettres de A à Z.

Les règles prévues sont :

- les minuscules sont converties en majuscules ;
- les lettres de A à Z sont acceptées ;
- les autres caractères sont ignorés ;
- les caractères ignorés ne doivent pas faire tourner les rotors.

Exemple :

```text
Entrée utilisateur :
Bonjour Quentin ! 123

Texte réellement traité :
BONJOURQUENTIN
```

Cette logique sera placée dans le module `input`.

---

## 14. Objectif du premier jalon

Le premier jalon du projet ne doit pas encore implémenter toute la machine Enigma.

Il doit simplement permettre de valider la structure du projet.

Objectifs :

- créer l'arborescence ;
- compiler un premier programme ;
- afficher un menu console ;
- permettre la saisie lettre par lettre ;
- permettre la saisie d'une phrase complète ;
- nettoyer les entrées utilisateur ;
- ajouter les premiers tests du module `input`.

Ce premier jalon permettra de vérifier que le projet est bien organisé avant d'ajouter la logique complexe des rotors.

---

## 15. Règles de développement

Quelques règles à respecter pendant le développement :

1. Le fichier `main.c` ne doit pas contenir la logique Enigma.
2. Le moteur Enigma ne doit pas dépendre de l'application console.
3. Les variables globales modifiables doivent être évitées.
4. Chaque module doit avoir un rôle clair.
5. Les fichiers `.h` déclarent les fonctions.
6. Les fichiers `.c` implémentent les fonctions.
7. Les tests doivent être ajoutés progressivement.
8. La documentation doit évoluer en même temps que le code.
9. Le projet doit rester portable entre Windows, Linux et macOS.
10. Le code doit rester compréhensible pour un développeur débutant, mais organisé proprement.

---

## 16. Évolution prévue

Le projet évoluera progressivement.

Ordre conseillé :

```text
1. Structure du dépôt
2. Application console minimale
3. Module input
4. Tests du module input
5. Module rotor
6. Tests du module rotor
7. Module reflector
8. Module plugboard
9. Module machine
10. Rotation des rotors
11. Double-stepping
12. Chargement de fichiers de configuration
13. Tests complets avec résultats connus
14. Documentation complète
15. Version Arduino
16. Version web
```

Cette progression permet d'éviter de tout coder d'un coup et de garder un projet propre à chaque étape.
8. Module plugboard
9. Module machine
10. Rotation des rotors
11. Double-stepping
12. Chargement de fichiers de configuration
13. Tests complets avec résultats connus
14. Documentation complète
15. Version Arduino
16. Version web
```

Cette progression permet d'éviter de tout coder d'un coup et de garder un projet propre à chaque étape.
4. Chaque module doit avoir un rôle clair.
5. Les fichiers `.h` déclarent les fonctions.
6. Les fichiers `.c` implémentent les fonctions.
7. Les tests doivent être ajoutés progressivement.
8. La documentation doit évoluer en même temps que le code.
9. Le projet doit rester portable entre Windows, Linux et macOS.
10. Le code doit rester compréhensible pour un développeur débutant, mais organisé proprement.

---

## 16. Évolution prévue

Le projet évoluera progressivement.

Ordre conseillé :

```text
1. Structure du dépôt
2. Application console minimale
3. Module input
4. Tests du module input
5. Module rotor
6. Tests du module rotor
7. Module reflector
8. Module plugboard
9. Module machine
10. Rotation des rotors
11. Double-stepping
12. Chargement de fichiers de configuration
13. Tests complets avec résultats connus
14. Documentation complète
15. Version Arduino
16. Version web
```

Cette progression permet d'éviter de tout coder d'un coup et de garder un projet propre à chaque étape.
Exemple :

```bash
./scripts/run_tests.sh
```
Fichier généré via GPT 5.5