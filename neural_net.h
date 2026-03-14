#ifndef NEURAL_NET_H
#define NEURAL_NET_H

typedef struct{
	float weights_ih[8][16];
	float weights_ho[16][4];
	float hidden[16];
	float output[4];
	float bias_h[16];
	float bias_o[4];
} NeuralNet;

#endif
