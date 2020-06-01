#include "window.h"



Window::Window(){
    hbox = new QHBoxLayout();

    QHBoxLayout *hbox2 = new QHBoxLayout();

    QPushButton *button = new QPushButton("Открыть каталог");
    button->connect(button, &QPushButton::clicked, this, &Window::clickButtonOpen);

    editPath = new QLineEdit();
    editPath->setReadOnly(true);

    QLabel *label = new QLabel("Текущий каталог");

    hbox2->addWidget(label);
    hbox2->addWidget(editPath);
    hbox2->addWidget(button);

    treeWidgetListImage = new QTreeWidget();
    treeWidgetListImage->setColumnCount(1);
    treeWidgetListImage->setHeaderLabel("Изображения");
    treeWidgetListImage->connect(treeWidgetListImage, &QTreeWidget::itemClicked, this, &Window::clickOnItemImage);
    treeWidgetListImage->setStyleSheet("background-color: #f0f0f0; border: 0px solid black;");

    labelImage = new QLabel();
    labelImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    labelImage->setMinimumSize(240, 160);
    labelImage->setAlignment(Qt::AlignCenter);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    labelInfo = new QLabel();

    hbox->addWidget(treeWidgetListImage, 1);
    hbox->addWidget(line);
    hbox->addWidget(labelImage, 3);

    QVBoxLayout *vbox1 = new QVBoxLayout(this);
    vbox1->addLayout(hbox2);
    vbox1->addLayout(hbox);
    vbox1->addWidget(labelInfo);

    //viewListImage();

}

void Window::viewListImage()
{

    QDir dir(filePath);
    QStringList listSuffix = {"*.jpg", "*.png", "*.png"};
    dir.setNameFilters(listSuffix);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    treeWidgetListImage->clear();
    for (int i = 0; i < list.size(); i++){
        QFileInfo info = list.at(i);
        qDebug() << info.filePath() << endl;
        QTreeWidgetItem *item = new QTreeWidgetItem(treeWidgetListImage);
        item->setText(0, info.fileName());

    }

}

void Window::clickOnItemImage()
{
    QString pathImage = filePath + "/" + treeWidgetListImage->currentItem()->data(0,0).toString();
    pixmap.load(pathImage);
    QFileInfo info(pathImage);

    labelInfo->setText("Filename: " + info.fileName() + "\n" + "Size: " + QString::number(info.size()) + " byte" + "\n" + "Date creation: " + info.birthTime().toString());
    qDebug() << filePath + "/" + treeWidgetListImage->currentItem()->data(0,0).toString() << endl;
    updateImage();

}

void Window::resizeEvent(QResizeEvent *event){
   QSize scaledSize = pixmap.size();  //Размер изображения
   scaledSize.scale(labelImage->size(), Qt::KeepAspectRatio); //Меняем размер до размеров QLabel
   if (!labelImage->pixmap() || scaledSize != labelImage->pixmap()->size()){
       updateImage();
   }
}

void Window::updateImage()
{
   qDebug() << rand() % 10 << endl;
   if (!pixmap.isNull()){
       labelImage->setPixmap(pixmap.scaled(labelImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
   }
}

void Window::clickButtonOpen()
{
    filePath = QFileDialog::getExistingDirectory(this, tr("Open directory"), "",
                                                 QFileDialog :: ShowDirsOnly |  QFileDialog :: DontResolveSymlinks);
    if (!filePath.isEmpty()){
        editPath->setText(filePath);
        viewListImage();
    }
}


