//
//  Mandelbrot.hpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 02/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

// Pour générer Mandelbrot : utiliser ce code dans le main.cpp
/*/ Lancement de Mandelbrot et Dynamicien
 Dynamicien dynamicien;
 dynamicien.peindreEnBlanc = true;
 dynamicien.borneDIteration = borne;
 
 function<Complexe(Homogene)> dyn = [borne](Homogene point){
 Mandelbrot mandel;
 mandel.borneDIteration = borne;
 return mandel.convergencePourParametre(point.carteY());
 };
 //*/

#ifndef Mandelbrot_h
#define Mandelbrot_h

#include <cstdlib>
#include <iostream>
#include <vector>

#include <thread>
#include <cmath>
#include <complex>

#include "Algebre.h"
#include "Parametres.h"


struct Mandelbrot {
    Mandelbrot(const unsigned int &borne): borneDIteration(borne){};

	unsigned int borneDIteration;

    std::complex<double> convergencePourParametre(std::complex<double> c);
};

#endif /* Mandelbrot_h */
