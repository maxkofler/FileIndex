#ifndef __FILEINDEX_H__
#define __FILEINDEX_H__

#include "fs.h"

class FileIndex{

public:
    FileIndex(FS* fs);

private:

    /**
     * @brief   The filesystem to use
     */
    FS*                         _fs;

};

#endif
