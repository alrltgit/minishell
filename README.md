# Minishell

## 🐚 Overview

**Minishell** is a simplified Unix shell implementation written in C. It mimics the behavior of a basic bash shell by parsing and executing user commands with support for environment variables, redirections, pipes, and built-in commands.

This project is developed as part of the 42 School curriculum to deepen understanding of process management, input parsing, and low-level system programming in Unix-based systems.

## 🚀 Features

- **Prompt display**
- **Command parsing** (including quotes and escape characters)
- **Built-in commands**:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **Environment variables** handling (`$VAR`)
- **Redirections**:
  - Input (`<`)
  - Output (`>`)
  - Append (`>>`)
  - Here-doc (`<<`)
- **Pipes** (`|`)
- **Error handling** for invalid commands and syntax
- **Signal handling** (e.g., `Ctrl+C`, `Ctrl+D`)
- **Exit status** management

## 👥 Collaborators

This project was developed collaboratively as part of the 42 School curriculum.

| Name               | GitHub Profile                    |
|--------------------|-----------------------------------|
| hceviz             | https://github.com/hceviz         |

## 📦 Installation

```bash
git clone https://github.com/your-username/minishell.git
cd minishell
make
