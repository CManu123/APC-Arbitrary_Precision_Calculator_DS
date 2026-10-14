# Arbitrary Precision Calculator Using Data Structures

## About the Project

This project implements an Arbitrary Precision Calculator using data structures. It performs arithmetic operations on very large integers that may exceed the limits of built-in numeric data types.

The digits of each number are stored in a doubly linked list. The program processes the digits to calculate the result for the selected arithmetic operation.

## Operations

- Addition
- Subtraction
- Multiplication
- Division

## Data Structures and Concepts Used

- Doubly linked lists
- Dynamic memory allocation
- Pointers and structures
- Carry and borrow handling
- Command-line arguments

## Project Files

```text
APC/
├── main.c
├── apc.c
├── apc.h
├── add.c
├── sub.c
├── mul.c
└── div.c
```

## Compilation

Make sure GCC is installed. Open a terminal in the project folder and run:

```bash
gcc main.c apc.c add.c sub.c mul.c div.c -o apc
```

## How to Run

Pass the first number, operator, and second number as command-line arguments.

### Addition

```bash
./apc 123456789123456789 + 987654321987654321
```

### Subtraction

```bash
./apc 1000000000000000000 - 123456789
```

### Multiplication

```bash
./apc 123456789 x 987654321
```

### Division

```bash
./apc 1000000000000 / 25
```

The program displays the result of the selected operation. Use the operator symbols supported by your implementation and avoid dividing by zero.

## How It Works

1. The program accepts two numbers and an arithmetic operator.
2. The digits are stored in doubly linked lists.
3. The selected operation processes the digits and handles carry or borrow when required.
4. The calculated result is stored and displayed.

## What I Learned

- Applying data structures to solve a practical problem
- Using doubly linked lists to represent large numbers
- Managing memory dynamically
- Working with pointers and structures
- Implementing arithmetic algorithms

## Author

C Manu

## Note

This project was developed for learning purposes as a data structures project. Check the supported input format and operation behavior in the source code before use.
