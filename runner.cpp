#include "runner.h"

Runner::Runner(NeuralNetwork *n) :
		network(n) {
	runSimulation();
}

void Runner::dump() const {
	cout << "Last bad move:" << endl;
	vector<State> baddies = getBadStates();
	constants::printMove(baddies[baddies.size()-1].first,baddies[baddies.size()-1].second);

	cout << "Last good move:" << endl;
	vector<State> goodies = getBadStates();
	constants::printMove(goodies[goodies.size()-1].first,goodies[goodies.size()-1].second);
	cout << endl;
}

void Runner::runSimulation() {
	short player = 1;
	short row, column;
	short state = 0;
	while (!state) {
		network->getMove(game.getBoard(player), row, column);
		moves.push_back(std::make_tuple(row, column, player));
		state = game.makeMove(row, column, player);
		player = (player % 2) + 1;
	}
	endState = state;
}

vector<State> Runner::getGoodStates() const {
	vector<State> states = std::vector<State>();
	TicTacToe pseudoGame;
	for (auto move : moves) {
		if (std::get<2>(move) == endState || (endState == -1 && std::get<2>(move) == circle))
			states.push_back(std::make_pair(pseudoGame.getBoard(std::get<2>(move)), move));
		pseudoGame.makeMove(std::get<0>(move), std::get<1>(move), std::get<2>(move));
	}
	return states;
}

vector<State> Runner::getBadStates() const {
	vector<State> states = std::vector<State>();
	TicTacToe pseudoGame;
	for (auto move : moves) {
		if (std::get<2>(move) != endState || (endState == -1 && std::get<2>(move) == cross))
			states.push_back(std::make_pair(pseudoGame.getBoard(std::get<2>(move)), move));
		pseudoGame.makeMove(std::get<0>(move), std::get<1>(move), std::get<2>(move));
	}
	return states;
}
