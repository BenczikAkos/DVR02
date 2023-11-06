#pragma once
#ifndef COMPOSITION_MODE_H
#define COMPOSITION_MODE_H

enum class CompositionMode {
	MIP = 0,
	Accumulate = 1,
	Average = 2,
	Isosurface = 3,
	Gradient = 4,
	PARCEnter = 5,
	PARCPass = 6
};

#endif // !COMPOSITION_MODE_H