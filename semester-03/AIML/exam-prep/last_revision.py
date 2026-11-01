### First lets practice drawing the graphs:
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E', 'G'],
    'G': ['F']
}
for node, neighbors in graph.items():
    print(f"Node: {node} -> {neighbors}")

import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
for node, neighbors in graph.items():
    for n in neighbors:
        G.add_edge(node, n)

nx.draw(G, with_labels=True)
plt.title("Displaying a Graph")
# plt.show()

# First up are the uninformed Searches:
# ---------------------------------------------------------------------------------------
# Lets practice BFS: 
# ---------------------------------------------------------------------------------------
def b_reconstruct_path(goal:str, parents:dict[str,str]):
    curr = goal
    path = []
    while curr != None:
        path.append(curr)
        curr = parents[curr]
    path.reverse()
    return path

from collections import deque
def BFS(start:str, goal:str, graph:dict[str,list[str]]):
    visited = []
    parents = {start:None}
    frontier = deque([start])
    if start == goal:
        return b_reconstruct_path(goal, parents), visited

    while frontier:
        curr = frontier.popleft()

        if curr not in visited:
            visited.append(curr)

        childern = graph.get(curr,[])
        for child in childern:
            if child not in parents:
                parents[child] = curr
                visited.append(child)
                frontier.append(child)
                if child == goal:
                    return b_reconstruct_path(goal, parents), visited
    return None, visited

path, visited = BFS('A', 'G', graph)
print("BFS Traversal Order:", visited)
print("BFS Path Found:", path)
# Notes: With above version, i can easily calculate, depth, path, visited, etc all possible things in question.

# ---------------------------------------------------------------------------------------
# Now lets practice UCS:
def u_reconstruct_path(goal:str, parents:dict[str,tuple[int,str]]):
    curr = goal
    path = []
    while curr != None:
        path.append(curr)
        curr = parents[curr][1]
    path.reverse()
    return path

import heapq
def UCS(start:str, goal:str, graph:dict[str,list[int,str]]):
    visited = []
    parents = {start:(0,None)}
    frontier = [(0,start)]

    while frontier:
        cost, curr = heapq.heappop(frontier)

        if curr in visited:
            continue # Cheaper path already taken for this node
        visited.append(curr)

        if curr == goal:
            return u_reconstruct_path(goal, parents), visited

        childern = graph.get(curr, [])
        for c_cost, child in childern:
            total_cost = c_cost + cost
            if child not in parents or total_cost < parents[child][0]:
                parents[child] = (total_cost, curr)
                heapq.heappush(frontier, (total_cost, child))
    return None, visited
wgraph = {
        "S": [(1, "A"), (5, "B")],
        "A": [(1, "C")],
        "C": [(1, "G")],
        "B": [(1, "G")],
        "G": [],
    }
unweighted_view = {n: [c for _, c in edges] for n, edges in wgraph.items()}
print("UCS (cheapest)      :", UCS(start="S", goal="G", graph=wgraph))
print("BFS (fewest edges)  :", BFS(start="S", goal="G", graph=unweighted_view), "<- 2 edges but cost 6")

# ---------------------------------------------------------------------------------------
# Now finally DFS:
# Note that the structure of dfs is fundamentally different from above 2, so it will be tricky, but i will try to solve without checking older version
def d_reconstruct_path(goal:str, parents:dict[str,tuple[int,str]]):
    curr = goal
    path = []
    while curr != None:
        path.append(curr)
        curr = parents[curr]
    path.reverse()
    return path

def DFS(start:str, goal:str, graph:dict[str,list[str]]):
    visited = []
    parents = {}
    stack = [(start,None)]

    while start: 
        curr, parent = stack.pop()

        if curr in parents: 
            continue     # A node is making a loop, Check for it.
        parents[curr] = parent
        visited.append(curr)

        if curr == goal:
            return d_reconstruct_path(goal, parents), visited

        childern = graph.get(curr,[])
        for child, in reversed(childern):
            if child not in parents:
                stack.append((child,curr))
    return None, visited

