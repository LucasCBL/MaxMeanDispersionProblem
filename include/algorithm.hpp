/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase algorithm
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include "distance-matrix.hpp"
#pragma once
#include "solution.hpp"
/**
 * @brief virtual algorithm class(strategy pattern) used to solve a max mean dispersion problem
 * 
 */
class algorithm {
protected: 
  distanceMatrix problem_;
  int maxIterations_;
  int maxNoImprovIterations_;
public:
/**
 * @brief Construct a new algorithm object with a distance matrix as the container for the problem
 * 
 * @param problem 
 */
  algorithm(distanceMatrix problem) {
    problem_ = problem;
    maxIterations_ = 0;
    maxNoImprovIterations_ = 0;
  }
  /**
   * @brief Construct a new algorithm object with max iterations and max iterations without imporvements
   * 
   * @param problem 
   * @param maxIterations 
   * @param maxNoImprovIterarions 
   */
  algorithm(distanceMatrix problem, int maxIterations, int maxNoImprovIterarions) {
    maxIterations_ = maxIterations;
    maxNoImprovIterations_ = maxNoImprovIterarions;
    problem_ = problem;
  }
  /**
   * @brief Sets the value of the problem object
   * 
   * @param problem new problem
   */
  void setProblem(distanceMatrix problem) {
    problem_ = problem;
  }
  /**
   * @brief Solves the current problem 
   * 
   * @return nodeSolution solution
   */
  virtual nodeSolution solve() = 0;
};
