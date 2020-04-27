/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase distance matrix
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include "../include/distance-matrix.hpp"
 /**
 * @brief Construct a new distance Matrix object
 * 
 * @param nodes Number of nodes for the matrix
 * @param dataVector Vextor containing the necessary data for the matrix
 */
distanceMatrix::distanceMatrix(int nodes, std::vector<float> dataVector) {
  nodes_ = nodes;
  dMatrix_.resize(nodes_, std::vector<float>(nodes_, 0));
  int vectorIndex = 0;
  for(int i = 0; i < nodes - 1; i++) {
    for(int j = i + 1; j < nodes; j++) {
      dMatrix_[i][j] = dataVector[vectorIndex];
      dMatrix_[j][i] = dataVector[vectorIndex];
      vectorIndex++;
    }
  }
}
/**
   * @brief Method for printing the entire matrix
   * 
   */
void distanceMatrix::print() {
  std::cout << "nodes: " << nodes_ << std::endl;
  std::cout << "i|j";
  for(int i = 1; i <= nodes_; i++){
    std::cout << "\t" << i;
  }
  std::cout << std::endl;
  for(int i = 0; i < nodes_; i++) {
    std::cout << i + 1 << "   ";
    for(int j = 0; j < nodes_; j++) {
      std::cout << "\t" << dMatrix_[i][j];
    }
    std::cout << std::endl;
  } 
}
/**
   * @brief At function for a cell inside the matrix, returns a reference to the cell
   * 
   * @param i first node
   * @param j second node
   * @return float& cell contents
   */
float& distanceMatrix::at(int i,int j) {
  return dMatrix_[i][j];
}
/**
   * @brief [] operator, acts as at, but instead returns the vector of distances for a specific node
   * 
   * @param i node
   * @return std::vector<float>& 
   */
std::vector<float>& distanceMatrix::operator[](int i) {
  return dMatrix_[i];
}
/**
   * @brief Sets the value of a cell
   * 
   * @param i first node
   * @param j second node
   * @param value change value
   */
void distanceMatrix::set(int i, int j, float value) {
  dMatrix_[i][j] = value;
}
/**
   * @brief returns the value of a cell without any reference
   * 
   * @param i first node
   * @param j second node
   * @return float cell value
   */
float distanceMatrix::get(int i, int j) {
  return dMatrix_[i][j];
}
/**
   * @brief Get the amount of nodes making the matrix
   * 
   * @return int number of nodes
   */
int distanceMatrix::getNodes() {
  return nodes_;
}
/**
   * @brief Copy constructor
   * 
   * @param copy The matrix to be copied upon this*
   * @return distanceMatrix this*
   */
distanceMatrix distanceMatrix::operator=(distanceMatrix copy){
  this->nodes_ = copy.nodes_;
  this->dMatrix_.clear();
  this->dMatrix_ = copy.dMatrix_;
  return (*this); 
}
/**
   * @brief Get the mean dispersion for the given solution
   * 
   * @param solution given solution
   * @return float mean
   */
float distanceMatrix::getMd(nodeSolution solution) {
  float sumOfEdges = 0;
  for(int i = 0; i < solution.size() - 1; i++) {
    for(int j = i + 1; j < solution.size(); j++) {
      sumOfEdges += dMatrix_[solution[i]][solution[j]];
    }
  }
  if(solution.size() == 0 ){
    return -INFINITY;
  }
  return sumOfEdges / solution.size();
}
 /**
   * @brief Gets the mean dispersion for the given solution if node was added to it, using the previously 
   * calculated sum of edges for the solution
   * @param solution actual solution
   * @param currentEdgeSum sum of edges from the solution
   * @param node node to be added
   * @return float 
   */
float distanceMatrix::getNewMdAdd(nodeSolution solution, float currentEdgeSum, int node){
  float sumOfEdges = currentEdgeSum;
  if(solution.size() == 0 ){
    return -INFINITY;
  }
  for(int i = 0; i < solution.size(); i++) {
    sumOfEdges += dMatrix_[solution[i]][node];
  }
  return sumOfEdges / (solution.size() + 1);
}
/**
   * @brief Gets the mean dispersion for the given solution if node was deleted from it, using the previously 
   * calculated sum of edges for the solution
   * @param solution actual solution
   * @param currentEdgeSum sum of edges from the solution
   * @param node node to be deleted
   * @return float 
   */
float distanceMatrix::getNewMdDelete(nodeSolution solution, float currentEdgeSum, int node){
  float sumOfEdges = currentEdgeSum;
  for(int i = 0; i < solution.size(); i++) {
    // el del propio nodo es 0 asi que funciona
    sumOfEdges -= dMatrix_[solution[i]][node];
  }
  if(solution.size() == 0 ){
    return -INFINITY;
  }
  return sumOfEdges / (solution.size() - 1);
}
/**
   * @brief Gets one pair of nodes from the list of nodes with an edge of maximum size
   * 
   * @return nodeSolution pair of nodes
   */
nodeSolution distanceMatrix::getMaxEdge() {
  std::vector<std::pair<int, int>> biggestEdges;
  biggestEdges.push_back(std::make_pair(0,1));
  float biggestVal = 0;
  for(int i = 0; i < nodes_ - 1; i++) {
    for(int j = i + 1; j < nodes_; j++) {
      if(dMatrix_[i][j] > biggestVal) {
        biggestEdges.clear();
        biggestEdges.push_back(std::make_pair(i,j));
        biggestVal = dMatrix_[i][j];
      } else if(dMatrix_[i][j] == biggestVal) {
        biggestEdges.push_back(std::make_pair(i,j));
      }
    }
  }
  //srand(time(NULL));
  //std::cout << biggestEdges.size() << std::endl;
  int randValue = rand() % (biggestEdges.size());
  nodeSolution selectedPair;
  selectedPair.push_back(biggestEdges[randValue].first);
  selectedPair.push_back(biggestEdges[randValue].second);
  return selectedPair;
}
/**
   * @brief Gets the list of nodes with any positive value.
   * 
   * @return std::vector<int> 
   */
std::vector<int> distanceMatrix::getPosibleNodes() {
  std::vector<int> candidateList;
  for (int i = 0; i < nodes_; i++) {
    for (int j = 0; j < nodes_; j++) {
      if (dMatrix_[i][j] >= 0 && (candidateList.size() == 0 || candidateList[candidateList.size() - 1] != i)) {
        candidateList.push_back(i);
      }
    }
  }
  return candidateList;
}
