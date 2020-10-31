#include "batch.h"

Batch::Batch(unsigned uMaxNumVertices, QOpenGLExtraFunctions * e):
    _uMaxNumVertices( uMaxNumVertices ), extraFunctions(e),
    _uNumUsedVertices( 0 ), _vao( 0 ), _vbo( 0 ),
    _config(GL_TRIANGLE_STRIP, 0, 0 ), _lastVertex( glm::vec2(), glm::vec4() )
{
    //batch最好的尺寸在1-4MB. Number of elements that can be stored in a
    //batch is determined by calculating #bytes used by each vertex


//    if( uMaxNumVertices < 1000 )
//        {
//            std::ostringstream strStream;
//            strStream << __FUNCTION__ << " uMaxNumVertices{" << uMaxNumVertices << "} is too small. Choose a number >= 1000 ";
//            throw ExceptionHandler( strStream );
//        }


//    if(Settings::getOpenglVersion().x >= 3 )
//    {
    // 生成VAO的对象名字在&_vao中，创建“1”个VAO对象，&_vao对应的就是VAO对象名字，
    // 不一定是连续整数、但一定不与之前重复。
    extraFunctions->glGenVertexArrays(1, &_vao);

    // 绑定名字为_vao的VAO，若_vao=0则打破现有VAO的binding
    extraFunctions->glBindVertexArray(_vao);

    // 生成VBO的名字_vbo,同glGenVertexArrays
    extraFunctions->glGenBuffers(1, &_vbo);

    // 绑定名字为_vbo的VBO，Target是VBO绑定的目标，GL_ARRAY_BUFFER是顶点属性、GL_TEXTURE_BUFFER 纹理属性。
    extraFunctions->glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // Target同上，size是VBO新数据的尺寸，data=nullptr是数据，usage是数据存储的期望使用模式，
    // 比如GL_STREAM_READ....
    extraFunctions->glBufferData(GL_ARRAY_BUFFER,
                                 uMaxNumVertices * sizeof( GuiVertex ), nullptr, GL_STREAM_DRAW );
    // opengl version > 3.0

//    unsigned uOffset = 0;
//    ShaderManager::enableAttribute( A_POSITION, sizeof( GuiVertex ), uOffset );
//    uOffset += sizeof( glm::vec2 );
//    ShaderManager::enableAttribute( A_COLOR, sizeof( GuiVertex ), uOffset );
//    uOffset += sizeof( glm::vec4 );
//    ShaderManager::enableAttribute( A_TEXTURE_COORD0, sizeof( GuiVertex ), uOffset );
//    glBindVertexArray( 0 );
//    ShaderManager::disableAttribute( A_POSITION );
//    ShaderManager::disableAttribute( A_COLOR );
//    ShaderManager::disableAttribute( A_TEXTURE_COORD0 );

    // 解绑
    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
//        if( GL_NO_ERROR != glGetError() )
//        {
//            cleanUp();
//            throw ExceptionHandler( __FUNCTION__ + std::string( " failed to create batch" ) );
//        }
//    }

}

Batch::~Batch() { cleanUp(); }

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

int Batch::getPriority() const { return _config.iPriority; }

//getPriority
//------------------------------------------------------------------------
//adds vertices to batch and also sets the batch config options

void Batch::add( const std::vector<GuiVertex>& vVertices, const BatchConfig& config )
{ _config = config; add( vVertices ); }

