/*
 * Synapse.cpp
 *
 *  Created on: 26.09.2016
 *      Author: David
 */

#include "Synapse.h"

#include "node.h"
#include "Neuron.h"

Synapse::Synapse() {
	// TODO Auto-generated constructor stub

}

Synapse::~Synapse() {
	// TODO Auto-generated destructor stub
}

double Synapse::getSignal() {
	return weight*((Neuron*) in)->activity;
}