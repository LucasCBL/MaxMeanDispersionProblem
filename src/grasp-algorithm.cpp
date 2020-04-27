/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase grasp
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include "../include/grasp-algorithm.hpp"
/**
 * @brief Solve function implementation for grasp, it works by iterating until one of its stop conditions is reached
 * a loop of constructionPhase() and localSearch() to generate and optimize solutions.
 * @return nodeSolution the best solution obtained
 */
nodeSolution grasp::solve() {
  std::vector<int> candidates = problem_.getPosibleNodes();
  // la funcion
  nodeSolution bestSolution;
  bestSolution.push_back(0);
  float bestMd = problem_.getMd(bestSolution);
  int iterations = 0;
  int noImprovement = 0;
  while(iterations < maxIterations_ && noImprovement < maxNoImprovIterations_) {
    iterations++;
    nodeSolution initialSolution = constructionPhase(candidates);
    nodeSolution localOptimum = localSearch(initialSolution, candidates);
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
 * @brief Function to create a new solution using RCL, and selecting a random element from it until the
 * solution reaches a size previously selected at random
 * 
 * @param initialCandidates nodes that can be included in the solution
 * @return nodeSolution generated solution
 */
nodeSolution grasp::constructionPhase(std::vector<int> initialCandidates) {
  nodeSolution solution;
  int firstNode = rand() % initialCandidates.size();
  solution.push_back(initialCandidates[firstNode]);
  // size between 2 nodes and maxNodes
  int solutionSize = (rand() % (initialCandidates.size() - 2)) + 2;
  while (solution.size() < solutionSize) {
    nodeSolution RCL = makeRCL(solution, initialCandidates);
    int selectedK = rand() % RCL.size();
    solution.push_back(RCL[selectedK]);
  }
  return solution;
}
/**
 * @brief Funtion to create a RCL array based on an initial solution, returns remainingNodes * alpha elements
 * 
 * @param solution initial solution
 * @param candidates potential nodes
 * @return nodeSolution array of RCL nodes
 */
nodeSolution grasp::makeRCL(nodeSolution solution, std::vector<int> candidates) {
  //resolucion alternativa, se dejo, porque aunque es más eficiente el tamaño del vector RCL 
  //es muy pequeño entorno a 0
  
  /*  Γ
  float gamma = getMaxMd(solution, candidates);
  nodeSolution RCL;
  //std::cout << "----------------\n";
  for(int i = 0; i < candidates.size(); i++) {
    if(std::find(solution.begin(), solution.end(), candidates[i]) == solution.end()) {
      solution.push_back(candidates[i]);
      float testMd = problem_.getMd(solution);
      solution.pop_back();
      // el problema con usar alfa para calcular rcl es que cuanto mas cercano a 0 menor será rcl
      if (testMd >= (gamma - (alpha_ * abs(gamma)))) {
        RCL.push_back(candidates[i]);
      }
    }
  }
  return RCL;
  */
 
  nodeSolution sortedNodes;
  std::vector<float> sortedMd;
  nodeSolution RCL;
  // Sorts the candidate nodes that arent already in the solution 
  for (int i = 0; i < candidates.size(); i++) {
    if (std::find(solution.begin(), solution.end(), candidates[i]) == solution.end()) {
      solution.push_back(candidates[i]);
      float temp = problem_.getMd(solution);
      solution.pop_back();
      int pos = 0;
      for (int j = 0; j < sortedMd.size(); j++) {
        if (temp < sortedMd[j]) {
          pos++;
        }
      }
      // the node is inserted in its correct location inside the array
      sortedMd.insert(sortedMd.begin() + pos, temp);
      sortedNodes.insert(sortedNodes.begin() + pos, candidates[i]);
    }
  }
  int percent = (sortedNodes.size() / (1 / alpha_));
  // if percent is 0 for example when size is less than 5 with alpha 0.2 returns one node
  percent = percent == 0 ? 1 : percent;
  std::copy(sortedNodes.begin(), sortedNodes.begin() + percent, std::back_inserter(RCL));
  return RCL;
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
nodeSolution grasp::localSearch(nodeSolution solution, std::vector<int> candidates) {
  bool improvement = true;
  while(improvement) { // si ambos greedy devuelven -1 se sale del bucle
    improvement = false; 
    //greedy destructivo
    int worstNode = getWorstMdNode(solution);
    if(worstNode != -1) {
      improvement = true;
      solution.erase(solution.begin() + worstNode);
    }
    //greedy constructivo
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
int grasp::getWorstMdNode(nodeSolution actualSolution) {
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
int grasp::getMaxMdNode(nodeSolution actualSolution, std::vector<int> candidates) {
  nodeSolution kVertex;
  kVertex.push_back(-1);
  float currentMd = problem_.getMd(actualSolution);
  float currentEdgeSum = currentMd * (float)actualSolution.size();

  for(int i = 0; i < candidates.size(); i++) {
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