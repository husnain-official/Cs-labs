def dfs_iterative(start:str, goal:str, graph:dict[str, list[str]]):
    stack = [(start,None)]
    visited = []
    parents = {}

    while stack:
        current, parent = stack.pop()

        if current in parents:
            continue

        parents[current] = parent
        visited.append(current)

        if current == goal:
            return reconstruct_path(goal,parents), visited

        # Expand
        for node in reversed(expand(current,graph)):
            if node not in parents:
                stack.append((node, current))

    return None, visited

def expand(node:str, graph:dict[str,list[str]]):
    return graph.get(node,[])

def reconstruct_path(goal:str, parents:dict[str,str]):
    current = goal
    path = []
    while current is not None:
        path.append(current)
        current = parents[current]
    path.reverse
    return path


# ---------------------------------------------------------------- recursive
def dfs_recursive(start: str, goal: str, graph: dict[str, list[str]]):
    parents = {start: None}       # key present == already discovered
    order = []
 
    def visit(node: str) -> bool:
        order.append(node)
        if node == goal:
            return True
        for child in expand(node, graph):
            if child not in parents:
                parents[child] = node
                if visit(child):           # stop everything the moment the goal is found
                    return True
        return False                       # dead end: backtrack to the caller
 
    if visit(start):
        return reconstruct_path(goal, parents), order
    return None, order
 
 
# ---------------------------------------------------------------- tests

if __name__ == "__main__":
    graph = {
        "S": ["A", "B"],
        "A": ["C"],
        "B": ["G"],
        "C": ["A", "G"],          # C -> A is a cycle
        "G": [],
    }
 
    print("iterative :", dfs_iterative("S", "G", graph))
    # print("recursive :", dfs_recursive("S", "G", graph))
    print("unreachable:", dfs_iterative("S", "Z", graph))
    # Note: DFS returns S-A-C-G (3 edges); the shortest path is S-B-G (2 edges).
 
    # Depth test: a chain of 5000 nodes
    n = 5000
    chain = {str(i): [str(i + 1)] for i in range(n)}
    path, _ = dfs_iterative("0", str(n), chain)
    if path :
        print("iterative on 5000-chain: path length", len(path))
    # try:
    #     dfs_recursive("0", str(n), chain)
    # except RecursionError:
    #     print("recursive on 5000-chain: RecursionError")
