#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>

using namespace std;

const int MAX_ITERATIONS = 100;
const int NUM_BEES = 50;
const double PROB_MOVE_TOWARDS_BEST = 0.7;
const double PROB_RANDOM_SEARCH = 0.3;
const double MAX_RANGE = 10.0;
const double MIN_RANGE = -10.0;
const int NUM_DIMENSIONS = 2;  

double random_double(double min, double max) {
    return min + (max - min) * (double(rand()) / RAND_MAX);
}

double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

class Bee {
public:
    vector<double> solution;
    double fitness1;
    double fitness2;
    
    Bee(int numDim){
        solution.resize(numDim, 0.0);
        fitness1 = numeric_limits<double>::lowest();
        fitness2 = numeric_limits<double>::lowest();
    }

    void initialize(double minRange, double maxRange) {
        for (double& s : solution) {
            s = random_double(minRange, maxRange);
        }
    }

    void evalFitness() {
        // f1 = x1
        fitness1 = solution[0];

        // f2 = 1 - sqrt(x1) - (x1/x2 - 1)^2
        fitness2 = 1 - sqrt(fitness1) - pow(fitness1 / solution[1] - 1, 2);
    }
};

class ABC {
private:
    vector<Bee> bees;
    vector<double> globalBestSolution;
    double globalBestFitness1;
    double globalBestFitness2;

public:
    ABC(int numBees, int numDim, double minRange, double maxRange):
        globalBestFitness1(numeric_limits<double>::lowest()), globalBestFitness2(numeric_limits<double>::lowest()){
        bees.resize(numBees, Bee(numDim));
        for (Bee& bee: bees){
            bee.initialize(minRange, maxRange);
        }
    }

    void run(int maxIterations) {
        for (int iter = 0; iter < maxIterations; ++iter) {
            for (Bee& bee : bees) {
                bee.evalFitness();

                if (bee.fitness1 > globalBestFitness1 && bee.fitness2 > globalBestFitness2) {
                    globalBestFitness1 = bee.fitness1;
                    globalBestFitness2 = bee.fitness2;
                    globalBestSolution = bee.solution;
                }
            }

            phase1();
            phase2();
            phase3();

            cout << "Iteration " << iter + 1 << " - Best Fitness (f1, f2): (" << globalBestFitness1 << ", " << globalBestFitness2 << ")" << endl;
        }

        cout << "\nGlobal Best Fitness (f1, f2): (" << globalBestFitness1 << ", " << globalBestFitness2 << ")" << endl;
        cout << "Best Solution: ";
        for (double s : globalBestSolution) {
            cout << s << " ";
        }
        cout << endl;
    }

private:
    void phase1() {
        for (Bee& bee : bees) {
            for (double& s : bee.solution) {
                s += random_double(-1.0, 1.0);
                s = clamp(s, MIN_RANGE, MAX_RANGE); 
            }
        }
    }

    void phase2() {
        for (Bee& bee : bees) {
            double rand_num = random_double(0.0, 1.0);
            if (rand_num < PROB_MOVE_TOWARDS_BEST) {
                for (size_t i = 0; i < bee.solution.size(); ++i) {
                    bee.solution[i] += 0.5 * (globalBestSolution[i] - bee.solution[i]);
                    bee.solution[i] = clamp(bee.solution[i], MIN_RANGE, MAX_RANGE);  
                }
                bee.evalFitness();
            }
        }
    }

    void phase3() {
        for (Bee& bee : bees) {
            double rand_num = random_double(0.0, 1.0);
            if (rand_num < PROB_RANDOM_SEARCH) {
                for (double& s : bee.solution) {
                    s = random_double(MIN_RANGE, MAX_RANGE);
                }
            }
        }
    }
};

int main() {
    srand(time(0));

    ABC obj1(NUM_BEES, NUM_DIMENSIONS, MIN_RANGE, MAX_RANGE);
    obj1.run(MAX_ITERATIONS);

    return 0;
}
