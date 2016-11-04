#pragma once

#include <iostream>
#include <vector>
#include <chrono>

#include "NeuralNet.h"

bool RunTests(void);

static int TestIdempotence(int layerCount, int layerSize);
static int TestCreateLayerCountOne(void);
static int TestLayerSizeZero(void);
static void MeasureEncodingTime(int count, int size);
static void MeasureDecodingTime(int count, int size);