path, visited = DFS(start='A', goal='G', graph=graph)
print("DFS Traversal Order:", visited)
print("DFS Path:", path)

# ---------------------------------------------------------------------------------------
# Not, in the notebooks but still worth doing, 
# The wildcard DLS, IDS will use this, so no need for IDS practice, just do DLS
def DLS(start:str, goal:str, max_depth:int, graph:dict[str,list[str]]):
    visited = []
    stack = [(start,[start])]
    cutoff = "False"

    while stack:
        curr, path = stack.pop()
        visited.append(curr)

        if curr == goal:
            return path, visited, "Found"

        childern = [c for c in graph.get(curr, []) if c not in path]
        length = len(path) - 1
        if length >= max_depth:
            cutoff = cutoff or bool(childern)
            continue 

        for child in reversed(childern):
            if child not in path:
                stack.append((child, path+ [child]))

    return None, visited, ("Depth Reached" if cutoff else "Failed")

dl_graph = {
        "S": ["A", "B"],
        "A": ["C", "D"],
        "B": ["G"],
        "C": ["E"],
        "D": ["A"],            # D -> A is a cycle
        "E": ["G"],
        "G": [],
    }
print("DLS limit=4:", DLS("S", "G", 4, dl_graph))
print("DLS limit=3:", DLS("S", "G", 3, dl_graph))
print("DLS limit=2:", DLS("S", "G", 2, dl_graph))
print("DLS limit=1:", DLS("S", "G", 1, dl_graph))

# Now the Informed Searches
# ---------------------------------------------------------------------------------------
# But first lets revise, how to display the graph:
i_graph = {
    'A': [('B', 2), ('C', 5)],
    'B': [('A', 2), ('D', 4), ('E', 3)],
    'C': [('A', 5), ('F', 2)],
    'D': [('B', 4), ('G', 6)],
    'E': [('B', 3), ('F', 1)],
    'F': [('C', 2), ('E', 1), ('G', 3)],
    'G': [('D', 6), ('F', 3)]
}

IG = nx.Graph()
for node in i_graph:
    for neighbor, cost in i_graph[node]:
        IG.add_edge(node, neighbor, weight=cost)
pos = {
    'A': (0, 2),
    'B': (2, 3),
    'C': (2, 1),
    'D': (4, 4),
    'E': (4, 2),
    'F': (4, 0),
    'G': (6, 3)
}
edge_labels = nx.get_edge_attributes(IG, 'weight')
nx.draw(IG,pos, with_labels=True)
nx.draw_networkx_edge_labels(IG,pos,edge_labels=edge_labels)
plt.title("Weighted Graph")
plt.show()

heuristic = {
    'A': 7,
    'B': 6,
    'C': 4,
    'D': 6,
    'E': 3,
    'F': 2,
    'G': 0
}

print("Heuristic values:")

for node, value in heuristic.items():
    print(f"h({node}) = {value}")



# ---------------------------------------------------------------------------------------
def a_reconstruct_path(goal:str, parents:dict[str,tuple[int,str]]):
    curr = goal
    total_cost = parents[goal][0]
    path = []
    while curr != None:
        path.append(curr)
        curr = parents[curr][1]
    path.reverse()
    return path, total_cost

def A_star(start:str, goal:str, graph:dict[str,list[str]], huristics_graph:dict[int]):
    visited = []
    parents = {start:(0,None)}
    frontier = [(0,0,start)]

    while frontier:
        f_val, g_val, curr = heapq.heappop(frontier)

        if curr in visited: # Cheaper Alternative Found and used already
            continue
        visited.append(curr)

        if curr == goal:
            path, cost = a_reconstruct_path(goal, parents)
            return path,cost, visited

        childern = graph.get(curr,[])
        for child, child_g_val in childern:
            child_h_val = int(huristics_graph.get(child))
            new_g = g_val + child_g_val
            new_f = new_g + child_h_val

            if child not in parents or new_g < parents[child][0]:
                parents[child] = (new_g, curr)
                heapq.heappush(frontier, (new_f,new_g,child))
    return None, -1, visited

astar_path, Acost, visited = A_star(
    'A',
    'G',
    i_graph, 
    heuristic
    )

