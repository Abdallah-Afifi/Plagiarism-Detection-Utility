#ifndef _DOCUMENT_H
#define _DOCUMENT_H

class Document {
public: 
    string getText();
    int getId();
private:
    int id;
    string text;
};

#endif //_DOCUMENT_H
