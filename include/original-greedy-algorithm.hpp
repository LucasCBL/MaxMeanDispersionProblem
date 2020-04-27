/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase greedy destructiva
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
 * @brief Destructive greedy algorithm for solving max mean dispersion problems
 * 
 */
class originalGreedy : public algorithm {
private:
public:
  /**
 * @brief Construct a new original destructive Greedy algorithm object
 * 
 * @param problem 
 */
  originalGreedy(distanceMatrix problem) : algorithm(problem) {}
  /**
   * @brief parting from a solution formed by all the nodes in the problem space, we delete the node 
   * we get  from getWorstMd until it returns -1
   * 
   * @return nodeSolution local optimum
   */
  nodeSolution solve();
  /**
   * @brief returns the worst node in the current solution, meaning the one which drags down the
   * md value the most, returns -1 if it doesnt find a node that drags the md value down.
   * 
   * @param actualSolution current solution to improve
   * @return int node or -1
   */
  int getWorstMd(nodeSolution actualSolution);
};

