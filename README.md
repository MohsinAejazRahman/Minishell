# 🐚 Minishell - A Tiny Bash Clone

`minishell` is one of the most complex and rewarding projects in the 42 core curriculum. It challenges you to rebuild a miniature version of the Unix `bash` shell from scratch. You’ll need to implement **parsing**, **tokenization**, **built-in commands**, **pipes**, **redirections**, **signals**, and **environment variable expansion**, all while working within the limits of low-level C and a strict set of allowed functions.

> 🔍 **Note:**  
> This README provides a **project overview**, scope clarification, and build/test instructions.  
> 
> For an in-depth analysis of **bash behavior**, **allowed function behavior**, **parser architecture**, and **execution logic**, see the full [GUIDE.md](./GUIDE.md).  
> 
> For step-by-step implementation strategies, file structuring tips, and practical coding suggestions, refer to the [TUTORIAL.md](./TUTORIAL.md).

<br>

---

# 📑 Table of Contents

* [🐚 minishell](#-minishell)
* [📑 Table of Contents](#-table-of-contents)
* [🧭 How to Navigate This Repository](#-how-to-navigate-this-repository)
* [📁 Project Structure](#-project-structure)
* [📄 About the Project](#-about-the-project)
    * [🧾 General Overview](#-general-overview)
    * [🧩 Parsing Overview](#-parsing-overview)
    * [⚙️ Execution Model](#️-execution-model)
* [🧪 Compiling and Testing](#-compiling-and-testing)
* [📚 Additional Resources](#-additional-resources)


<br>

---

# 📁 Project Structure

```
📁 Minishell/
├── GUIDE.md
├── Makefile
├── README.md
├── TUTORIAL.md
├── include
│   └── minishell.h
├── library
│   └── libft
└── src
    ├── debug
    │   └── minishell_printf_utils.c
    ├── execution
    │   ├── buildin
    │   │   ├── cd.c
    │   │   ├── cd_actions.c
    │   │   ├── cd_utils.c
    │   │   ├── echo.c
    │   │   ├── env.c
    │   │   ├── exit.c
    │   │   ├── export.c
    │   │   ├── export_actions.c
    │   │   ├── export_utils.c
    │   │   ├── export_utils_1.c
    │   │   ├── pwd.c
    │   │   └── unset.c
    │   ├── execute
    │   │   ├── buildins_check.c
    │   │   ├── execution_manager.c
    │   │   ├── multiple_execution.c
    │   │   ├── multiple_execution_utils.c
    │   │   └── single_execution.c
    │   └── utils
    │       ├── error_print.c
    │       ├── find_path.c
    │       └── ft_getenv.c
    ├── minishell_main.c
    ├── parser
    │   ├── minishell_ast_parser.c
    │   ├── minishell_cmds_handler.c
    │   ├── minishell_expansion.c
    │   ├── minishell_lexical_analysis.c
    │   ├── minishell_redirections.c
    │   ├── minishell_syntactical_analysis.c
    │   ├── minishell_token_handler.c
    │   └── utils
    │       └── minishell_expansion_utils.c
    ├── signal
    │   └── minishell_signal_process.c
    ├── terminal
    │   ├── minishell_terminal.c
    │   ├── minishell_terminal_utils.c
    │   └── minishell_terminal_utils_extra.c
    └── utils
        ├── minishell_free.c
        └── minishell_utils.c
```

<br>

---

# 🧭 How to Navigate This Repository

This repository is intentionally structured to separate theory, guidance, and code. Explore it at your own pace, but consider approaching it like as a software engineer would: 
- read the spec
- plan your architecture
- iterate with intention.

> If you're currently building your own version of `minishell`, I highly recommend:
> 
> 1. **Start by reading the [GUIDE.md](./GUIDE.md)** — it explains the expected behavior of your shell, from parsing user input to executing processes, and gives you the theoretical foundation to make design decisions.
> 
> 2. **Attempt your own implementation** after reviewing the guide, without jumping into the code directly. This helps reinforce your understanding and encourages original problem-solving.
> 
> 3. **Use [TUTORIAL.md](./TUTORIAL.md)** if you get stuck, need clarification, or want structured advice on how to organize your files and approach difficult milestones. It includes practical suggestions, ordering strategies, and example workflows.

<br>

---

# 📄 About the Project

## 🧾 General Overview

During the `minishell` project, you will deepen your understanding of how a Unix shell like **bash** operates at a fundamental level. The purpose of this project is to build a simplified shell that interprets user commands, manages processes, and interacts with the operating system environment. You will learn how to handle command parsing, environment variables, and process control structures. This project requires mastering important data structures such as linked lists, maps and binary trees (for managing tokens and environment variables) and various structs that represent commands, redirections, and execution contexts.

## 🧩 Parsing Overview

The parsing component involves breaking down user input into meaningful elements such as commands, arguments, pipes, redirections, and environment variables. You will become familiar with tokenizing input strings, handling quoting and escaping rules, expanding variables, and processing here-documents. This prepares the shell to correctly understand and prepare commands before execution.

## ⚙️ Execution Model

The execution phase involves interpreting the parsed data to launch processes, set up pipelines, handle input/output redirections, and execute built-in commands. You will learn how to manage child processes, handle signals appropriately, and implement the shell’s built-in functions like `cd`, `export`, and `exit`. The focus here is on coordinating system calls and process flow to achieve the expected shell behavior.

<br>

---

# 🧪 Compiling and Testing

To get started, clone the repository locally using:

```bash
git clone https://github.com/MohsinAejazRahman/Minishell.git Minishell
cd minishell
```
Compile your project simply by running:

```bash
make
```

You can use the following make commands for cleaning:

- `make clean` — deletes object files  
- `make fclean` — deletes object files and the executable  
- `make re` — runs **fclean** then **recompiles** everything  

To test your shell, I recommend using the automated tester by [zstenger93](https://github.com/zstenger93/42_minishell_tester), which I also used during development. The guide for using this tester is available on its GitHub page. Achieving 100% the tester is very challenging, my implementation does not reach full marks. However, with the help of this [GUIDE.md](./GUIDE.md)  and the [TUTORIAL.md](./TUTORIAL.md), you will have a better chance of reaching that goal.

<br>

---

# 📚 Additional Resources

- Full implementation and design details can be found in the [GUIDE.md](./GUIDE.md)  
- Step-by-step advice, file structure tips, and coding suggestions are available in [TUTORIAL.md](./TUTORIAL.md)  
- Official Bash documentation for reference and understanding:  
  - [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)  
  - [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bashref.html)
