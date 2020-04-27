/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase multistart
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
 * @brief Multi start algoritm for solving max mean dispersion problems
 * 
 */
class multistart : public algorithm {
private:
  bool anxious_;
public:
/**
 * @brief Construct a new multistart algorithm object
 * 
 * @param problem problem to solve, can be changed dinamically by using setPorblem
 * @param maxIter maximum number of iterations
 * @param maxNoImpIter maximum number of iterations without improvement
 * @param anxious boolean to activate anxious mode, by default its false
 */
  multistart(distanceMatrix problem, int maxIter, int maxNoImpIter, bool anxious = false) :
      algorithm(problem, maxIter, maxNoImpIter), anxious_(anxious) {}
  /**
   * @brief Solve function for miltistart algorithm, it works similarly to grasp, but the initial solutions are
   * generated randomly.
   * 
   * @return nodeSolution 
   */
  nodeSolution solve();
  /**
   * @brief generates a random solution to evaluate
   * 
   * @param candidates posible nodes for generating the solution
   * @return nodeSolution generated solution
   */
  nodeSolution constructionPhase(std::vector<int> candidates) ;
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

