/*
 * NeuralNetwork.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "NeuralNetwork.h"

#include <cmath>

#include "Neuron.h"
#include "Synapse.h"
#include "constants.h"

NeuralNetwork::NeuralNetwork(int inNodes, int outNodes, int hiddenNodes) :
		bias(new Neuron()) {
	bias->setActivity(1.0);

	for (int i = 0; i < inNodes; ++i)
		inputs.push_back(new Neuron());
	for (int i = 0; i < hiddenNodes; ++i)
		hidden.push_back(new Neuron());
	for (int i = 0; i < outNodes; ++i)
		outputs.push_back(new Neuron());

	for (int i = 0; i < inNodes; ++i)
		for (int j = 0; j < hiddenNodes; ++j)
			synapses.push_back(new Synapse(inputs[i], hidden[j]));
	for (int i = 0; i < inNodes; ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(new Synapse(inputs[i], outputs[j]));
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = 0; j < outNodes; ++j)
			synapses.push_back(new Synapse(hidden[i], outputs[j]));
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = i + 1; j < hiddenNodes; ++j)
			synapses.push_back(new Synapse(hidden[i], hidden[j]));
	for (int i = 0; i < hiddenNodes; ++i)
		synapses.push_back(new Synapse(bias, hidden[i]));
	for (int i = 0; i < outNodes; ++i)
		synapses.push_back(new Synapse(bias, outputs[i]));
}

NeuralNetwork::~NeuralNetwork() {

}

void NeuralNetwork::feedForward(vector<double> inp) {
	for (int neuronIdx = 0; neuronIdx < inp.size(); neuronIdx++) {
		inputs[neuronIdx]->setActivity(inp[neuronIdx]);
	}
	for (int neuronIdx = 0; neuronIdx < hidden.size(); neuronIdx++) {
		hidden[neuronIdx]->feedForward();
	}
	for (int neuronIdx = 0; neuronIdx < outputs.size(); neuronIdx++) {
		outputs[neuronIdx]->feedForward();
	}
}

void NeuralNetwork::backProp(vector<double> correctOutput, bool correct) {
	for (int neuronIdx = outputs.size() - 1; neuronIdx >= 0; neuronIdx--) {
		//double* deltas = new double[neurons.size()];
		//if(neuronIdx >= outputNeurons) {
		if (correct) {
			outputs[neuronIdx]->delta = Neuron::sigmoidPrime(
					outputs[neuronIdx]->getNetInput())
					* (correctOutput[neuronIdx]
							- outputs[neuronIdx]->getActivity());
		} else {
			outputs[neuronIdx]->delta =
					Neuron::sigmoidPrime(outputs[neuronIdx]->getNetInput())
							* (correctOutput[neuronIdx]
									- outputs[neuronIdx]->getActivity()
									- sgn(
											correctOutput[neuronIdx]
													- outputs[neuronIdx]->getActivity()));
		}
		//}
	}
	for (int neuronIdx = hidden.size() - 1; neuronIdx >= 0; neuronIdx--) {
		double tempSum = 0;
		for (Edge* curOut : hidden[neuronIdx]->childs) {
			tempSum += ((Synapse*) curOut)->weight
					* ((Neuron*) curOut->out)->delta;
		}
		hidden[neuronIdx]->delta = Neuron::sigmoidPrime(
				hidden[neuronIdx]->getNetInput()) * tempSum;
		//}
	}
	for (Synapse* cur : synapses) {
		cur->weight += /*cur->learningRate*/Synapse::learningRate
				* ((Neuron*) cur->in)->getActivity()
				* ((Neuron*) cur->out)->delta;
	}
}

vector<double> NeuralNetwork::evalInput(vector<double> inp) {
	feedForward(inp);
	return getOutput();
}

Move NeuralNetwork::getMove(Board board) {
	return getMoveNode(evalInput(getNodeBoard(board)));
}

vector<double> NeuralNetwork::getOutput() const {
	vector<double> output;
	for (int i = 0; i < outputs.size(); i++) {
		output.push_back(outputs[i]->getActivity());
	}
	return output;
}
