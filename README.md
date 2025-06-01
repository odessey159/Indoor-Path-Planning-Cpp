# Indoor-Path-Planning-Cpp

This project implements a graph-based indoor navigation system using C++. It models the layout of a multi-floor building and calculates the shortest path between any two rooms using Dijkstra's algorithm.

## Features

- Models an indoor environment with:
  - Multiple floors
  - Offices, corridors, elevators, and cross-floor passages
- Automatic graph construction from room layout
- Special handling for:
  - Elevator logic (inter-floor edge weights)
  - Horizontal floor connections (e.g., sky bridges)
- Efficient Dijkstra implementation for shortest path search
- Command-line interface with readable path output

## Algorithms and Data Structures

- Graph Representation: Adjacency list with weighted undirected edges
- Pathfinding: Dijkstra’s algorithm using priority queue
- Floor mapping and logical encoding of rooms, elevators, and special connections
