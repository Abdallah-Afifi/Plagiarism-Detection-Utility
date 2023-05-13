#include "Document.h"
#include <string>

Document::Document(const std::string& title, const std::string& content)
    : title(title), content(content) {}

std::string Document::getTitle() const {
    return title;
}

std::string Document::getContent() const {
    return content;
}
