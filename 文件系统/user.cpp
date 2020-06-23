#include "user.h"
#include "ui_user.h"
#include"errorpage.h"
#include "ui_errorpage.h"

User::User(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);

    //初始化磁盘块
    for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            diskSpace[i][j]=0;
        }
    }

    //查看文件目录
    catalogue=ui->CATALOGUE;
    catalogue->setFixedSize(331,501);
    catalogue->setHeaderHidden(true);
    catalogue->expandAll();
    catalogue->setColumnCount(2);
    connect(catalogue,&QTreeWidget::clicked,this,[=]{file_iterator=searchFile(catalogue->currentItem());});
    root=new QTreeWidgetItem;
    root->setText(0,"目录");
    catalogue->addTopLevelItem(root);

    formatButton=new QPushButton(this);
    formatButton->setText("格式化磁盘");
    formatButton->setGeometry(230,20,120,40);
    connect(formatButton,&QPushButton::clicked,this,[=]{clearDisk();});

    //文件显示模块
    File_name=ui->fname;
    inputTXT=ui->input;
    File_name->setText("未打开文件");
    inputTXT=ui->input;
    saveButton=new QPushButton(this);
    saveButton->setText("保存");
    saveButton->setGeometry(680,25,100,50);
    saveButton->setEnabled(false);
    connect(saveButton,&QPushButton::clicked,this,[=]{saveFile();});
    closeButton=new QPushButton(this);
    closeButton->setText("关闭文件");
    closeButton->setGeometry(850,25,100,50);
    closeButton->setEnabled(false);
    connect(closeButton,&QPushButton::clicked,this,[=]{closeFile();});

    //创建、打开、删除文件
    ui->label_2->hide();
    ui->label_3->hide();
    ui->inputName->hide();
    createFileButton=new QPushButton(this);
    createFileButton->setText("创建文件");
    createFileButton->setGeometry(50,645,100,50);
    connect(createFileButton,&QPushButton::clicked,this,[=]{createFile();});
    submitFileNameButton=new QPushButton(this);
    submitFileNameButton->setText("√");
    submitFileNameButton->setGeometry(370,610,40,25);
    submitFileNameButton->hide();
    connect(submitFileNameButton,&QPushButton::clicked,this,[=]{submitFileName();});
    openFileButton=new QPushButton(this);
    openFileButton->setText("打开文件");
    openFileButton->setGeometry(180,645,100,50);
    connect(openFileButton,&QPushButton::clicked,this,[=]{openFile();});
    deleteFileButton=new QPushButton(this);
    deleteFileButton->setText("删除文件");
    deleteFileButton->setGeometry(310,645,100,50);
    connect(deleteFileButton,&QPushButton::clicked,this,[=]{deleteFile();});
    createFolderButton=new QPushButton(this);
    createFolderButton->setText("创建文件夹");
    createFolderButton->setGeometry(440,645,100,50);
    connect(createFolderButton,&QPushButton::clicked,this,[=]{createFolder();});
    submitFolderNameButton=new QPushButton(this);
    submitFolderNameButton->setText("√");
    submitFolderNameButton->setGeometry(370,610,40,25);
    submitFolderNameButton->hide();
    connect(submitFolderNameButton,&QPushButton::clicked,this,[=]{submitFolderName();});
    deleteFolderButton=new QPushButton(this);
    deleteFolderButton->setText("删除文件夹");
    deleteFolderButton->setGeometry(570,645,100,50);
    connect(deleteFolderButton,&QPushButton::clicked,this,[=]{deleteFolder();});

    read();//读取文件信息

    connect(ui->exitButton,&QPushButton::clicked,this,[=]{save();});
}

User::~User()
{
    delete ui;
}

int User::searchFileByIterator(QTreeWidgetItemIterator it){
    QString name=(*it)->text(0);
    for(int i=0;i<cata.size();i++){
        if(name==cata[i].file_name&&(*it)->parent()->text(0)==cata[i].parent){
            return i;
        }
    }
    return -1;
}

void User::save(){
    //打开或创建xml文件
    QFile file("proInfo.xml");
    QDomDocument doc;
    if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return;
    //写入xml头部
    QDomProcessingInstruction instruction; //添加处理命令
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    //添加根节点
    QDomElement XMLroot=doc.createElement("目录");
    doc.appendChild(XMLroot);

    QTreeWidgetItemIterator it(catalogue);
    while(*it){
        if((*it)->text(1)=="文件"){
            QDomElement file=doc.createElement("file");
            file.setAttribute("name",(*it)->text(0)); //方式一：创建属性  其中键值对的值可以是各种类型
            file.setAttribute("content",cata[searchFileByIterator(it)].content);
            file.setAttribute("parent",cata[searchFileByIterator(it)].parent);
            file.setAttribute("diskRow",cata[searchFileByIterator(it)].disk_id.first);
            file.setAttribute("diskCol",cata[searchFileByIterator(it)].disk_id.second);
            XMLroot.appendChild(file);
        }
        else if((*it)->text(1)=="文件夹"){
            QDomElement folder=doc.createElement("folder");
            folder.setAttribute("name",(*it)->text(0));
            folder.setAttribute("parent",(*it)->parent()->text(0));
            XMLroot.appendChild(folder);
        }
        ++it;
    }

    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
    this->close();
}

