'''
General Concept: 
Follow Best-First-Search structure with the eval function being depth. 
Also the datastructure being used will be a Queue.
'''
class Node:
    def __init__(self, state =None, parent=None, action = None):
        self.state = state
        self.parent = parent
        self.action = action

def expand(node:str, graph:dict[str,list[str]]) -> list[str]:
    childern = list(graph[node])
    return childern

# BFS of a Disconnected Undirected Graph:
from collections import deque
def BFS(initial:str, goal:str) -> str|None:
    frontier = deque()
    frontier.append(initial)

    parents:dict[str,str] = {initial:None}
    visited:list[str] = []
    while(frontier):
        current = frontier.popleft()
        visited.append(current)         # To visualize all generated nodes. 
        # Check:
        if current == goal:
            return parents
        # Else, Generate childern for current and add them in the frontier
        childern = expand(current,graph)
        for child in childern:
            if child not in parents:     # No-Repetition-Avoid Loops
                frontier.append(child)   # FIFO
                parents[child] = current # To backtrack later
    return None

def reconstruct_path(goal:str, parents):
    path = []
    current = goal
    while current is not None:
        path.append(current)
        current = parents[current]
    path.reverse()
    return path

# Visualization
import networkx as nx
import matplotlib.pyplot as plt
def visualize_graph(graph, path=None):
    G = nx.DiGraph()
    for node, neighbors in graph.items():
        for neighbor in neighbors:
            G.add_edge(node, neighbor)

    pos = nx.spring_layout(G)
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_color='lightblue',
            node_size=2000, font_size=15, font_weight='bold', edge_color='gray')
    if path:
        nx.draw_networkx_edges(G, pos, edgelist=list(zip(path, path[1:])),
                               edge_color='red', width=2.5)
    plt.title("BFS Path Visualization")
    plt.show()


# Testing/Playing Around
# Example graph represented as an adjacency list/ a dictionary of lists of characters.
graph = {   
    'A': ['B','C'],
    'B': ['D','E'],
    'C': ['F','G'],
    'D': ['H','I'],
    'E': ['J','K'],
    'F': ['L','M'],
    'G': ['N','O'],
    'H':['P'],
    'I':['Q'],
    'J':['R'],
    'K':['S'],
    'L':['T'],
    'M':['U'],
    'N':['V'],
    'O':['W'],
    'P':[],
    'Q':[],
    'R':[],
    'S':[],
    'T':[],
    'U':[],
    'V':[],
    'W':[],

}
start_node = 'A'
goal_node = 'W'
parents = BFS(start_node, goal_node)

if parents:
    path = reconstruct_path(goal_node, parents)
    visualize_graph(graph, path)
else:
    print(f"No path found from {start_node} to {goal_node}")