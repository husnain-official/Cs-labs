def dfs_iterative(start:str, goal:str, max_depth:int , graph:dict[str, list[str]]):
    stack = [(start,[start])] # Node, Path from start ; depth = len(path)-1
    visited = []
    cutoff = False
    while stack:
        current, path = stack.pop()
        visited.append(current)

        if current == goal:
            return path, visited, "Found"

        childern = [c for c in expand(current, graph) if c not in path]
        if len(path) -1 == max_depth:
            cutoff = cutoff or bool(childern)
            continue

        for child in reversed(childern):
            stack.append((child,path+[child]))

    return None, visited, ("cutoff" if cutoff else "failure")

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

if __name__ == "__main__":
    graph = {
        "S": ["A", "B"],
        "A": ["C"],
        "B": ["G"],
        "C": ["A", "G"],          # C -> A is a cycle
        "G": [],
    }
 
    print("iterative :", dfs_iterative("S", "G",1, graph))
    print("iterative :", dfs_iterative("S", "G",2, graph))
    print("iterative :", dfs_iterative("S", "G",3, graph))
    # print("recursive :", dfs_recursive("S", "G", graph))
    print("unreachable:", dfs_iterative("S", "Z",3, graph))
    # Note: DFS returns S-A-C-G (3 edges); the shortest path is S-B-G (2 edges).
 