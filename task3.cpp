#include <iostream>
#include <string>
using namespace std;

// ======== ПРОТОТИПИ ДРУЖНІХ ФУНКЦІЙ ========
class File;
class ReadableFile;
class WritableFile;
class ReadWriteFile;

istream& operator>>(istream& in, File& f);
ostream& operator<<(ostream& out, const File& f);
istream& operator>>(istream& in, ReadableFile& rf);
ostream& operator<<(ostream& out, const ReadableFile& rf);
istream& operator>>(istream& in, WritableFile& wf);
ostream& operator<<(ostream& out, const WritableFile& wf);
istream& operator>>(istream& in, ReadWriteFile& rwf);
ostream& operator<<(ostream& out, const ReadWriteFile& rwf);

// ======== КЛАСИ ========
class File {
protected:
    string fileName;
    long fileSize;
public:
    File(string name = "", long size = 0) : fileName(name), fileSize(size) {}

    virtual void display() const {
        cout << "File name: " << fileName << endl;
        cout << "File size: " << fileSize << " bytes" << endl;
    }

    virtual ~File() {
        cout << "Destructor of File called for " << fileName << endl;
    }

    friend istream& operator>>(istream& in, File& f);
    friend ostream& operator<<(ostream& out, const File& f);
};

class ReadableFile : virtual public File {
protected:
    bool canRead;
public:
    ReadableFile(string name = "", long size = 0, bool read = true)
        : File(name, size), canRead(read) {}

    void display() const override {
        File::display();
        cout << "Can read: " << (canRead ? "Yes" : "No") << endl;
    }

    virtual ~ReadableFile() {
        cout << "Destructor of ReadableFile called for " << fileName << endl;
    }

    friend istream& operator>>(istream& in, ReadableFile& rf);
    friend ostream& operator<<(ostream& out, const ReadableFile& rf);
};

class WritableFile : virtual public File {
protected:
    bool canWrite;
public:
    WritableFile(string name = "", long size = 0, bool write = true)
        : File(name, size), canWrite(write) {}

    void display() const override {
        File::display();
        cout << "Can write: " << (canWrite ? "Yes" : "No") << endl;
    }

    virtual ~WritableFile() {
        cout << "Destructor of WritableFile called for " << fileName << endl;
    }

    friend istream& operator>>(istream& in, WritableFile& wf);
    friend ostream& operator<<(ostream& out, const WritableFile& wf);
};

class ReadWriteFile : public ReadableFile, public WritableFile {
public:
    ReadWriteFile(string name = "", long size = 0, bool read = true, bool write = true)
        : File(name, size), ReadableFile(name, size, read), WritableFile(name, size, write) {}

    void display() const override {
        File::display();
        cout << "Can read: " << (canRead ? "Yes" : "No") << endl;
        cout << "Can write: " << (canWrite ? "Yes" : "No") << endl;
    }

    virtual ~ReadWriteFile() {
        cout << "Destructor of ReadWriteFile called for " << fileName << endl;
    }

    friend istream& operator>>(istream& in, ReadWriteFile& rwf);
    friend ostream& operator<<(ostream& out, const ReadWriteFile& rwf);
};

// ======== РЕАЛІЗАЦІЯ ДРУЖНІХ ФУНКЦІЙ ========
istream& operator>>(istream& in, File& f) {
    cout << "Enter file name: ";
    in >> f.fileName;
    cout << "Enter file size: ";
    in >> f.fileSize;
    return in;
}

ostream& operator<<(ostream& out, const File& f) {
    out << "File name: " << f.fileName << ", size: " << f.fileSize << " bytes";
    return out;
}

istream& operator>>(istream& in, ReadableFile& rf) {
    in >> static_cast<File&>(rf);
    cout << "Can read (1-yes, 0-no): ";
    in >> rf.canRead;
    return in;
}

ostream& operator<<(ostream& out, const ReadableFile& rf) {
    out << static_cast<const File&>(rf);
    out << ", can read: " << (rf.canRead ? "Yes" : "No");
    return out;
}

istream& operator>>(istream& in, WritableFile& wf) {
    in >> static_cast<File&>(wf);
    cout << "Can write (1-yes, 0-no): ";
    in >> wf.canWrite;
    return in;
}
ostream& operator<<(ostream& out, const WritableFile& wf) {
    out << static_cast<const File&>(wf);
    out << ", can write: " << (wf.canWrite ? "Yes" : "No");
    return out;
}

istream& operator>>(istream& in, ReadWriteFile& rwf) {
    in >> static_cast<File&>(rwf);
    cout << "Can read (1-yes, 0-no): ";
    in >> rwf.canRead;
    cout << "Can write (1-yes, 0-no): ";
    in >> rwf.canWrite;
    return in;
}

ostream& operator<<(ostream& out, const ReadWriteFile& rwf) {
    out << static_cast<const File&>(rwf);
    out << ", can read: " << (rwf.canRead ? "Yes" : "No");
    out << ", can write: " << (rwf.canWrite ? "Yes" : "No");
    return out;
}

// ======== MAIN ========
int main() {
    ReadWriteFile rwf;
    cin >> rwf;
    cout << endl << "Information about ReadWriteFile:" << endl;
    rwf.display();

    cout << endl << "Output operator demonstration:" << endl;
    cout << rwf << endl;

    return 0;
}
