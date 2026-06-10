# Enigma Simulator Project Organization

This document describes the file organization of the **Enigma Simulator** project, the purpose of each folder and file, and the general rules to follow in order to keep the code clean, maintainable, and scalable.

The goal of this project is to simulate an Enigma machine in a realistic way, using a clean architecture that can support multiple interfaces:

- a console application;
- an Arduino version;
- a possible web interface;
- a reusable Enigma engine that can be used in different contexts.

The main idea is to clearly separate:

- the Enigma encryption engine;
- the user interface;
- configuration files;
- tests;
- documentation;
- development helper scripts.

---

## 1. General Repository Structure

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

## 2. Architecture Principle

The project must be organized around one main rule:

> The Enigma engine must be independent from the user interface.

This means that the code responsible for encryption must not depend on the console, Arduino, a web page, or any specific display system.

The Enigma engine should be reusable by multiple applications.

```text
Console application
        |
        v
Enigma engine
        ^
        |
Arduino application
        ^
        |
Web interface
```

The console application, Arduino version, and web interface are only different interfaces around the same engine.

---

## 3. Root Files

### `README.md`

Main file of the GitHub repository.

It should briefly present:

- the goal of the project;
- the current development status;
- how to build the program;
- how to run the program;
- usage examples;
- the main planned features.

This file is usually the first file read by someone discovering the project.

---

### `LICENSE`

File defining the license of the project.

It specifies what other people are allowed to do with the source code.

Possible licenses include:

- MIT;
- GPL;
- Apache 2.0.

For a personal and educational project, the MIT license is often simple and permissive.

---

### `.gitignore`

File used by Git to ignore specific files or folders.

It should avoid versioning:

- compiled files;
- build directories;
- temporary files;
- automatically generated files;
- editor-specific files.

Example:

```gitignore
build/
*.o
*.obj
*.exe
*.out
*.a
*.so
*.dll
*.dylib
.vscode/
.idea/
.DS_Store
Thumbs.db
```

---

### `Makefile`

File containing shortcut commands.

Even if the project uses CMake, the Makefile can simplify common commands.

Example commands:

```bash
make build
make test
make clean
```

The Makefile does not necessarily need to contain the full build logic. It can simply call CMake.

---

### `CMakeLists.txt`

Main CMake configuration file.

CMake allows the project to be built on several systems:

- Linux;
- macOS;
- Windows.

It can also manage:

- executables;
- internal libraries;
- compiler options;
- tests.

For a portable project, CMake is preferable to a Makefile alone.

---

## 4. `docs/` Folder

The `docs/` folder contains the technical documentation of the project.

The documentation should be written progressively, alongside the code.

---

### `docs/architecture.md`

Document describing the global organization of the project.

It explains:

- the folder structure;
- the purpose of the main files;
- the separation between the Enigma engine and the interfaces;
- architectural choices;
- development rules.

This is the document you are currently reading.

---

### `docs/enigma-rules.md`

Document describing the theoretical behavior of the Enigma machine.

It should explain:

- the role of the keyboard;
- the role of the plugboard;
- the role of the rotors;
- the role of the reflector;
- the path of a letter through the machine;
- rotor stepping;
- double-stepping;
- supported characters.

This file will serve as a reference to verify that the code follows the real behavior of an Enigma machine.

---

### `docs/usage-cli.md`

Document explaining how to use the console application.

It should contain:

- available commands;
- usage modes;
- letter-by-letter mode;
- full sentence mode;
- configuration options;
- input and output examples.

---

### `docs/build.md`

Document explaining how to build the project.

It should contain instructions for:

- Linux;
- macOS;
- Windows.

It may also specify the required tools:

- C compiler;
- CMake;
- Make;
- Git.

---

### `docs/tests.md`

Document explaining how to run and understand the tests.

It should explain:

- how to run the tests;
- how to add a new test;
- which modules are tested;
- how to read test results.

---

## 5. `config/` Folder

The `config/` folder contains configuration files used by the simulator.

These files make it possible to separate settings from the source code.

This avoids modifying and recompiling the program every time a configuration changes.

---

### `config/rotors/`

This folder contains the definitions of historical rotors and reflectors.

Example:

```text
config/rotors/historical_rotors.ini
```

This file may contain:

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

These values describe the available components, but not necessarily the active configuration of the machine.

---

### `config/examples/`

This folder contains examples of complete machine configurations.

Example:

```text
config/examples/enigma_m3_default.ini
```

A complete configuration file may contain:

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

This type of file describes a machine ready to be used.

---

## 6. `include/enigma/` Folder

The `include/enigma/` folder contains the `.h` header files.

In C, `.h` files are used to declare structures, types, and functions that can be used by other files.

