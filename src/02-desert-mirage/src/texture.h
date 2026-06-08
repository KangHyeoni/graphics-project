#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture{
public:
    unsigned int ID;
    int width;
    int height;
    int channels;
    std::string path;
    bool isLoaded = false;

    Texture() {}
    Texture(const char* filePath)
    {
        path = std::string(filePath);
        stbi_set_flip_vertically_on_load(true);

        unsigned char *data = stbi_load(filePath, &width, &height, &channels, 0);
        if (data)
        {
            glGenTextures(1, &ID);
            glBindTexture(GL_TEXTURE_2D, ID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            if(channels == 3){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }else{
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);
            isLoaded = true;
        }
        else
        {
            std::cout << "Failed to load texture: " << filePath << std::endl;
            isLoaded = false;
        }
        stbi_image_free(data);
    }

    static unsigned int GetDummyTexture() {
        static unsigned int dummyID = 0;
        if (dummyID == 0) {
            glGenTextures(1, &dummyID);
            glBindTexture(GL_TEXTURE_2D, dummyID);
            unsigned char white[] = { 255, 255, 255, 255 };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        return dummyID;
    }
};

#endif
