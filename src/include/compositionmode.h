#pragma once
#ifndef COMPOSITION_MODE_H
#define COMPOSITION_MODE_H

enum class CompositionMode {
	MIP = 0,
	Accumulate = 1,
	Average = 2,
	Isosurface = 3,
	PARCVis = 4,
	PARCPass = 5
};

#endif // !COMPOSITION_MODE_H