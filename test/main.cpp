#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include "ui_list_button.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    FileSelectorWindow window;
    window.setWindowTitle("文件选择器示例");
    window.resize(400, 500);
    window.show();
    
    return app.exec();
}
