## Trees:
### Introduction: 
A tree is a non-linear data structure. 
It is also hierarchial. 
It is mostly used to represent and organize data in a parent-child relation. 

### Formal Definition: 
**In Graph Theory:**  A tree is a connected, acyclic, undirected graph.
**In Computer Science (Rooted Trees)** A tree is a directed, acyclic graph (specifically a special case of a Directed Acyclic Graph or DAG) where:
1. There is a single root node with an in-degree of 0 (no incoming edges).
2. Every other node has an in-degree of exactly 1 (one incoming edge from its parent).
3. There are zero paths that can loop a node back to itself.

### Terminology: 
Nodes: "Element in a tree is a called a node". 

Root-Node: "Top-most node of any tree, which does not have a parent ". 

Parent-Node: "Immediate predecessor of another node".

Child-Nodes: "Immediate successor of another node". 
                        All nodes are child nodes, except from root node, i.e they all have a parent, i.e are generated from expansion of some node. 

Internal-Nodes: "Nodes which has atleast 1 child". 

Leaf-Nodes or External-Nodes: "Nodes which do not have any childern".
                        i.e the lowest level of the tree in that branch. 

Ancestor: "Any node on the path from root to a certain node".
                Immediate Predecessor / Parent is also a ancestor. 

Desendent: "Any node y can be called a desendent of node x if x is a ansestor of y". 
 
Sibling: "Nodes sharing the same parent".

Level of a Node: "Number of edges from root to that node in path".
                The root node is at level 0.

Neighbor of a Node: "Parent or childern of a node".
                Parent has neighbors, 1. Its childern 2. Its parents.

Sub-tree: "A node and all its desendents form a sub-tree".
                Each leaf node, can be considered a sub tree itself. 

Edge: "Connection or link between 2 nodes".
                Note: If a tree has n nodes then atleast N-1 edges. 

Path: "A sequence of consecutie edges that connect 2 nodes".

Depth of a tree: "Maximum depth of any node in the tree".

Height of a Node: "The length of the longest downward path from that specific node to a leaf node".

### Why Tree is considered a non-linear data structure?
Data in a tree is not stored sequentially (i.e., not in a linear order). Instead, it is organized across multiple levels, forming a hierarchical structure. Because of this arrangement, a tree is classified as a non-linear data structure.

### Importance: 
1. Trees are usefull in cases where data naturally forms a hierarchy.
2. File systems on computers are structured as trees, with folders containing subfolders and files.  
3. The DOM (Document Object Model) of an HTML page is a tree:The `<html>` tag is the root. `<head>` and `<body>` are its children.These tags can have their own child nodes, forming a hierarchical structure.
4. Trees help in efficient data organization and retrieval for hierarchical relationships.

### Types:



### Properies: 

- A tree goes level by level, so we say that the root node is at level/depth of 0. 


### Visuals: 

graph TD;
    15["15"] --> 35["35"];
    15 --> 9["9"];
    15 --> 40["40"];
    35 --> 3["3"];
    35 --> 6["6"];
    3 --> 1["1"];
    3 --> 10["10"];
    40 --> 5["5"];
    40 --> 7["7"];
    5 --> 8["8"];
    5 --> 4["4"];
    5 --> 41["41"];

    %% Styling matching the original colors
    classDef default fill:#e0e0e0,stroke:#333,stroke-width:1px,color:#000;
    classDef ancestor fill:#f8d7da,stroke:#333,stroke-width:1px,color:#000;
    classDef rootGreen fill:#d4edda,stroke:#333,stroke-width:1px,color:#000;
    classDef greenSubtree fill:#28a745,stroke:#333,stroke-width:1px,color:#fff;

    class 15,35,9,6,1,10 default;
    class 3 ancestor;
    class 40 rootGreen;
    class 5,7,8,4,41 greenSubtree;