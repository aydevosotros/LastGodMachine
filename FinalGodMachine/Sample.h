#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <vector>

typedef std::vector<std::vector<double> > std::vector<double>;

class Sample{
public:
	int getNFeatures(){
		return input.size();
	}

	const std::vector<double>& getInput() const {
		return input;
	}

	void setInput(const std::vector<double>& input) {
		this->input = input;
	}

	int getResult() const {
		return result;
	}

	void setResult(int result) {
		this->result = result;
	}
	
private:
	std::vector<double> input;
	int result;
};

#endif /* SAMPLE_H_ */
