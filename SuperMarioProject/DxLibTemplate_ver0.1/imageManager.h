#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include"const.h"

struct ImageInfo
{
	// DrawGraph等で使用する実際の画像番号
	int imageHandle;
	// 画像ファイルの場所(フォルダ名・ファイル名を含む)
	const char* imagePath;
};

class ImageManager
{
private:
	ImageManager();
	ImageManager& operator = (ImageManager& other) = delete;
	ImageManager(const ImageManager& other) = delete;
	ImageInfo imageInfoArray[IMAGE_INFO_LENGTH];

public:
	enum IMAGENAME
	{

		IMAGE_MAX,
	};

	static ImageManager* getInstance();

	void initImageManager();
	bool setImageInfo(int imageId, const char* imagePath);
	void loadImageAll();
	int getImageHandle(int imageId);
	void clearImageManager();
};



#endif