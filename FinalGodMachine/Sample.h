#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <vector>

typedef std::vector<std::vector<double> > double_2M;

class Sample{
public:
	int getNFeatures(){
		return input.size();
	}

	const double_2M& getInput() const {
		return input;
	}

	void setInput(const double_2M& input) {
		this->input = input;
	}

	int getResult() const {
		return result;
	}

	void setResult(int result) {
		this->result = result;
	}
	
private:
	double_2M input;
	int result;
};

#endif /* SAMPLE_H_ */
