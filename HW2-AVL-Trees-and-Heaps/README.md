# 🚀 HW2: Priority Task Scheduler & Sequence Quality Monitor

This repository contains two completely scratch-built C++ implementations focusing on advanced data structures: **Heaps** and **AVL Trees**.

> ⚠️ **Technical Highlight:** The use of the C++ Standard Template Library (STL) was strictly prohibited for this project. All data structures, dynamic memory management, and tree rotations were implemented manually from the ground up.

---

## ⏱️ Part 1: Aging Task Scheduler (Heaps)
Simulates a multi-processor task scheduling system using custom Min-Heap and Max-Heap structures.

* **The "Aging" Algorithm:** Implements a priority queue where a task's priority naturally increases the longer it waits in the queue to prevent starvation.
* **Custom Data Structures:** * `TaskMaxHeap`: Manages the waiting queue based on the dynamically calculated *Effective Priority*.
  * `ProcessorMinHeap`: Tracks processor availability to efficiently assign tasks the exact moment a core becomes free.
* **Time Complexity:** Achieves strict **$O(N \log N)$** execution time. This was accomplished by optimizing the priority mathematical formula, completely eliminating the need to linearly iterate through the queue to update priorities at each time step.

## 🧬 Part 2: Sequencing Quality Monitor (AVL Trees)
A high-performance genomic sequence analyzer using a sliding window approach over massive datasets.

* **The Algorithm:** Calculates the "Local Impact Sum" (the sum of the $P$ lowest quality scores) within a sliding window of size $W$, while updating a "Global Quality Metric".
* **Core Structure:** A fully self-balancing **AVL Tree**.
* **Tree Augmentation:** To meet the demanding **$O(N \log W)$** complexity requirement, every tree node is uniquely augmented with `subtree_size`, `subtree_sum`, and `value_count`. This architectural decision eliminates the need to traverse $P$ nodes linearly, allowing sum calculations to be performed in pure logarithmic time.

---

## 🛠️ Compilation & Execution
A `Makefile` is provided to compile both executables easily.

```bash
# Compile both programs
make all

# Run the scheduler (Question 1)
./scheduler <input_file.txt>

# Run the monitor (Question 2)
./monitor <input_file.txt>

# Clean the directory
make clean
```

---
*Disclaimer: This repository is intended to serve as a personal portfolio. Copying these solutions for academic submissions is a violation of the Bilkent University Honor Code.*
