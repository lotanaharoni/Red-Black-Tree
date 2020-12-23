<h1> Red-black tree analyze program</h1>

## Table of Contents

1. [Language](#Language)
2. [Introduction](#introduction)
3. [Api](#Api)
4. [Supported OS](#supported-os)

---

## Language

This program is written in C.
<br>

## Introduction

This program analyzes a Red-black tree.<br>
It guarantees searching, insertion and deletion in O(log(n)) time.<br>
When the tree is modified, the new tree is rearranged and repainted.
<br>


## Api

```typescript
int containsRBTree(RBTree *tree, void *data)
/**
 * This function searches data in the tree.
 */

int addToRBTree(RBTree *tree, void *data)
/**
 * This function addes data to the tree.
 */

RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
/**
 * This function creates a new tree.
 */

void freeRBTree(RBTree *tree)
/**
 * This function releases all the tree's data.
 */

```

## Supported OS

I'm developing on linux and macOS, and the program was tested on linux.
    
