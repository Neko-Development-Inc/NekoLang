#include "NekoFile.h"

namespace files {

    string NekoFile::getFilepath() const {
        return filepath;
    }

    std::unique_ptr<NekoWriter>& NekoFile::getWriter() {
        if (writer == nullptr)
            writer = std::make_unique<NekoWriter>(*this);
        return writer;
    }

    std::unique_ptr<NekoReader>& NekoFile::getReader() {
        if (reader == nullptr)
            reader = std::make_unique<NekoReader>(*this);
        return reader;
    }
};