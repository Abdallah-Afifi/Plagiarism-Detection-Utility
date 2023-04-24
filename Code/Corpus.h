#ifndef _CORPUS_H
#define _CORPUS_H

class Corpus {
public: 

void addDocument(Document doc);
Document getDocument(int id);

private: 
    list<Document> documents;
};

#endif //_CORPUS_H
