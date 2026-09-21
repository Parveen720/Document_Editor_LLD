#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class DocumnetElement{
    public:
    virtual string render()=0;
};

class TextElement:public DocumnetElement{
    private:
    string text;

    public:
    TextElement(string text){
        this->text=text;
    }

    string render() override{
        return text;
    }
};

class ImageElement:public DocumnetElement{
    private:
    string imagepath;

    public:
    ImageElement(string imagepath){
        this->imagepath=imagepath;

    }
    string render() override{
        return "[Image:" +imagepath+"]";
    }
};

class NewLineElement: public DocumnetElement{
    public:
    string render() override{
        return "\n";
    }
};

class Document{
    private:
    vector<DocumnetElement*> documnetElements;

    public:
    void addElement(DocumnetElement* element){
        documnetElements.push_back(element);
    }

    string render(){
        string result;
        for(auto element:documnetElements){
            result+=element->render();
        }
        return result;
    }
};

class Persistence{
    public:
    virtual void save(string data)=0;
};

class FileStorage:public Persistence{
    public:
    void save(string data) override{
        ofstream outFile("document.txt");
        if(outFile){
            outFile<<data;
            outFile.close();
            cout<<"Document saved to document.txt"<<endl;
        }
        else{
            cout<<"Error:Unable to open file for writing"<<endl;
        }
    }
};

class DBStorage:public Persistence{
    public:
    void save(string data) override{

    }
};

class DocumentEditor{
    private:
    Document* document;
    Persistence* storage;
    string renderedDocument;

    public:
    DocumentEditor(Document* document,Persistence* storage){
        this->document=document;
        this->storage=storage;
    }


    void addText(string text){
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath){
        document->addElement(new ImageElement(imagePath));
    }

    void addNewLine(){
        document->addElement(new NewLineElement());
    }

    string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument=document->render();
        }
        return renderedDocument;
    }

    void saveDocument(){
        storage->save(renderDocument());
    }
};
int main(){
   Document* document=new Document();
   Persistence* persistence=new FileStorage();

   DocumentEditor* editor=new DocumentEditor(document,persistence);

   editor->addText("Hello, World!");
   editor->addNewLine();
   editor->addText("this is a real world document editor");
   editor->addNewLine();
   editor->addText("indented texxt after a new line");
   editor->addNewLine();
   editor->addImage("picture.jpg");
   cout<<editor->renderDocument()<<endl;
   editor->saveDocument();

 return 0;
}