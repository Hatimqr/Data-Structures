#include "vfs_tree.h"

Position::Position(Inode* inode){
    this->inode = inode;
}

Position::Position(){
    this->inode = NULL;
}

Position::~Position(){
}

//getters
Position Position::parent() const{
    if (this->isRoot())throw invalid_argument("Current Node is Root");
    
    return Position(this->inode->parent);
}

bool Position:: isRoot() const{
    return this->inode->getParent() == NULL;
}

bool Position::isExternal() const{
    return this->inode->children.empty();
}

string Position:: getName()const{
    return this->inode->getFName();
}

int Position:: getFileSize()const{
    return this->inode->getFSize();
}

string Position:: getDate()const{
    return this->inode->getDate();
}

bool Position:: isFile(){
    return inode->getIsFile();
}


//add node to the vector of a position object
void Position::addNode(Inode* newFile){
    if (!checkUniqueName(newFile->getFName(), newFile->getIsFile())) throw invalid_argument("File name already exists");
    
    newFile->parent = this->inode;
    inode->children.push_back(newFile);
}


//check a node
void Position:: displayNode(){
    if(this->inode->fname == "root") throw invalid_argument("Current Node is ROOT");
    Inode *node = this->inode;
    // Eachlineshows:filetype(dir/file),filename,size,date
    string filetype;
    if (node->isFile)
        filetype = "file";
    else 
        filetype = "dir";
    
    cout <<  node->fname << ", " << node->fsize << ", " << filetype << ", " << node->date << endl;

}

// make a vector of position object with the inode vector
MyVector<Position>* Position:: childrenPositions()const{
    MyVector<Position> *childPos = new MyVector<Position>;
    MyVector <Inode*> *ChildNode = &inode->children;
    
    for (int i = 0; i<ChildNode->size(); i++){
        Position *pos = new Position(ChildNode->at(i));
        childPos->push_back(*pos);
    }
    return childPos;
}

// send a node to the recycle bin and set all subnodes to not in tree
Position* Position:: removeChild(string name){
    MyVector<Inode*> *children = &inode->children;
    for (int i = 0; i<children->size(); i++){
        if (children->at(i)->getFName() == name){
            Position* pos = new Position(children->at(i));
            children->erase(i);
            Inode *node = pos->inode;

            node->inTree(false);

            return pos;
        }
    }
    throw invalid_argument("File/ Folder not found");
}

// check if name is unique in the vector of a position object/ directory
bool Position:: checkUniqueName(string name, bool isfile){
    MyVector<Position>* children = this->childrenPositions();
    for (int i = 0; i<children->size(); i++){
        if (children->at(i).getName() == name){
            if (children->at(i).isFile() == isfile)
                return false;
        }
    }
    return true;
}







//contructor reads files and initializes root, current and previous node
VFS_Tree:: VFS_Tree(){
    Inode* root = new Inode("root", 0, false, getDate());
    rootNode = new Position(root);
    readfile("vfs.dat");

    currentNode = rootNode;
    previousNode = currentNode;
}

// write to file and delete entire tree
VFS_Tree:: ~VFS_Tree(){
    writefile("vfsout.dat");
    delete rootNode->inode;
}


bool VFS_Tree:: empty() const{
    return n==1;
}

Position* VFS_Tree:: root() const{
    return rootNode;
}

Position* VFS_Tree:: current() const{
    return currentNode;
}


//
Position* VFS_Tree:: find(string name) const{
    MyStack<Position> NodeStack = MyStack<Position>(1000);
    NodeStack.push(*rootNode);
    Position* current;

    if (rootNode->childrenPositions()->empty()) return NULL;
    // everything into stack and if name is found, display
    while (!NodeStack.empty()){
        *current = NodeStack.top();
        NodeStack.pop();
        if (current->getName() == name){
            cout << pwd(current) << endl;
        }
        MyVector<Position>* children = current->childrenPositions();
        for (int i = 0; i<children->size(); i++){
            NodeStack.push(children->at(i));
        }
    }
    return NULL;
}

