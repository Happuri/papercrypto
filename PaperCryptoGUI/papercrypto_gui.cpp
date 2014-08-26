#include "papercrypto_gui.h"
#include "ui_papercrypto_gui.h"
#include "cotp.h"
#include <QMessageBox>
#include <QColor>
#include <QShortcut>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <fstream>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextStream>
papercrypto_gui::papercrypto_gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::papercrypto_gui)
{

    ui->setupUi(this);
    prepare_window();
    prepare_menu();

    QSize fixedSize(480,555);
    setMinimumSize(fixedSize);
    setMaximumSize(fixedSize);


}

papercrypto_gui::~papercrypto_gui()
{
    delete ui;
}

void papercrypto_gui::prepare_menu()
{
    QMenu *fileMenu=ui->menuBar->addMenu("File");
    //fileMenu = menuBar()->addMenu(tr("&File"));
    //fileMenu->addAction(newAct);

    openMAct = new QAction(tr("&Open..."), this);
    openMAct->setShortcuts(QKeySequence::Open);
    openMAct->setStatusTip(tr("Open an existing file"));
    connect(openMAct, SIGNAL(triggered()), this, SLOT(open_mess()));

    saveMAct = new QAction(tr("&Save"), this);
    saveMAct->setShortcuts(QKeySequence::Save);
    saveMAct->setStatusTip(tr("Save the message to disk"));
    connect(saveMAct, SIGNAL(triggered()), this, SLOT(save_mess()));

    savePAct = new QAction(tr("&Save pad"), this);
    savePAct->setShortcuts(QKeySequence::SaveAs);
    savePAct->setStatusTip(tr("Save the pad to disk"));
    connect(savePAct, SIGNAL(triggered()), this, SLOT(save_pad()));


    openPAct = new QAction(tr("&Open..."), this);
    openPAct->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    openPAct->setStatusTip(tr("Open an existing file"));
    connect(openPAct, SIGNAL(triggered()), this, SLOT(open_pad()));


    fileMenu->addAction(openMAct);
    fileMenu->addAction(saveMAct);
    fileMenu->addAction(savePAct);
    fileMenu->addAction(openPAct);

    QMenu *helpMenu=ui->menuBar->addMenu("Help");


    aboutAct = new QAction(tr("&About us"), this);
    helpMenu->addAction(aboutAct);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void papercrypto_gui::open_pad()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Pad"),"",tr("Text File (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;
    else
    {
        //fileName+=".txt";
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }


        //QTextStream ReadFile(&file);
        //ui->message->setText(ReadFile.readAll());

        QTextStream in(&file);
        //in.setVersion(QDataStream::Qt_4_5);
        QString tmp=in.readAll();

        ui->pad->setText(tmp);
    }


}

void papercrypto_gui::save_pad()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Pad"),"",tr("Text File (*.txt);;All Files (*)"));

    if (fileName.isEmpty()) return;
    else
    {
        //fileName+=".txt";
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }
        fstream cfile;
        cfile.open(fileName.toStdString().c_str(),ios::in | ios::out | ios::trunc);
        QString to_save=ui->pad->toPlainText();
        cfile << to_save.toStdString();
        cfile.close();

    }
}


void papercrypto_gui::open_mess()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Message"),"",tr("Text File (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) return;
    else
    {
        //fileName+=".txt";
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }


        //QTextStream ReadFile(&file);
        //ui->message->setText(ReadFile.readAll());

        QTextStream in(&file);
        //in.setVersion(QDataStream::Qt_4_5);
        QString tmp=in.readAll();

        ui->message->setText(tmp);
    }




}

void papercrypto_gui::about()
{

    QMessageBox::about(this, tr("About Menu"),
            tr("We invite to visit our profile on github "
               "<a href=https://github.com/rfree/papercrypto> https://github.com/rfree/papercrypto</a>"));
}

void papercrypto_gui::prepare_window()
{

    ui->message->setTabChangesFocus(1);
    ui->crypt_message->setTabChangesFocus(1);
    ui->pad->setTabChangesFocus(1);
    ui->crypt_message->setReadOnly(1);
    ui->checkBox->setShortcutEnabled(1);

    //Shortcuts
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close()));
    ui->ok_button->setShortcut(Qt::Key_Return);
    ui->checkBox->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_A);
    ui->clear_button->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Q);

    //Connecting buttons, checkbox and combobox
    connect(ui->ok_button,SIGNAL(clicked()),this,SLOT(run()));
    connect(ui->quit_button,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changed_combo_box(int)));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(padtextedit_disable()));
    connect(ui->clear_button,SIGNAL(clicked()),this,SLOT(clear()));

}

void papercrypto_gui::save_mess()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Message"),"",tr("Text File (*.txt);;All Files (*)"));

    if (fileName.isEmpty()) return;
    else
    {
        //  fileName+=".txt";
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }
        fstream cfile;
        cfile.open(fileName.toStdString().c_str(),ios::in | ios::out | ios::trunc);
        QString to_save=ui->crypt_message->toPlainText();
        cfile << to_save.toStdString();
        cfile.close();

    }

}

