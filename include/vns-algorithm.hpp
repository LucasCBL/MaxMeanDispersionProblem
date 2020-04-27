/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase vns
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include <algorithm>
#include "distance-matrix.hpp"
#include "algorithm.hpp"
#include <stdlib.h>  
#include <time.h> 
#include <cmath>
#pragma once
/**
 * @brief Variable Neighbour Search algorithm for max mean dispersion problem
 * 
 */
class vns : public algorithm {
private:
  float kmax_;
  bool anxious_;
public:
  /**
   * @brief Construct a new vns algorithm object
   * 
   * @param problem problem to solve, can be changed dinamically by using setPorblem
   * @param maxIter maximum number of iterations
   * @param maxNoImpIter maximum number of iterations without improvement
   * @param kmax number of max neightbourhoods to explore in each iteration 
   * @param anxious boolean to activate anxious mode, by default its false
   */
  vns(distanceMatrix problem, int maxIter, int maxNoImpIter, float kmax = 2, bool anxious = false) :
      algorithm(problem, maxIter, maxNoImpIter), kmax_(kmax), anxious_(anxious) {}
  /**
   * @brief solve function for the vns algorithm, it works by generating a random solution, and then
   * generating a random solution in the k neighbourhood of the current solution, which is +-k size of
   * the current solution in this case, and then does a localSearch for that solution, if it reaches a better
   * solution than the current k resets to one and the current solution changes to the new one, 
   * it does this until kmax is reached, then repeats this until a stop condition is reached
   * 
   * @return nodeSolution best found solution
   */
  nodeSolution solve();
  /**
   * @brief constructs a new random solution for a determined size
   * 
   * @param candidates candidate nodes
   * @param solutionSize target size
   * @return nodeSolution generated solution
   */
  nodeSolution constructSolution(std::vector<int> candidates, int solutionSize);
  /**
   * @brief calls constructSolution with a size in the K neighbourhood
   * 
   * @param candidates candidate nodes
   * @param solutionSize current solution
   * @param k k neighbourhood
   * @return nodeSolution 
   */
  nodeSolution shake(std::vector<int> candidates, int solutionSize, int k);
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
  nodeSolution localSearch(nodeSolution solution, std::vector<int> candidates);
  /**
   * @brief returns the worst node found in the current solution, if deleting any node doesnt improve the solution
   * it returns -1
   * 
   * @param actualSolution solution to evaluate
   * @return int node or -1 if the solution doesnt improve
   */
  int getWorstMdNode(nodeSolution actualSolution);
  /**
   * @brief returns the best node found in candidates to add to the solution, if adding any node doesnt improve 
   * the solution, it returns -1
   * 
   * @param actualSolution solution to improve
   * @param candidates nodes to evaluate
   * @return int node or -1 if the solution doesnt improve
   */
  int getMaxMdNode(nodeSolution actualSolution, std::vector<int> candidates);
};