//add file to current directory
void VFS_Tree:: touch(string filename, int size){
    // check if current is a folder and file can be created
    if(currentNode->isFile()) throw invalid_argument("Current is not a folder. File cannot be created");
    Inode* newfile = new Inode(filename, size, true, getDate());
    // add the file to directory
    if (currentNode->checkUniqueName(filename, true)){
        currentNode->addNode(newfile); 
        // newfile->parent = currentNode->inode;
        n++;
    }else{
        throw invalid_argument("File with same name already exists");
    }

    while (newfile->parent != NULL){
        newfile = newfile->parent;
        newfile->fsize += size;
    }
} 


void VFS_Tree:: mkdir(string foldername){
    // check if current is a folder and folder can be created
    if(currentNode->isFile()) throw invalid_argument("Current is not a folder. Folder cannot be created");
    // create folder
    Inode* newfolder = new Inode(foldername, 10, false, getDate());
    // add the folder to directory
    if (currentNode->checkUniqueName(foldername, false)){
        currentNode->addNode(newfolder); 
        // newfolder->parent = currentNode->inode;
        n++;
    }else{
        throw invalid_argument("Folder with same name already exists");
    }
    while (newfolder->parent != NULL){
        newfolder = newfolder->parent;
        newfolder->fsize += 10;
        
    }
    
} 
// display all nodes in current directory
void VFS_Tree:: ls(){ 
    if(currentNode->isFile()) throw invalid_argument("Current is not a folder. Command is invalid");
    MyVector<Position>* children = currentNode->childrenPositions();
    for (int i = 0; i < children->size(); i++)
        children->at(i).displayNode();
} 

//temporarily display a sorted directory
void VFS_Tree:: lsSort(){
    if(currentNode->isFile()) throw invalid_argument("Current is not a folder. Command is invalid");

    //bubble sort in descending order of file size
    MyVector<Position>* children = currentNode->childrenPositions();

    for (int i = 0; i < children->size()-1;i++){
        bool shifted = false;
        for (int j = 0; j < children->size()-i-1; j++){
            if (children->at(j).getFileSize() < children->at(j+1).getFileSize()){
                Position second = children->at(j+1);
                children->erase(j+1);
                children->insert(j, second);
                shifted = true;
            }
        }
        if (shifted == false) break;
    }
    // print
    for (int i = 0; i < children->size(); i++)
        children->at(i).displayNode();

} 



//traverse the tree
void VFS_Tree:: cd(string arg){
    if (arg == ".."){
        if (currentNode->isRoot()) throw invalid_argument("Current directory is the root directory. Cannot return further uptree");
        previousNode = currentNode;
        *currentNode = currentNode->parent();


    }else if(arg == ""){
        if (currentNode->isRoot()) return;
        previousNode = currentNode;
        currentNode = rootNode;


    }else if (arg == "-"){
        if (previousNode == NULL) throw invalid_argument("No previous directory");
        Position* temp = currentNode;
        currentNode = previousNode;
        previousNode = temp;

    }else if (arg.find("/") != string::npos){
        Position temp = *currentNode;
        string path = arg;
        stringstream ss(path);
        string token;
        getline(ss, token, '/'); // skip the first slash
        if (token != "") throw invalid_argument("Path must start with /");

        while(getline(ss, token, '/')){
            bool found = false;
            MyVector<Position>* children = currentNode->childrenPositions();
            for (int i = 0; i<children->size(); i++){
                if (children->at(i).getName() == token){
                    if (children->at(i).isFile()) throw invalid_argument("The specified name belongs to a file. directory cannot be changed");
                    currentNode = &children->at(i);
                    found = true;
                    break;
                }
            }
            if (found) throw invalid_argument("The specified path does not exist");
        }
        *previousNode = temp;
    }        
    else{
        MyVector<Position>* children = currentNode->childrenPositions();
        for (int i = 0; i < children->size(); i++){
            if (children->at(i).getName()== arg){
                if (children->at(i).isFile()) throw invalid_argument("The specified name belongs to a file. directory cannot be changed");
                previousNode = currentNode;
                currentNode = &children->at(i);
            }
        }
    } 
}
 
//get the path of something in the current subtree
void VFS_Tree:: realpath(string name) const{
    MyVector <Position> *children = currentNode->childrenPositions();
    for (int i = 0; i<children->size(); i++){
        if (children->at(i).getName() == name){
            if (!children->at(i).isFile()) continue;
            cout << pwd(&children->at(i)) << endl;
            return;
        }
    }
    throw invalid_argument("File not found");
} 

