# Exact line by line, DLS, not 1 line updated. 
def dfs_iterative(start:str, goal:str, max_depth:int , graph:dict[str, list[str]]):
    stack = [(start, None, 0)]
    visited = []
    parents = {}

    while stack:
        current, parent, depth = stack.pop()

        if depth > max_depth:
            continue

        if current in parents:
            continue

        parents[current] = (parent,depth+1)
        visited.append(current)

        if current == goal:
            return reconstruct_path(goal,parents), visited

        # Expand
        for node in reversed(expand(current,graph)):
            if node not in parents:
                stack.append((node, current, depth+1))

    if depth > max_depth:
        print("Could not find goal within limited depth")

    return None, visited

def expand(node:str, graph:dict[str,list[str]]):
    return graph.get(node,[])

def reconstruct_path(goal:str, parents:dict[str,str]):
    current = goal
    path = []
    while current is not None:
        path.append(current)
        current = parents[current][0]
    path.reverse
    return path

# Now, convert into IDS: 
def ids(start:str, goal:str, max_depth:int, graph:dict[str,list[str]]):
    for i in range(1,max_depth+1):
        path, visited = dfs_iterative(start, goal, i, graph)
        print(f"\n\nAt depth {i}: Path:{path} \nVisited{visited}")

ids_graph = {
    'N0': ['N1', 'SideA'],
    'N1': ['N2'],
    'N2': ['N3', 'Dead1'],
    'N3': ['N4'],
    'N4': ['N5'],
    'N5': ['N6', 'Dead2'],
    'N6': ['N7'],
    'N7': ['N8'],
    'N8': ['N9'],
    'N9': ['N10', 'Dead3'],
    'N10': ['N11'],
    'N11': ['N12'],
    'N12': [],       # Goal node
    'SideA': [],     # Dead end at depth 1
    'Dead1': [],     # Dead end at depth 3
    'Dead2': [],     # Dead end at depth 6
    'Dead3': []      # Dead end at depth 10
}
start_node = 'N0'
goal_node = 'N12'
max_allowed_depth = 12

ids(start_node, goal_node, max_allowed_depth, ids_graph)