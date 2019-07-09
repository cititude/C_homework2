#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QMessageBox>

class myMessageBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit myMessageBox(QObject *parent = nullptr);

private:

protected:
    void showEvent(QShowEvent* event);
};

#endif // MYMESSAGEBOX_H
