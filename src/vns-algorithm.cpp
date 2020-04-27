/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase vns
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include "../include/vns-algorithm.hpp"
/**
 * @brief solve function for the vns algorithm, it works by generating a random solution, and then
 * generating a random solution in the k neighbourhood of the current solution, which is +-k size of
 * the current solution in this case, and then does a localSearch for that solution, if it reaches a better
 * solution than the current k resets to one and the current solution changes to the new one, 
 * it does this until kmax is reached, then repeats this until a stop condition is reached
 * 
 * @return nodeSolution best found solution
 */
nodeSolution vns::solve() {
  std::vector<int> candidates = problem_.getPosibleNodes();
  int solutionSize = (rand() % (problem_.getNodes() - 2)) + 2;
  nodeSolution solution = constructSolution(candidates, solutionSize);
  //std::cout << "shake done\n";
  nodeSolution bestSolution = localSearch(solution, candidates);
  //std::cout << "search done\n";
  float bestMd = problem_.getMd(solution);
  int iterations = 0;
  int noImprovement = 0;
  int k = 1;
  while(iterations < maxIterations_ && noImprovement < maxNoImprovIterations_) {
    iterations++;
    k = 1;
    while(k <= kmax_) {
      nodeSolution tempSolution = shake(candidates, solutionSize, k);
     // std::cout << "shake done\n";
      nodeSolution localOptimum = localSearch(tempSolution, candidates);
      //std::cout << "search done\n";
      float testMd = problem_.getMd(localOptimum);
      if(testMd > bestMd) {
        bestSolution = localOptimum;
        bestMd = testMd;
        solutionSize = localOptimum.size();
        k = 1;
        noImprovement = 0;
      } else {
        noImprovement++;
        k++;
      }
    }
  }
  return bestSolution;
}
/**
 * @brief constructs a new random solution for a determined size
 * 
 * @param candidates candidate nodes
 * @param solutionSize target size
 * @return nodeSolution generated solution
 */
nodeSolution vns::constructSolution(std::vector<int> candidates, int solutionSize) {
  nodeSolution solution;
  while (solution.size() < solutionSize) {
    int selected = rand() % candidates.size();
    if(std::find(solution.begin(), solution.end(), candidates[selected]) == solution.end()) {
      solution.push_back(selected);
    }
  }
  return solution;
}
/**
 * @brief calls constructSolution with a size in the K neighbourhood
 * 
 * @param candidates candidate nodes
 * @param solutionSize current solution
 * @param k k neighbourhood
 * @return nodeSolution 
 */
nodeSolution vns::shake(std::vector<int> candidates, int solutionSize, int k) {
  // seleccionamos un tamaño aleatorio en el entorno, puede ser positivo o negativo
  int size = (rand() % 2 == 1) ? solutionSize + k : solutionSize - k;
  size = (size < 1) ? solutionSize + k : size;
  size = (size > candidates.size()) ? solutionSize - k : size;
  // si k es muy elevado para el numero de nodos puede ocurrir esto
  size = (size < 1) ? 1 : size;
  size = (size < 2) ? candidates.size() : size;
  return constructSolution(candidates, size);
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
nodeSolution vns::localSearch(nodeSolution solution, std::vector<int> candidates) {
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
int vns::getWorstMdNode(nodeSolution actualSolution) {
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

  int selectedK = rand() %  (kVertex.size());
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
int vns::getMaxMdNode(nodeSolution actualSolution, std::vector<int> candidates) {
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


  int selectedK = rand() %  (kVertex.size());
  return kVertex[selectedK];  
}