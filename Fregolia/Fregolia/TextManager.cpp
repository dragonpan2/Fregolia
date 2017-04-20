#include "TextManager.h"

TextManager::TextManager() { }

TextManager::~TextManager()
{
    FT_Done_FreeType(mFTLib);
}

void TextManager::loadFont(std::string pFontFile, int pFontSize)
{
    if(FT_Init_FreeType(&mFTLib))
    fprintf(stderr, "Erreur d'initialisation FreeType.");

    if(FT_New_Face(mFTLib, pFontFile.c_str(), 0, &mFTFont))
        fprintf(stderr, "Erreur de chagement de police.");

    FT_Set_Pixel_Sizes(mFTFont, 0, pFontSize);
}

void TextManager::setFont(std::string pFontFile)
{
    if(FT_New_Face(mFTLib, pFontFile.c_str(), 0, &mFTFont))
        fprintf(stderr, "Erreur de chagement de police.");
}

void TextManager::setFontSize(int pFontSize)
{
    FT_Set_Pixel_Sizes(mFTFont, 0, pFontSize);
}




TextLine::TextLine()
{
    mTranslateMat = glm::mat4(1.0f);
}

TextLine::~TextLine() { }

void TextLine::setText(std::string pText)
{
    float x = 0;
    float y = 0;

    for(int i = 0; i < pText.size(); ++i)
    {
        if(FT_Load_Char(mFTFont, pText[i], FT_LOAD_RENDER))
            continue;

        std::vector<glm::vec2> mListePoints;
        std::vector<glm::vec2> mListeTex;

        textCharacter newChar;
        newChar.mChar = pText[i];

        newChar.mGlyph = mFTFont->glyph;

        /// CREATION DE LA TEXTURE DE L'IMAGE DU CARACTERE
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &newChar.mTexture);

        glBindTexture(GL_TEXTURE_2D, newChar.mTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA,
                     newChar.mGlyph->bitmap.width, newChar.mGlyph->bitmap.rows,
                     0, GL_ALPHA, GL_UNSIGNED_BYTE,
                     newChar.mGlyph->bitmap.buffer);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        /// POSITIONS UTILES POUR L'AFFICHAGE
        float xPos = x + (newChar.mGlyph->bitmap_left * (2/SCREEN_WIDTH)); /// Change to offset for changing font size
        float yPos = -y - (newChar.mGlyph->bitmap_top * (2/SCREEN_HEIGHT));
        float width = newChar.mGlyph->bitmap.width * (2/SCREEN_WIDTH);
        float height = newChar.mGlyph->bitmap.rows * (2/SCREEN_HEIGHT);

        /// CREATION DES COORDS DES POINTS
        mListePoints.push_back(glm::vec2(xPos, -yPos));
        mListePoints.push_back(glm::vec2(xPos + width, -yPos));
        mListePoints.push_back(glm::vec2(xPos, -yPos - height));
        mListePoints.push_back(glm::vec2(xPos + width, -yPos - height));

        /// CREATION DES COORDS DE TEXTURE
        mListeTex.push_back(glm::vec2(0, 0));
        mListeTex.push_back(glm::vec2(1, 0));
        mListeTex.push_back(glm::vec2(0, 1));
        mListeTex.push_back(glm::vec2(1, 1));

        /// CREATION DES BUFFERS

        glGenBuffers(1, &newChar.mVerticesVBO);

        glBindBuffer(GL_ARRAY_BUFFER, newChar.mVerticesVBO);

        glBufferData(GL_ARRAY_BUFFER,
                    mListePoints.size() * sizeof(glm::vec2),
                    mListePoints.data(),
                    GL_DYNAMIC_DRAW);

        glGenBuffers(1, &newChar.mTextureVBO);

        glBindBuffer(GL_ARRAY_BUFFER, newChar.mTextureVBO);

        glBufferData(GL_ARRAY_BUFFER,
                    mListeTex.size() * sizeof(glm::vec2),
                    mListeTex.data(),
                    GL_DYNAMIC_DRAW);

        mListeTexte.push_back(newChar);

        /// CHANGEMENT POSITION POUR PROCHAIN CARACTERE
        x += (newChar.mGlyph->advance.x >> 6) * (2/SCREEN_WIDTH);
        y += (newChar.mGlyph->advance.y >> 6) * (2/SCREEN_HEIGHT);
    }
}

void TextLine::setLocation(glm::vec2 pLocation)
{
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(pLocation.x, pLocation.y, 0.0f));
}

void TextLine::drawText(GLuint pShaderProgram, float pTimeElapsed, glm::vec4 pColor, glm::mat4 pView, glm::mat4 pProj)
{
    glUseProgram(pShaderProgram);

    GLint vertAttribute = glGetAttribLocation(pShaderProgram, "Coord2D");
    GLint texAttribute = glGetAttribLocation(pShaderProgram, "texCoords");

    if(vertAttribute < 0 || texAttribute < 0)
    {
        std::cout << "OpenGL: " << glGetError() << std::endl;
    }

    GLint tex = glGetUniformLocation(pShaderProgram, "Texture");
    if(tex < 0)
    {
        std::cout << "OpenGL: " << glGetError() << std::endl;
    }

    for(unsigned int i = 0; i < mListeTexte.size(); ++i)
    {
        glEnableVertexAttribArray(vertAttribute);
        glBindBuffer(GL_ARRAY_BUFFER, mListeTexte[i].mVerticesVBO);

        glVertexAttribPointer(vertAttribute,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              0);

        glEnableVertexAttribArray(texAttribute);
        glBindBuffer(GL_ARRAY_BUFFER, mListeTexte[i].mTextureVBO);

        glVertexAttribPointer(texAttribute,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              0);

        glBindTexture(GL_TEXTURE_2D, mListeTexte[i].mTexture);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(pShaderProgram, "Texture"), GL_TEXTURE0);

        glm::mat4 mTotalMat = mTranslateMat;

        glUniformMatrix4fv(glGetUniformLocation(pShaderProgram, "MMat"), 1, GL_FALSE, glm::value_ptr(mTotalMat));
        glUniformMatrix4fv(glGetUniformLocation(pShaderProgram, "VMat"), 1, GL_FALSE, glm::value_ptr(pView));
        glUniformMatrix4fv(glGetUniformLocation(pShaderProgram, "PMat"), 1, GL_FALSE, glm::value_ptr(pProj));

        glUniform1f(glGetUniformLocation(pShaderProgram, "time"), pTimeElapsed);
        glUniform4fv(glGetUniformLocation(pShaderProgram, "Color"), 1, glm::value_ptr(pColor));
        //std::cout << mListeTexte[i].mTexture << "\t" << mListeTexte[i].mVerticesVBO << "\t" << mListeTexte[i].mTextureVBO << std::endl;
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}


