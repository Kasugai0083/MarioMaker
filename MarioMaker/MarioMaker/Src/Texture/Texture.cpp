#include "Texture.h"
#include <d3dx9.h>
#include <stdlib.h>
#include <assert.h>
#include <map>


std::map<std::string, Texture*> g_TextureList2;

void LoadTexture(std::string fileName_) {
	if (!g_TextureList2[fileName_]) {
		g_TextureList2[fileName_] = new Texture;
	}
	CreateTexture(fileName_.c_str(), g_TextureList2[fileName_]);
}

Texture* GetTexture(std::string fileName_)
{
	return g_TextureList2[fileName_];
}

void AllReleaseTexture() {
	for (auto list : g_TextureList2) {
		if (!list.second) {
			delete list.second;
			list.second = nullptr;
		}
	}
}

void ReleaseCategoryTexture(std::string fileName_) {
	g_TextureList2[fileName_] = nullptr;
	delete g_TextureList2[fileName_];
}


