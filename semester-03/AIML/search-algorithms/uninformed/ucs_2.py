import heapq
def ucs(start:str, goal:str, graph:dict[str,list[tuple[int,str]]]) :
    frontier = [(0, start)]                 # To move the search forward
    parents = {start:(0,None)}              # To reconstruct the path
    visited = []                            # To visualize all nodes expored

    while frontier:
        parent_cost , parent =  heapq.heappop(frontier)  
        # Checks
        if parent in visited:   # Already Expanded at a cheaper cost. But are we sure, it will always be like this ? 
            continue
        visited.append(parent)              # Add it to visisted
            
        if parent == goal:
            return parents,visited
        
        # Expand 
        neighbors = expand(parent, graph)
        for node_cost, node in neighbors: 
            total_cost = parent_cost + node_cost
            if node not in parents or total_cost < parents[node][0] :
                parents[node] = (total_cost,parent)
                heapq.heappush(frontier,(total_cost,node))
            
    return None

def expand(node:str, graph:dict[str,[tuple[int,str]]]):
    return graph.get(node,[])

def reconstruct_path(goal:str, parents:dict[str,tuple[int,str]]):
    current = goal
    path = []
    while current is not None:
        path.append(current)
        current = parents[current][1]
    path.reverse()
    return path

import networkx as nx
import matplotlib.pyplot as plt
def visualize_graph(graph, path=None, directed=True, title="UCS Path"):
    G = nx.DiGraph() if directed else nx.Graph()
    G.add_nodes_from(graph)                    # keeps isolated nodes too
    for node, edges in graph.items():
        for cost, neighbor in edges:           # <-- Fixed: unpacked as (cost, neighbor)
            G.add_edge(node, neighbor, weight=cost)

    pos = nx.spring_layout(G, seed=42)         # fixed seed = same layout each run
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=1500,
            font_size=14, font_weight='bold', edge_color='gray')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=nx.get_edge_attributes(G, 'weight'),
                                 font_size=11)
    if path and len(path) > 1:
        nx.draw_networkx_edges(G, pos, edgelist=list(zip(path, path[1:])),
                               edge_color='red', width=2.5)
    plt.title(title)
    plt.show()



graph = {"S": [(2,"A"), (5,"B")], "A": [(2,"B")]}
start = 'S'
goal = 'B'
directed = False
result = ucs(start, goal, graph)
if result:
    parents, visited = result
    path = reconstruct_path(goal, parents)
    total = parents[goal][0]             # cost is stored in the dict now
    print(f": path={path}, cost={total}, expanded={visited}")
    visualize_graph(graph, path, directed, f"cost {total}")
else:
    print(f": no path from {start} to {goal}")
    visualize_graph(graph, None, directed, f" no path")