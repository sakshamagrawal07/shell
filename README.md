# Shell — Unix-like Shell Implementation in C

Shell is a modular Unix-like shell built in **C**, developed as part of the Codecrafters Shell Challenge.  
It implements core shell functionalities such as lexical analysis, parsing, process execution, pipes, redirection, built-in commands, external commands and executables in the ***PATH*** environment, command history, and autocomplete, closely mirroring the architecture of real shells like `bash`.

This project demonstrates strong understanding of **operating systems, process management, and system-level programming in C**.

---

## 🚀 Key Features

### ✅ Command Execution
- Executes external programs using `fork()` and `execvp()`.
- Resolves commands via the `PATH` environment variable.
- Manages child processes using `wait()`.

### ✅ Built-in Commands
Implemented directly in the shell process (without spawning child processes):

- `cd` — change directory
- `pwd` — print working directory
- `echo` — output text
- `exit` — terminate shell
- `type` — identify whether a command is builtin or external
- `history` — display command history

### ✅ Lexical Analysis (Lexer)
- Converts raw input into tokens.
- Handles whitespace, quotes, pipes, and redirection operators.
- Ensures correct tokenization of complex command strings.

### ✅ Parsing Engine
- Transforms tokens into structured command representations.
- Identifies pipelines, redirections, and arguments.
- Prepares commands for execution.

### ✅ Pipes and Inter-Process Communication
- Supports multi-stage pipelines using `pipe()` and `dup2()`.
- Example:
  ```sh
  ls | grep .c | wc -l


## ⚙️ Running The Code (Linux)

1. Clone the repo and make sure you have a gcc installed
2. Install the dependencies using the below commands
    ```bash
    sudo apt update
    sudo apt install build-essential libreadline-dev
    ```
3. Build and run
    ```bash
    make run
    ```