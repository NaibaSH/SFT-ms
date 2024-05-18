#pragma once
#ifndef DELIVERY_H
#define DELIVERY_H
#include "mapping.h"

#define TRUCK_MAX_WEIGHT 1200 // Kilograms
#define TRUCK_MAX_VOLUME 50	  // square meters

#define BOX_SMALL 0.5 // square meters
#define BOX_MEDIUM 1
#define BOX_LARGE 5

struct Truck
{
	struct Point location;
	double remainingWeight;
	double remainingVolume;
};

struct Package
{
	double weight;
	double size;
	struct Point destination;
};

/**
* Return true (1) if the weight of the package is within the expected limits
* @param weight - the weight of the package to check
* @returns true (1) if the weight is between the package limits
*/
int verifyPackageWeight(double weight);
/**
* Return true (1) if the size of the package is one of the defined sizes. Currentrly they are BOX_SMALL, BOX_MEDIUM and BOX_LARGE constants.
* @param size - the size of the package to check
* @returns true (1) if the size of the package is one of the defined sizes
*/
int verifyPackageSize(double size);
/**
* Return true (1) if the weight of the package would be able to fit within the selected truck, based on the weight.
* @param truck - Truck struct, with its current data.
* @param weight - the weight of the package to check.
* @returns true (1) if the truck is capable to hold the weight of the package
*/
int verifyTruckWeightRemaining(struct Truck truck, double weight);
/**
* Return true (1) if the size of the package would be able to fit within the truck object, based on the size.
* @param truck - Truck struct, with its current data.
* @param size - the size of the package to check.
* @returns true (1) if the truck is capable to hold the size of the package.
*/
int verifyTruckSizeRemaining(struct Truck truck, double size);

#endif