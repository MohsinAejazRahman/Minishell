# 📖 Introduction

This guide provides an in-depth exploration of the architecture, edge cases, and implementation strategies required to build a fully functioning **`minishell`**. It complements the `README.md` by focusing on the **internal logic** and **system-level behavior** expected in a compliant 42 shell project.

If you're new to process management, shell behavior, or terminal manipulation, we strongly recommend starting with simpler 42 projects like [`pipex`](https://github.com/) or [`minitalk`](https://github.com/) to gain experience with **pipes**, **signals**, and **process creation** before diving into `minishell`.

This document is divided into sections that cover:
- **How `bash` behaves** and how `minishell` should replicate it.
- The **specific allowed functions**, their constraints, and proper usage patterns.
- A detailed breakdown of **parsing** techniques (like variable expansion and tokenization).
- The **execution phase**, including pipelines, redirections, and built-in commands.

Use this guide to understand the **why** and **how** behind each subsystem in `minishell`, while referring to `TUTORIAL.md` for practical implementation strategies and folder structure suggestions.

---

# 📑 Table of Contents

* [📖 Introduction](#-introduction)
* [📑 Table of Contents](#-table-of-contents)
* [🖥️ Bash Behavior](#️-bash-behavior)

* [🔧 Allowed Functions](#-allowed-functions)
    * [🧠 Memory & Allocation](#-memory--allocation)
    * [🖨️ Output & Errors](#-output--errors)
    * [📖 Input Handling & Line Editing](#-input-handling--line-editing)
    * [📂 File & Directory Operations](#-file--directory-operations)
    * [🔀 Duplication & Piping](#-duplication--piping)
    * [🧬 Process Creation & Execution](#-process-creation--execution)
    * [⏳ Waiting on Processes](#-waiting-on-processes)
    * [📶 Signals](#-signals)
    * [📟 Terminal & TTY](#-terminal--tty)
    * [🌿 Environment & Shell State](#-environment--shell-state)
    * [🎛️ Termcap / Termios](#-termcap--termios)

* [🧠 Parsing](#-parsing)
    * [🔹 Tokenization](#-tokenization)
    * [🔹 Word Expansion](#-word-expansion)
    * [🔹 Quote Handling](#-quote-handling)
    * [🔹 Redirections](#-redirections)
    * [🔹 Here-Documents (<<)](#-here-documents-)
    * [🔹 Environment Variables](#-environment-variables)

* [🚀 Execution](#-execution)
    * [🔗 Pipelines](#-pipelines)
    * [📤 Redirection Logic](#-redirection-logic)
    * [⚙️ Built-in Commands](#️-built-in-commands)

<br>

---

# 🖥️ Bash Behavior


<br>

---

# 🔧 Allowed Functions

## 🧠 Memory & Allocation
### 🧠 `malloc`
### ♻️ `free`

<br>

## 🖨️ Output & Errors
### 🖊️ `write`
### 🖨️ `printf`
### 🛠️ `strerror`
### 🚨 `perror`

<br>

## 📖 Input Handling & Line Editing
### 📚 `readline`
### 📝 `add_history`
### 🧹 `rl_clear_history`
### 🔄 `rl_on_new_line`
### 🧾 `rl_replace_line`
### 🔁 `rl_redisplay`

<br>

## 📂 File & Directory Operations
### 🕳️ `access`
### 🗂️ `open`
### 📥 `read`
### ❌ `close`
### 📁 `chdir`
### 🧭 `getcwd`
### 📊 `stat`
### 📊 `lstat`
### 📊 `fstat`
### ❌ `unlink`
### 📂 `opendir`
### 📃 `readdir`
### 📁 `closedir`

<br>

## 🔀 Duplication & Piping
### 🔁 `dup`
### 🔁 `dup2`
### 🧵 `pipe`

<br>

## 🧬 Process Creation & Execution
### 🧬 `fork`
### 🧠 `execve`
### 💥 `kill`
### 🛑 `exit`

<br>

## ⏳ Waiting on Processes
### ⏳ `wait`
### ⏳ `waitpid`
### ⏳ `wait3`
### ⏳ `wait4`

<br>

## 📶 Signals
### ⚡ `signal`
### 🔔 `sigaction`
### ➖ `sigemptyset`
### ➕ `sigaddset`

<br>

## 📟 Terminal & TTY
### 🖥️ `isatty`
### 🧾 `ttyname`
### 🔢 `ttyslot`
### ⚙️ `ioctl`

<br>

## 🌿 Environment & Shell State
### 🌿 `getenv`

<br>

## 🎛️ Termcap / Termios
### 🧷 `tcsetattr`
### 🧷 `tcgetattr`
### 🎨 `tgetent`
### 🎨 `tgetflag`
### 🎨 `tgetnum`
### 🎨 `tgetstr`
### 🎯 `tgoto`
### 🎯 `tputs`



<br>

---

# 🧠 Parsing

## 🧩 Word Expansion  
## 🧩 Quote Handling  
## 🧩 Redirections  
## 🧩 Here-Documents (<<)  
## 🧩 Environment Variables  

<br>

---

# 🚀 Execution

## 🔗 Pipelines  
## 📤 Redirection Logic  

### `🧩 echo`
### `🧩 cd`
### `🧩 pwd`
### `🧩 export`
### `🧩 unset`
### `🧩 env`
### `🧩 exit`

