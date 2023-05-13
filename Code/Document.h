#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

class Document {
private:
    std::string title;
    std::string content;

public:
    Document(const std::string& title, const std::string& content);

    std::string getTitle() const;
    std::string getContent() const;
};

#endif // DOCUMENT_H
