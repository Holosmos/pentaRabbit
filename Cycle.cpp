#include "Cycle.h"

using namespace std;


bool Cycle::donneUnCycle(Homogene z0){
	
	// Calcul d'une partie l'orbite positive
	
	vector<Homogene> orbite(0);
	Homogene zEps(z0.x + c_eps, z0.y + c_eps/2);
	orbite.push_back(z0);
	c_point = Homogene(0.0);
	
	// On répertorie les images successives en les comparant aux précédentes
	
	for (unsigned int i = 1; i<= c_borne; i++) {
		z0 = fonctionIteree(z0);
		orbite.push_back(z0);
		for (unsigned int j=0; j<i; j++) {
			if (z0.distanceAvec(orbite[j]) <c_eps){
				
				// Si deux images sont eps-proches alors on vérifie que le cycle périodique potentiellement trouvé est suffisamment attractif
				c_point = z0;
				for (unsigned int k = 1; k<= i; k++) {
					zEps = fonctionIteree(zEps);
				}
				return z0.distanceAvec(zEps) < c_eps/10;
			}
		}
	}
	return false;
}

Homogene Cycle::chercheUnCycleAuPoint(Homogene z0){
	if (donneUnCycle(z0)) {
		return c_point;
	}
	return pointDefaut;
}

void Cycle::calculeLesCyclesAttractifs(){
	srand (static_cast <unsigned> (time(0)));

    unsigned int nombreTrouve = 0 ;

	// Etude du point à l'infini
	Homogene cycleInfini = chercheUnCycleAuPoint(pointInfini); // Tente le cycle à l'infini

	if (cycleInfini.x != pointDefaut.x || cycleInfini.y != pointDefaut.y) { // Regarde si on récupère un cycle ou le point par défaut
		cyclesAttractifs->push_back(cycleInfini);
        nombreTrouve++;
	}

	// Tirage de quelques points
	for (unsigned int j = 1; j <= nombreDeTirages && nombreTrouve < nombreDeCyclesVoulus; j++) {

		complex<double> z((((rand()%2==0)?-1:1)*rand()%45678)/45678.*j/10.,
				   (((rand()%2==0)?-1:1)*rand()%45678)/45678.*j/10.);

		Homogene z0(z);
		Homogene cycleZ0 = chercheUnCycleAuPoint(z0);

		if (cycleZ0.x != pointDefaut.x || cycleZ0.y != pointDefaut.y) {
			if (nEstPasDejaUnCycle(cycleZ0)){ // vérifie que le cycle n'est pas déjà existant dans la liste
				cyclesAttractifs->push_back(cycleZ0);
                nombreTrouve++;
				if (affichageDesCycles)
                    cycleZ0.print();
			}
		}

	}
    if (affichageDesCycles)
        cout << cyclesAttractifs->size() << endl;
}

bool Cycle::nEstPasDejaUnCycle(const Homogene &point){

	// Vérification que le cycle n'est pas déjà répertorié

	unsigned long nombreDeCycles = cyclesAttractifs->size();

	for (int j = 0; j < nombreDeCycles; j++) {

		Homogene cycle = (*cyclesAttractifs)[j];
		Homogene copie = point;

		if (copie.distanceAvec(cycle) < parametreDistance) {
			return false;
		}

		bool estDifferent = false;

		// On itère jusqu'à nombreIterationsTests qui représente la longueur maximale pour un cycle considéré
		for (int k = 1; k <= nombreIterationsTests && !estDifferent; k++) {
			copie = fonctionIteree(copie);
			if (copie.distanceAvec(cycle) < parametreDistance) {
				return false;
			}
			if (copie.distanceAvec(point) < parametreDistance) { // C'est le cas où le cycle s'est bouclé sans rencontrer l'autre cycle
				estDifferent = true;
			}
		}
	}
	return true;
}

void Cycle::chercheANouveau(const complex<double> &origine, const double &echelle){

	 // Recherche plus ciblée de cycles

	 for (unsigned int j = 1; j<= nombreDeTirages; j++) {
		 complex<double> z((((rand()%2==0)?-1:1)*rand()%123456)/123456.*echelle/10.,
					(((rand()%2==0)?-1:1)*rand()%123456)/123456.*echelle/10.);
		 z = z + origine;

		 Homogene z0(z);
		 Homogene cycleZ0 = chercheUnCycleAuPoint(z0);

		 if (cycleZ0.x != pointDefaut.x || cycleZ0.y != pointDefaut.y) {
			 if (nEstPasDejaUnCycle(cycleZ0)){ // vérifie que le cycle n'est pas déjà existant dans la liste
				 cyclesAttractifs->push_back(cycleZ0);
				 if (affichageDesCycles)
                     cycleZ0.print();
			 }
		 }
    }
	if (affichageDesCycles)
        cout << cyclesAttractifs->size() << endl;
 }
