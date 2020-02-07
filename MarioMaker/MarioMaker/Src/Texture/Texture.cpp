#include <d3dx9.h>
#include <stdlib.h>
#include "Texture.h"
#include <assert.h>

// カテゴリごとのテクスチャ保存用配列
static Texture** g_TextureList[MAX_TEXTURE_CATEGORY] = { nullptr };

// カテゴリのテクスチャ最大サイズの配列
// シーン追加時に記入を忘れないように
int TextureCaterogySize[] = {
	TitleCategoryTextureList::TitleTextureMax,
	GameCategoryTextureList::GameTextureMax,
	ClearCategoryTextureList::ClearTextureMax,
};

// IDチェック
bool IsCategoryRangeCheck(int category_id, int texture_id);

void InitTexture()
{
	AllReleaseTexture();

	for (int i = 0; i < MAX_TEXTURE_CATEGORY; i++)
	{
		g_TextureList[i] = (Texture * *)malloc(sizeof(Texture*) * TextureCaterogySize[i]);

		for (int j = 0; j < TextureCaterogySize[i]; j++)
		{
			g_TextureList[i][j] = (Texture*)malloc(sizeof(Texture));

			g_TextureList[i][j]->TexutreData = nullptr;
		}
	}
}

void ReleaseCategoryTexture(int release_category)
{
	if (g_TextureList[release_category] == nullptr)
	{
		return;
	}

	for (int i = 0; i < TextureCaterogySize[release_category]; i++)
	{
		if (g_TextureList[release_category][i]->TexutreData == nullptr)
		{
			continue;
		}

		g_TextureList[release_category][i]->TexutreData->Release();
		g_TextureList[release_category][i]->TexutreData = nullptr;
	}
}

void AllReleaseTexture()
{
	for (int i = 0; i < MAX_TEXTURE_CATEGORY; i++)
	{
		if (g_TextureList[i] == NULL)
		{
			continue;
		}
		ReleaseCategoryTexture(i);
		for (int j = 0; j < TextureCaterogySize[i]; j++)
		{
			free(g_TextureList[i][j]);
		}
		free(g_TextureList[i]);
		g_TextureList[i] = NULL;
	}
}

bool LoadTexture(const char* file_name, int id, int texture_id)
{
	if (IsCategoryRangeCheck(id, texture_id) == false)
	{
		return false;
	}

	return CreateTexture(file_name, g_TextureList[id][texture_id]);
}

Texture* GetTexture(int category_id, int texture_id)
{
	if (IsCategoryRangeCheck(category_id, texture_id) == false)
	{
		return nullptr;
	}
	return g_TextureList[category_id][texture_id];
}

bool IsCategoryRangeCheck(int category_id, int texture_id)
{
	if (category_id <= -1 ||
		category_id >= MAX_TEXTURE_CATEGORY)
	{
		return false;
	}

	if (texture_id <= -1 ||
		texture_id >= TextureCaterogySize[category_id])
	{
		return false;
	}

	return true;
}
