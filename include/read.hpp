/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase fileHandler
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "./distance-matrix.hpp"
#pragma once
/**
 * @brief clase para el manejo de ficheros, es decir, lectura de los datos del problema
 * 
 */
class fileHandler{
private:
  std::string inputFile_;
public:
  /**
  * @brief Construct a new file Handler object
  * 
  * @param input 
  */
  fileHandler(std::string input): inputFile_(input){}
  /**
   * @brief Reads inputFile_ with a node\n affinities... format and returns a matrix with the contents.
   * 
   * @return distanceMatrix 
   */
  distanceMatrix read();
};


