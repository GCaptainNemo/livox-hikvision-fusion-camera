#include "batch.h"

Batch::Batch(unsigned uMaxNumVertices, QOpenGLExtraFunctions * e):
    _uMaxNumVertices( uMaxNumVertices ), extraFunctions(e),
    _uNumUsedVertices( 0 ), _vao( 0 ), _vbo( 0 ),
    _config(GL_TRIANGLE_STRIP, 0, 0 ), _lastVertex( glm::vec3(), glm::vec4() )
{
    defaultBatchConfig = new BatchConfig(0X00, 0, 0);
    //batch最好的尺寸在1-4MB. Number of elements that can be stored in a
    //batch is determined by calculating #bytes used by each vertex


    // 生成VAO的对象名字在&_vao中，创建“1”个VAO对象，&_vao对应的就是VAO对象名字，
    // 不一定是连续整数、但一定不与之前重复。
    extraFunctions->glGenVertexArrays(1, &_vao);
    qDebug() << "vao = " << _vao;


    // 绑定名字为_vao的VAO，若_vao=0则打破现有VAO的binding
    extraFunctions->glBindVertexArray(_vao);

    // 生成VBO的名字_vbo,同glGenVertexArrays
    extraFunctions->glGenBuffers(1, &_vbo);
    qDebug() << "vbo = " << _vbo;

    // 绑定名字为_vbo的VBO，Target是VBO绑定的目标，GL_ARRAY_BUFFER是顶点属性、GL_TEXTURE_BUFFER 纹理属性。
    extraFunctions->glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Target同上，size是VBO新数据的尺寸，data=nullptr是数据若为null则代表仅预留这么多的空间，
    // usage是数据存储的期望使用模式，
    // 比如GL_STREAM_READ...., GL_STREAM_DRAW使用显存
    extraFunctions->glBufferData(GL_ARRAY_BUFFER,
                                 uMaxNumVertices * sizeof( float ), nullptr, GL_STREAM_DRAW );
    // opengl version > 3.0
    // 解绑, 参数为0
    extraFunctions->glBindVertexArray(0);
    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );

}

Batch::~Batch() { cleanUp(); }


void Batch::emptyData()
{
    // 清空VBO中的数据
    extraFunctions->glBindVertexArray(_vao);
    extraFunctions->glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    extraFunctions->glBufferData(GL_ARRAY_BUFFER,
            _uMaxNumVertices * sizeof( float ), nullptr, GL_STREAM_DRAW );
    _uNumUsedVertices = 0;

    // 解绑, 参数为0
    extraFunctions->glBindVertexArray(0);
    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
    _uNumUsedVertices = 0;
}


void Batch::cleanUp()
{
    if( _vbo != 0 )
    {
        // 解绑
        extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
        // 删除“1”个VBO，名字是_vbo
        extraFunctions->glDeleteBuffers( 1, &_vbo );
        _vbo = 0;
    }

    if( _vao != 0 )
    {
        extraFunctions->glBindVertexArray( 0 );
        extraFunctions->glDeleteVertexArrays( 1, &_vao );
        _vao = 0;
    }
}//cleanUp

bool Batch::isBatchConfig( const BatchConfig& config ) const { return ( config == _config ); }
//isBatchConfig

//------------------------------------------------------------------------

bool Batch::isEmpty() const { return ( 0 == _uNumUsedVertices ); }

//isEmpty
//------------------------------------------------------------------------

//returns true if the number of vertices passed in can be stored in this batch
//without reaching the limit of how many vertices can fit in the batch
bool Batch::isEnoughRoom( unsigned uNumVertices ) const
{
    //2 extra vertices are needed for degenerate triangles between each strip
    unsigned uNumExtraVertices = ( GL_TRIANGLE_STRIP == _config.uRenderType && _uNumUsedVertices > 0 ? 2 : 0 );
    return ( _uNumUsedVertices + uNumExtraVertices + uNumVertices <= _uMaxNumVertices );
}
//isEnoughRoom

//------------------------------------------------------------------------
//returns the batch that contains the most number of stored vertices between
//this batch and the one passed in
Batch* Batch::getFullest( Batch* pBatch )
{
    return ( _uNumUsedVertices > pBatch->_uNumUsedVertices ? this : pBatch );
}//getFullest

//------------------------------------------------------------------------

// int Batch::getPriority() const { return _config.iPriority; }

//getPriority
//------------------------------------------------------------------------
//adds vertices to batch and also sets the batch config options

//void Batch::add( const std::vector<GuiVertex>& vVertices, const BatchConfig & config )
//{ _config = config; add( vVertices ); }

//add
//------------------------------------------------------------------------
void Batch::add( const std::vector<float> * verticePositions)
{
    //2 extra vertices are needed for degenerate triangles between each strip
    extraFunctions->glBindVertexArray( _vao );
    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, _vbo );

    // Use glMapBuffer instead, if moving large chunks of data > 1MB
    // 真正的绑定Vertex数据
    extraFunctions-> glBufferData( GL_ARRAY_BUFFER,
                                _uNumUsedVertices  * sizeof( float),
                                verticePositions, GL_STATIC_DRAW);

    extraFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    extraFunctions->glEnableVertexAttribArray(0);

    extraFunctions->glBindVertexArray( 0 );

    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
    _uNumUsedVertices = verticePositions->size();
    qDebug() << "vao = " << _vao << "_uNumUsedVertices = " << _uNumUsedVertices;
}
//add

//------------------------------------------------------------------------
void Batch::draw()
{
    if( _uNumUsedVertices == 0 )
    {
        //nothing in this buffer to render
        return;
    }
    glColor4d(1.0, 0, 0, 0);
    extraFunctions->glBindVertexArray( _vao );
    extraFunctions->glDrawArrays( GL_POINTS, 0, _uNumUsedVertices );
    extraFunctions->glBindVertexArray( 0 );
}//render

