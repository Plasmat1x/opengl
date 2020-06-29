#include "Text.h"
#include "ResourceManager.h"

Text::Text():
    position(glm::vec2(0.0f, 0.0f)),
    size(12),
    color(glm::vec3(1.0f)),
    scale(glm::vec2(1.0f))
{

}


Text::~Text()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

void Text::bindGlyphs()
{
    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }
}

void Text::load(std::string font, GLuint size)
{
    this->size = size;
    this->shader = ResourceManager::getShader("text");

    initModel();

    this->characters.clear();

    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    FT_Set_Pixel_Sizes(face, 0, this->size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    bindGlyphs();
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    init();
}

void Text::init()
{
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        character = characters[*c];

        _size.x += (character.size.x + character.bearing.x) * scale.x;
        _size.y = characters['j'].size.y * scale.y;
    }
}

void Text::setShader(Shader shader)
{
    this->shader = shader;
}

void Text::setText(std::string text)
{
    this->text = text;
}

void Text::setPosition(glm::vec2 position)
{
    this->position = position;
}


void Text::setPosition(glm::vec2 position, GLfloat xoffset, GLfloat yoffset)
{
    this->position.x = position.x + xoffset;
    this->position.y = position.y + yoffset;
}

void Text::setColor(glm::vec3 color)
{
    this->color = color;
}

void Text::setSize(GLuint size)
{
    this->size = size;
}

void Text::setScale(glm::vec2 scale)
{
    this->scale = scale;
}

glm::vec2 Text::getSize()
{
    return this->_size;
}

void Text::draw()
{
    x = position.x;
    y = position.y;

    this->shader.use();
    this->shader.SetVector3f("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        character = characters[*c];

        GLfloat xpos = x + character.bearing.x * scale.x;
        GLfloat ypos = y + (this->characters['H'].bearing.y - character.bearing.y) * scale.y;

        GLfloat w = character.size.x * scale.x;
        GLfloat h = character.size.y * scale.y;

        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 },
            { xpos,     ypos,       0.0, 0.0 },

            { xpos,     ypos + h,   0.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 1.0 },
            { xpos + w, ypos,       1.0, 0.0 }
        };
        glBindTexture(GL_TEXTURE_2D, character.ID);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (character.advance >> 6) * scale.x;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::initModel()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