They describe the public interface of the code.

---

### `include/enigma/enigma.h`

Main header file of the engine.

It may include other important headers to make the engine easier to use.

Example:

```c
#include "enigma/machine.h"
#include "enigma/config.h"
#include "enigma/error.h"
```

This file can act as the public entry point for using the Enigma engine.

---

### `include/enigma/machine.h`

Declares the structure representing a complete Enigma machine.

It may contain:

- the `EnigmaMachine` structure;
- initialization functions;
- encryption functions;
- machine reset functions.

Possible function examples:

```c
int enigma_machine_init(EnigmaMachine *machine, const EnigmaConfig *config);
bool enigma_encrypt_char(EnigmaMachine *machine, char input, char *output);
```

---

### `include/enigma/rotor.h`

Declares the structure representing a rotor.

It may contain:

- the rotor wiring;
- the current position;
- the ring setting;
- the turnover notch;
- forward and backward encryption functions.

---

### `include/enigma/reflector.h`

Declares the structure representing the reflector.

The reflector sends the signal back through the rotors in the opposite direction.

Unlike rotors, it does not rotate.

---

### `include/enigma/plugboard.h`

Declares the structure representing the plugboard.

The plugboard is the connection panel located at the front of the machine.

It allows some letters to be swapped in pairs.

Example:

```text
A <-> V
B <-> S
```

---

### `include/enigma/config.h`

Declares structures and functions related to configuration.

It may contain:

- the `EnigmaConfig` structure;
- file loading functions;
- configuration validation functions.

---

### `include/enigma/input.h`

Declares functions used to validate and normalize user input.

Its role is to handle the characters accepted by Enigma.

Planned rules:

- lowercase letters are converted to uppercase;
- only letters from A to Z are accepted;
- spaces are ignored;
- digits are ignored;
- accented characters are ignored;
- punctuation is ignored.

---

### `include/enigma/error.h`

Declares the error codes used in the project.

This avoids returning magic values such as `-1`, `0`, or `1` without a clear meaning.

Possible example:

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

## 7. `src/enigma/` Folder

The `src/enigma/` folder contains the `.c` files.

These files contain the actual implementation of the functions declared in the `.h` files.

---

### `src/enigma/enigma.c`

File that can contain high-level functions of the Enigma engine.

It may be used to group convenient functions, such as encrypting a full text.

---

### `src/enigma/machine.c`

Contains the logic of a complete Enigma machine.

It must handle:

- rotor stepping;
- the passage through the plugboard;
- the forward passage through the rotors;
- the passage through the reflector;
- the backward passage through the rotors;
- the second passage through the plugboard;
- encrypting a letter;
- double-stepping.

This is one of the most important files in the project.

---

### `src/enigma/rotor.c`

Contains the logic of a rotor.

It must handle:

- internal wiring;
- converting a letter to an index;
- converting an index to a letter;
- rotor position;
- ring setting;
- forward signal passage;
- backward signal passage;
- turnover notch detection.

---

### `src/enigma/reflector.c`

Contains the logic of the reflector.

The reflector is simpler than a rotor because it does not rotate.

However, it must still be validated correctly, because its wiring must be coherent.

---

### `src/enigma/plugboard.c`

Contains the logic of the plugboard.

It must handle:

- initialization without pairs;
- adding pairs;
- pair validation;
- letter swapping;
- conflict detection.

Conflict example:

```text
AB AC
```

Here, the letter `A` is used in two different pairs. This configuration must be rejected.

---

### `src/enigma/config.c`

Contains the logic used to load and validate configuration files.

It must transform a configuration file into a C structure usable by the engine.

The Enigma engine must not directly read files.

This is the role of the `config` module.

---

### `src/enigma/input.c`

Contains the logic used to validate user input.

It must provide functions to:

- check whether a character is accepted;
- convert a lowercase letter to uppercase;
- clean a complete sentence;
- ignore unsupported characters.

Example:

```text
Input: Bonjour Quentin ! 123
Output: BONJOURQUENTIN
```

---

### `src/enigma/error.c`

May contain functions related to errors.

Example:

```c
const char *enigma_status_to_string(EnigmaStatus status);
```

This function would convert an error code into a readable message.

---

## 8. `apps/` Folder

The `apps/` folder contains the different applications using the Enigma engine.

Each application must remain separated from the engine.

---

### `apps/cli/`

Console application of the project.

This will be the first application developed.

---

### `apps/cli/main.c`

Entry point of the console program.

Its role is to:

- display the menu;
- read user choices;
- read a letter or a sentence;
- load a configuration;
- call the Enigma engine;
- display the result.

The `main.c` file must not contain the internal logic of Enigma.

It must not directly handle:

