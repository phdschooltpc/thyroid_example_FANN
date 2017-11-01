/*Author D.Patoukas 
* d.patoukas@gmail.com
* attempting to test a trained ann against some testing data 
*  
* 
*/

#include <stdio.h>
#include <time.h>

#include "fann.h"

int main(int argc, char const *argv[])
{
	#ifdef TIMER_ON
	//timing declaration
	clock_t start, diff,start_big, diff_big;
	int msec;
	#endif

	//initiallize variables
	fann_type *calc_out;
	unsigned int i;
	int ret = 0;

	struct fann *ann;
	struct fann_train_data *data;
	
	//create ann from file	
	ann = fann_create_from_file("thyroid_trained.net");
	if(!ann)
	{
		printf("Error creating ann --- ABORTING.\n");
		return -1;
	}

	//read data to be tested
	data = fann_read_train_from_file("thyroid.test");
	fann_reset_MSE(ann);
	
	#ifdef TIMER_ON
	start_big = clock();
	#endif
	for(i=0; i<fann_length_train_data(data); i++)
	{
		calc_out = fann_test(ann, data->input[i], data->output[i]);
		printf("Result:(%f,%f,%f)| Should be:(%f,%f,%f)| Delta:(%f,%f,%f)\n",
			   calc_out[0],calc_out[1],calc_out[2],
			   data->output[i][0],data->output[i][1],data->output[i][2],
			   (float) fann_abs(calc_out[0] - data->output[i][0]),
			   (float) fann_abs(calc_out[1] - data->output[i][1]),
			   (float) fann_abs(calc_out[2] - data->output[i][2]));
	}
	printf("MSE error on %d test data: %f\n",fann_length_train_data(data), fann_get_MSE(ann));

	#ifdef TIMER_ON
	diff_big = clock()-start_big;
	msec = diff_big * 1000 / CLOCKS_PER_SEC;
	printf("Overall testing phase,in %ds and %dms\n",msec/1000, msec%1000);
	#endif
	
	printf("Cleaning up.\n");
	fann_destroy_train(data);
	fann_destroy(ann);
		
	return 0;
}