import heapq
class A_star:
    def search(self, start:str, goal:str, graph:dict[str, list]):
        visited = []
        parents = {start:(0, None)}
        frontier = [(0,0,start)]

        while frontier:
            total, accumulated, current = heapq.heappop(frontier)

            if current in visited:  # A cheapter path has been found 
                continue
            visited.append(current)

            if current == goal: 
                return self.reconstruct_path(goal, parents), visited

            childern = self.expand(current, graph)
            for h_val, g_val, child in childern:
                new_g = accumulated + g_val
                new_f = new_g + h_val

                if child not in parents or new_g < parents[child][0]:
                    parents[child] = (new_g, current)
                    heapq.heappush(frontier, (new_f, new_g, child))

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

import heapq
class Greedy:
    def search(self, start:str, goal:str, graph:dict[str,list]):
        visited = []
        parents = {start:None}
        frontier = [(0, start)]

        while frontier: 
            cost, curr = heapq.heappop(frontier)

            if curr in visited: 
                continue
            visited.append(curr)

            if curr == goal: 
                return self.reconstruct_path(goal, parents), visited

            childern = self.expand(curr, graph)
            for child_cost, child in childern:
                if  child not in parents: 
                    parents[child] = curr
                    heapq.heappush(frontier, (child_cost, child))
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
    


# Test with your weighted graph:
wgraph = {
    "S": [(1, "A"), (5, "B")],
    "A": [(1, "C")],
    "C": [(1, "G")],
    "B": [(1, "G")],
    "G": [],
}
# Admissible heuristic h(n) (never overestimates true cost to G)
h = {"S": 3, "A": 2, "B": 1, "C": 1, "G": 0}

# Or, if using Option A's 3-tuple format (edge_cost, h(child), child):
agraph = {
    "S": [(1, 2, "A"), (5, 1, "B")],
    "A": [(1, 1, "C")],
    "C": [(1, 0, "G")],
    "B": [(1, 0, "G")],
    "G": [],
}
print("A* :", A_star().search("S", "G", agraph))
# Output -> (['S', 'A', 'C', 'G'], ['S', 'A', 'C', 'G'])

greedy_graph = {
        "S": [(10, "X"), (2, "A"), (1, "B")],
        "X": [(10, "Y")],
        "Y": [],
        "A": [(1, "C")],
        "C": [(0, "G")],
        "B": [(0, "G")],
        "G": [],
    }
print("Greedy :", Greedy().search("S", "G", greedy_graph))
