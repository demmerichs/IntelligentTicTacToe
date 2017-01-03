/*
 * NeuralNetwork.h
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "constants.h"

#include <vector>
using std::vector;

class Neuron;
typedef std::shared_ptr<Neuron> NeuronPtr;
class Synapse;
typedef std::shared_ptr<Synapse> SynapsePtr;

class NeuralNetwork {
public:
	NeuralNetwork(string s);
	NeuralNetwork(unsigned inNodes, unsigned outNodes, unsigned hiddenNodes);
	NeuralNetwork(unsigned inNodes, unsigned outNodes, unsigned layers,
			unsigned layerNodes);

	void saveNetwork(string s) const;

	void feedForward(vector<double> input);
	vector<double> backProp(vector<vector<double> > inputs,
			vector<vector<double> > correctOutputs, vector<double> scaling);

	vector<double> getOutput() const;
	vector<double> evalInput(vector<double> input);
	Move getMove(Board board);
	Move getProbableMove(Board board);

	vector<NeuronPtr> inputs;
	vector<NeuronPtr> hidden;
	vector<NeuronPtr> outputs;
	vector<SynapsePtr> synapses;

private:
	void simpleBackProp(vector<double> correctOutputs, double scale = 1.0);
	NeuronPtr getNeuron(unsigned idx) const;

	NeuronPtr bias;
};

#endif /* NEURALNETWORK_H_ */
