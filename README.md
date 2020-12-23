<h1> Red-black tree analyze program</h1>

## Table of Contents

1. [Language](#Language)
2. [Introduction](#introduction)
3. [Library functions](#Library-functions)
4. [Supported OS](#supported-os)
5. [Internal tools](#Internal-tools)

---

## Language

This program is written in C.
<br>

## Introduction

This program analyzes a Red-black tree. The program
This is a static library, that creates and manages user-level threads.<br>
The library implements Round-Robin scheduling alghorithm.<br>
Each thread can be in one of the following states: RUNNING, BLOCKED and READY.
<br>

### Benefits

- The user can create, block, resume and terminate threads.
- The library supports different threads with different priorities, high priority threads will<br>
  get more time in the CPU when their turn arrive.

## Library functions

```typescript
int diameter(Tree *myTree, int root)
/**
 * This function checks what is the diameter of a tree.
 */

int printRoot(Tree *treeToCheck, int numberOfVertexes)
/**
 * This function checks if the line's length in the text is valid.
 */

void bfs(Tree *myTree, int startVertex)
/**
 * This function returns the value of the root in the graph.
 */

void resetTree(Tree *myTree)
/**
 * This function resets the values in the vertex's children.
 */

```

## Supported OS

I'm developing on linux and macOS, and the program was tested on linux.

## Internal tools


- The following headers are included in the program: 'queue.h' and 'ctype.h'
    
