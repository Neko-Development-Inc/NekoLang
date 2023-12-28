#ifndef NEKOFILE_H
#define NEKOFILE_H

#include "../../headers.h"
#include "NekoWriter.h"
#include "NekoReader.h"

class files::NekoFile {
public:
    NekoFile(const string& filepath)
        : filepath(filepath),
          writer(nullptr),
          reader(nullptr) { }

    ~NekoFile() = default;

    string getFilepath() const;
    std::unique_ptr<NekoWriter>& getWriter();
    std::unique_ptr<NekoReader>& getReader();

private:
    const string filepath;

    std::unique_ptr<NekoWriter> writer;
    std::unique_ptr<NekoReader> reader;
};

#endif //NEKOFILE_H