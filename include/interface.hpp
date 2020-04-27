/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Diseño y análisis de algoritmos
* Curso: 3º
* @file Fichero con la definicion de la clase interfaz
* @author Lucas Christian Bodson Lobato <alu0101111254@ull.edu.es>
* @copyright Lucas Christian Bodson Lobato 2020
* @version 1.0.1

*/
#include "distance-matrix.hpp"
#include "read.hpp"
#include "algorithm.hpp"
#include "greedy-algorithm.hpp"
#include "original-greedy-algorithm.hpp"
#include "grasp-algorithm.hpp"
#include "multi-start-algorithm.hpp"
#include "vns-algorithm.hpp"
#include "solution.hpp"
#include <algorithm>
#include <chrono>
#include <typeinfo> // para sacar el tipo del algoritmo
#pragma once
/**
 * @brief Interface class, it interacts with me user
 * 
 */
class interface {
  //srand(time(NULL));
private:
  std::string fileName_;
  distanceMatrix problem_;
  algorithm* method_;
  int print_;
public:
  /**
   * @brief Construct a new interface object
   * 
   */
  interface(){ 
  }
  /**
   * @brief Run menu, selects problem file, algorithm, number of executions, and print options, then calls
   * buildMethod and run.
   */
  void menu() {
    std::cout << "Bienvenido/a al estudio del problema Max Mean Dispersion\n";
    std::cout << "Introduzca el fichero problema(si no desea modificar el fichero introduzca 0):";
    std::string input;
    std::cin >> input;
    if(input != "0" ){
      fileName_ = input;
    }
    int method = 0;
    while (method < 1 || method > 5) {
      std::cout << "Los algoritmos disponibles son :\n";
      std::cout << "\t1 Greedy constructivo\n";
      std::cout << "\t2 Greedy destructivo\n";
      std::cout << "\t3 GRASP\n";
      std::cout << "\t4 Multiarranque\n";
      std::cout << "\t5 VNS\n";
      std::cout << "Seleccione el algoritmo a usar: ";
      std::cin >> method;
    }
    int iterations = 0;
    while (iterations < 1) {
      std::cout << "introduzca el numero de veces que quiere ejecutar el algoritmo: ";
      std::cin >> iterations; 
    }
    std::cout << "Si desea imprimir todas las iteraciones introduzca 1: ";
    std::cin >> print_;
    fileHandler lector(fileName_);
    problem_ = lector.read();
    buildMethod(method);
    run(iterations);
    std::cout << "si desea volver a ejecutar el programa introduzca 1: ";
    int option;
    std::cin >> option;
    if (option == 1) {
      menu();
    }
  }
  /**
   * @brief Creates an algorithm object and asks for the necesary inputs for them
   * 
   * @param method method to build
   */
  void buildMethod(int method) {
    switch(method) {
      case 1:
        method_ = new greedy(problem_);
      break;
      case 2:
        method_ = new originalGreedy(problem_);
      break;
      case 3:{
        std::cout << "Introduzca las especificaciones para grasp\n";
        int maxIter = 0; // max iterations
        int maxNoImpIter = 0; // max no improvement iterations
        float alpha = 0.0;
        int anxious = -1;
        while(maxIter < 1) {
          std::cout << "\tNumero de iteraciones máximas:";
          std::cin >> maxIter;
        }
        while(maxNoImpIter < 1) {
          std::cout << "\tNumero de iteraciones sin mejora máximas:";
          std::cin >> maxNoImpIter;
        }
        while(alpha <= 0 || alpha > 1) {
          std::cout << "\tAlpha (numero entre 0 y 1 que significa el procentaje de  los nodos disponibles incluidos en el RCL):";
          std::cin >> alpha;
        }
        while(anxious < 0) {
          std::cout << "\tModo ansioso(1 -> si):";
          std::cin >> anxious;
        }
        method_ = new grasp(problem_, maxIter, maxNoImpIter, alpha, (anxious == 1));
      }
      break;
      case 4: {
        std::cout << "Introduzca las especificaciones para el algoritmo multiarranque\n";
        int maxIter = 0; // max iterations
        int maxNoImpIter = 0; // max no improvement iterations
        int anxious = -1;
        while(maxIter < 1) {
          std::cout << "\tNumero de iteraciones máximas:";
          std::cin >> maxIter;
        }
        while(maxNoImpIter < 1) {
          std::cout << "\tNumero de iteraciones sin mejora máximas:";
          std::cin >> maxNoImpIter;
        }
        while(anxious < 0) {
          std::cout << "\tModo ansioso(1 -> si):";
          std::cin >> anxious;
        }
        method_ = new multistart(problem_, maxIter, maxNoImpIter, (anxious == 1));
      }
      break;
      case 5:{
        std::cout << "Introduzca las especificaciones para vns\n";
        int maxIter = 0; // max iterations
        int maxNoImpIter = 0; // max no improvement iterations
        float kmax = 0.0;
        int anxious = -1;
        while(maxIter < 1) {
          std::cout << "\tNumero de iteraciones máximas:";
          std::cin >> maxIter;
        }
        while(maxNoImpIter < 1) {
          std::cout << "\tNumero de iteraciones sin mejora máximas:";
          std::cin >> maxNoImpIter;
        }
        while(kmax <= 0) {
          std::cout << "\tNumero de entornos máximos (kmax):";
          std::cin >> kmax;
        }
        while(anxious < 0) {
          std::cout << "\tModo ansioso(1 -> si):";
          std::cin >> anxious;
        }
        method_ = new vns(problem_, maxIter, maxNoImpIter, kmax, (anxious == 1));
      }
      break;
      default:
        std::cerr << "algoritmo invalido\n";
      break;
    }
  }
  /**
   * @brief runs the solve algorithm and prints results
   * 
   * @param iterations number of excutions
   */
  void run(int iterations) {
    float sumOfMeans = 0.0;
    for(int i = 0; i < iterations; i++){
      auto start_time = std::chrono::high_resolution_clock::now();
      nodeSolution solution = method_ -> solve();
      auto end_time = std::chrono::high_resolution_clock::now();
      auto time = end_time - start_time;
      if( print_ == 1){
        solution.print();
        if( time / std::chrono::milliseconds(1) < 1) {
          std::cout << "\ttime: " << time / std::chrono::microseconds(1) << "μs\n";
        } else {
          std::cout << "\ttime: " << time / std::chrono::milliseconds(1) << "ms\n";
        }
        
        std::cout << "\t mean: " << problem_.getMd(solution) << std::endl;
        std::cout << "-----------------------------\n";
      }
      sumOfMeans += problem_.getMd(solution);
    }
    std::cout << "Avg mean = " << sumOfMeans / iterations << std::endl;
    delete method_;
  }
};
