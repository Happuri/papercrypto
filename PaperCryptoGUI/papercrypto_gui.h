#ifndef PAPERCRYPTO_GUI_H
#define PAPERCRYPTO_GUI_H

#include <QMainWindow>
#include <QString>
namespace Ui {
class papercrypto_gui;
}

class papercrypto_gui : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit papercrypto_gui(QWidget *parent = 0);
    ~papercrypto_gui();
     bool check_pad(QString &, QString);

public slots:
    void start_encryption();
    void changed_combo_box(int);
    void padtextedit_disable();
    void clear();
    void start_decryption();
    void run();
    //menu
    void open_mess();
    void open_pad();
    void save_mess();
    void save_pad();
    void about();

protected:
    //void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::papercrypto_gui *ui;
    void prepare_window();
    void prepare_menu();
    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *openMAct;
    QAction *saveMAct;
    QAction *openPAct;
    QAction *savePAct;
    QAction *aboutAct;
};

#endif // PAPERCRYPTO_GUI_H
