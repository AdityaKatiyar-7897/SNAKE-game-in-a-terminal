#include "neural_net.h"
#include "neural_net.h"
#include <math.h>
#include <stdlib.h>

void init_network(NeuralNet *net) {
    for (int i = 0; i < INPUT_SIZE; i++)
        for (int j = 0; j < HIDDEN_SIZE; j++)
            net->weights_ih[i][j] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

    for (int i = 0; i < HIDDEN_SIZE; i++)
        for (int j = 0; j < OUTPUT_SIZE; j++)
            net->weights_ho[i][j] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

    for (int i = 0; i < HIDDEN_SIZE; i++)
        net->bias_h[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

    for (int i = 0; i < OUTPUT_SIZE; i++)
        net->bias_o[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}

float sigmoid(float x){
	return 1.0f / (1.0f + expf(-x));
}

void forward(NeuralNet *net, float inputs[INPUT_SIZE]) {
	for (int j = 0; j < HIDDEN_SIZE; j++) {
	    net->hidden[j] = 0;
	    for (int i = 0; i < INPUT_SIZE; i++) {
	        net->hidden[j] += inputs[i] * net->weights_ih[i][j];
	    }
	    net->hidden[j] += net->bias_h[j];
	    net->hidden[j] = sigmoid(net->hidden[j]);
	}

	for (int j = 0; j < OUTPUT_SIZE; j++) {
	    net->output[j] = 0;
	    for (int i = 0; i < HIDDEN_SIZE; i++) {
	        net->output[j] += net->hidden[i] * net->weights_ho[i][j];
	    }
	    net->output[j] += net->bias_o[j];
	    net->output[j] = sigmoid(net->output[j]);
	}
}

int get_action(NeuralNet *net){
	int best = 0;
	for (int i = 1 ; i < OUTPUT_SIZE; i++){
		if (net->output[i] > net->output[best]){
			best = i;
		}
	}
	return best;
}
