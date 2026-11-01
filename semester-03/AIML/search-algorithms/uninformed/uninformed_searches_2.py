from collections import deque
class BFS:
    def search(self, start:str, goal:str, graph:dict[str,list[str]]):
        visited = []            # Purpose: TO visualize all visited nodes
        parents = {start:None}  # Purpose: TO backtrack the final path decided on
        frontier = deque([start])   # Purpose: TO continue the FIFO search

        if start == goal:
            visited.append(start)
            return self.reconstruct_path(goal,parents), visited       

        while(frontier):
            current = frontier.popleft()

            if current not in visited:  
                visited.append(current)

            childern = self.expand(current, graph)
            for child in childern:
                if child not in parents:    # This means it has been expanded before
                    parents[child] = current
                    frontier.append(child)
                    # As this is BFS, we can just check here, if goal is generated.
                    if child == goal:
                        return self.reconstruct_path(goal, parents), visited

        return None,visited 

# BTW, this is not needed, by definition, Path = Earliest Solution, so len(path) - 1, will simply give the correct depth as well.
    def search_with_depth(self, start:str, goal:str, graph:dict[str,list[str]]):
        visited = []            # Purpose: TO visualize all visited nodes
        parents = {start:None}  # Purpose: TO backtrack the final path decided on
        frontier = deque([(start,0)])   # Purpose: TO continue the FIFO search

        if start == goal:
            visited.append(start)
            return self.reconstruct_path(goal,parents), visited, 0  

        while(frontier):
            current, depth = frontier.popleft()

            if current not in visited:  
                visited.append(current)

            childern = self.expand(current, graph)
            for child in childern:
                if child not in parents:    # This means it has been expanded before
                    parents[child] = current
                    frontier.append((child, depth+1))
                    # As this is BFS, we can just check here, if goal is generated.
                    if child == goal:
                        return self.reconstruct_path(goal, parents), visited, depth+1

        return None,visited,None

    def expand(self,node:str, graph:dict[str, list[str]]):
        return graph.get(node, [])

    def reconstruct_path(self, goal:str, parents:dict[str,str]):
        path = []
        current = goal
        while current is not None:
            path.append(current)
            current = parents[current]
        path.reverse()
        return path

import heapq
class UCS:
    def search(self, start:str, goal:str, graph:dict[str, list[str]]):
        visited = []
        frontier = [(0, start)]
        parents = {start:(None,0)}

        while frontier:
            cost, current = heapq.heappop(frontier)

            if current in visited:  # A cheaper path has already been tested to this Node.
                continue
            visited.append(current)

            if current == goal:
                return self.reconstruct_path(goal, parents), visited

            childern = self.expand(current, graph) 
            for c_cost, child in childern: 
                total_cost = cost + c_cost
                if child not in parents or total_cost < parents[child][1]:
                    parents[child] = (current,total_cost)
                    heapq.heappush(frontier,(total_cost, child))

        return None, visited



    def expand(self,node:str, graph:dict[str, list[str]]):
        return graph.get(node, [])

    def reconstruct_path(self, goal:str, parents:dict[str,tuple]):
        path = []
        current = goal
        while current is not None:
            path.append(current)
            current = parents[current][0]
        path.reverse()
        return path

class DFS:  
    def search(self, start:str, goal:str, graph:dict[str,list[str]]):
        visited = []
        parents = {}
        stack = [(start,None)]

        while stack:
            current, parent = stack.pop()

            if current in parents:  # A node is making a loop, Check for it.
                continue

            parents[current] = parent
            visited.append(current)

            if current == goal: 
                return self.reconstruct_path(goal, parents), visited

            for child in reversed(self.expand(current, graph)):
                if child not in parents:
                    stack.append((child,current))

        return None, visited    
            
    def expand(self,node:str, graph:dict[str, list[tuple]]):
        return graph.get(node, [])
    
    def reconstruct_path(self, goal:str, parents:dict[str,tuple[int,str]]):
        path = []
        current = goal
        while current is not None:
            path.append(current)
            current = parents[current]
        path.reverse()
        return path
            
class DLS:
    def search(self, start:str, goal:str, max_depth:int, graph:dict[str,list[str]]):
        visited = []
        stack = [(start, [start])]  
        cutoff = False

        while stack:
            current , path = stack.pop()
            visited.append(current)

            if current == goal:
                return path, visited, "Found"

            childern = [c for c in self.expand(current, graph) if c not in path]
            length = len(path) - 1
            if length >= max_depth:
                cutoff = cutoff or bool(childern)
                continue 

            for child in reversed(childern):
                stack.append((child, path + [child]))

        return None, visited, ("Cutoff" if cutoff else "Failed")

            
    def expand(self,node:str, graph:dict[str, list[tuple]]):
        return graph.get(node, [])

class IDS:
    def search(self, start:str, goal:str, max_depth:int, graph:dict[str, list[str]]):
        for i in range(1, max_depth+1):
            path, visited, message = DLS().search(start, goal, i, graph)
            if path != None:
                print(f" Found Goal At Depth: {len(path)-1}\nPath: {path}\nVisited: {visited}\nMessage: {message}")
                return
        print(f"Did not found a path to the goal, SEARCH FAILED")

# ------------------------------------------------------------------ main
def main():
    graph = {
        "S": ["A", "B"],
        "A": ["C", "D"],
        "B": ["G"],
        "C": ["E"],
        "D": ["A"],            # D -> A is a cycle
        "E": ["G"],
        "G": [],
    }
    print("=== Unweighted graph, S -> G ===")
    print("BFS :", BFS().search("S", "G", graph))
    print("DFS :", DFS().search("S", "G", graph))
    print("DLS limit=2:", DLS().search("S", "G", 2, graph))
    print("DLS limit=1:", DLS().search("S", "G", 1, graph))
    print("IDS:")
    print("  ->", IDS().search("S", "G", 6, graph))
    print("IDS on unreachable goal Z (stops when nothing is cut off):")
    print("  ->", IDS().search("S", "Z", 10, graph))
 
    wgraph = {
        "S": [(1, "A"), (5, "B")],
        "A": [(1, "C")],
        "C": [(1, "G")],
        "B": [(1, "G")],
        "G": [],
    }
    unweighted_view = {n: [c for _, c in edges] for n, edges in wgraph.items()}
    print("\n=== Weighted graph, S -> G ===")
    print("UCS (cheapest)      :", UCS().search("S", "G", wgraph))
    print("BFS (fewest edges)  :", BFS().search("S", "G", unweighted_view),
          "<- 2 edges but cost 6")
 
    trap = {"S": ["A", "B"], "A": ["B"], "B": ["G"], "G": []}
    print("\n=== DLS trap: G is reachable within limit 2 via S-B-G ===")
    print("correct DLS                  :", DLS().search("S", "G", 2, trap)[::2])
    # print("DLS with global visited set  :", dls_with_global_visited("S", "G", 2, trap),
    #       "<- misses it")
 
 
if __name__ == "__main__":
    main()