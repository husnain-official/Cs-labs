# Finally we do the Genetic local optimization. 
# Purpose: To translate the individual from the population which is being represented as a string into a int which can be plugged into a fitness function
def decode(chromosome:str) -> int: 
    return int(chromosome,2)

# Purpose: To evaluate each individual's value, and this is what we are maximizing or atleast trying to.
def fitness(chromosome:str)->int:
    x = decode(chromosome)
    return x*x

# Now we need a initial population
# Purpose: To make a random chromosome, as we need to start from somewhere so randomly create 1, then call this how many times
import random
def create_chromosome(chromosome_length:int)->str:
    bits = [random.choice('01') for _ in range(chromosome_length)]
    return ''.join(bits)

# Purpose: To make the entire population
def create_population(size:int, chromosome_length:int)->list[str]:
    population = [create_chromosome(chromosome_length) for _ in range(size)]
    return population

TOURNAMENT_SIZE = 3
MUTATION_RATE = 0.05

def tournament_selection(population)->str:
    contestents = random.sample(population, TOURNAMENT_SIZE)
    best = max(contestents, key=fitness)
    return best

def crossover(parent1:str, parent2:str):
    point = random.randint(1, len(parent1) - 1)
    child1 = parent1[:point] + parent2[point:]
    child2 = parent2[:point] + parent1[point:]
    return child1, child2

def mutation(chromosome:str)->str:
    mutataed_bits = []
    for bit in chromosome:
        if random.random() < MUTATION_RATE:
            _bit = ('0' if bit == 1 else '1')
            mutataed_bits.append(_bit)
        else:
            mutataed_bits.append(bit)
    return ''.join(mutataed_bits)



# ==========================================
# 1. Parameters:
CHROMOSOME_LENGTH = 5       # 5 bits -> numbers 0 to 31
POPULATION_SIZE = 8         # 8 chromosomes per generation
CROSSOVER_RATE = 0.8        # 80% chance parents swap tails
MUTATION_RATE = 0.05        # 5% chance each bit flips
TOURNAMENT_SIZE = 3         # 3 random contestants per tournament
GENERATIONS = 50            # Max loop iterations
TARGET_FITNESS = 31 ** 2    # 961 (Global Maximum for x^2 on 0..31)


# ==========================================
# 3. Building the next generation: 
def create_next_generation(population:list[str]):
    # Step:01 Elitism: 
    elite = max(population, key=fitness)
    new_population = [elite]

    # Step:02 Filling in the rest of the generation: 
    while len(new_population) < len(population):
        p1 = tournament_selection(population)
        p2 = tournament_selection(population)

        # Step:03 Crossover
        if random.random() < MUTATION_RATE:
            c1, c2 = crossover(p1,p2)
        else:
            c1, c2 = p1,p2

        # Step:04 Mutation
        c1 = mutation(c1)
        c2 = mutation(c2)

        # Finally add to next generation:
        new_population.append(c1)
        if len(new_population) < len(population):
            new_population.append(c2)
    return new_population


# ==========================================
# 4. The main function
def genetic_algorithm():
    population = create_population(POPULATION_SIZE, CHROMOSOME_LENGTH)

    for gen in range(GENERATIONS):
        elite = max(population, key=fitness)
        elite_val = fitness(elite)
        avg_val = sum(fitness(c) for c in population) / POPULATION_SIZE
        print(f"Gen {gen:02d} | Best: {elite} (x={decode(elite):2d}) | Score: {elite_val:3d} | Avg: {avg_val:6.2f}")

        # Early Stopping: 
        if elite_val >= TARGET_FITNESS:
            print(f"\nTarget reached at Generation {gen}!")
            break

        population = create_next_generation(population)

    best_chrom = max(population, key=fitness)
    return best_chrom, decode(best_chrom), fitness(best_chrom)

if __name__ == "__main__":
    random.seed(42)
    best_c, best_x, best_f = genetic_algorithm()
    print(f"Final Best -> Chromosome: {best_c}, x = {best_x}, Fitness = {best_f}")