- rotor wiring;
- the plugboard;
- the reflector;
- double-stepping.

It should only coordinate calls to the other modules.

---

### `apps/arduino/`

Folder reserved for a future Arduino version.

The Enigma engine should remain independent enough to be reused here.

The Arduino version may not use `.ini` files.

It may initialize the configuration directly in the code.

---

### `apps/web/`

Folder reserved for a future web version.

For now, this folder may contain only a `README.md`.

Later, it may contain:

- an HTML/CSS/JavaScript interface;
- a WebAssembly version of the engine;
- or a web client calling an API.

---

## 9. `tests/` Folder

The `tests/` folder contains the project tests.

Tests are used to automatically verify that the program works correctly.

They are essential for a clean project.

---

### `tests/test_input.c`

Tests user input validation.

Examples to test:

- `a` becomes `A`;
- `Z` remains `Z`;
- `1` is ignored;
- `!` is ignored;
- a full sentence is cleaned correctly.

---

### `tests/test_rotor.c`

Tests the behavior of a single rotor.

It should verify:

- forward signal passage;
- backward signal passage;
- rotor position;
- ring setting;
- turnover notch detection.

---

### `tests/test_plugboard.c`

Tests the plugboard.

It should verify:

- an unplugged letter remains unchanged;
- a pair correctly swaps two letters;
- an invalid configuration is rejected;
- a letter cannot be used in two different pairs.

---

### `tests/test_machine.c`

Tests the complete machine.

It should verify:

- encryption of one letter;
- rotor stepping;
- the complete signal path through all components;
- behavior with invalid characters.

---

### `tests/test_enigma_vectors.c`

Tests the simulator using known results.

This file is important to verify that the simulator produces the same results as a real Enigma configuration.

It will contain historical validation tests.

---

## 10. `scripts/` Folder

The `scripts/` folder contains development helper scripts.

These scripts are not part of the Enigma engine.

---

### `scripts/run_tests.sh`

Script used to run all tests more easily.

Example:

```bash
./scripts/run_tests.sh
```

---

### `scripts/format_check.sh`

Script used to check code formatting.

It may later be used with a tool such as `clang-format`.

---

## 11. Machine State Management

Rotor positions, settings, and the current machine state must not be stored in mutable global variables.

The correct approach is to store the state inside a structure.

Conceptual example:

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

This way, several machines could exist at the same time if needed.

It also makes the code easier to test.

---

## 12. Global Variables

Mutable global variables should be avoided.

Bad idea:

```c
int current_rotor_position = 0;
```

Better idea:

```c
typedef struct
{
    int position;
} Rotor;
```

Global constants are acceptable if they represent fixed data.

Example:

```c
static const char ROTOR_I_WIRING[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
```

General rule:

```text
Historical constants: allowed
Current machine state: stored inside a structure
User settings: stored inside a configuration structure
Input variables: local to the application
```

---

## 13. User Input Handling

The simulator must accept only letters from A to Z.

Planned rules:

- lowercase letters are converted to uppercase;
- letters from A to Z are accepted;
- all other characters are ignored;
- ignored characters must not rotate the rotors.

Example:

```text
User input:
Bonjour Quentin ! 123

Text actually processed:
BONJOURQUENTIN
```

This logic will be placed in the `input` module.

---

## 14. Goal of the First Milestone

The first milestone of the project should not implement the full Enigma machine yet.

It should simply validate the project structure.

Goals:

- create the folder structure;
- build a first program;
- display a console menu;
- allow letter-by-letter input;
- allow full sentence input;
- clean user input;
- add the first tests for the `input` module.

This first milestone will make it possible to check that the project is well organized before adding the complex rotor logic.

---

## 15. Development Rules

Some rules to follow during development:

1. The `main.c` file must not contain the Enigma logic.
2. The Enigma engine must not depend on the console application.
3. Mutable global variables should be avoided.
4. Each module must have a clear responsibility.
5. `.h` files declare functions.
6. `.c` files implement functions.
7. Tests must be added progressively.
8. Documentation must evolve alongside the code.
9. The project must remain portable between Windows, Linux, and macOS.
10. The code must remain understandable for a beginner developer while still being cleanly organized.

---

## 16. Planned Evolution

The project will evolve progressively.

Recommended order:

```text
1. Repository structure
2. Minimal console application
3. Input module
4. Input module tests
5. Rotor module
6. Rotor module tests
7. Reflector module
8. Plugboard module
9. Machine module
10. Rotor stepping
11. Double-stepping
12. Configuration file loading
13. Full tests with known results
14. Complete documentation
15. Arduino version
16. Web version
```

This progression avoids coding everything at once and helps keep the project clean at every step.

File generated via GPT 5.5