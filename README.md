# 🐚 Minishell  
### 💻 Un interpréteur de commandes inspiré de Bash  

## 📌 Description  
Minishell est une implémentation simple mais complète d'un **interpréteur de commandes** (shell), inspiré de **Bash**. Ce projet a été réalisé dans le cadre de l'École 42, dans le but de comprendre la gestion des processus, des entrées/sorties et des pipes sous Linux.  

Minishell gère l'exécution de commandes UNIX, le traitement des **redirections**, des **pipes** et des **variables d'environnement**. Il permet également la gestion de commandes internes comme `cd`, `echo`, `export`, `unset`, et bien d'autres.  

## 🔧 Fonctionnalités  
✔️ **Exécution de commandes externes**  
✔️ **Gestion des redirections** : `>`, `<`, `>>`  
✔️ **Gestion des pipes** : `|`  
✔️ **Gestion des variables d'environnement** : `echo $VAR`, `export`, `unset`  
✔️ **Commande interne `cd`** pour changer de répertoire  
✔️ **Commande interne `echo`** pour afficher du texte  
✔️ **Commande interne `export`** pour définir des variables d'environnement  
✔️ **Commande interne `unset`** pour supprimer des variables d'environnement  
✔️ **Gestion des exit codes `echo $?`**   


## 🏗️ Installation et Compilation  

### 📥 Cloner le projet  
```sh
git clone https://github.com/tle-dref/minishell.git
cd minishell
```
🔨 Compiler
```sh
make
```
🚀 Lancer Minishell
```sh
./minishell
```
Tu peux maintenant utiliser ton Minishell pour exécuter des commandes, gérer des pipes et redirections, et interagir avec ton terminal comme un shell normal.

⚙️ Technologies utilisées
🟢 Langage : C
🔧 Librairies : readline
💻 Système : UNIX
