# First lets do Hill Climbing:
import numpy as np
import random
import matplotlib.pyplot as plt
def f(x): 
    return np.sin(x*5) * np.cos(x/40) - 10

def best_neighbor(f, current, step, domain):
    candidates = [current+step, current-step]
    candidates = [c for c in candidates if domain[0] <= c <= domain[1]]

    if not candidates:
        return current

    best = max(candidates, key=f)
    return best

def Steepest_ascent(f, start, step, domain, max_iterations = 1000):
    current = start
    path = [current]

    for _ in range(max_iterations):
        next = best_neighbor(f, current, step, domain)
        if f(next) <= f(current):
            break

        current = next
        path.append(current)

    return current, f(current), path

# Fixes Local Extremas
def Stochastic_ascent(f, start, step, domain, max_iterartions=1000):
    current = start
    path = [current]

    for _ in range(max_iterartions):
        candidates = [current+step, current-step]
        candidates = [c for c in candidates if domain[0] <= c <= domain[1]]
        better = [c for c in candidates if f(c) > f(current)]

        if not better:
            break

        next = random.choice(better)
        current = next
        path.append(current)
    return current, f(current), path

def First_choice_ascent(f, start, step, domain, max_iterations=1000):
    current = start
    path = [current]

    for _ in range(max_iterations):
        candidate = current + random.uniform(-step,+step)
        candidate = min(max(candidate, domain[0]), domain[1])

        if f(candidate) <= f(current):
            continue

        current = candidate
        path.append(current)

    return current, f(current), path

def sideways_search( f, start, step, domain, max_iterartions=1000, max_sideways = 50):
    current = start
    path = [current]
    sideway_steps = 0

    for _ in range(max_iterartions):
        best = best_neighbor(f, current, step, domain)
        if f(best) < f(current):
            break
        if f(best) == f(current):
            if sideway_steps >= max_sideways:
                break
            sideway_steps += 1
        else: 
            sideway_steps = 0

        current = best
        path.append(current)
    return current, f(current), path

# Will do Random Restart after Simulated anneling is done.
# Run Hill-Climbing from a starting point that gets trapped in a small local hill

import numpy as np
import random
def simulated_anneling(f, start,  domain, step = .5, tempreture=10, cooling_rate = .995 ,max_iterations = 2000):
    temp = tempreture
    current = start
    current_val = f(current)
    path = [current]
    # Track the best score found so far: 
    best, best_val = current, current_val

    for _ in range(max_iterations):
        candidate = current + random.uniform(-step, step)
        candidate = min(max(candidate, domain[0]), domain[1])
        candidate_val = f(candidate)

        delta = candidate_val - current_val
        if delta > 0 or random.random() < np.exp(delta/temp):
            current, current_val = candidate, candidate_val
            if current_val > best_val: 
                best, best_val = current, current_val

        temp *= cooling_rate
        path.append(current)

    return best, best_val, path



        

    

# 0-----------------------------------------------------------------------------------------------
# Special function with a flat plateau/shoulder at x in [8.5, 9.5] to test Sideways Search!
def f_with_plateau(x):
    val = np.sin(x) + np.sin(2.2 * x)
    # Create a flat shoulder between x=2.2 and x=2.8
    if isinstance(x, np.ndarray):
        return np.where((x >= 2.2) & (x <= 2.8), f(2.2), val)
    return f(2.2) if 2.2 <= x <= 2.8 else val

if __name__ == "__main__":
    random.seed(42)
    domain = (0, 20)
    step = 0.1
    start_x = 10.0  # Starts in a valley where left and right both have hills!

    # Run the first 3 on standard f(x)
    s_x, s_val, s_path = Steepest_ascent(f, start_x, step, domain)
    st_x, st_val, st_path = Stochastic_ascent(f, start_x, step, domain)
    fc_x, fc_val, fc_path = First_choice_ascent(f, start_x, step=0.3, domain=domain)

    # Run Sideways Search starting on a flat shoulder (x = 2.5) where Steepest Ascent would immediately quit!
    plateau_start = 2.5
    sw_x, sw_val, sw_path = sideways_search(f_with_plateau, plateau_start, step, domain, max_sideways=15)

    # Print Summary Results
    print(f"1. Steepest Ascent   | Start: {start_x:4.1f} -> End x: {s_x:6.3f} | Max f(x): {s_val:6.3f} | Steps: {len(s_path)-1}")
    print(f"2. Stochastic Ascent | Start: {start_x:4.1f} -> End x: {st_x:6.3f} | Max f(x): {st_val:6.3f} | Steps: {len(st_path)-1}")
    print(f"3. First-Choice HC   | Start: {start_x:4.1f} -> End x: {fc_x:6.3f} | Max f(x): {fc_val:6.3f} | Steps: {len(fc_path)-1}")
    print(f"4. Sideways Search   | Start: {plateau_start:4.1f} -> End x: {sw_x:6.3f} | Max f(x): {sw_val:6.3f} | Steps: {len(sw_path)-1}")

    # Plot all 4 in a 2x2 Grid
    x_vals = np.linspace(domain[0], domain[1], 1000)
    fig, axes = plt.subplots(2, 2, figsize=(14, 9))

    configs = [
        (axes[0, 0], "1. Steepest-Ascent HC", f, start_x, s_x, s_val, s_path, "red"),
        (axes[0, 1], "2. Stochastic HC", f, start_x, st_x, st_val, st_path, "purple"),
        (axes[1, 0], "3. First-Choice HC", f, start_x, fc_x, fc_val, fc_path, "darkorange"),
        (axes[1, 1], "4. Sideways Moves HC (Starts on Flat Shoulder x=2.5)", f_with_plateau, plateau_start, sw_x, sw_val, sw_path, "blue"),
    ]

    for ax, title, func, st, end_x, end_val, path, color in configs:
        ax.plot(x_vals, func(x_vals), color="lightgray", linewidth=2, label="Landscape")
        ax.plot(path, [func(p) for p in path], marker="o", markersize=4, color=color, label="Climb Path")
        ax.scatter([st], [func(st)], color="green", s=90, zorder=5, label=f"Start ({st})")
        ax.scatter([end_x], [end_val], color="black", marker="*", s=150, zorder=6, label=f"Peak ({end_x:.2f}, {end_val:.2f})")
        ax.set_title(title, fontweight="bold")
        ax.set_xlabel("x")
        ax.set_ylabel("f(x)")
        ax.legend(loc="lower left", fontsize=8)
        ax.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.show()
