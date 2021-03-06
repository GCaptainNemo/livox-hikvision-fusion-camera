﻿#include "batchmanager.h"

int BatchManager::buffer_index = 0;

BatchManager::BatchManager( unsigned uNumBatches, unsigned numVerticesPerBatch, QOpenGLExtraFunctions * e) :
    _uNumBatches( uNumBatches ), _maxNumVerticesPerBatch( numVerticesPerBatch ), extraFunctions(e)
{

//    //a good size for each batch is between 1-4MB in size. Number of elements that can be stored in a
//    //batch is determined by calculating #bytes used by each vertex


    //create desired number of batches, 为_vBatches预留空间reserve,但在空间内不创建对象，
    // 且在push_back()/insert()之前不能[]引用vector。

    _vBatches.reserve( uNumBatches );
    for( unsigned u = 0; u < uNumBatches; ++u )
    {
        _vBatches.push_back(  new Batch( numVerticesPerBatch,  extraFunctions));
    }
}//BatchManager

//------------------------------------------------------------------------
BatchManager::~BatchManager() { _vBatches.clear(); }
//~BatchManager


// -----------------------------------------------------------------------
//void BatchManager::add( const std::vector<GuiVertex> & vVertices, const BatchConfig& config )
//{
//    _vBatches[BatchManager::buffer_index]->emptyData();
//    _vBatches[BatchManager::buffer_index]->add(vVertices, config);
//    buffer_index = (buffer_index + 1) % _uNumBatches;
//}
////add data in a vbo(queue)





// -----------------------------------------------------------------------
void BatchManager::add( const std::vector<float> * verticePositions)
{

    _vBatches[BatchManager::buffer_index]->emptyData();
    _vBatches[BatchManager::buffer_index]->add(verticePositions);
    buffer_index = (buffer_index + 1) % _uNumBatches;
}


// -----------------------------------------------------------------------

void BatchManager::renderAll()
{
    for( unsigned u = 0; u < _uNumBatches; ++u )
    {
        qDebug() << "u = " << u;
        _vBatches[u]->draw();
    }

}


//render data in all batch

//------------------------------------------------------------------------
//void BatchManager::render( const std::vector<GuiVertex> & vVertices, const BatchConfig& config )
//{

//    Batch* pEmptyBatch = nullptr;
//    Batch* pFullestBatch = _vBatches[0];

//    //determine which batch to put these vertices into
//    for( unsigned u = 0; u < _uNumBatches; ++u )
//    {
//        Batch* pBatch = _vBatches[u];
//        if( pBatch->isBatchConfig( config ) )
//            // 先确认batch config是否一样
//        {

//            if( !pBatch->isEnoughRoom( vVertices.size() ) )
//                // 如果pBatch的空间不够添加，就先清空再添加
//            {
//                //first need to empty this batch before adding anything to it
//                emptyBatch( false, pBatch );
//            }

//            pBatch->add( vVertices );
//            return;
//        }

//        //store pointer to first empty batch
//        if( nullptr == pEmptyBatch && pBatch->isEmpty() ) { pEmptyBatch = pBatch; }

//        //store pointer to fullest batch
//        pFullestBatch = pBatch->getFullest( pFullestBatch );
//    }

//    //if we get here then we didn't find an appropriate batch to put the vertices into
//    //if we have an empty batch, put vertices there
//    if( nullptr != pEmptyBatch )
//    {
//        pEmptyBatch->add( vVertices, config );
//        return;
//    }

//    //no empty batches were found therefore we must empty one first and then we can use it
//    emptyBatch( false, pFullestBatch );
//    pFullestBatch->add( vVertices, config );
//}
//render

//------------------------------------------------------------------------
//empty all batches by rendering their contents now
void BatchManager::emptyAll()
{
    for( unsigned u = 0; u < _uNumBatches; ++u )
    {
//        emptyBatch( true, _vBatches[u] );
        emptyBatch( _vBatches[u] );

    }
}//emptyAll

//------------------------------------------------------------------------
//struct CompareBatch : public std::binary_function
//{
//    bool operator()( const Batch* pBatchA, const Batch* pBatchB ) const
//    {
//        return ( pBatchA->getPriority() > pBatchB->getPriority() );
//    }//operator()
//};//CompareBatch

//------------------------------------------------------------------------



// empty specific patch
void BatchManager::emptyBatch( Batch* pBatchToEmpty )
{
    pBatchToEmpty->emptyData();
}




//empties the batches according to priority. If emptyAll is false then
//only empty the batches that are lower priority than the one specified
//AND also empty the one that is passed in


void BatchManager::emptyBatch( bool emptyAll, Batch* pBatchToEmpty )
{
    //sort batches by priority
//    std::priority_queue<Batch*, CompareBatch> queue;
//    for( unsigned int u = 0; u < _uNumBatches; ++u )
//    {
//        //add all non-empty batches to queue which will be sorted by order
//        //from lowest to highest priority
//        if( !_vBatches[u]->isEmpty() )
//        {
//            if( emptyAll )
//            {
//                queue.push( _vBatches.get() );
//            }
//            else if( _vBatches[u]->getPriority() < pBatchToEmpty->getPriority() )
//            {
//                //only add batches that are lower in priority
//                queue.push( _vBatches.get() );
//            }
//        }
//    }

//    //render all desired batches
//    while( !queue.empty() )
//    {
//        Batch* pBatch = queue.top();
//        pBatch->render();
//        queue.pop();
//    }

//    if( !emptyAll )
//    {
//        //when not emptying all the batches, we still want to empty
//        //the batch that is passed in, in addition to all batches
//        //that have lower priority than it
//        pBatchToEmpty->render();
//    }
}//emptyBatch
