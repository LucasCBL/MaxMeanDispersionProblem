/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase solution
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include <vector>
#include <iostream>
#pragma once
/**
 * @brief Solution class, it inherits from vector<int> as it is a container for nodes
 * 
 */
class nodeSolution : public std::vector<int> {
public:
  /**
 * @brief Construct a new node Solution object
 * 
 * @param size 
 */
  nodeSolution(int size): std::vector<int>(size){}
  /**
   * @brief Construct a new node Solution object with no empty constructor
   * 
   */
  nodeSolution(): std::vector<int>(){}
  /**
   * @brief print function, prints the node array between {..} separated by commas
   * 
   */
  void print() {
    for(int i = 0; i < size(); i++) {
      if(i == 0) {
        std::cout << "{"<< at(i);
      } else {
        std::cout << ", "<< at(i);
      }
    }
    std::cout << "}\n";
  }
};
