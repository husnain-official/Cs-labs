'''
General Concept: 
Follow Best-First-Search structure with the eval function being cost. 
Also the datastructure being used will be a Priority Queue.
'''

def expand(node: str, graph: dict[str, list[tuple[str, int]]]) -> list[tuple[str, int]]:
    return graph[node]                       # list of (neighbor, edge_cost)

# UCS:
import heapq
def UCS(initial:str, goal:str, graph) -> str|None:
    frontier = [(0, initial)] 

    parents = {initial: (0,None)}

    visited:list[str] = []
    while(frontier):
        cost_upto_parent, current = heapq.heappop(frontier)

        if current in visited:       # already expanded with a cheaper cost
            continue
        visited.append(current)

        if current == goal:
            return parents,visited

        # Generate childern for current and add them in the frontier
        neighbors = expand(current,graph)
        for child, cost in neighbors:
            total_cost = cost + cost_upto_parent
            if child not in parents or total_cost < parents[child][0]:     # Re-enter only if cheaper
                parents[child] = (total_cost,current) # To backtrack later
                heapq.heappush(frontier,(total_cost,child) )

    return None

def reconstruct_path(goal:str, parents):
    path = []
    current = goal
    while current is not None:
        path.append(current)
        current = parents[current][1]
    path.reverse()
    return path

import heapq
import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(graph, path=None, directed=True, title="UCS Path"):
    G = nx.DiGraph() if directed else nx.Graph()
    G.add_nodes_from(graph)                  # keeps isolated nodes too
    for node, edges in graph.items():
        for neighbor, cost in edges:
            G.add_edge(node, neighbor, weight=cost)

    pos = nx.spring_layout(G, seed=42)       # fixed seed = same layout each run
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=1500,
            font_size=14, font_weight='bold', edge_color='gray')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=nx.get_edge_attributes(G, 'weight'),
                                 font_size=11)
    if path:
        nx.draw_networkx_edges(G, pos, edgelist=list(zip(path, path[1:])),
                               edge_color='red', width=2.5)
    plt.title(title)
    plt.show()

def make_undirected(edges):
    """[(a, b, w), ...] -> adjacency list with the edge stored both ways."""
    graph = {}
    for a, b, w in edges:
        graph.setdefault(a, []).append((b, w))
        graph.setdefault(b, []).append((a, w))
    return graph

def run(name, graph, start, goal, directed):
    result = UCS(start, goal, graph)
    if result:
        parents, visited = result
        path = reconstruct_path(goal, parents)
        total = parents[goal][0]             # cost is stored in the dict now
        print(f"{name}: path={path}, cost={total}, expanded={visited}")
        visualize_graph(graph, path, directed, f"{name}: cost {total}")
    else:
        print(f"{name}: no path from {start} to {goal}")
        visualize_graph(graph, None, directed, f"{name}: no path")

# ---------- Tests ----------
# 1) Directed: the cheapest path is NOT the fewest-hops path (BFS would give A-B-D-G, cost 9)
g1 = {
    'A': [('B', 1), ('C', 4)],
    'B': [('C', 2), ('D', 5)],
    'C': [('D', 1)],
    'D': [('G', 3)],
    'G': [],
}
run("Directed", g1, 'A', 'G', directed=True)            # A,B,C,D,G  cost 7

# 2) Undirected with cycles (each edge stored both ways)
g2 = make_undirected([
    ('S', 'A', 7), ('S', 'B', 2), ('S', 'C', 3), ('A', 'B', 3),
    ('A', 'D', 4), ('B', 'D', 4), ('B', 'H', 1), ('C', 'L', 2),
    ('D', 'F', 5), ('H', 'F', 3), ('H', 'G', 2),
])
run("Undirected", g2, 'S', 'G', directed=False)         # S,B,H,G  cost 5

# 3) Disconnected: goal unreachable
g3 = make_undirected([('A', 'B', 1), ('C', 'D', 2)])
run("Disconnected", g3, 'A', 'D', directed=False)       # no path