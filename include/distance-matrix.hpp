/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase distance matrix
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <stdlib.h>  
#include <time.h> 
#include "solution.hpp"
#pragma once

/**
 * @brief Matrix containing all distances from one node to another, it also contains methods
 * pertaining to getting and calculating other related information from it
 * 
 */
class distanceMatrix {
private:
  int nodes_;
  std::vector <std::vector <float>> dMatrix_;
public:
  /**
 * @brief Construct a new distance Matrix object
 * 
 * @param nodes Number of nodes for the matrix
 * @param dataVector Vextor containing the necessary data for the matrix
 */
  distanceMatrix(int nodes, std::vector<float> dataVector);
  /**
   * @brief Construct a new empty distance Matrix object
   * 
   */
  distanceMatrix(void){};
  /**
   * @brief Copy constructor
   * 
   * @param copy The matrix to be copied upon this*
   * @return distanceMatrix this*
   */
  distanceMatrix operator=(distanceMatrix copy);
  /**
   * @brief Method for printing the entire matrix
   * 
   */
  void print();
  /**
   * @brief At function for a cell inside the matrix, returns a reference to the cell
   * 
   * @param i first node
   * @param j second node
   * @return float& cell contents
   */
  float& at(int i,int j);
  /**
   * @brief [] operator, acts as at, but instead returns the vector of distances for a specific node
   * 
   * @param i node
   * @return std::vector<float>& 
   */
  std::vector<float>& operator[](int i);
  /**
   * @brief Sets the value of a cell
   * 
   * @param i first node
   * @param j second node
   * @param value change value
   */
  void set(int i, int j, float value);
  /**
   * @brief returns the value of a cell without any reference
   * 
   * @param i first node
   * @param j second node
   * @return float cell value
   */
  float get(int i, int j);
  /**
   * @brief Get the amount of nodes making the matrix
   * 
   * @return int number of nodes
   */
  int getNodes();
  /**
   * @brief Get the mean dispersion for the given solution
   * 
   * @param solution given solution
   * @return float mean
   */
  float getMd(nodeSolution solution);
  /**
   * @brief Gets the mean dispersion for the given solution if node was added to it, using the previously 
   * calculated sum of edges for the solution
   * @param solution actual solution
   * @param currentEdgeSum sum of edges from the solution
   * @param node node to be added
   * @return float 
   */
  float getNewMdAdd(nodeSolution solution, float currentEdgeSum, int node);
   /**
   * @brief Gets the mean dispersion for the given solution if node was deleted from it, using the previously 
   * calculated sum of edges for the solution
   * @param solution actual solution
   * @param currentEdgeSum sum of edges from the solution
   * @param node node to be deleted
   * @return float 
   */
  float getNewMdDelete(nodeSolution solution, float currentEdgeSum, int node);
  /**
   * @brief Gets one pair of nodes from the list of nodes with an edge of maximum size
   * 
   * @return nodeSolution pair of nodes
   */
  nodeSolution getMaxEdge();
  /**
   * @brief Gets the list of nodes with any positive value.
   * 
   * @return std::vector<int> 
   */
  std::vector<int> getPosibleNodes();

};


