# Plazza

**Plazza** is a C++ project that simulates a pizzeria. You interact via a shell to place pizza orders; the program spawns kitchen processes, each running a thread-pool of cooks, balances the load across kitchens, manages ingredient stocks with timed refills, and uses IPC to communicate between reception and kitchens.

---

## 🧩 Features

* **Interactive shell** for placing orders and showing status
* **Dynamic kitchen processes**: forks new kitchens when needed and closes idle ones
* **Thread-pool of cooks** per kitchen, yielding when idle
* **Load balancing**: assigns pizzas one by one to keep all kitchens busy
* **IPC abstraction** with `<<`/`>>` overload for message packing/unpacking
* **Ingredient stock**: starts with 5 units of each, regenerates every N ms
* **Shutdown idle kitchens** after 5 s of no work
* **Easy pizza extension**: add new types via enum and config

---

## 🎯 Objectives

* Practice **process** creation (`fork`, `exit`, `wait`)
* Implement an **IPC** (message queue, pipe, shared memory...)
* Manage **threads** (STL threads, POSIX threads) with **mutexes** and **condition variables**
* Solve **load balancing**, **synchronization**, and **communication** problems

---

## ⚙️ Build

```bash
git clone https://github.com/Enoal-Fauchille-Bolle/Plazza.git
cd plazza
# with Makefile
make
```

Available Makefile rules:

* `make`  builds the binary `plazza`
* `make clean` removes object files
* `make fclean` removes object files and the binary
* `make re`  runs `fclean` then `make`

---

## 🚀 Usage

```bash
./plazza <multiplier> <cooks_per_kitchen> <stock_refresh_ms>
```

* **multiplier** (float > 0): scales pizza bake times (accepts values < 1)
* **cooks\_per\_kitchen** (int > 0): number of threads per kitchen
* **stock\_refresh\_ms** (int > 0): milliseconds between ingredient restocks

Example:

```bash
./plazza 2 5 2000
```

---

## 🍕 Pizza Orders

Use the interactive shell to enter one or more orders separated by `;`:

```
regina XXL x2; fantasia M x3; margarita S x1
```

* **TYPE**: regina, margarita, americana, fantasia
* **SIZE**: S, M, L, XL, XXL
* **NUMBER**: x1, x2, …

Grammar:

```
Syntax: TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*
TYPE: [a-zA-Z]+
SIZE: S | M | L | XL | XXL
NUMBER: x[1-9][0-9]*
```

---

## 🏛️ Architecture Overview

1. **Reception (parent process)**

   * Parses commands, spawns/forks kitchens
   * Distributes pizzas one by one for balanced load
   * Listens for "order ready" messages and logs them

2. **Kitchen (child processes)**

   * Maintains a **thread-pool** of cooks (STL threads or pthreads)
   * Holds an **ingredient stock** (map of ingredient→count)
   * Refills stock every *N* ms
   * Refuses orders if queue ≥ 2 × cooks; signals reception to fork new kitchen
   * Closes itself if idle for 5 s

3. **IPC Layer**

   * Encapsulated in a class with `operator<<`/`>>`
   * Serializes `PizzaType` and `PizzaSize` enums

4. **Pizzas**

   * Margarita: dough, tomato, gruyère; bake = 1 s × multiplier
   * Regina: dough, tomato, gruyère, ham, mushrooms; 2 s × multiplier
   * Americana: dough, tomato, gruyère, steak; 2 s × multiplier
   * Fantasia: dough, tomato, eggplant, goat cheese, "chef love"; 4 s × multiplier

---

## 📄 License

This project is released under the **MIT License**. See [LICENSE](LICENSE).