// return path of current node
string VFS_Tree:: pwd(Position* current) const{
    Position temp = *current;
    MyStack <Position> history = MyStack<Position>(20);
    string path;
    
    if (temp.isRoot()) return "/";
    while (!temp.isRoot()){
        history.push(temp);
        temp = temp.parent();
    }
    while(!history.empty()){
        path += "/" + history.top().getName();
        history.pop();
    }
    return path;
} 

//find a file and send it to a folder in the current directory
void VFS_Tree:: mv(string filename, string foldername){
    //if there is a '/' in the filename, throw an error

    Position curr = *currentNode;
    Position *fileNode = findHelper(filename, curr);

    Position curr2 = *currentNode;
    Position *folderNode = findHelper(foldername, curr2);



    
    if (fileNode == NULL || folderNode == NULL || folderNode->isFile() || !fileNode->isFile())
        throw runtime_error("Invalid file or folder");
    else{
        string name = fileNode->getName();
        Position parent = fileNode->parent();
        
        parent.removeChild(name);
        int size = fileNode->getFileSize();
        Inode* newNode = fileNode->inode;
        while (newNode->parent != NULL){
            newNode = newNode->parent;
            newNode->fsize -= size;
        }


        folderNode->addNode(fileNode->inode);
        size = folderNode->getFileSize();
        Inode* newfile = folderNode->inode;
        while (newfile->parent != NULL){
            newfile = newfile->parent;
            newfile->fsize += size;
        }

    }
} 

// remove a node and send it to the bin
void VFS_Tree:: rm(string name){
    // arbitrary path
    // if a '/' is found, then remove the last '/' and everything after it
    // then call cd on the new path and do regular mv on the last node in the path

    if (name.find("/") != string::npos){
        string path = name;
        int pos = path.find_last_of("/");
        path = path.substr(0, pos);
        cd(path);
        name = name.substr(pos+1);
    }
    

    if (bin.isFull()) throw invalid_argument("Bin is full. Please empty the bin first before deleting");
    Position* nodeToDelete = currentNode->removeChild(name);
    bin.enqueue(nodeToDelete);
    nodeToDelete->inode->inTree(false);
    n--;

    int size = nodeToDelete->getFileSize();
    Inode* newNode = nodeToDelete->inode;
    while (newNode->parent != NULL){
        newNode = newNode->parent;
        newNode->fsize -= size;
    }
    
} 

// delete contents of the bin. calls the destructor of the inode class
void VFS_Tree:: emptyBin(){
    while (!bin.isEmpty()) {
        Position *posToDelete = bin.dequeue();
        delete posToDelete->inode;
    }
} 

// show the first thing in the bin along with its path if it exists using pwd
void VFS_Tree:: showBin(){
    if (bin.isEmpty()) throw invalid_argument("Bin is empty");
    Position* front = bin[bin.getFront()];

    string type;
    if (front->isFile()) 
        type = "File";
    else
        type = "Dir";

    cout << pwd(front) << ", " << front->getFileSize() << ", " << type << ", " << front->getDate() << endl;
} 

// get a node back from the bin
void VFS_Tree:: recover(){
    Position* retrieve = bin.dequeue();
    Position parent = retrieve->parent();
    


    if (!parent.checkUniqueName(retrieve->getName(), retrieve->isFile())) throw invalid_argument("File/ Folder with same name already exists");

    if (parent.inode->isInTree){
        parent.addNode(retrieve->inode);
        retrieve->inode->inTree(true);
        n++;

        Inode* newNode = retrieve->inode;
        int size = newNode->getFSize();
        while (newNode->parent != NULL){
            newNode = newNode->parent;
            newNode->fsize += size;
        }
    }
    else{
        throw invalid_argument("Parent not found in tree");
    }


} 
// recursively find the first instance of a node in the tree given a name
Position* VFS_Tree:: findHelper(string name, Position pos)const{
    if (pos.isExternal()) 
            return NULL;

    if (name == "")
        return rootNode;
         
    MyVector<Position> *children = pos.childrenPositions();
    for (int i = 0; i < children->size(); i++) {
        if (children->at(i).getName() == name) {
            return &children->at(i);
        }
        Position *foundNode = findHelper(name, children->at(i));
        if (foundNode != NULL) {
            return foundNode;
        }
    }
    return NULL;
}


