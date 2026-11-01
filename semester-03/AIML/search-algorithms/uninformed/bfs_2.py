from collections import deque
def bfs(start:str, goal:str, graph:dict[str,list[str]])->dict[str,str]|None:
    # Initial Check
    if start == goal:
        return {start:None}
    # First we create the frontier -> Purpose: To move formward the search.
    frontier = deque()
    frontier.append(start)
    # Purpose: Path followed, to later backtrack, to the start to get exact final path chosen. 
    parents = {start: None}
    # The visited set -> Purpose: Only to visualize the total nodes explored.
    visited = []

    # The loop, will contniue for all nodes or till goal is reached. 
    while(frontier):
        current = frontier.popleft()
        visited.append(current)

        childern = expand(current, graph)
        for child in childern:
            if child not in parents:
                frontier.append(child)
                parents[child] = current
                if child == goal:     # BFS is tested at generation. 
                    return parents
    return None

def expand(node:str, graph:dict[str,list[str]])-> list[str]:
    return graph.get(node,[])

def reconstruct_path(goal:str, parents:dict[str,str]):
    if not parents:
        return
    current = goal 
    path = []
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
graph = {'S': ['A','B'], 'A':['B']}
start_node = 'S'
goal_node = 'B'
parents = bfs(start_node, goal_node,graph)

if parents:
    path = reconstruct_path(goal_node, parents)
    visualize_graph(graph, path)
else:
    print(f"No path found from {start_node} to {goal_node}")