/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase greedy destructiva
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include "../include/original-greedy-algorithm.hpp"

/**
 * @brief parting from a solution formed by all the nodes in the problem space, we delete the node 
 * we get  from getWorstMd until it returns -1
 * 
 * @return nodeSolution local optimum
 */
nodeSolution originalGreedy::solve() {
  nodeSolution solution(problem_.getNodes());
  for(int i = 0; i < solution.size(); i++) {
    solution[i] = i;
  }
  int badVertex = getWorstMd(solution);
  while(badVertex != -1){
    solution.erase(solution.begin() + badVertex);
    badVertex = getWorstMd(solution);
  }
  return solution;
}
/**
 * @brief returns the worst node in the current solution, meaning the one which drags down the
 * md value the most, returns -1 if it doesnt find a node that drags the md value down.
 * 
 * @param actualSolution current solution to improve
 * @return int node or -1
 */
int originalGreedy::getWorstMd(nodeSolution actualSolution) {
    nodeSolution kVertex;
    kVertex.push_back(-1);
    float current = problem_.getMd(actualSolution);
    float currentEdgeSum =  current * actualSolution.size();
    for(int i = 0; i < actualSolution.size(); i++) {
      const int vertex = actualSolution[i];
      float testValue = problem_.getNewMdDelete(actualSolution, currentEdgeSum, vertex); 
      if(testValue > current) {
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