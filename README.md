Indoor Path Planning Agent System (C++ + Python + LLM)

This project implements a graph-based indoor navigation system for a twin-tower building structure, and extends it into an LLM-driven navigation agent.

It models a multi-floor environment and supports natural language queries for route planning by integrating a C++ pathfinding engine with a Python-based agent.

Features
Building Modeling
Twin-tower structure (Tower A and Tower B)
Multi-floor layout with scalable number of floors
Node types:
Offices
Corridors
Elevators
Cross-tower connections only at ground floor
Cross-floor connections (crossbeams) every 10 floors

This follows the original assignment specification of modeling a twin-tower indoor graph system.

Graph Construction
Graph is constructed dynamically based on node encoding
No hardcoded topology
Supports large-scale environments
Weighted Path Planning
Corridor edges: constant weight
Elevator edges: floor-dependent weights
Cross-tower edges: fixed high cost

Elevator weights are configurable (eWeights), enabling different routing behaviors.

Shortest Path Algorithm
Dijkstra’s algorithm with priority queue
Adjacency list representation
Optimized for performance on large graphs
Path Validation
Validates correctness of generated paths:
Legal transitions between node types
Floor consistency
Elevator constraints
LLM-based Navigation Agent

The system is extended with a Python-based agent:

Accepts natural language queries
Extracts structured parameters (start, end)
Calls the C++ backend via HTTP API
Returns readable path results
System Architecture

User input is processed through a multi-layer system:

User (CLI)
  → Python Agent (Flask + LLM)
  → C++ HTTP Server (/route)
  → Dijkstra Path Engine
Algorithms and Data Structures
Graph: adjacency list with weighted edges
Pathfinding: Dijkstra’s algorithm
Node encoding:
Office: A120, B10025
Corridor: AC1109
Elevator: BE1101
Dynamic weight system:
Elevator weights provided as input matrix (eWeights)
Enables adaptive routing
Core Function
int FindShortestPath(
    std::string start,
    std::string end,
    std::vector<std::string>& path,
    int** eWeights
);
Returns total path distance
Outputs node sequence of the path

This function satisfies the assignment requirement for shortest path computation.

How to Run
Start C++ Server
g++ server.cpp reference.cpp util.cpp -o server
./server
Start Python Agent
python agent.py
Run CLI Client
python client.py
Example

Input:

From A125 to B923

Output:

Distance: 176
Path: B111 → BC111 → ... → A115
Summary

This project combines graph algorithms, system design, and LLM-based interaction.
It extends a classical shortest path problem into a practical navigation system with natural language interface.
