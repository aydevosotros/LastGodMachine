#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <vector>

class Sample{
public:
	void scalate(double value){
		for(unsigned int i = 0; i < input.size(); i++){
			input[i] /= value;
		}
	}

	int getNFeatures(){
		return input.size();
	}

	const std::vector<double>& getInput() const {
		return input;
	}

	void setInput(const std::vector<double>& input) {
		this->input = input;
	}

	std::vector<int> getResult() const {
		return result;
	}

	void setResult(std::vector<int> result) {
		this->result = result;
	}
	
private:
	std::vector<double> input;
	std::vector<int> result;
};

#endif /* SAMPLE_H_ */
