/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase greedy constructiva
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include "../include/greedy-algorithm.hpp"
/**
 * @brief Solve function, generates an initial solution by taking one pair with the best 
 * affinity between themselves, and adds the node returned from getMaxMd until it returns -1
 * 
 * @return nodeSolution local optimum
 */
nodeSolution greedy::solve() {
  /*
  Seleccionar la arista (i, j) con mayor afinidad;
  2: S = {i, j};
  3: repeat
  4: S  ∗ = S;
  5: Obtener el vértice k que maximiza md(S ∪ {k});
  6: if md(S ∪ {k}) ≥ md(S) then
  7: S = S ∪ {k};
  8: until (S∗ == S)
  9: Devolver S∗;
  */
  nodeSolution solution = problem_.getMaxEdge();
  int kVertex = getMaxMd(solution);
  
  while(kVertex != -1){
    solution.push_back(kVertex);
    kVertex = getMaxMd(solution);
  }

  return solution;
}
/**
 * @brief returns the best node found in candidates to add to the solution, if adding any node doesnt improve 
 * the solution, it returns -1
 * 
 * @param actualSolution solution to improve
 * @return int node or -1
 */
int greedy::getMaxMd(nodeSolution actualSolution) {
    nodeSolution kVertex;
    kVertex.push_back(-1);
    float currentMd = problem_.getMd(actualSolution);
    float currentEdgeSum = currentMd * (float)actualSolution.size();

    for(int i = 0; i < problem_.getNodes(); i++) {
      //verifica si existe el elemento i en la solucion, devuelve true si no lo encuentra
      if(std::find(actualSolution.begin(), actualSolution.end(), i) == actualSolution.end()) {
        float testMd = problem_.getNewMdAdd(actualSolution, currentEdgeSum, i);
        if(testMd > currentMd) {
          currentMd = testMd;
          kVertex.clear();
          kVertex.push_back(i);
        } else if(testMd == currentMd) {
          kVertex.push_back(i);
        }
      }
    }

    int selectedK = rand() %  (kVertex.size());
    return kVertex[selectedK]; 
  }