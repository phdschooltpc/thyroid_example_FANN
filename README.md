# Thyroid disease example for FANN
Machine learning example to be compiled and run on a workstation that has FANN installed 

## How to use
Ensure that you have [FANN installed](http://leenissen.dk/fann/wp/help/installing-fann/) in your workstation.

Compile the files using the makefile.

Execute:
```bash
./thyroid_train
./thyroid_test
```
## Suggestions

### Train

The thyroid_train.c is program that will create the training network to be used for testing. Executing will produce a new .net
file that contains all the information about the network you just trained. Using different input parameteres will produce
different networks which will vary in performance, accuracy and size.
Since we are running on an embedded platform our goal is to create a network with as much accuracy is possible using the least amount of space and computation.

#### Things to try:

If you want to modify your network start testing with some small changes in the thyroid_train.c:

+ Change max_epochs
+ Change num_layers
+ Change num_neurons_hidden

You can observe the changes in the .net file. Take careful notice of the size of your network as you will have to 
use this data as input on your MSP430.

You can always use the provided example if you don't feel like changing the network.

### Test 

Now that you have a network designed you can use the thyroid_test.c to test it against a number of samples found in thyroid.test.
This sampling procedure is the one that you will have to execute intermittently on your embedded devices. 

The amount of tests that you will manage to execute significantly impacts the evaluated accuracy of your implementation, but space constraints 
are a limiting factor on small devices. More tests on the MSP signify a more robust evaluation of a neural network.


## Now What?

Once you have designed your neural network and your testing facility you can use the provided scripts to convert your data
into header files and use them in your embedded application

```bash
./strip-train-data thyroid_trained.net
./strip-test-data thyroid.test [number_of_tests]

```








#
Why use headers? 

Some people claim that a magic SD card can be of help...

Some disagree

Pick your side....and fight!!


![vs logo](https://orig00.deviantart.net/4075/f/2009/364/3/a/mortal_kombat_logo_by_unmanuel.png "vs logo")
