# First we will start with, Hill CLimb and its Variations
import numpy as np
import random
class Hill_climb:
    def Steepest_ascent(self,f, start, step, domain, max_iterations=1000):
        current = start
        path = [start]  # For visualization later on
        
        for _ in range(max_iterations):
            next = self.get_best_neighbors(current, f, step, domain)

            if f(next) <= f(current):
                break

            path.append(next)
            current = next

        return current, f(current), path
    # Steepest Ascent will not handle sholders, plateus, ridges etc any edge cases and will also get struct on local extremas
    # 1.    |   First we write the stochastic hill climbing, where out of the upward moves, 1 is choosen randomly
    def Stochastic_search(self, start, f, step, domain, max_iterarions= 1000):
        current = start
        path = [current]

        for _ in range(max_iterarions):
            candidates = [current+step, current-step]
            candidates = [c for c in candidates if domain[0]<= c <= domain[1]]

            strictly_better = [c for c in candidates if f(current) < f(c)]

            if not strictly_better:
                break

            current = random.choice(strictly_better)
            path.append(current)
        return current, f(current), path

    # 2.    |   
    def first_choice_search(self, f, start, step, domain, max_iterations=1000):
        current  = start
        path = [current]

        for _ in range(max_iterations):
            candidate = candidate + random.uniform(-step, step)
            candidate = min(max(candidate, range[0]),range[1])

            if f(candidate) > f(current):
                current = candidate
                path.append(current)

        return current, f(current), path

    # 3.    |   
    def sideways_search(self, f, start, step, domain, max_iterartions=1000, max_sideways = 50):
        current = start
        path = [current]
        sideway_moves = 0

        for _ in range(max_iterartions):
            next = self.get_best_neighbors(current, f, step, domain)
            if f(next) < f(current):
                continue
            if f(next) == f(current):
                if sideway_moves >= max_sideways:
                    break
                sideway_moves += 1
            else:
                sideway_moves = 0
            current = next
            path.append(current)

        return current, f(current), path


    



        
    # Helpers: 
    def get_best_neighbors(self, x, f, step, domain):
        candidates = [x-step, x+step]
        candidates = [c for c in candidates if domain[0] <= c <= domain[1]]
        best =  max(candidates, key=f)
        return best
    
    # Objective Function:   The one we are trying to Maximize/Minimize
    def f(self, x:int)->int:
        return np.sin(x*x*5) * np.cos(x/40) - 10



def simulated_anelling(f, start, domain, step= 0.5, tempreture = 10, cooling_rate = 0.95, max_iterations = 1000):
    curr = start
    curr_val = f(curr)
    temp = tempreture
    path = [curr]

    best, best_val = curr, curr_val

    for _ in range(max_iterations):
        next = curr + random.uniform(-step, step)
        next_val = f(next)

        delta = next_val - curr_val

        if delta > 0 or random.random() < np.exp(delta/temp):
            curr, curr_val = next, next_val
            if curr_val > best_val:
                best, best_val = curr, curr_val
        temp *= cooling_rate
        path.append(curr)

    return best, best_val, path
