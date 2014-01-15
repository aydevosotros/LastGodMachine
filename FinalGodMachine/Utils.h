#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "float.h"

//Sin novedad
class Utils{
public:
	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	    std::stringstream ss(s);
	    std::string item;
	    while (std::getline(ss, item, delim)) {
	        elems.push_back(item);
	    }
	    return elems;
	}

	static std::vector<std::string> split(const std::string &s, char delim) {
	    std::vector<std::string> elems;
	    split(s, delim, elems);
	    return elems;
	}

	static std::vector<double> vStovD(std::vector<std::string> vS){
		std::vector<double> vD;
		for(unsigned int i = 0; i < vS.size(); i++){
			vD.push_back(atof(vS[i].c_str()));
		}
		return vD;
	}

	static double getElement(std::vector<double> vect, std::vector<int> info, int l, int j, int k){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			if(i == info.size()-2){
				index += info[i]*info[i+1];
			} else {
				index += info[i]*(info[i+1]-1);
			}
		}

		if(i == info.size()-2){
			index += j*info[i+1];
		} else {
			index += j*(info[i+1]-1);
		}

		index += k;

		return vect[index];
	}

	//falta modificar igual que en el get
	static void setElement(std::vector<double> &vect, std::vector<int> info, int l, int j, int k, double element){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			if(i == info.size()-2){
				index += info[i]*info[i+1];
			} else {
				index += info[i]*(info[i+1]-1);
			}
		}

		if(i == info.size()-2){
			index += j*info[i+1];
		} else {
			index += j*(info[i+1]-1);
		}

		index += k;

		vect[index] = element;
	}

	static void plotData(std::vector<double> x, std::vector<double> y){
		std::ofstream myfile;
		myfile.open ("dataset.dat");
		for(int i = 0; i < x.size(); i++)
			myfile << x[i] << " " << y[i] << std::endl;
		myfile.close();
		system("gnuplot -persist -e \"plot './datafile.dat' using 1:2 title 'X' with linespoints, './datafile.dat' using 1:2 title 'Y' with points\"");
	}

	static void scalation(std::vector<Sample> &trainingSet){
		double absolMax = DBL_MIN;

		for(unsigned int i = 0; i < trainingSet.size(); i++){
			for(unsigned int j = 0; j < trainingSet[i].getInput().size(); j++){
				double num = trainingSet[i].getInput()[j];

				if(num < 0){
					num *= -1.0;
				}

				if(num > absolMax){
					absolMax = num;
				}
			}
		}

		for(unsigned int i = 0; i < trainingSet.size(); i++){
			trainingSet[i].scalate(absolMax);
		}
	}
};

#endif /* SAMPLE_H_ */
