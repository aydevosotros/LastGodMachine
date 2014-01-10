#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <vector>

//Por determinar
class Sample{
public:
	std::vector<double> input;
	int result;

	int getNFeatures(){
		return input.size();
	}
};



#endif /* SAMPLE_H_ */
