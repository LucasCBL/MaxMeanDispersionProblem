/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase greedy constructiva
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include <algorithm>
#include "distance-matrix.hpp"
#include "algorithm.hpp"
#include <stdlib.h>  
#include <time.h> 
#pragma once
/**
 * @brief constructive greedy algoritm for solving max mean dispersion problems
 * 
 */
class greedy : public algorithm {
private:
public:
  /**
   * @brief Construct a new greedy algorithm object
   * 
   * @param problem max mean dispersion problem to solve, stored inside a distance matrix
   */
  greedy(distanceMatrix problem) : algorithm(problem) {}
  /**
   * @brief Solve function, generates an initial solution by taking one pair with the best 
   * affinity between themselves, and adds the node returned from getMaxMd until it returns -1
   * 
   * @return nodeSolution local optimum
   */
  nodeSolution solve();
  /**
   * @brief returns the best node found in candidates to add to the solution, if adding any node doesnt improve 
   * the solution, it returns -1
   * 
   * @param actualSolution solution to improve
   * @return int node or -1
   */
  int getMaxMd(nodeSolution actualSolution);
};

