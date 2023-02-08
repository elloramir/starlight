#pragma once

#include <inttypes.h>

class Texture
{
public:
	uint32_t id;
	int32_t width, height;

	// NOTE(elloramir): it expects RGBA data
	void load(int32_t width, int32_t height, const uint8_t *data);
	void unload();
};