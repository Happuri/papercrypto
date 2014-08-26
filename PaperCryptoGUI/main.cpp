#include <QApplication>



#include "papercrypto_gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    papercrypto_gui w;
    w.show();
    
    return a.exec();
}
