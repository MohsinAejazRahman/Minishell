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

* [📚 Additional Resources](#-additional-resources)

<br>

---

# 🖥️ Bash Behavior


<br>

---

# 🔧 Allowed Functions

## 🧠 Memory & Allocation  
### 🧠 `void *malloc(size_t size)`  
Allocates a block of memory of the given size (in bytes) and returns a pointer to the beginning of the block. The contents of the newly allocated memory are uninitialized.

**Minishell usage**  
`malloc` is widely used in Minishell to allocate memory dynamically for tokens, command structures, environment variable arrays, and user input lines. Each time the shell needs to store data that is variable in length or determined at runtime, `malloc` is required.

**Inputs**

| Data Type   | Variable Name | Description                             |
|-------------|----------------|-----------------------------------------|
| `size_t`    | `size`         | Number of bytes to allocate             |

**Outputs**

| Output               | When This Output is Returned                |
|----------------------|---------------------------------------------|
| `void * (non-NULL)`  | On success, returns a pointer to allocated memory |
| `NULL`               | If the allocation fails (e.g., out of memory)    |

<br>

### ♻️ `void free(void *ptr)`  
Frees a previously allocated memory block pointed to by `ptr`. The behavior is undefined if `ptr` was not returned by `malloc`, `calloc`, `realloc`, or if it was already freed.

**Minishell usage**  
`free` is used in Minishell to deallocate memory once it is no longer needed — for instance, when cleaning up after parsing commands, freeing the environment list, or after command execution. It helps avoid memory leaks by releasing unused memory.

**Inputs**

| Data Type   | Variable Name | Description                                       |
|-------------|----------------|---------------------------------------------------|
| `void *`    | `ptr`          | Pointer to memory previously allocated by malloc |

**Outputs**

| Output | When This Output is Returned          |
|--------|----------------------------------------|
| `void` | Always (function has no return value) |

<br>

## 🖨️ Output & Errors  
### 🖊️ `ssize_t write(int fd, const void *buf, size_t count)` 
Writes up to `count` bytes from the buffer `buf` to the file descriptor `fd`. It is a low-level system call and provides unformatted output directly to files or streams.

**Minishell usage**  
In `minishell`, `write` is used for outputting text directly to standard output (`fd = 1`) or standard error (`fd = 2`), especially in error-handling routines or when printing prompts and messages without requiring formatting.

**Inputs**

| Data Type       | Variable Name | Description                              |
|----------------|----------------|------------------------------------------|
| `int`          | `fd`           | File descriptor to write to              |
| `const void *` | `buf`          | Buffer containing the data to write      |
| `size_t`       | `count`        | Number of bytes to write                 |

**Outputs**

| Output            | When This Output Is Given                 |
|------------------|--------------------------------------------|
| `>= 0` (ssize_t)  | Number of bytes successfully written       |
| `-1`              | On error (e.g., bad file descriptor)       |

<br>

### 🖨️ `int printf(const char *format, ...)`
Prints formatted output to the standard output using a format string. It supports a wide range of format specifiers and variable arguments.

**Minishell usage**  
Used in `minishell` primarily for debugging purposes or formatted output when handling commands, variables, or displaying status messages in a user-friendly manner.

**Inputs**

| Data Type           | Variable Name | Description                                   |
|--------------------|----------------|-----------------------------------------------|
| `const char *`     | `format`       | Format string specifying output layout        |
| `...`              | `...`          | Additional arguments to substitute in format  |

**Outputs**

| Output   | When This Output Is Given                       |
|----------|--------------------------------------------------|
| `>= 0`   | Number of characters printed on success          |
| `< 0`    | If an output error occurs                        |

<br>

### 🛠️ `char *strerror(int errnum)`
Returns a pointer to a string that describes the error code `errnum`. This string is statically allocated and must not be modified or freed.

**Minishell usage**  
Used in `minishell` to display human-readable error messages when system calls fail, often paired with functions like `write` or `printf` for meaningful diagnostics.

**Inputs**

| Data Type | Variable Name | Description                      |
|-----------|----------------|----------------------------------|
| `int`     | `errnum`       | Error number from `errno`        |

**Outputs**

| Output       | When This Output Is Given             |
|--------------|----------------------------------------|
| `char *`     | Pointer to static error string on any input |

<br>

### 🚨 `void perror(const char *s)`
Prints the string `s` followed by a colon, a space, the textual representation of the current error (`errno`), and a newline to the standard error.

**Minishell usage**  
In `minishell`, `perror` is used to report system call failures. It allows users to see exactly what went wrong, combining a custom label (like the command name) with the system message.

**Inputs**

| Data Type       | Variable Name | Description                       |
|----------------|----------------|-----------------------------------|
| `const char *` | `s`            | Custom prefix string for the message |

**Outputs**

| Output   | When This Output Is Given                |
|----------|-------------------------------------------|
| `void`   | Always outputs to `stderr` with message   |

<br>

## 📖 Input Handling & Line Editing
### 📚 `char *readline(const char *prompt)`

Provides a prompt and waits for the user to input a line of text. The function returns the line once the user presses Enter. It also handles basic line editing and history navigation automatically.

**Minishell usage**  
In `minishell`, `readline` is used to capture user input as command lines. It handles displaying the prompt, reading input efficiently, and integrating with command history features.

**Inputs**

| Data Type       | Variable Name | Description                 |
|----------------|----------------|-----------------------------|
| `const char *` | `prompt`       | Text displayed before input |

**Outputs**

| Output     | When This Output Is Given                |
|------------|-------------------------------------------|
| `char *`   | On success, a pointer to the input line   |
| `NULL`     | On EOF or read error                      |

<br>

### 📝 `void add_history(const char *line)`

Adds the given line to the in-memory history list so that it can be accessed using the up/down arrow keys in future prompts.

**Minishell usage**  
After a command is successfully parsed or executed in `minishell`, `add_history` is called to store the input so users can recall it later using keyboard navigation.

**Inputs**

| Data Type       | Variable Name | Description                   |
|----------------|----------------|-------------------------------|
| `const char *` | `line`         | The line to add to history    |

**Outputs**

| Output | When This Output Is Given |
|--------|----------------------------|
| `void` | Always (no return value)   |

<br>

### 🧹 `void rl_clear_history(void)`

Clears the entire readline history list, freeing the memory associated with it.

**Minishell usage**  
May be used when the shell is exiting or resetting its state, to release memory used by the input history.

**Inputs**

| Data Type | Variable Name | Description             |
|-----------|----------------|-------------------------|
| `void`    | —              | No input parameters     |

**Outputs**

| Output | When This Output Is Given |
|--------|----------------------------|
| `void` | Always                     |

<br>

### 🔄 `int rl_on_new_line(void)`

Prepares the internal readline state to begin a new line. It is used when output occurs during line editing to reset line status.

**Minishell usage**  
Used internally or manually in `minishell` when asynchronous messages (like signal notifications) appear during prompt input to ensure proper display and interaction.

**Inputs**

| Data Type | Variable Name | Description          |
|-----------|----------------|----------------------|
| `void`    | —              | No input parameters  |

**Outputs**

| Output | When This Output Is Given              |
|--------|-----------------------------------------|
| `0`    | On success                             |
| `-1`   | If readline is not in a valid state    |

<br>

### 🧾 `void rl_replace_line(const char *text, int clear_undo)`

Replaces the currently edited line in readline’s buffer with the given text. Useful for modifying input programmatically.

**Minishell usage**  
Can be used in `minishell` to update the current input buffer—e.g., for autocomplete, re-editing previous commands, or custom key bindings.

**Inputs**

| Data Type       | Variable Name  | Description                                  |
|----------------|----------------|----------------------------------------------|
| `const char *` | `text`         | New text to replace current input line       |
| `int`          | `clear_undo`   | Whether to clear undo history (non-zero = yes) |

**Outputs**

| Output | When This Output Is Given |
|--------|----------------------------|
| `void` | Always                     |

<br>

### 🔁 `void rl_redisplay(void)`

Forces readline to reprint the prompt and the current input buffer. Useful if external output interrupted the current line being typed.

**Minishell usage**  
Used in `minishell` when signal handlers (e.g., for `SIGINT`) need to redraw the prompt cleanly after clearing or interrupting input.

**Inputs**

| Data Type | Variable Name | Description          |
|-----------|----------------|----------------------|
| `void`    | —              | No input parameters  |

**Outputs**

| Output | When This Output Is Given |
|--------|----------------------------|
| `void` | Always                     |

<br>

## 📂 File & Directory Operations  
### 🕳️ `int access(const char *pathname, int mode)`

Checks the calling process’s ability to access a file specified by `pathname` according to the `mode` requested (e.g., read, write, execute).

**Minishell usage**  
Used in `minishell` to verify the existence and permissions of files before attempting operations like executing commands or opening files.

**Inputs**

| Data Type       | Variable Name | Description                         |
|----------------|----------------|-------------------------------------|
| `const char *` | `pathname`     | Path to the file to check           |
| `int`          | `mode`         | Access mode flags (e.g., R_OK, W_OK) |

**Outputs**

| Output | When This Output Is Given                          |
|--------|--------------------------------------------------|
| `0`    | On success (access permitted)                     |
| `-1`   | On error (access denied or file not found)       |

<br>

### 🗂️ `int open(const char *pathname, int flags, ...)`

Opens the file specified by `pathname` with given `flags` (e.g., read, write, create). May take an optional mode argument for permissions if a file is created.

**Minishell usage**  
Used to open files for reading input/output redirection and file creation in `minishell`.

**Inputs**

| Data Type       | Variable Name | Description                                    |
|----------------|----------------|------------------------------------------------|
| `const char *` | `pathname`     | Path to the file to open                        |
| `int`          | `flags`        | Flags specifying open mode (O_RDONLY, O_WRONLY, etc.) |
| `mode_t`       | *(optional)*   | Permissions to use if file is created          |

**Outputs**

| Output | When This Output Is Given                    |
|--------|----------------------------------------------|
| `>=0`  | File descriptor on success                    |
| `-1`   | On error (file cannot be opened/created)    |

<br>

### 📥 `ssize_t read(int fd, void *buf, size_t count)`

Reads up to `count` bytes from the file descriptor `fd` into the buffer `buf`.

**Minishell usage**  
Used to read data from files or input streams (e.g., reading commands, reading heredoc input).

**Inputs**

| Data Type       | Variable Name | Description                      |
|----------------|----------------|----------------------------------|
| `int`          | `fd`           | File descriptor to read from     |
| `void *`       | `buf`          | Buffer to store read data        |
| `size_t`       | `count`        | Maximum number of bytes to read  |

**Outputs**

| Output | When This Output Is Given                   |
|--------|---------------------------------------------|
| `>=0`  | Number of bytes read on success              |
| `0`    | EOF reached (no bytes read)                  |
| `-1`   | On error                                     |

<br>

### ❌ `int close(int fd)`

Closes the file descriptor `fd`, freeing system resources.

**Minishell usage**  
Used in `minishell` to close files and pipes after use to avoid descriptor leaks.

**Inputs**

| Data Type | Variable Name | Description                |
|-----------|----------------|----------------------------|
| `int`     | `fd`           | File descriptor to close   |

**Outputs**

| Output | When This Output Is Given                    |
|--------|----------------------------------------------|
| `0`    | On success                                  |
| `-1`   | On error (invalid descriptor)               |

<br>

### 📁 `int chdir(const char *path)`

Changes the current working directory to the directory specified by `path`.

**Minishell usage**  
Implements the `cd` command functionality to change directories.

**Inputs**

| Data Type       | Variable Name | Description             |
|----------------|----------------|-------------------------|
| `const char *` | `path`         | Path to change directory to |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                              |
| `-1`   | On error (directory does not exist or permission denied) |

<br>

### 🧭 `char *getcwd(char *buf, size_t size)`

Gets the current working directory path, storing it in `buf`.

**Minishell usage**  
Used to retrieve and display the current directory, e.g., for prompts or `pwd` command.

**Inputs**

| Data Type       | Variable Name | Description                      |
|----------------|----------------|----------------------------------|
| `char *`       | `buf`          | Buffer to store directory path   |
| `size_t`       | `size`         | Size of buffer                   |

**Outputs**

| Output     | When This Output Is Given             |
|------------|---------------------------------------|
| `buf`      | On success, pointer to buffer         |
| `NULL`     | On failure                           |

<br>

### 📊 `int stat(const char *pathname, struct stat *statbuf)`

Retrieves status information about the file specified by `pathname`.

**Minishell usage**  
Used to gather file information such as type and permissions, often to handle redirections or test file existence.

**Inputs**

| Data Type          | Variable Name | Description                |
|-------------------|----------------|----------------------------|
| `const char *`    | `pathname`     | Path to the file            |
| `struct stat *`   | `statbuf`      | Pointer to struct to fill   |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### 📊 `int lstat(const char *pathname, struct stat *statbuf)`

Similar to `stat`, but does not follow symbolic links (returns info about the link itself).

**Minishell usage**  
Used in `minishell` to detect symlinks without resolving them.

**Inputs**

| Data Type          | Variable Name | Description               |
|-------------------|----------------|---------------------------|
| `const char *`    | `pathname`     | Path to the file           |
| `struct stat *`   | `statbuf`      | Pointer to struct to fill  |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### 📊 `int fstat(int fd, struct stat *statbuf)`

Retrieves status information about the file referred to by the open file descriptor `fd`.

**Minishell usage**  
Used to get information about files or pipes opened during command execution.

**Inputs**

| Data Type          | Variable Name | Description               |
|-------------------|----------------|---------------------------|
| `int`             | `fd`           | Open file descriptor       |
| `struct stat *`   | `statbuf`      | Pointer to struct to fill  |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### ❌ `int unlink(const char *pathname)`

Deletes a name from the filesystem (removes a file).

**Minishell usage**  
Can be used when implementing commands like `rm` or cleaning temporary files.

**Inputs**

| Data Type       | Variable Name | Description              |
|----------------|----------------|--------------------------|
| `const char *` | `pathname`     | Path to the file to remove |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### 📂 `DIR *opendir(const char *name)`

Opens a directory stream corresponding to the directory name.

**Minishell usage**  
Used when reading directory contents for commands like `ls`.

**Inputs**

| Data Type       | Variable Name | Description               |
|----------------|----------------|---------------------------|
| `const char *` | `name`         | Path to the directory      |

**Outputs**

| Output   | When This Output Is Given                |
|----------|------------------------------------------|
| `DIR *`  | On success, pointer to directory stream  |
| `NULL`   | On error                              |

<br>

### 📃 `struct dirent *readdir(DIR *dirp)`

Reads the next directory entry from the directory stream.

**Minishell usage**  
Used to iterate through files in a directory for listing or processing.

**Inputs**

| Data Type   | Variable Name | Description               |
|-------------|----------------|---------------------------|
| `DIR *`     | `dirp`         | Directory stream pointer  |

**Outputs**

| Output            | When This Output Is Given           |
|------------------|------------------------------------|
| `struct dirent *` | Pointer to next directory entry     |
| `NULL`            | On end of directory or error        |

<br>

### 📁 `int closedir(DIR *dirp)`

Closes the directory stream opened by `opendir`.

**Minishell usage**  
Used to free resources after finishing directory reading operations.

**Inputs**

| Data Type   | Variable Name | Description                |
|-------------|----------------|----------------------------|
| `DIR *`     | `dirp`         | Directory stream pointer   |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |


<br>

## 🔀 Duplication & Piping  
### 🔁 `int dup(int oldfd)`

Duplicates the file descriptor `oldfd`, returning a new file descriptor that refers to the same open file description.

**Minishell usage**  
Used in `minishell` to duplicate file descriptors when setting up redirections or preserving original descriptors before changes.

**Inputs**

| Data Type | Variable Name | Description                  |
|-----------|----------------|------------------------------|
| `int`     | `oldfd`        | File descriptor to duplicate |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `>=0`  | New file descriptor on success           |
| `-1`   | On error                                |

<br>

### 🔁 `int dup2(int oldfd, int newfd)`

Duplicates the file descriptor `oldfd` to `newfd`, closing `newfd` first if it is open. It makes `newfd` refer to the same file description as `oldfd`.

**Minishell usage**  
Used to redirect standard input/output/error to files or pipes by replacing specific descriptors.

**Inputs**

| Data Type | Variable Name | Description                  |
|-----------|----------------|------------------------------|
| `int`     | `oldfd`        | File descriptor to duplicate |
| `int`     | `newfd`        | Target file descriptor       |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `newfd`| On success                             |
| `-1`   | On error                              |

<br>

### 🧵 `int pipe(int pipefd[2])`

Creates a unidirectional data channel (pipe). `pipefd[0]` is the read end, `pipefd[1]` is the write end.

**Minishell usage**  
Used to create communication channels between processes for piping commands.

**Inputs**

| Data Type    | Variable Name | Description                |
|--------------|----------------|----------------------------|
| `int[2]`     | `pipefd`       | Array to store pipe fds    |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |
 

<br>

## 🧬 Process Creation & Execution  
### 🧬 `pid_t fork(void)`

Creates a new process by duplicating the calling process. The new process (child) receives a unique process ID.

**Minishell usage**  
Used in `minishell` to create child processes for executing commands without blocking the main shell process.

**Inputs**

| Data Type | Variable Name | Description              |
|-----------|----------------|--------------------------|
| `void`   | —              | No input parameters      |

**Outputs**

| Output  | When This Output Is Given               |
|---------|-----------------------------------------|
| `> 0`   | PID of child process (in parent)        |
| `0`     | In the child process                     |
| `-1`    | On error (process not created)           |

<br>

### 🧠 `int execve(const char *pathname, char *const argv[], char *const envp[])`

Replaces the current process image with a new process image specified by `pathname`. Passes arguments and environment variables to the new process.

**Minishell usage**  
Used to execute commands by replacing the shell process or a child process with the specified executable.

**Inputs**

| Data Type           | Variable Name | Description                           |
|--------------------|----------------|-------------------------------------|
| `const char *`     | `pathname`     | Path to the executable               |
| `char *const argv[]` | `argv`        | Argument list to the executable      |
| `char *const envp[]` | `envp`        | Environment variables for the process|

**Outputs**

| Output | When This Output Is Given                      |
|--------|------------------------------------------------|
| `-1`   | On error (does not return on success)          |

<br>

### 💥 `int kill(pid_t pid, int sig)`

Sends a signal `sig` to the process or process group identified by `pid`.

**Minishell usage**  
Used to send signals like `SIGINT` or `SIGTERM` to processes, e.g., to terminate or interrupt running commands.

**Inputs**

| Data Type | Variable Name | Description                      |
|-----------|----------------|----------------------------------|
| `pid_t`   | `pid`          | Process or process group ID       |
| `int`     | `sig`          | Signal number to send             |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### 🛑 `void exit(int status)`

Terminates the calling process immediately with the given exit status.

**Minishell usage**  
Used to terminate the shell or child processes with a specific exit code.

**Inputs**

| Data Type | Variable Name | Description            |
|-----------|----------------|------------------------|
| `int`     | `status`       | Exit status code       |

**Outputs**

| Output | When This Output Is Given            |
|--------|------------------------------------|
| `void` | Does not return (process exits)    |


<br>

## ⏳ Waiting on Processes  
### ⏳ `pid_t wait(int *wstatus)`

Waits for any child process to change state (terminate or stop), and retrieves its termination status.

**Minishell usage**  
Used in `minishell` to wait for child processes to finish execution before continuing or collecting exit status.

**Inputs**

| Data Type | Variable Name | Description                          |
|-----------|----------------|------------------------------------|
| `int *`   | `wstatus`      | Pointer to store child status info |

**Outputs**

| Output  | When This Output Is Given                    |
|---------|----------------------------------------------|
| `> 0`   | PID of the child that changed state          |
| `-1`    | On error (no child processes or failure)     |

<br>

### ⏳ `pid_t waitpid(pid_t pid, int *wstatus, int options)`

Waits for a specific child process (or a group) identified by `pid` to change state, with optional flags.

**Minishell usage**  
Used to wait for a particular child process (e.g., a specific command) to finish, optionally handling asynchronous signals.

**Inputs**

| Data Type | Variable Name | Description                               |
|-----------|----------------|-------------------------------------------|
| `pid_t`   | `pid`          | Process ID or special values (-1, 0, etc.) |
| `int *`   | `wstatus`      | Pointer to store child status info       |
| `int`     | `options`      | Flags controlling wait behavior           |

**Outputs**

| Output  | When This Output Is Given                    |
|---------|----------------------------------------------|
| `> 0`   | PID of the child that changed state          |
| `0`     | If WNOHANG option is set and no child exited |
| `-1`    | On error                                     |

<br>

### ⏳ `pid_t wait3(int *wstatus, int options, struct rusage *rusage)`

Waits for any child process to change state and optionally returns resource usage information.

**Minishell usage**  
Less commonly used in `minishell`, but can be used to collect resource usage along with child process status.

**Inputs**

| Data Type          | Variable Name | Description                         |
|-------------------|----------------|-------------------------------------|
| `int *`           | `wstatus`      | Pointer to store child status info  |
| `int`             | `options`      | Flags controlling wait behavior      |
| `struct rusage *` | `rusage`       | Pointer to store resource usage info |

**Outputs**

| Output  | When This Output Is Given                    |
|---------|----------------------------------------------|
| `> 0`   | PID of the child that changed state          |
| `0`     | If WNOHANG option is set and no child exited |
| `-1`    | On error                                     |

<br>

### ⏳ `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)`

Waits for a specific child process to change state and optionally returns resource usage.

**Minishell usage**  
Used similarly to `waitpid` but also retrieves resource usage data for the child process.

**Inputs**

| Data Type          | Variable Name | Description                           |
|-------------------|----------------|---------------------------------------|
| `pid_t`           | `pid`          | Process ID or special values          |
| `int *`           | `wstatus`      | Pointer to store child status info    |
| `int`             | `options`      | Flags controlling wait behavior        |
| `struct rusage *` | `rusage`       | Pointer to store resource usage info  |

**Outputs**

| Output  | When This Output Is Given                    |
|---------|----------------------------------------------|
| `> 0`   | PID of the child that changed state          |
| `0`     | If WNOHANG option is set and no child exited |
| `-1`    | On error                                     |


<br>

## 📶 Signals  
### ⚡ `sighandler_t signal(int signum, sighandler_t handler)`

Sets a signal handler function `handler` for the signal number `signum`. It changes the action taken by a process on receipt of the specified signal.

**Minishell usage**  
Used in `minishell` to handle signals like `SIGINT` (Ctrl+C) to properly interrupt running commands or the shell prompt.

**Inputs**

| Data Type            | Variable Name | Description                         |
|---------------------|----------------|-------------------------------------|
| `int`               | `signum`       | Signal number to handle             |
| `sighandler_t`      | `handler`      | Pointer to the signal handling function |

**Outputs**

| Output        | When This Output Is Given                     |
|---------------|-----------------------------------------------|
| `sighandler_t`| Previous signal handler on success            |
| `SIG_ERR`     | On error                                      |

<br>

### 🔔 `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`

Examines or changes the action taken by a process on receipt of a specific signal.

**Minishell usage**  
Used for more robust signal handling than `signal()`, allowing control over signal masks and flags.

**Inputs**

| Data Type               | Variable Name | Description                          |
|------------------------|----------------|------------------------------------|
| `int`                  | `signum`       | Signal number                      |
| `const struct sigaction *` | `act`       | New action for the signal          |
| `struct sigaction *`   | `oldact`       | Previous action (can be NULL)      |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### ➖ `int sigemptyset(sigset_t *set)`

Initializes the signal set pointed to by `set` to exclude all signals.

**Minishell usage**  
Used to initialize signal sets before adding or removing signals for blocking/unblocking.

**Inputs**

| Data Type | Variable Name | Description               |
|-----------|----------------|---------------------------|
| `sigset_t *` | `set`        | Pointer to signal set     |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### ➕ `int sigaddset(sigset_t *set, int signum)`

Adds the signal `signum` to the signal set pointed to by `set`.

**Minishell usage**  
Used to build signal masks for blocking specific signals during critical sections.

**Inputs**

| Data Type | Variable Name | Description                |
|-----------|----------------|----------------------------|
| `sigset_t *` | `set`        | Pointer to signal set      |
| `int`       | `signum`      | Signal number to add       |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |


<br>

## 📟 Terminal & TTY  
### 🖥️ `int isatty(int fd)`

Checks if the file descriptor `fd` refers to a terminal device.

**Minishell usage**  
Used in `minishell` to detect if input/output is connected to a terminal, enabling interactive features like prompts and line editing.

**Inputs**

| Data Type | Variable Name | Description                  |
|-----------|----------------|------------------------------|
| `int`     | `fd`           | File descriptor to check     |

**Outputs**

| Output | When This Output Is Given                   |
|--------|---------------------------------------------|
| `1`    | If `fd` is a terminal device                |
| `0`    | If `fd` is not a terminal                    |
| `-1`   | On error                                    |

<br>

### 🧾 `char *ttyname(int fd)`

Returns a string describing the terminal device associated with the file descriptor `fd`.

**Minishell usage**  
Used to retrieve the terminal device name, for example to manage terminal-specific settings or display information.

**Inputs**

| Data Type | Variable Name | Description               |
|-----------|----------------|---------------------------|
| `int`     | `fd`           | File descriptor to query  |

**Outputs**

| Output    | When This Output Is Given                |
|-----------|------------------------------------------|
| `char *`  | Pointer to terminal device name on success |
| `NULL`    | On error                                |

<br>

### 🔢 `int ttyslot(void)`

Returns the index of the current terminal in the system’s user accounting database (utmp).

**Minishell usage**  
Used less commonly, but can be used in `minishell` for session or terminal management features.

**Inputs**

| Data Type | Variable Name | Description          |
|-----------|----------------|----------------------|
| `void`    | —              | No input parameters  |

**Outputs**

| Output | When This Output Is Given              |
|--------|----------------------------------------|
| `>=0`  | Slot number of the terminal            |
| `-1`   | On error                             |

<br>

### ⚙️ `int ioctl(int fd, unsigned long request, ...)`

Performs device-specific input/output control operations on the file descriptor `fd`.

**Minishell usage**  
Used to manipulate terminal settings or other device-specific operations, for example to control line buffering or modes.

**Inputs**

| Data Type         | Variable Name | Description                  |
|------------------|----------------|------------------------------|
| `int`            | `fd`           | File descriptor               |
| `unsigned long`  | `request`      | Request code for operation    |
| `...`            | —              | Additional arguments as needed|

**Outputs**

| Output | When This Output Is Given             |
|--------|---------------------------------------|
| `0`    | On success                          |
| `-1`   | On error                           |


<br>

## 🌿 Environment & Shell State  
### 🌿 `char *getenv(const char *name)`

Retrieves the value of the environment variable specified by `name`.

**Minishell usage**  
Used in `minishell` to access environment variables for command execution, variable expansion, and shell configuration.

**Inputs**

| Data Type       | Variable Name | Description                     |
|----------------|----------------|---------------------------------|
| `const char *` | `name`         | Name of the environment variable |

**Outputs**

| Output    | When This Output Is Given                |
|-----------|------------------------------------------|
| `char *`  | Pointer to the value string if variable exists |
| `NULL`    | If the environment variable is not found  |


<br>

## 🎛️ Termcap / Termios  
### 🧷 `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`

Sets the parameters associated with the terminal referred to by `fd` from the `termios` structure.

**Minishell usage**  
Used in `minishell` to configure terminal settings such as canonical mode, echo, and signal handling for interactive input.

**Inputs**

| Data Type               | Variable Name      | Description                               |
|------------------------|-------------------|-------------------------------------------|
| `int`                  | `fd`              | File descriptor of the terminal           |
| `int`                  | `optional_actions`| When the changes take effect (e.g., TCSANOW) |
| `const struct termios *` | `termios_p`      | Pointer to termios structure with settings |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### 🧷 `int tcgetattr(int fd, struct termios *termios_p)`

Gets the parameters associated with the terminal referred to by `fd` and stores them in the `termios` structure.

**Minishell usage**  
Used to retrieve current terminal settings before modifying them or restoring them later.

**Inputs**

| Data Type          | Variable Name | Description                  |
|-------------------|----------------|------------------------------|
| `int`             | `fd`           | File descriptor of terminal   |
| `struct termios *` | `termios_p`    | Pointer to store terminal settings |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `0`    | On success                             |
| `-1`   | On error                              |

<br>

### 🎨 `int tgetent(char *bp, const char *termname)`

Loads the terminal entry for the terminal named `termname` into the buffer `bp`.

**Minishell usage**  
Used to initialize terminal capabilities for cursor movement, screen manipulation, and other features.

**Inputs**

| Data Type       | Variable Name | Description                      |
|----------------|----------------|----------------------------------|
| `char *`       | `bp`           | Buffer to load terminal entry    |
| `const char *` | `termname`     | Terminal name                    |

**Outputs**

| Output | When This Output Is Given                  |
|--------|--------------------------------------------|
| `1`    | On success                                |
| `0`    | If terminal type not found                 |
| `-1`   | If terminal database could not be found   |

<br>

### 🎨 `int tgetflag(char *id)`

Returns the value of a boolean terminal capability identified by `id`.

**Minishell usage**  
Used to query terminal boolean capabilities like "auto-margins" or "has meta key."

**Inputs**

| Data Type | Variable Name | Description                   |
|-----------|----------------|-------------------------------|
| `char *`  | `id`           | Two-character capability name |

**Outputs**

| Output | When This Output Is Given                    |
|--------|----------------------------------------------|
| `1`    | Capability is true                           |
| `0`    | Capability is false                          |
| `-1`   | Capability not found                         |

<br>

### 🎨 `int tgetnum(char *id)`

Returns the value of a numeric terminal capability identified by `id`.

**Minishell usage**  
Used to query numeric terminal capabilities like number of columns or lines.

**Inputs**

| Data Type | Variable Name | Description                   |
|-----------|----------------|-------------------------------|
| `char *`  | `id`           | Two-character capability name |

**Outputs**

| Output | When This Output Is Given                  |
|--------|--------------------------------------------|
| `>=0`  | Numeric value of capability               |
| `-1`   | Capability not found                       |

<br>

### 🎨 `char *tgetstr(char *id, char **area)`

Returns the string value of a terminal capability identified by `id`. Stores any returned strings in the area pointed to by `*area` and updates it.

**Minishell usage**  
Used to retrieve control strings for cursor movements, screen clearing, etc.

**Inputs**

| Data Type    | Variable Name | Description                   |
|--------------|----------------|-------------------------------|
| `char *`     | `id`           | Two-character capability name |
| `char **`    | `area`         | Pointer to buffer area pointer |

**Outputs**

| Output   | When This Output Is Given                |
|----------|------------------------------------------|
| `char *` | Pointer to capability string on success |
| `NULL`   | Capability not found                     |

<br>

### 🎯 `char *tgoto(const char *cap, int col, int row)`

Generates a cursor movement string from the capability `cap` for the given column and row.

**Minishell usage**  
Used to produce cursor positioning sequences for terminal control.

**Inputs**

| Data Type     | Variable Name | Description                |
|---------------|----------------|----------------------------|
| `const char *`| `cap`          | Cursor movement capability |
| `int`         | `col`          | Column number              |
| `int`         | `row`          | Row number                 |

**Outputs**

| Output   | When This Output Is Given                |
|----------|------------------------------------------|
| `char *` | Cursor movement control string           |

<br>

### 🎯 `int tputs(const char *str, int affcnt, int (*putc)(int))`

Outputs the string `str` to the terminal, padding as needed. The `putc` function is called to output each character.

**Minishell usage**  
Used to print control sequences that manipulate the terminal display.

**Inputs**

| Data Type              | Variable Name | Description                             |
|-----------------------|----------------|---------------------------------------|
| `const char *`        | `str`          | Control string to output               |
| `int`                 | `affcnt`       | Number of lines affected (for padding)|
| `int (*)(int)`        | `putc`         | Function to output characters          |

**Outputs**

| Output | When This Output Is Given                |
|--------|------------------------------------------|
| `int`  | Usually 0 on success                     |




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

<br>

---

# 📚 Additional Resources

#### 🧠 Memory & Allocation  
[`man malloc`](https://man7.org/linux/man-pages/man3/malloc.3.html) - The manual page for `malloc`, describing dynamic memory allocation functions in the C library.  
[`man free`](https://man7.org/linux/man-pages/man3/free.3.html) - Manual for `free`, the function to release dynamically allocated memory.  

#### 🖨️ Output & Errors  
[`man write`](https://man7.org/linux/man-pages/man2/write.2.html) - The system call manual for `write`, describing low-level file descriptor output.  
[`man printf`](https://man7.org/linux/man-pages/man3/printf.3.html) - The formatted output function manual in the C library.  
[`man strerror`](https://man7.org/linux/man-pages/man3/strerror.3.html) - Describes the function to convert error codes to human-readable strings.  
[`man perror`](https://man7.org/linux/man-pages/man3/perror.3.html) - Describes the function that prints a descriptive error message to stderr.  

#### 📖 Input Handling & Line Editing  
[`man readline`](https://man7.org/linux/man-pages/man3/readline.3.html) - Documentation for the `readline` library for line input editing.  
[`man add_history`](https://man7.org/linux/man-pages/man3/add_history.3.html) - Manual for adding a line to the readline history list.  
[`man rl_clear_history`](https://man7.org/linux/man-pages/man3/rl_clear_history.3.html) - Clears the readline history list.  
[`man rl_on_new_line`](https://man7.org/linux/man-pages/man3/rl_on_new_line.3.html) - Handles the readline cursor when moving to a new line.  
[`man rl_replace_line`](https://man7.org/linux/man-pages/man3/rl_replace_line.3.html) - Replaces the current line in the readline buffer.  
[`man rl_redisplay`](https://man7.org/linux/man-pages/man3/rl_redisplay.3.html) - Refreshes the readline input line display.  

#### 📂 File & Directory Operations  
[`man access`](https://man7.org/linux/man-pages/man2/access.2.html) - Checks file accessibility.  
[`man open`](https://man7.org/linux/man-pages/man2/open.2.html) - Opens files or devices.  
[`man read`](https://man7.org/linux/man-pages/man2/read.2.html) - Reads data from a file descriptor.  
[`man close`](https://man7.org/linux/man-pages/man2/close.2.html) - Closes a file descriptor.  
[`man chdir`](https://man7.org/linux/man-pages/man2/chdir.2.html) - Changes the current working directory.  
[`man getcwd`](https://man7.org/linux/man-pages/man3/getcwd.3.html) - Gets the current working directory path.  
[`man stat`](https://man7.org/linux/man-pages/man2/stat.2.html) - Retrieves file status information.  
[`man lstat`](https://man7.org/linux/man-pages/man2/lstat.2.html) - Similar to stat but does not follow symbolic links.  
[`man fstat`](https://man7.org/linux/man-pages/man2/fstat.2.html) - Retrieves file status for an open file descriptor.  
[`man unlink`](https://man7.org/linux/man-pages/man2/unlink.2.html) - Deletes a name from the filesystem.  
[`man opendir`](https://man7.org/linux/man-pages/man3/opendir.3.html) - Opens a directory stream.  
[`man readdir`](https://man7.org/linux/man-pages/man3/readdir.3.html) - Reads directory entries.  
[`man closedir`](https://man7.org/linux/man-pages/man3/closedir.3.html) - Closes a directory stream.  

#### 🔀 Duplication & Piping  
[`man dup`](https://man7.org/linux/man-pages/man2/dup.2.html) - Duplicates a file descriptor.  
[`man dup2`](https://man7.org/linux/man-pages/man2/dup2.2.html) - Duplicates a file descriptor to a given descriptor number.  
[`man pipe`](https://man7.org/linux/man-pages/man2/pipe.2.html) - Creates a pipe for interprocess communication.  

#### 🧬 Process Creation & Execution  
[`man fork`](https://man7.org/linux/man-pages/man2/fork.2.html) - Creates a new process by duplicating the calling process.  
[`man execve`](https://man7.org/linux/man-pages/man2/execve.2.html) - Executes a program, replacing the current process image.  
[`man kill`](https://man7.org/linux/man-pages/man2/kill.2.html) - Sends a signal to a process or group.  
[`man exit`](https://man7.org/linux/man-pages/man3/exit.3.html) - Terminates the calling process.  

#### ⏳ Waiting on Processes  
[`man wait`](https://man7.org/linux/man-pages/man2/wait.2.html) - Waits for any child process to change state.  
[`man waitpid`](https://man7.org/linux/man-pages/man2/waitpid.2.html) - Waits for a specific child process to change state.  
[`man wait3`](https://man7.org/linux/man-pages/man2/wait3.2.html) - Waits for child process state changes and resource usage info.  
[`man wait4`](https://man7.org/linux/man-pages/man2/wait4.2.html) - Same as wait3 but for a specific child process.  

#### 📶 Signals  
[`man signal`](https://man7.org/linux/man-pages/man2/signal.2.html) - Sets signal handlers.  
[`man sigaction`](https://man7.org/linux/man-pages/man2/sigaction.2.html) - Examines or changes signal actions.  
[`man sigemptyset`](https://man7.org/linux/man-pages/man3/sigemptyset.3.html) - Initializes signal set to empty.  
[`man sigaddset`](https://man7.org/linux/man-pages/man3/sigaddset.3.html) - Adds a signal to a signal set.  

#### 📟 Terminal & TTY  
[`man isatty`](https://man7.org/linux/man-pages/man3/isatty.3.html) - Checks if file descriptor is a terminal.  
[`man ttyname`](https://man7.org/linux/man-pages/man3/ttyname.3.html) - Returns terminal device name.  
[`man ttyslot`](https://man7.org/linux/man-pages/man3/ttyslot.3.html) - Returns terminal slot number.  
[`man ioctl`](https://man7.org/linux/man-pages/man2/ioctl.2.html) - Device-specific I/O control operations.  

#### 🌿 Environment & Shell State  
[`man getenv`](https://man7.org/linux/man-pages/man3/getenv.3.html) - Retrieves environment variable values.  

#### 🎛️ Termcap / Termios  
[`man tcsetattr`](https://man7.org/linux/man-pages/man3/tcsetattr.3.html) - Sets terminal attributes.  
[`man tcgetattr`](https://man7.org/linux/man-pages/man3/tcgetattr.3.html) - Gets terminal attributes.  
[`man tgetent`](https://man7.org/linux/man-pages/man3/tgetent.3.html) - Loads terminal entry.  
[`man tgetflag`](https://man7.org/linux/man-pages/man3/tgetflag.3.html) - Gets boolean terminal capabilities.  
[`man tgetnum`](https://man7.org/linux/man-pages/man3/tgetnum.3.html) - Gets numeric terminal capabilities.  
[`man tgetstr`](https://man7.org/linux/man-pages/man3/tgetstr.3.html) - Gets string terminal capabilities.  
[`man tgoto`](https://man7.org/linux/man-pages/man3/tgoto.3.html) - Generates cursor movement strings.  
[`man tputs`](https://man7.org/linux/man-pages/man3/tputs.3.html) - Outputs terminal control strings with padding.  
