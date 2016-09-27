#include <iostream>

#include "NeuralNetwork.h"
#include "runner.h"

using namespace std;

int main() {
	NeuralNetwork* nn = new NeuralNetwork(27, 9, 100);
	while (true) {
		int numSims;
		cin >> numSims;
		if(numSims<=0)
			break;
		cout << "|                    |" << endl << " ";
		int progressCounter = 1;
		for (int i = 0; i < numSims; ++i) {
			while(i*20 >= (numSims-1)*progressCounter){
				cout << "#" << flush;
				++progressCounter;
			}
			Runner run(nn);
			vector<State> goodies = run.getGoodStates();
			for (auto state : goodies) {
				nn->feedForward(getNodeBoard(state.first));
				nn->backProp(getNodeMove(state.second), true); //TODO check with Marvin if correct parameter
			}
			vector<State> baddies = run.getBadStates();
			for (auto state : baddies) {
				nn->feedForward(getNodeBoard(state.first));
				nn->backProp(getNodeMove(state.second), false); //TODO check with Marvin if correct parameter
			}
			if(i==numSims-1){
				cout << endl;
				run.dump();
			}
		}
	}
	return 0;
}
