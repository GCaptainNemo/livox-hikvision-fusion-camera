#ifndef BATCHMANAGER_H
#define BATCHMANAGER_H

#include <vector>
#include "batch.h"

// The BatchManager class is responsible for keeping a pool of batches (_vBatches).
// When BatchManager.render is called from the Game Engine, it will figure out which Batch
// should be used for the incoming vertices (vVertices) using the BatchConfig specified.
// If a Batch doesn't get filled all the way, then the vertices will be held on until a later
// time when they have to be rendered, or when the BatchManager.emptyAll function is called.
// My implementation of the BatchManager is shown below:
class BatchManager
{
    public:
    private:
        std::vector<Batch*> _vBatches;
        unsigned _uNumBatches;
        unsigned _maxNumVerticesPerBatch;
        QOpenGLExtraFunctions * extraFunctions;

        //^^^^------ variables above ------|------ functions below ------vvvv

    public:
        BatchManager( unsigned uNumBatches, unsigned numVerticesPerBatch, QOpenGLExtraFunctions * e );
        ~BatchManager();

        void render( const std::vector<GuiVertex>& vVertices, const BatchConfig& config );

        void emptyAll();

    protected:
    private:
        BatchManager( const BatchManager& c ); //not implemented
        BatchManager& operator=( const BatchManager& c ); //not implemented

        void emptyBatch( bool emptyAll, Batch* pBatchToEmpty );
        void emptyBatch(Batch* pBatchToEmpty );
};//BatchManager



#endif // BATCHMANAGER_H
