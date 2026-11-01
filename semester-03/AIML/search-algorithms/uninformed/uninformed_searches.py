# First we describe the simplest search, BFS
from collections import deque
class BFS:
    def search(self,start:str, goal:str, graph:dict[str,list[str]]):
        parents = {start:None}
        visited = []
        frontier = deque()
        frontier.append(start)
        if start == goal:
            visited.append(start)
            return self.reconstruct_path(goal,parents), visited

        while(frontier):
            current = frontier.popleft()

            if current not in visited:
                visited.append(current)
            
            childern = self.expand(current, graph)
            for child in childern:
                if child not in parents:
                    parents[child] = current
                    frontier.append(child)
                    if child == goal:
                        return self.reconstruct_path(goal,parents),visited
        return None,visited 

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
# Now UCS, almost the same thing, with only difference being the cost added now
import heapq
class UCS:
    def search(self, start:str, goal:str, graph:dict[str,list[tuple]]):
        frontier = [(0,start)]
        visited = []
        parents = {start:(0,None)}

        while frontier:
            cost, current = heapq.heappop(frontier)

            if current in visited:
                continue

            visited.append(current)

            if current == goal:
                return self.reconstruct_path(goal, parents), visited

            childern = self.expand(current, graph)
            for child_cost, child in childern:
                total_cost = cost+child_cost
                if child not in parents or total_cost < parents[child][0]:
                    parents[child] = (total_cost, current)
                    heapq.heappush(frontier,(total_cost,child))
        return None, visited

    def expand(self,node:str, graph:dict[str, list[tuple]]):
            return graph.get(node, [])
    
    def reconstruct_path(self, goal:str, parents:dict[str,tuple[int,str]]):
        path = []
        current = goal
        while current is not None:
            path.append(current)
            current = parents[current][1]
        path.reverse()
        return path
# Now DFS, with max differences as from BFS and UCS which are very similar
class DFS:
    def search(self, start:str, goal:str, graph:dict[str,str]):
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
                return self.reconstruct_path(goal, parents), visited

            childern = reversed(self.expand(current, graph))
            for child in childern:
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
# Versions of DFS:
# 1. 
class DLS:
    def search(self, start:str, goal:str, max_depth:int, graph:dict[str,str]):
        stack = [(start, [start])] # node, path from start; depth = len(path) - 1
        visited = []
        cutoff = False

        while stack:
            current, path = stack.pop()
            visited.append(current)

            if current == goal:
               return path, visited, "Found"

            childern = [c for c in self.expand(current,graph) if c not in path]
            if len(path) -1 == max_depth:
                cutoff = cutoff or bool(childern)
                continue

            for child in reversed(childern):
                stack.append((child, path + [child]))

        return None, visited, ("cutoff" if cutoff else "failed")
           

    def expand(self,node:str, graph:dict[str, list[tuple]]):
        return graph.get(node, [])
    
    def reconstruct_path(self, goal:str, parents:dict[str,tuple[int,str]]):
        path = []
        current = goal
        while current is not None:
            path.append(current)
            current = parents[current][0]
        path.reverse()
        return path
# 2. 
class IDS:
    def search(self,start:str, goal:str, depth:int, graph:dict[str,list]):
        searcher = DLS()
        for i in range(1, depth+1):
            path, visited, result = searcher.search(start,goal,i,graph)
            print(f"At depth{i}: Result:{result},\nPath:{path},\nVisited{visited}")
        return

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