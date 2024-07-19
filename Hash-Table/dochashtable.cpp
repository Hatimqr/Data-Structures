#include "dochashtable.h"
#include "MyList.h"
#include "Heap.h"

// constructor for hash table. repetitions is 1 by default because the first time you insert into the table its the first word.
HashNode::HashNode(long key, string word, int repetitions){
    this->key = key;
    this->repetitions = repetitions;
    this->word = word;
    this->next = NULL;
}

//initialize heap and buckets based on capicity which is determined by the number of unique words in the largest file. default hash function is 5
DocHASHTABLE::DocHASHTABLE(int capacity){
    this->capacity = capacity;
    this->MaxHeap = new Heap(capacity);
    this->buckets = new MyList<HashNode>[capacity];
    this->numTotal = 0;
    this->hashMode = 5;
}


DocHASHTABLE::~DocHASHTABLE(){
    // set everything in the heap to NULL and delete the array.
    delete MaxHeap;
    // delete each linked list in the buckets and delete the hash table. 
    delete [] buckets;
}

long DocHASHTABLE::hashCode(string key){
    //depending on the hashmode attribute, use the corresponding hash function
    switch (hashMode)
    {
    case 1:
        return hash1(key);
    case 2:
        return hash2(key);
    case 3:
        return hash3(key);
    case 4:
        return hash4(key);
    case 5:
        return hash5(key);
    case 6:
        return hash6(key);
    }
}

//change the hashmode attribute
void DocHASHTABLE::select_hashFun(int choice){
    this->hashMode = choice;
}

// import file and put words into the hash table
int DocHASHTABLE::import(string path){

    ifstream fin(path);
    if (fin.is_open()){
        string word;
        while (fin >> word){ // get strings seperated by whitespaces
            word = cleanWord(word); // clean the word
            if (word.length()>0){ // check if string is empty
                insert(word);
                ++numTotal; // increament total number of words
            }
        }
    }
    else{
        throw invalid_argument("Error. File could not be opened.");
    }
    fin.close();

}

// loop through hash table and check size of buckets
int DocHASHTABLE::count_collisions(){
    int collisions = 0;
    for (int i = 0; i < capacity; i++){
        int bucketSize = buckets[i].getSize();
        if (bucketSize > 1) // if there are more than one elements in the bucket, there is a collision
            collisions += (bucketSize-1); //-1 because the first element is not a collision
    }
    return collisions;
}
// size of Maxheap is the number of unique words
int DocHASHTABLE::count_unique_words(){
    return MaxHeap->getSize();
}

// return attribute
int DocHASHTABLE::count_words(){
    return numTotal;
}

void DocHASHTABLE::insert(string word){
    int key = compression(hashCode(word)); // get hashcode
    if (key < 0) key = key * -1; // make sure key is positive again

    
    MyList<HashNode>* bucket = &buckets[key];
    for (auto it : *bucket){ // check if word is already in hashtable
        HashNode* node = it.ptr;
        if (node->word == word){ // if the word is found in the hashtable, increment its value
            node->repetitions++; // increment repetitions in hashtable
            MaxHeap->siftup(node->heapIndex); // adjust the heap
            return;
        }
    }
    // if not in hashtable, add it
    HashNode* node = new HashNode(key, word);
    node->heapIndex = MaxHeap->getSize()+1;
    buckets[key].addFront(node);
    MaxHeap->insert(node);
}   

// insert in reverse. get hashcode and index. get to the bucket. iterate bucket until word is found, if not return 0
int DocHASHTABLE:: find_freq(string word){
    int key = compression(hashCode(word));
    if (key < 0) key *= -1;

    MyList<HashNode>* bucket = &buckets[key];
    for (auto it : *bucket){ // check if word is already in hashtable
        HashNode* node = it.ptr;
        if (node->word == word){ // if the word is found in the hashtable, increment its value
            return node->repetitions;
        }
    }
    return 0;
}
// top of the heap
string DocHASHTABLE:: find_max(){
    return MaxHeap->getMax().word;
}

//sumation hash function
long DocHASHTABLE:: hash1(string word){
    long hash = 0;
    for (char c : word){
        hash+=(int)c;
    }
    return hash;
}

// polinomial shifthash function
long DocHASHTABLE:: hash2(string word){
    unsigned long hash = 0;
    int m = word.length();
    int a = 3;
    for (char c : word){
        hash+=((int)c*pow(a,m));
        m--;
    }
    return hash;
}

// cycle shift hash function
long DocHASHTABLE:: hash3(string word){
    unsigned long hash = 0;

    for (char c : word){
        c = c << 5 | c >> 11;
        hash+=(unsigned int)c;
    }
    return hash;
}

// djb2 hash function
long DocHASHTABLE:: hash4(string word){ 
    unsigned long hash = 5381;
    for (char c : word) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// FNV hash function
long DocHASHTABLE:: hash5(string word){ 
    const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;

	for (char c : word) {
        hash *= fnv_prime;
        hash ^= c;
    }
	return hash;
}

//jenkins one-at-a-time hash function
long DocHASHTABLE:: hash6(string word){ 
    unsigned long hash = 0;
    for (char c : word) {
        hash = (hash << 4) + c;
        unsigned long g = hash & 0xF0000000L;
        if (g != 0) {
            hash ^= g >> 24;
        }
        hash &= ~g;
    }
    return hash;
}

// compress to get an index in range of the hash table
int DocHASHTABLE:: compression(long hash){
    if (hash < 0) hash *= -1; // make sure key is positive
    long constant = 3;
    long offset = 5;
    return (constant*hash + offset) % capacity;
}

string DocHASHTABLE:: cleanWord(string word){
    string chars_to_remove = ".,\!?;"; // characters to remove
    bool popped; // to continue checking or not

    do
    {
        popped = false;
        // loop through every char to remove. if the last character of the word is equal to any of them, pop it and repeat. the function
        for (char c : chars_to_remove){
            if (word.back() == c){
                word.pop_back();
                popped = true; // if nothing is popped the while loop will terminate
            }
        }
    }while (popped);

    transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lowercase
    return word;
}


