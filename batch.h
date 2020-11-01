#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H


#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <QOpenGLExtraFunctions>
#include <gl/GL.h>
//#include <gl/glew.h>
//#pragma comment(lib, "glew32.lib")


//#include <gl/GL.h>
//#include <gl/GLU.h>


// Notice that the GuiVertex defines a 2D coordinate on the screen that can contain a color
// and a texture coordinate.
struct GuiVertex {
    glm::vec2 position;
    glm::vec4 color;
    glm::vec2 texture;
    GuiVertex( glm::vec2 positionIn, glm::vec4 colorIn, glm::vec2 textureIn = glm::vec2() ) :
    position( positionIn ),
    color( colorIn ),
    texture( textureIn )
    {}
};//GuiVertex



// A BatchConfig defines how the vertices should be interpreted (uRenderType); be it a set of GL_LINES,
// set of GL_TRIANGLES, or a set of GL_TRIANGLE_STRIPS. The iPriority value indicates which order Batches
// should be rendered in. A higher priority value indicates that the Batch of vertices will appear on top
// of another Batch that has a lower priority. If vertices stored in a Batch have texture coordinates, then
// we need to know which texture to use (uTextureId). Lastly, if the vertices need to be transformed before being rendered,
// then their transformMatrix will contain a non-identity matrix. In this example I will be working with vertices defined this way:

struct BatchConfig
{
    unsigned uRenderType; // 一个Batch中数据的渲染方式，GL_LINES, GL_TRIANGLES....
    int iPriority;        // 一个Batch的渲染优先级
    unsigned uTextureId;  // 假如Batch中的节点对应一个纹理坐标，我们需要知道纹理的ID
    glm::mat4 transformMatrix; //initialized as identity matrix， 假如vertices的点需要变换

    // 结构体的初始化函数
    BatchConfig( unsigned uRenderTypeIn, int iPriorityIn, unsigned uTextureIdIn ) :
        uRenderType( uRenderTypeIn ), iPriority( iPriorityIn ), uTextureId( uTextureIdIn ) {}

    bool operator==( const BatchConfig& other) const
    {
        if( uRenderType != other.uRenderType || iPriority != other.iPriority ||
            uTextureId != other.uTextureId || transformMatrix != other.transformMatrix )
        {
            return false;
        }

        return true;
    }

    bool operator!=( const BatchConfig& other) const { return !( *this == other ); }
};//BatchConfig



// Notice that a Batch keeps track of how many vertices can be stored inside it
// (_uMaxNumVertices), as well as how many vertices are actually used in this
// batch (_uNumUsedVertices). A VBO is constructed to actually store the vertices
// on the GPU when a Batch is created. Each Batch can only store a particular set
// of vertices as defined in the BatchConfig.

class Batch
{
private:
    unsigned _uMaxNumVertices;     // 0 - 2 ^ 32 - 1, unsigned int
    unsigned _uNumUsedVertices;
    unsigned _vao; //only used in OpenGL v3.x +
    unsigned _vbo;
    BatchConfig _config;
    GuiVertex _lastVertex;    // Vertex attribute position, color, texture. 三角形绘制时采用
    //^^^^------ variables above ------|------ functions below ------vvvv

public:
    Batch(unsigned uMaxNumVertices, QOpenGLExtraFunctions * extraFunctions);
    ~Batch();

    bool isBatchConfig( const BatchConfig& config ) const;
    bool isEmpty() const;
    bool isEnoughRoom( unsigned uNumVertices ) const;

    Batch* getFullest( Batch* pBatch );
    int getPriority() const;

    void emptyData();
    void add( const std::vector<GuiVertex>& vVertices, const BatchConfig& config );
    void add( const std::vector<GuiVertex>& vVertices );
    void render();

protected:
private:
    Batch( const Batch& c ); //not implemented
    Batch& operator=( const Batch& c ); //not implemented
    void cleanUp();
    QOpenGLExtraFunctions * extraFunctions;

};


#endif // BATCHRENDERER_H