void papercrypto_gui::run()
{
    switch(ui->comboBox->currentIndex())
    {
        case 0:
            start_encryption();
            break;
        case 1:
            start_decryption();
            break;
    }

}

void papercrypto_gui::start_encryption()
{
    QString mess;
    string enc_mess, lpad, cmess;
    cOTP encryption;
    ui->crypt_message->clear();
    ui->pad->setTextColor(QColor("black"));
    mess=ui->message->toPlainText();
    cmess=encryption.conv_mess(mess.toStdString());
    ui->message->setText(QString::fromStdString(cmess));
    ui->label_2->setText("Pad:");

    if(ui->checkBox->isChecked()) //if checkbox is checked - random pad
    {
        ui->pad->setReadOnly(1);
        enc_mess=encryption.enc_menu(mess.toStdString(),0);
    }
    else //if not
    {
        QString Qpad = ui->pad->toPlainText();
        cout << "Mess length: " << mess.length() << endl;
        cout << "Pad length: " << Qpad.length() << endl;

        bool P=check_pad(Qpad,mess);
        if(!P) return;

        encryption.pad=Qpad.toStdString();
        enc_mess=encryption.enc_menu(mess.toStdString(),1);
        ui->pad->setText(QString::fromStdString(encryption.pad));
    }

    ui->crypt_message->setText(QString::fromStdString(enc_mess));
    ui->pad->setText(QString::fromStdString(encryption.pad));
}

void papercrypto_gui::changed_combo_box(int index)
{
    QString tmp;
    switch(index)
    {

        case 0:
            tmp=ui->crypt_message->toPlainText();
            ui->message->setText(tmp);
            ui->crypt_message->clear();
            tmp.clear();
            ui->label->setText("Message: ");
            ui->label_2->setText("Pad:");
            ui->label_3->setText("Encrypted\n message:");
            ui->crypt_message->setReadOnly(1);
            ui->message->setReadOnly(0);
            ui->checkBox->setDisabled(0);
            ui->checkBox->setChecked(0);
            ui->pad->setReadOnly(0);
            break;
        case 1:
            tmp=ui->crypt_message->toPlainText();
            ui->message->setText(tmp);
            ui->crypt_message->clear();
            tmp.clear();
            ui->label->setText("Message: ");
            ui->label_2->setText("Pad:");
            ui->label_3->setText("Decrypted\n message:");
            ui->crypt_message->setReadOnly(1);
            ui->pad->setReadOnly(0);
            ui->message->setReadOnly(0);
            ui->checkBox->setDisabled(1);
            break;
    }

}

void papercrypto_gui::padtextedit_disable()
{
    if(ui->checkBox->isChecked())
    {
        ui->pad->clear();
        ui->pad->setReadOnly(1);
    }
    else ui->pad->setReadOnly(0);
}

void papercrypto_gui::start_decryption()
{
    ui->crypt_message->clear();
    QString Qpad, Qencrypt, Qmess;
    string clear_mess;
    Qpad=ui->pad->toPlainText();
    Qencrypt=ui->message->toPlainText();
    bool P=check_pad(Qpad,Qencrypt);
    if(!P) return;

    cOTP decryption;
    clear_mess=decryption.dec(Qencrypt.toStdString(),Qpad.toStdString());
    ui->crypt_message->setText(QString::fromStdString(clear_mess));


}

void papercrypto_gui::clear()
{
    ui->pad->setTextColor(QColor("black"));
    ui->pad->clear();
    ui->message->clear();
    ui->crypt_message->clear();
}

bool papercrypto_gui::check_pad(QString &Qpad, QString mess)
{
    if(Qpad.length()<mess.length()) // pad is shorter than message
    {
        //QMessageBox messageBox;
        //messageBox.critical(0,"Error","Pad MUST be the same length as message!");
        //messageBox.setFixedSize(500,200);
        ui->pad->setTextColor( QColor( "red" ) );
        ui->pad->setText(Qpad);
        ui->pad->setTextColor(QColor("black"));

        ui->label_2->setText(ui->label_2->text()+"\ntoo short!");
        return false;
    }
    else if(Qpad.length()>mess.length())
    {
        Qpad=Qpad.left(mess.length());
        cout << "pad: " << Qpad.length() << endl;
        ui->pad->setTextColor( QColor( "green" ) );
        ui->pad->setText(Qpad);
        //ui->pad->setTextColor(QColor("black"));
        ui->label_2->setText(ui->label_2->text()+"\ntoo long!\ncorrected");
        return true;
    }

}

/*
// save
int fw = ui->textEdit->fontWeight();
QColor tc = ui->textEdit->textColor();
// append
ui->textEdit->setFontWeight( QFont::DemiBold );
ui->textEdit->setTextColor( QColor( "red" ) );
ui->textEdit->append( entry );
// restore
ui->textEdit->setFontWeight( fw );
ui->textEdit->setTextColor( tc );
*/
