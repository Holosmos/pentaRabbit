//
//  Moteur.hpp
//  Simulation Dynamiques
//
//  Created by Raphaël Alexandre on 08/01/2018.
//  Copyright © 2018 Raphaël Alexandre. All rights reserved.
//

#ifndef Moteur_h
#define Moteur_h

#include <stdio.h>
#include <complex>
#include "Dynamicien.h"
#include "Julia.h"
#include "Mandelbrot.h"


void remplitImage(std::vector<unsigned char> *image, const std::vector<std::complex<double>> &matrice, const unsigned int &y, const unsigned int &longueur, const bool &peindreEnBlanc);

std::vector<double> coloration(complex<double> couleur, bool peindreEnBlanc);

vector<unsigned char> faireImage(unsigned int &hauteur, const unsigned int &longueur, complex<double> &origine, const double &echelle, const bool &peindreEnBlanc, const bool &symetrieVerticale, Dynamicien &dynamicien);

#endif /* Moteur_h */
