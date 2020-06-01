#include <QtWidgets>

class Window : public QWidget{
    Q_OBJECT
public:
    Window();
private:
    QHBoxLayout *hbox;
    QLabel *labelImage;
    QPixmap pixmap;
    QTreeWidget *treeWidgetListImage;
    QLineEdit *editPath;
    QString filePath;
    QLabel *labelInfo;

private slots:
    void viewListImage();
    void clickOnItemImage();
    void resizeEvent(QResizeEvent *event);
    void updateImage();
    void clickButtonOpen();
};


