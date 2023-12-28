#ifndef NEKOREADER_H
#define NEKOREADER_H

#include "../../headers.h"

class files::NekoReader {
public:
    NekoReader(const NekoFile& nekoFile)
            : nekoFile(nekoFile) { }

private:
    const NekoFile& nekoFile;
};

#endif //NEKOREADER_H