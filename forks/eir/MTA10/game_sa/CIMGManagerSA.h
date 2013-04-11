/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.2
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/CIMGManagerSA.h
*  PURPOSE:     Image accelerated archive management
*  DEVELOPERS:  Martin Turski <quiret@gmx.de>
*  INSPIRATION: fastman92 <http://fastman92.tk>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef _IMAGE_MANAGER_SA_
#define _IMAGE_MANAGER_SA_

#define ARRAY_ModelLoadCache    0x009654B4  //usually a pointer to the LoadModelInfo static array

void IMG_Initialize( void );
void IMG_Shutdown( void );

enum eLoadingState : unsigned char
{
    MODEL_UNAVAILABLE,
    MODEL_LOADED,
    MODEL_LOADING,
    MODEL_LOD,    // Perhaps
    MODEL_RELOAD
};

// Allocated at 0x008E4CC0 in an array[MAX_MODELS]
class CModelLoadInfoSA  // size: 20
{
public:
    unsigned short  m_primaryModel;     // 0
    unsigned short  m_secondaryModel;   // 2
    unsigned short  m_lastID;           // 4
    unsigned char   m_flags;            // 6
    unsigned char   m_imgID;            // 7
    unsigned int    m_blockOffset;      // 8
    unsigned int    m_blockCount;       // 12
    eLoadingState   m_eLoading;         // 16

    BYTE            m_pad[3];           // 17

    bool __thiscall             GetOffset           ( unsigned int& offset, unsigned int& blockCount ) const;
    void __thiscall             SetOffset           ( unsigned int offset, unsigned int blockCount );
    unsigned int __thiscall     GetStreamOffset     ( void ) const;

    // Binary offsets: (1.0 US and 1.0 EU): 0x00407480
    inline void __thiscall      PushIntoLoader      ( CModelLoadInfoSA *chainInfo )
    {
        unsigned short thisId = this - *(CModelLoadInfoSA**)ARRAY_ModelLoadCache;
        unsigned short chainId = chainInfo - *(CModelLoadInfoSA**)ARRAY_ModelLoadCache;

        unsigned short primId = m_primaryModel = chainInfo->m_primaryModel;
        m_secondaryModel = chainId;

        chainInfo->m_primaryModel = thisId;

        ( *(CModelLoadInfoSA**)ARRAY_ModelLoadCache + primId )->m_secondaryModel = thisId;
    }

    // inlined into RequestModel and FreeModel.
    inline void __thiscall      PopFromLoader       ( void )
    {
        // Appears to notify the loader; will not be loading anymore
        ( *(CModelLoadInfoSA**)ARRAY_ModelLoadCache + m_primaryModel )->m_secondaryModel = m_secondaryModel;
        ( *(CModelLoadInfoSA**)ARRAY_ModelLoadCache + m_secondaryModel )->m_primaryModel = m_primaryModel;

        m_secondaryModel = 0xFFFF;
        m_primaryModel = 0xFFFF;
    }
};

#define MAX_GTA_IMG_ARCHIVES    256     // hardcoded maximum (see CModelLoadInfoSA::m_imgID)

struct IMGFile
{
    char            name[40];               // 0
    bool            isNotPlayerImg;         // 40
    // ALIGNMENT: 3bytes pad
    unsigned int    handle;                 // 44
};

extern IMGFile imgArchives[MAX_GTA_IMG_ARCHIVES];

#endif //_IMAGE_MANAGER_SA_