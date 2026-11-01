import numpy as np
def f(x):
    return np.sin(x*5) * np.cos(x/40) - 10

def best_neighbor(f, current, step, domain):
    candidates = [current + step, current -step]
    candidates = [c for c in candidates if domain[0] <= c <= domain[1]]

    if not candidates:
        return current

    best = max(candidates, key=f)
    return best

def Stepest_Ascent(f, start, step, domain, max_iterations = 1000):
    curr = start
    path = [curr]

    for _ in range(max_iterations):
        next = best_neighbor(f, curr, step, domain)

        if f(next) <= f(curr):
            break

        curr = next
        path.append(curr)

    return curr, f(curr), path

import random
def Stochastic_hill(f, start, step, domain, max_iterations = 1000):
    curr = start
    path = [curr]
    
    for _ in range(max_iterations):
        candidates = [curr+step, curr-step]
        candidates = [c for c in candidates if domain[0] <= c <= domain[1]]
        better = [c for c in candidates if f(c) > f(curr)]
        if not better: 
            break
        # Now comes the schotastic part
        next = random.choice(better)
        curr = next
        path.append(curr)
    return curr, f(curr), path

def First_best_hill(f, start ,step, domain, max_iterations= 1000):
    curr = start
    path = [curr]

    for _ in range(max_iterations):
        next = curr + random.uniform(-step, step)
        next = min(max(next ,domain[0]), domain[1])

        if f(next) <= f(curr):
            continue

        curr = next
        path.append(curr)

    return curr, f(curr), path

def sideways_search( f, start, step, domain, max_iterartions=1000, max_sideways = 50):
    curr = start
    curr_val = f(curr)
    path = [curr]
    sideway_move = 0

    for _ in range(max_iterartions):
        next = best_neighbor(f, curr, step, domain)
        next_val = f(next)

        if next_val < curr_val :
            break
        if next_val == curr_val:
            if sideway_move >= max_sideways:
                break
            sideway_move += 1
        else:
            sideway_move = 0

        curr, curr_val = next, next_val
        path.append(curr)

    return curr, curr_val, path
             
# Now Stimulated Anelling: 
def stimulated_anelling(f, start, domain, step= 0.5, tempreture = 10, cooling_rate = 0.995 ,max_iterations = 1000):
    current = start
    curr_val = f(current)
    path = [current]
    temp = tempreture
    best,best_val = curr, curr_val
    
    for _ in range(max_iterations):
        candidate = current + random.uniform(-step,+step)
        candidate = min(max(candidate, domain[0]), domain[1])
        curr_val = f(current)
        cand_val = f(candidate)
        delta = cand_val - curr_val
        if delta > 0 or random.random() < np.exp(delta/temp):
            curr, curr_val = candidate, cand_val
            path.append(curr)

            if cand_val > best_val: 
                best, best_val = candidate, cand_val
        temp *= cooling_rate
    return best, best_val, path


    


import matplotlib.pyplot as plt
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
    s_x, s_val, s_path = Stepest_Ascent(f, start_x, step, domain)
    st_x, st_val, st_path = Stochastic_hill(f, start_x, step, domain)
    fc_x, fc_val, fc_path = First_best_hill(f, start_x, step=0.3, domain=domain)

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



