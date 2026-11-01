'''
Step: 01    |   The helpers: 
1. decode
2. fitness
3. make a chromosome
4. make a population, initial
5. tournament selection
6. crossover 
7. mutation

Step: 02    |   The main function: 
Make a new population 
1. Elitism
2. Tournaments
3. Crossovers
4. Mutation
5. addition
6. repetition




Step: 03    |   To be called directly
genetic_algorithm()

'''

#  The parameters
CHROMOSOME_LENGTH = 10
POPULATION_SIZE = 10
CROSSOVER_RATE = 0.7
MUTATION_RATE = 0.08
GENERATIONS = 100
TOURNAMENT_SIZE = 2
TARGET_FITNESS = 1023 ** 4   # stop early when this fitness is reached

# The helpers
def decode(chromo:str)->int:
    return int(chromo, 2)

def fitness(chromo:str)->int:
    x = decode(chromo)
    return x ** 4

import random
def make_chromo()->str:
    bits = [random.choice('01') for _ in range(CHROMOSOME_LENGTH)]
    return ''.join(bits)

def make_population()->list[str]:
    population = [make_chromo() for _ in range(POPULATION_SIZE)]
    return population

def tournament_selection(population:list[str]):
    contestents = random.sample(population, TOURNAMENT_SIZE)
    return max(contestents, key=fitness)

def crossover(p1:str, p2:str)-> tuple[str,str]:
    point = random.randint(1, (CHROMOSOME_LENGTH - 1))
    c1 = p1[:point] + p2[point:]
    c2 = p2[:point] + p1[point:]
    return c1,c2

def mutation(c1:str)->str:
    bits = []
    for bit in c1:
        if random.random() < MUTATION_RATE:
            _bit = ('1' if bit == '0' else '0')
            bits.append(_bit)
        else:
            bits.append(bit)
    return ''.join(bits)

# Step:02
def new_population(population:list[str])->list[str]:
    # 1. Elitism
    elite = max(population, key= fitness)
    elite_val = fitness(elite)

    new_population = [elite]

    while len(new_population) < len(population):
        # 2. Tournaments
        p1 = tournament_selection(population)
        p2 = tournament_selection(population)

        # 3. Crossover
        if random.random() < CROSSOVER_RATE:
            c1, c2  = crossover(p1,p2)
        else: 
            c1,c2 = p1,p2

        # 4. Mutation
        c1 = mutation(c1)
        c2 = mutation(c2)

        # 5. Addition
        new_population.append(c1)
        if len(new_population) < len(population):
            new_population.append(c2)
    return new_population

# Finally the main main function
def genetic_algorithm():
    population = make_population()

    for gen in range(GENERATIONS):
        elite  = max(population, key=fitness)
        elite_val = fitness(elite)
        avg_val = sum(fitness(c) for c in population) / len(population)
        print(f"Gen: {gen}, Elite: {elite}, Elite_value: {elite_val}, Avg_value: {avg_val}")

        if elite_val >= TARGET_FITNESS:
            print(f"\nFound in generation{gen}")
            break

        population = new_population(population)

    best_chrom = max(population, key=fitness)
    return best_chrom, decode(best_chrom), fitness(best_chrom)


if __name__ == "__main__":
    random.seed(42)
    best_c, best_x, best_f = genetic_algorithm()
    print(f"Final Best -> Chromosome: {best_c}, x = {best_x}, Fitness = {best_f}")