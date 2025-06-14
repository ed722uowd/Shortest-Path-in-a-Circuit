# Dijkstra Graph Path Finder:- Finding the shortest path in a combinational circuit

This project reads a `.bench` file (combinational gate netlist) describing a digital circuit, constructs a **directed sub graph** from the gates and connections, and then finds the **shortest path** between a given **input** and **output** node using **Dijkstra’s algorithm**.

---

## Project Structure

```
├── main.cpp           # Main program (parses arguments, calls functions)
├── function.cpp       # Graph building, Dijkstra logic
├── function.h         # Function declarations
├── graph.h            # Graph class with adjacency list
├── c17.bench.txt      # Example benchmark circuit
├── c432.bench.txt      # Example benchmark circuit
├── c499.bench.txt      # Example benchmark circuit
├── c7552.bench.txt      # Example benchmark circuit
└── README.md          # This file
```

---

## Compilation

To compile the code:

```bash
g++ -o main main.cpp
```

---

## How to Run

```bash
./main.exe c17.bench.txt G3gat G22gat
```

* `c17.bench.txt` is the circuit netlist
* `G3gat` is the **input node**
* `G22gat` is the **output node**

---

## `c17.bench.txt`

```
INPUT(G1gat)
INPUT(G2gat)
INPUT(G3gat)
INPUT(G6gat)
INPUT(G7gat)
OUTPUT(G22gat)
OUTPUT(G23gat)

G10gat = nand(G1gat, G3gat)
G11gat = nand(G3gat, G6gat)
G16gat = nand(G2gat, G11gat)
G19gat = nand(G11gat, G7gat)
G22gat = nand(G10gat, G16gat)
G23gat = nand(G16gat, G19gat)
```

---

## 🖨️ Graph Output

When run with the command:

```bash
./main.exe c17.bench.txt G3gat G22gat
```

The program prints the graph:

```
G3gat ----> G11gat, 2 ----> G10gat, 1 ---->
G10gat ----> G22gat, 0 ---->
G11gat ----> G19gat, 1 ----> G16gat, 2 ---->
G22gat ---->
G16gat ----> G23gat, 0 ----> G22gat, 0 ---->
G19gat ----> G23gat, 0 ---->
G23gat ---->
```

---

## 🧭 Shortest Path Output

```
G3gat-->G10gat-->G22gat
```

This indicates the shortest path from the input node `G3gat` to the output node `G22gat` through the circuit graph.

---

## Notes

* All edges are directed and have weights assigned based on the number of fan-outs.
* Dijkstra's algorithm ensures the shortest (least-weighted) path is found.
* If no path exists between the input and output, the program prints:

  ```
  No path to output: <output_node>
  ```

---

## License

Open for educational and personal use under the MIT License.

---