void User::findCatalogue(QString parentName){
    QTreeWidgetItemIterator it(catalogue);
    while(*it){
        if((*it)->text(0)==parentName){
            catalogue->setCurrentItem((*it));
            break;
        }
        ++it;
    }
}

void User::read(){
    //打开或创建文件
    QFile file("proInfo.xml");
    if(!file.open(QFile::ReadOnly)){
        return;
    }

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement XMLroot=doc.documentElement(); //返回根节点
    root->setText(0,XMLroot.nodeName());
    QDomNode node=XMLroot.firstChild(); //获得第一个子节点
    while(!node.isNull())  //如果节点不空
    {
        if(node.isElement()) //如果节点是元素
        {
            if(node.nodeName()=="file"){
                QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
                txtFile file;
                file.file_name=e.attribute("name");
                file.content=e.attribute("content");
                file.parent=e.attribute("parent");
                QString diskRow=e.attribute("diskRow");
                file.disk_id.first=diskRow.toInt();
                QString diskCol=e.attribute("diskCol");
                file.disk_id.second=diskCol.toInt();
                cata.push_back(file);
                diskSpace[file.disk_id.first][file.disk_id.second]=1;
                findCatalogue(file.parent);
                QTreeWidgetItem* fileNode=new QTreeWidgetItem;
                fileNode->setText(0,file.file_name);
                fileNode->setText(1,"文件");
                catalogue->currentItem()->addChild(fileNode);
           }
            else if(node.nodeName()=="folder"){
                QDomElement e=node.toElement();
                QString name=e.attribute("name");
                QString parent=e.attribute("parent");
                findCatalogue(parent);
                QTreeWidgetItem* folderNode=new QTreeWidgetItem;
                folderNode->setText(0,name);
                folderNode->setText(1,"文件夹");
                catalogue->currentItem()->addChild(folderNode);
            }
        }
        node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }

}

bool User::isDiskFull(){
    for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            if(diskSpace[i][j]==0){
                return false;
            }
        }
    }
    return true;
}

void User::submitFileName(){
    txtFile file;
    file.file_name=ui->inputName->text();
    if(ui->inputName->text().isEmpty()){
        file.file_name="未命名";
    }
    QTreeWidgetItem* fileNode=new QTreeWidgetItem;
    QTreeWidgetItem* parent=catalogue->currentItem();
    file.parent=parent->text(0);
    fileNode->setText(0,file.file_name);
    fileNode->setText(1,"文件");
    if(parent->text(1)=="文件"){//禁止在文件目录下创建文件
        submitFileNameButton->hide();
        ui->label_2->hide();
        ui->inputName->clear();
        ui->inputName->hide();
        createFileButton->setEnabled(true);
        createFolderButton->setEnabled(true);
        errorPage.errorInfo->setText("禁止在文件目录下创建");
        errorPage.show();
        return;
    }
    if(isDiskFull()==true){//磁盘已满则无法创建目录
        submitFileNameButton->hide();
        ui->label_2->hide();
        ui->inputName->clear();
        ui->inputName->hide();
        createFileButton->setEnabled(true);
        createFolderButton->setEnabled(true);
        errorPage.errorInfo->setText("磁盘已满");
        errorPage.show();
         return;
    }
    int itemChildrenCounts =parent->childCount();
        while(itemChildrenCounts--)
        {
            QTreeWidgetItem * child = parent->child(itemChildrenCounts); //index从大到小区做删除处理
            if(file.file_name==child->text(0)&&child->text(1)=="文件"){
                submitFileNameButton->hide();
                ui->label_2->hide();
                ui->inputName->clear();
                ui->inputName->hide();
                createFileButton->setEnabled(true);
                createFolderButton->setEnabled(true);
                errorPage.errorInfo->setText("该文件已存在");
                errorPage.show();
                return;
            }
        }
    ui->label_2->hide();
    ui->inputName->clear();
    ui->inputName->hide();
    createFileButton->setEnabled(true);
    createFolderButton->setEnabled(true);
    int flag=0;
    for(int i=0;i<2;i++){
        if(flag==1){
            break;
        }
        for(int j=0;j<2;j++){
            if(diskSpace[i][j]==0){
                diskSpace[i][j]=1;
                file.disk_id.first=i;
                file.disk_id.second=j;
                flag=1;
                break;
            }
        }
    }
    cata.push_back(file);
    parent->addChild(fileNode);
    submitFileNameButton->hide();
}
void User::createFile(){
    ui->label_2->show();
    ui->inputName->show();
    submitFileNameButton->show();
    createFileButton->setEnabled(false);
    createFolderButton->setEnabled(false);
}

