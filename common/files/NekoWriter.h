#ifndef NEKOWRITER_H
#define NEKOWRITER_H

#include "../../headers.h"

class files::NekoWriter {
public:
    NekoWriter(const NekoFile& nekoFile)
        : nekoFile(nekoFile) { }

private:
    const NekoFile& nekoFile;
};

#endif //NEKOWRITER_H