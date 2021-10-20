# QSimpleXMLParser
一个简单的、小的、并不高效、可能也不易用的XML解析器。大量借鉴了[TinyXML-2](https://github.com/leethomason/tinyxml2)。  

## 特点与坑
* 仅支持ASCII和UTF-8。
* 递归地进行解析。
* 没有很好的组织内存，每个节点独自被new，比较松散。未来可以加入TinyXML-2那样的内存池。
* 元素的属性没有当作节点处理。
* 不处理Declaration，单纯读入其内容。
* 子节点以链表组织，不支持子节点的随机访问。
* 接口不是很合理。

## 使用示例
从文件中读取XML，并解析
```c++
    XMLDocument doc;
    doc.loadFile("test.xml");
```
访问DOM树
```c++
    XMLNode* node1 = doc.firstChild();
    for(XMLNode* p = node1; p != nullptr; p = p->nextSibling()){
        cout<<node1.getValue()<<endl;
    }

    node1.addLastChild(new XMLText("Test"));

    delete node1.firstChild();
    
    node1.removeFirstChild();
```
将DOM打印为XML文档
```c++
    XMLPrinter printer(std::cout);
    doc.accept(printer);
```

# QSimpleXMLParser
A simply, small, inefficient, and probably unusable XML parser. Borrowed many things from [TinyXML-2](https://github.com/leethomason/tinyxml2).  

## Feature and Flaws
* Only support ASCII and UTF-8.
* Parse xml recusively.
* Memory management is not well. Every node object is newed standalone. Maybe implement memory pool like TinyXML-2.
* Attributes of elements are not treaded treated as nodes.
* Declaration will not be process. Only store its content.
* Children of a node are originzed by a link list.
* The interfaces may be not desirable.

## Example Usages
Read XML from file and parse it.
```c++
    XMLDocument doc;
    doc.loadFile("test.xml");
```
Visit the DOM tree.
```c++
    XMLNode* node1 = doc.firstChild();
    for(XMLNode* p = node1; p != nullptr; p = p->nextSibling()){
        cout<<node1.getValue()<<endl;
    }

    node1.addLastChild(new XMLText("Test"));

    delete node1.firstChild();
    
    node1.removeFirstChild();
```
Print DOM as XML document.
```c++
    XMLPrinter printer(std::cout);
    doc.accept(printer);
```