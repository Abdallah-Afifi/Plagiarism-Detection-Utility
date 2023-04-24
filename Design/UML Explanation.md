Document class has a composition relationship with Corpus class, which means that a Document object cannot exist without being part of a Corpus object. 
The multiplicity is one-to-many (1..*), since a Corpus can have multiple Documents but each Document can only belong to one Corpus.

Corpus class has an aggregation relationship with Document class, which means that a Corpus object is composed of multiple Document objects, but those Document objects can exist independently of the Corpus object. 
The multiplicity is many-to-one (*..1), since multiple Documents can belong to one Corpus but each Document can only belong to one Corpus.

PlagiarismDetector class has an association relationship with Corpus and Document classes. 
The multiplicity for Corpus is one-to-one (1..1), since a PlagiarismDetector can only use one Corpus object. The multiplicity for Document is one-to-one (1..1), since a PlagiarismDetector can only use one test document at a time.

BruteForceDetector and RabinKarpDetector classes both have a dependency relationship with Document and Corpus classes, since they 
need to access and analyze the text content of Documents and Corpus objects to perform plagiarism detection.

PerformanceComparator class has an association relationship with Document and Corpus classes, since it needs to compare the performance of plagiarism detection algorithms on a given test document and corpus. 
The multiplicity for Document is one-to-one (1..1), since the comparison is made for one test document at a time. The multiplicity for Corpus is one-to-one (1..1), since the comparison is made for one Corpus object at a time.
