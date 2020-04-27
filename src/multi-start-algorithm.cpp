/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase multistart
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include "../include/multi-start-algorithm.hpp"
/**
 * @brief Solve function for miltistart algorithm, it works similarly to grasp, but the initial solutions are
 * generated randomly.
 * 
 * @return nodeSolution 
 */
nodeSolution multistart::solve() {
  std::vector<int> candidates = problem_.getPosibleNodes();
  // la funcion
  nodeSolution bestSolution;
  bestSolution.push_back(0);
  float bestMd = problem_.getMd(bestSolution);
  int iterations = 0;
  int noImprovement = 0;
  while(iterations < maxIterations_ && noImprovement < maxNoImprovIterations_) {
    iterations++;
    nodeSolution solution = constructionPhase(candidates);
    nodeSolution localOptimum = localSearch(solution, candidates);
    float testMd = problem_.getMd(localOptimum);
    if(testMd > bestMd) {
      bestSolution = localOptimum;
      bestMd = testMd;
      noImprovement = 0;
    } else {
      noImprovement++;
    }
  }
  return bestSolution;
}
/**
 * @brief generates a random solution to evaluate
 * 
 * @param candidates posible nodes for generating the solution
 * @return nodeSolution generated solution
 */
nodeSolution multistart::constructionPhase(std::vector<int> candidates) {
    nodeSolution solution;
    int solutionSize = (rand() % (problem_.getNodes() - 2)) + 2;
    while (solution.size() < solutionSize) {
      int selected = rand() % candidates.size();
      if(std::find(solution.begin(), solution.end(), candidates[selected]) == solution.end()) {
        solution.push_back(selected);
      }
    }
    return solution;
  }

/**
 * @brief Local search algorithm, it uses two greedy algorithms previously implemented, a destructive greedy
 * (deletes the node which makes the solution better) and a constructive one(searches for a node which when added
 * improves the solution) and executes both one after the other until both of them return -1, which means both of them
 * didnt find any way to improve the solution
 * 
 * @param solution initial solution
 * @param candidates posible nodes
 * @return nodeSolution local optimum to the provided solution
 */
nodeSolution multistart::localSearch(nodeSolution solution, std::vector<int> candidates) {
  bool improvement = true;
  while(improvement) {
    improvement = false;
    int worstNode = getWorstMdNode(solution);
    if(worstNode != -1) {
      improvement = true;
      solution.erase(solution.begin() + worstNode);
    }
    int bestNode = getMaxMdNode(solution, candidates);
    if(bestNode != -1) {
      improvement = true;
      solution.push_back(bestNode);
    }
  }
  return solution;
}
/**
 * @brief returns the worst node found in the current solution, if deleting any node doesnt improve the solution
 * it returns -1
 * 
 * @param actualSolution solution to evaluate
 * @return int node or -1 if the solution doesnt improve
 */
int multistart::getWorstMdNode(nodeSolution actualSolution) {
  nodeSolution kVertex;
  kVertex.push_back(-1);
  float current = problem_.getMd(actualSolution);
  float currentEdgeSum =  current * actualSolution.size();
  for(int i = 0; i < actualSolution.size(); i++) {
    const int vertex = actualSolution[i];
    float testValue = problem_.getNewMdDelete(actualSolution, currentEdgeSum, vertex); 
    if(testValue > current) {
      if(anxious_) {
        return i;
      }
      current = testValue;
      kVertex.clear();
      kVertex.push_back(i);
    } else if(testValue == current) {
      kVertex.push_back(i);
    }
  }
  //std::cout << kVertex.size() << std::endl;
  int selectedK = rand() %  (kVertex.size());
  //std::cout << selectedK << std::endl;
  return kVertex[selectedK]; 
}
/**
 * @brief returns the best node found in candidates to add to the solution, if adding any node doesnt improve 
 * the solution, it returns -1
 * 
 * @param actualSolution solution to improve
 * @param candidates nodes to evaluate
 * @return int node or -1 if the solution doesnt improve
 */
int multistart::getMaxMdNode(nodeSolution actualSolution, std::vector<int> candidates) {
  nodeSolution kVertex;
  kVertex.push_back(-1);
  float currentMd = problem_.getMd(actualSolution);
  float currentEdgeSum = currentMd * (float)actualSolution.size();
  for(int i = 0; i < candidates.size(); i++) {
    //verifica si existe el elemento i en la solucion, devuelve true si no lo encuentra
    if(std::find(actualSolution.begin(), actualSolution.end(), candidates[i]) == actualSolution.end()) {
      float testMd = problem_.getNewMdAdd(actualSolution, currentEdgeSum, candidates[i]);
      if(testMd > currentMd) {
        if(anxious_) {
          return candidates[i];
        }
        currentMd = testMd;
        kVertex.clear();
        kVertex.push_back(candidates[i]);
      } else if(testMd == currentMd) {
        kVertex.push_back(candidates[i]);
      }
    }
  }
  //std::cout << kVertex.size() << std::endl;
  int selectedK = rand() %  (kVertex.size());
  //std::cout << selectedK << std::endl;
  return kVertex[selectedK];  
}