//add
//------------------------------------------------------------------------
void Batch::add( const std::vector<GuiVertex>& vVertices )
{
    //2 extra vertices are needed for degenerate triangles between each strip
    unsigned uNumExtraVertices = ( GL_TRIANGLE_STRIP == _config.uRenderType && _uNumUsedVertices > 0 ? 2 : 0 );
//    if( uNumExtraVertices + vVertices.size() > _uMaxNumVertices - _uNumUsedVertices )
//    {
//        std::ostringstream strStream; strStream << __FUNCTION__ << " not enough room for {" << vVertices.size() << "} vertices in this batch. Maximum number of vertices allowed in a batch is {" << _uMaxNumVertices << "} and {" << _uNumUsedVertices << "} are already used";

//        if( uNumExtraVertices > 0 )
//        {
//            strStream << " plus you need room for {" << uNumExtraVertices << "} extra vertices too";
//        }

//        throw ExceptionHandler( strStream );
//    }

//    if( vVertices.size() > _uMaxNumVertices )
//    {
//        std::ostringstream strStream; strStream << __FUNCTION__ << " can not add {" << vVertices.size() << "} vertices to batch. Maximum number of vertices allowed in a batch is {" << _uMaxNumVertices << "}";
//        throw ExceptionHandler( strStream );
//    }

//    if( vVertices.empty() )
//    {
//        std::ostringstream strStream;
//        strStream << __FUNCTION__ << " can not add {" << vVertices.size() << "} vertices to batch.";
//        throw ExceptionHandler( strStream );
//    }

    //add vertices to buffer
//    if( Settings::getOpenglVersion().x >= 3 )
//    {
    extraFunctions->glBindVertexArray( _vao );
//    }

    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, _vbo );

    if( uNumExtraVertices > 0 )
    {
        // 渲染方法是GL_TRIANGLE_STRIP时
        //need to add 2 vertex copies to create degenerate triangles between this strip
        //and the last strip that was stored in the batch
        // 退化三角形就是没有面积，不显示的三角形。
        // 更新一个VBA数据存储的子集，target是VBA的目标，offset是对VBA数据存储的偏移
        // size确认新数据存储的字节数  // data, 存入新数据的指针
        extraFunctions->glBufferSubData( GL_ARRAY_BUFFER, _uNumUsedVertices * sizeof( GuiVertex ),
                                         sizeof( GuiVertex ), &_lastVertex );


        extraFunctions->glBufferSubData( GL_ARRAY_BUFFER, ( _uNumUsedVertices + 1 ) * sizeof( GuiVertex ),
                                         sizeof( GuiVertex ), &vVertices[0] );
    }

    // Use glMapBuffer instead, if moving large chunks of data > 1MB
    // 真正的绑定Vertex数据
    extraFunctions-> glBufferSubData( GL_ARRAY_BUFFER,
                                      ( _uNumUsedVertices + uNumExtraVertices ) * sizeof( GuiVertex ),
                                      vVertices.size() * sizeof( GuiVertex ), &vVertices[0] );

//    if( Settings::getOpenglVersion().x >= 3 ) {
    extraFunctions->glBindVertexArray( 0 );

    extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
    _uNumUsedVertices = _uNumUsedVertices + vVertices.size() + uNumExtraVertices;
    _lastVertex = vVertices[vVertices.size() - 1];
}
//add

//------------------------------------------------------------------------
void Batch::render()
{
    if( _uNumUsedVertices == 0 )
    {
        //nothing in this buffer to render
        return;
    }

    bool usingTexture = INVALID_UNSIGNED != _config.uTextureId;

    ShaderManager::setUniform( U_USING_TEXTURE, usingTexture );

    if( usingTexture )
    {
        ShaderManager::setTexture( 0, U_TEXTURE0_SAMPLER_2D, _config.uTextureId );
    }

    ShaderManager::setUniform( U_TRANSFORM_MATRIX, _config.transformMatrix );
    //draw contents of buffer

    if( glGetString(GL_VERSION)[0] - 48 >= 3 )
    {
        extraFunctions->glBindVertexArray( _vao );
        extraFunctions->glDrawArrays( _config.uRenderType, 0, _uNumUsedVertices );
        extraFunctions->glBindVertexArray( 0 );
    }
    else
    {
        //OpenGL v2.x
        extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, _vbo );
        unsigned uOffset = 0;
        ShaderManager::enableAttribute( A_POSITION, sizeof( GuiVertex ), uOffset );
        uOffset += sizeof( glm::vec2 );
        ShaderManager::enableAttribute( A_COLOR, sizeof( GuiVertex ), uOffset );
        uOffset += sizeof( glm::vec4 );
        ShaderManager::enableAttribute( A_TEXTURE_COORD0, sizeof( GuiVertex ), uOffset );
        extraFunctions->glDrawArrays( _config.uRenderType, 0, _uNumUsedVertices );
        ShaderManager::disableAttribute( A_POSITION );
        ShaderManager::disableAttribute( A_COLOR );
        ShaderManager::disableAttribute( A_TEXTURE_COORD0 );
        extraFunctions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
    }

    //reset buffer
    _uNumUsedVertices = 0;
    _config.iPriority = 0;
}//render

