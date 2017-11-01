/*Author D.Patoukas 
* d.patoukas@gmail.com
* attempting to create a train program that will 
* output a train file for FANN. This file will e used as 
* an input to test against test data on a different program
*/

#include <stdio.h>

#include "fann.h"

int main(int argc, char const *argv[])
{
	//initiallizations of training phase
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 5;
	const float desired_error = (const float) 0.001;
	const unsigned int max_epochs = 2000;
	const unsigned int epochs_between_reports = 1000;
	
	//initiallizations for ann
	struct fann *ann;
	struct fann_train_data *train_data, *test_data;

	//Create a network
	train_data = fann_read_train_from_file("thyroid.train");

	ann = fann_create_standard(num_layers,
					  train_data->num_input, num_neurons_hidden, train_data->num_output);

	fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
	fann_set_learning_momentum(ann, 0.4f);

	//Train
	fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);

	printf("MSE error on test data: %f\n", fann_get_MSE(ann));

	//Save the train data
	fann_save(ann, "thyroid_trained.net");

	printf("Cleaning up.\n");
	fann_destroy_train(train_data);
	fann_destroy(ann);

	return 0;
}