void User::openFile(){
    if(searchFile(catalogue->currentItem())!=-1&&catalogue->currentItem()->text(1)=="文件"){
        file_iterator=searchFile(catalogue->currentItem());
        File_name->setText(cata[file_iterator].file_name);
        inputTXT->setPlainText(cata[file_iterator].content);
        openFileButton->setEnabled(false);
        saveButton->setEnabled(true);
        closeButton->setEnabled(true);
    }
}

void User::saveFile(){
    if(searchFile(catalogue->currentItem())!=-1){
    cata[file_iterator].content=inputTXT->toPlainText();
    }
}

int User::searchFile(QTreeWidgetItem* it){
    QString name=(*it).text(0);
    for(int i=0;i<cata.size();i++){
        if(name==cata[i].file_name&&it->parent()->text(0)==cata[i].parent){
            return i;
        }
    }
    return -1;
}
void User::closeFile(){
    File_name->setText("未打开文件");
    inputTXT->clear();
    file_iterator=-1;
    openFileButton->setEnabled(true);
    saveButton->setEnabled(false);
    closeButton->setEnabled(false);
}

void User::deleteFile(){
    if(catalogue->currentItem()!=NULL&&catalogue->currentItem()!=root&&catalogue->currentItem()->text(1)=="文件"){
        file_iterator=searchFile(catalogue->currentItem());
        diskSpace[cata[file_iterator].disk_id.first][cata[file_iterator].disk_id.second]=0;
        cata.erase(cata.begin()+file_iterator);
        delete catalogue->currentItem();
        file_iterator=-1;
    }
}

void User::submitFolderName(){
    QTreeWidgetItem* folderNode=new QTreeWidgetItem;
    folderNode->setText(0,ui->inputName->text());
    folderNode->setText(1,"文件夹");
    QTreeWidgetItem* parent=catalogue->currentItem();
    if(parent->text(1)=="文件"){//禁止在文件目录下创建文件夹
        submitFolderNameButton->hide();
        ui->label_3->hide();
        ui->inputName->clear();
        ui->inputName->hide();
        createFileButton->setEnabled(true);
        createFolderButton->setEnabled(true);
        errorPage.errorInfo->setText("禁止在文件目录下创建");
        errorPage.show();
        return;
    }
    int itemChildrenCounts =parent->childCount();
        while(itemChildrenCounts--)
        {
            QTreeWidgetItem * child = parent->child(itemChildrenCounts); //index从大到小区做删除处理
            if(folderNode->text(0)==child->text(0)&&child->text(1)=="文件夹"){
                submitFolderNameButton->hide();
                ui->label_3->hide();
                ui->inputName->clear();
                ui->inputName->hide();
                createFileButton->setEnabled(true);
                createFolderButton->setEnabled(true);
                errorPage.errorInfo->setText("该文件夹已存在");
                errorPage.show();
                return;
            }
        }
    parent->addChild(folderNode);
    submitFolderNameButton->hide();
    ui->label_3->hide();
    ui->inputName->clear();
    ui->inputName->hide();
    createFileButton->setEnabled(true);
    createFolderButton->setEnabled(true);
}

void User::createFolder(){
    ui->label_3->show();
    ui->inputName->show();
    submitFolderNameButton->show();
    createFileButton->setEnabled(false);
    createFolderButton->setEnabled(false);
}

void User::deleteFolder(){
    QTreeWidgetItem* now_floder=catalogue->currentItem();
    if(now_floder!=root&&now_floder->text(1)=="文件夹"){
    int itemChildrenCounts =now_floder->childCount();
        while(itemChildrenCounts--)
        {
            QTreeWidgetItem * child = now_floder->child(itemChildrenCounts); //index从大到小区做删除处理
            if(child->text(1)=="文件"){
                catalogue->setCurrentItem(child);
                file_iterator=searchFile(catalogue->currentItem());
                diskSpace[cata[file_iterator].disk_id.first][cata[file_iterator].disk_id.second]=0;
                cata.erase(cata.begin()+file_iterator);
            }
            now_floder->removeChild(child);
            delete child;
            child = nullptr;
        }
        delete now_floder;
        now_floder=nullptr;
    }
    catalogue->setCurrentItem(root);
}

void User::clearDisk(){
    catalogue->clear();
    root=new QTreeWidgetItem;
    root->setText(0,"目录");
    catalogue->addTopLevelItem(root);
}

