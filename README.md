# Pipex - 42 Project

## 📚 Description

**Pipex** is a project from School 42 that aims to reproduce the behavior of UNIX pipes in C.
The goal is to understand and manipulate processes, file redirections, and inter-process communication using system calls such as ``pipe()``, ``fork()``, ``dup2()``, and ``execve()``.

The program must replicate the following shell behavior:

```bash
< infile cmd1 | cmd2 > outfile
```

## 🛠️ Features

- Pipe creation between multiple processes
- Input and output redirection (``<``, ``>``)
- Command execution using ``execve``
- Proper error handling
- Accurate shell behavior
- Clean memory management
- Support for absolute paths and ``$PATH`` lookup


## 📂 Files

- ``srcs/`` : Contains all the project source files (.c)
- ``include/pipex.h`` : Project header
- ``Makefile`` : Project compilation

## 🚀 Usage

### 1. Compilation

```bash
make
```

### 2. Execution (mandatory part)

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Example:

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

### Equivalent to:

```bash
< input.txt grep hello | wc -l > output.txt
```

## ⚙️ How It Works

1. Open input and output files
2. Create a pipe
3. Fork the first process (``cmd1``)
4. Redirect input and output
5. Fork the second process (``cmd2``)
6. Execute commands using ``execve``

## 🌟 Bonus

### ✅ Multiple Commands Handling

The bonus part must reproduce the following behavior:

```bash
< infile cmd1 | cmd2 | cmd3 | ... | cmdn > outfile
```

#### Usage:
```bash
./pipex_bonus infile "cmd1" "cmd2" "cmd3" outfile
```

### Features:

- Dynamic creation of multiple pipes
- Correct chaining of commands
- Flexible argument handling
- Proper closing of all file descriptors

## 📌 Heredoc

The bonus also includes heredoc support, equivalent to:

```bash
cmd << LIMITER | cmd2 >> outfile
```

#### Usage:

```bash
./pipex_bonus here_doc LIMITER "cmd1" "cmd2" outfile
```

#### Behavior:

Read from standard input until the ``LIMITER`` is found
Write output to the file in append mode
Faithful reproduction of shell heredoc behavior

## 📝 Constraints

- Only allowed functions specified in the subject
- Mandatory use of ``execve``
- Strict error handling
- No memory leaks
- Shell-like behavior required

## 💡 Tips & Resources

- Test commands directly in the shell for comparison
- Always close unused file descriptors in each process
- Use ``valgrind`` to detect memory leaks
- Pay attention to ``$PATH`` resolution
- Don’t forget append mode (``>>``) for heredoc
