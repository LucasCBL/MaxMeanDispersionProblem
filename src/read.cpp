/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de los metodos de la clase fileHandler
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/

#include <iostream>
#include "../include/read.hpp"
/**
 * @brief Reads inputFile_ with a node\n affinities... format and returns a matrix with the contents.
 * 
 * @return distanceMatrix 
 */
distanceMatrix fileHandler::read() {
  std::fstream file;
  file.open(inputFile_);
  if(file.is_open()) {
    int nodes;
    file >> nodes;
    std::vector <float> distances;
    int counter = 0;
    int target = nodes - 1;
    while(!file.eof() && target != 0) {
      float tempValue;
      file >> tempValue;
      distances.push_back(tempValue);
      counter++;
      if (counter == target){
        counter = 0;
        target--;
      }
    }
    if(target != 0) {
      std::cerr << "Error, not enough data\n";
    }
    file.close();
    return distanceMatrix(nodes, distances);
  }else {
    std::cerr << "Error opening file\n";
  }
}