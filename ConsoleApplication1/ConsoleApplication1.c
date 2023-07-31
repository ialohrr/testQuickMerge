
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main()
{
	const int sampleRate = 2e6;
	const int recordTimeInS = 10;
	const int sampleperChannel = sampleRate * recordTimeInS;
	const int numberOfFilteredChannel = 3;
	const int numberOfSampleToAdd = numberOfFilteredChannel * sampleperChannel;
	const int numberOfBaseChannel = 36;
	const int numberOfBaseSamples = numberOfBaseChannel * sampleperChannel;
	const int mergedSize = numberOfBaseSamples + numberOfSampleToAdd;
	uint8_t* samplesToAdd;
	uint8_t* baseSample;
	uint8_t* mergedArray;

	samplesToAdd = (uint8_t*)malloc(numberOfSampleToAdd * sizeof(uint8_t));
	memset(samplesToAdd, 2, numberOfSampleToAdd * sizeof(uint8_t));

	baseSample = (uint8_t*)malloc(numberOfBaseSamples * sizeof(uint8_t));
	memset(baseSample, 4, numberOfBaseSamples * sizeof(uint8_t));

	mergedArray = (uint8_t*)malloc(mergedSize * sizeof(uint8_t));
	clock_t start = clock();

	for (int i = 0; i < numberOfSampleToAdd / numberOfFilteredChannel; i++)
	{
		int offset = i * numberOfBaseChannel + i*(numberOfFilteredChannel);
		memcpy(mergedArray + offset, baseSample, numberOfBaseChannel * sizeof(uint8_t));
		memcpy(mergedArray + offset + numberOfBaseChannel, samplesToAdd + (i * numberOfFilteredChannel), numberOfFilteredChannel * sizeof(uint8_t));
		//mergedArray[offset + numberOfContiguousSamples] = samplesToAdd[i];
	}


	clock_t end = clock();
	start = end - start;
	printf("merged array sample for proof of concept \n");
	for (size_t i = 0; i < (numberOfBaseChannel+numberOfFilteredChannel)*2; i++)
	{
		printf("%i", mergedArray[i]);
	}
	printf("\n");

	double time_taken = ((double)start) / CLOCKS_PER_SEC;
	time_taken *= 1000;

	printf("this method merged %i samples in %f milliseconds", mergedSize,time_taken);


	free(samplesToAdd);
	free(baseSample);
	free(mergedArray);
}