// get the current date
string VFS_Tree:: getDate(){
    time_t now = time(nullptr);
    tm* tm_now = localtime(&now);
    string date = to_string(tm_now->tm_mday) + "-" + to_string(tm_now->tm_mon + 1) + "-" + to_string(tm_now->tm_year +1900);
    return date;
}

// read the file and create the tree to intialize
void VFS_Tree:: readfile(string filename){

    ifstream inFile(filename);
    string line;

        if (inFile.is_open()) {

            while (getline(inFile, line)) {
                bool rootDone = false;

                stringstream ss(line);
                string path, sizeStr, date;
                getline(ss, path, ',');
                getline(ss, sizeStr, ',');
                getline(ss, date, ',');

                int size = stoi(sizeStr);
                int lastSlash = path.find_last_of('/');
                string name = path.substr(lastSlash + 1);
                path = path.substr(0, lastSlash);

                if (name == "" && !rootDone){
                    delete rootNode;
                    Inode *root = new Inode(path, 0, false, date);
                    rootNode = new Position(root);
                    rootNode->inode->parent = NULL;
                    currentNode = rootNode;
                    previousNode = rootNode;
                    rootDone = true;
                    continue;
                }
                
                cd(path);

                

                if (name.find('.') != string::npos){
                    addNode(name, size, true, date);
                }else{
                    addNode(name, size, false, date);
                }
                currentNode = rootNode;
            }
            inFile.close();
        }else{
            throw runtime_error("Unable to open file for reading");
        }
        inFile.close();
}

// write a file to save the tree to a .dat file
void VFS_Tree:: writefile(string filename){
    ofstream outFile(filename);
    outFile << pwd(rootNode) << ","<<rootNode->getFileSize() << "," <<rootNode->getDate() << endl;
    if (outFile.is_open()) {
        Position* curr = rootNode;
        MyVector<Position> *children = curr->childrenPositions();
        for (int i = 0; i < children->size(); i++) {
            if (children->at(i).isExternal()){
                outFile << pwd(&children->at(i))<< ","<<children->at(i).getFileSize() << "," <<children->at(i).getDate() << endl;
                continue;
            }
            else{
                outFile << pwd(&children->at(i)) << ","<<children->at(i).getFileSize() << "," <<children->at(i).getDate() << endl;
                writeHelper(&children->at(i), outFile);
            }
        }
        outFile.close();
    }
}

// helper function for writefile. recursively traverses the tree and writes a file
void VFS_Tree:: writeHelper(Position *pos, ofstream& outFile){
    MyVector<Position> *children = pos->childrenPositions();
    for (int i = 0; i < children->size(); i++){
        if (children->at(i).isExternal()){
            outFile << pwd(&children->at(i)) << ","<<children->at(i).getFileSize() << "," <<children->at(i).getDate() << endl;
            continue;
        }
        else{
            outFile << pwd(&children->at(i)) << ","<<children->at(i).getFileSize() << "," <<children->at(i).getDate() << endl;
            writeHelper(&children->at(i), outFile);
        }  
    }
}

// return the size of a specified file or folder
int VFS_Tree:: size(string path){
    *previousNode = *currentNode;
    *currentNode = *rootNode;
    cd(path);
    return currentNode->getFileSize();
    cd("-");
}

// helper function to add a node to the tree in the writefile function
void VFS_Tree:: addNode(string name, int size, bool isFile, string date){
    if(currentNode->isFile()) throw invalid_argument("Cannot add node to a file");
    Inode* newNode = new Inode(name, size, isFile, date);

    if (currentNode->checkUniqueName(name, isFile)){
        currentNode->addNode(newNode); 
        newNode->parent = currentNode->inode;
        n++;
    }else{
        throw invalid_argument("Folder with same name already exists");
    }


    while (newNode->parent != NULL){
        newNode = newNode->parent;
        newNode->fsize += size;
    }
}