print("A* Search Path:", astar_path)
print("Path Cost:", Acost)

# ---------------------------------------------------------------------------------------
# Finally the Greedy
def Greedy(start:str, goal:str,graph:dict[str,list[str]], huristics_graph:dict[int]):
    visited = []
    parents = {start:(0,None)}
    frontier = [(0,start)]

    while frontier:
        cost, curr = heapq.heappop(frontier)

        if curr in visited: 
            continue
        visited.append(curr)

        if curr == goal: 
            path, _cost = a_reconstruct_path(goal, parents)
            return path, _cost, visited

        childern = graph.get(curr,[])
        for child, _ in childern:
            child_cost = huristics_graph.get(child)
            if  child not in parents: 
                parents[child] = (child_cost + cost ,curr)
                heapq.heappush(frontier, (child_cost, child))
    return None, -1, visited

g_path, g_cost, visited = Greedy(
    'A',
    'G',
    i_graph, 
    heuristic
    )

print("Greedy Search Path:", g_path)
print("Path Cost:", g_cost)


# ---------------------------------------------------------------------------------------
# Now, starting local searches: 
import numpy as np
domain = (0,20)
def f(x): 
    return np.sin(x) + np.sin(2.2 * x)



# ---------------------------------------------------------------------------------------
# For the hill climbing lets do sideway steps one
def best_neighbor(f, curr, step, domain):
    candidates = [curr+step, curr-step]
    candidates = [c for c in candidates if domain[0] <= c <= domain[1]]
    best = max(candidates, key=f)
    return best

def sideway_hill_climbing(f, start, domain, step=0.5, max_iterations = 1000, max_sideway = 10):
    curr = start
    path = [curr]
    sideway = 0

    for _ in range(max_iterations):
        next = best_neighbor(f, curr, step, domain)

        if f(next) < f(curr):
            break
        if f(next) == f(curr):
            if sideway >= max_sideway:
                break
            sideway += 1
        else:
            sideway = 0
        curr = next
        path.append(curr)

    return curr, f(curr), path

sstart = 5.0
max_, max_val, path  = sideway_hill_climbing(f, sstart, domain)

x_values = np.linspace(domain[0], domain[1])
y_values = f(x_values)
plt.plot(x_values, y_values, label="f(x)")
plt.plot(path ,[f(p) for p in path], "ro-",label="Path")
plt.scatter(sstart, f(sstart), s=100, color="Green", label= "Start")
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title("Sideway hill climbing")
plt.grid()
plt.show()


# finally the simulated_anneling
import random
def simulated_anneling(f, start, domain, step=0.5, tempreture = 10, cooling_rate = .995, max_iterations = 1000):
    visited = [start]
    curr = start
    temp = tempreture
    best, best_val = curr, f(curr)
    for _ in range(max_iterations):
        next = curr + random.uniform(-step,step)
        next = min(max( next , domain[0]), domain[1])

        delta = f(next) - f(curr)
        if delta > 0  or random.random() < np.exp(delta/temp):
            curr = next
            visited.append(curr)
            if f(curr) > f(best):
                best, best_val = curr, f(curr)
        temp *= cooling_rate

    return curr, f(curr), visited

# Run Simulated Annealing from the SAME trapped starting point as Hill-Climbing
random.seed(7)
start_x = 0
domain_ = (0,20)
best_x, best_val, sa_path = simulated_anneling(f, start_x, domain_)

print(f"Started at x = {start_x}")
print(f"Simulated Annealing found x = {best_x:.3f}, f(x) = {best_val:.3f}")

plt.figure(figsize=(10, 5))
plt.plot(x_values, y_values, label="f(x)")
plt.plot(sa_path, [f(p) for p in sa_path], color='orange', alpha=0.5, label="SA path (exploration)")
plt.scatter([start_x], [f(start_x)], color='green', s=100, zorder=5, label="Start")
plt.scatter([best_x], [best_val], color='red', s=100, zorder=5, label="Best found")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.title("Simulated Annealing Escapes the Local Maximum")
plt.legend()
plt.grid(True)
plt.show()


