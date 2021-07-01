#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H
#include <KMessageWidget>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QListWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QDialog>
#include <QLineEdit>
#include "mainwindow.h"
#include "core.h"
#include "monitor/monitor.h"
#include "monitor/abstractmonitor.h"
#include "dialogs/renderwidget.h"

class ExportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExportDialog(QWidget *parent=nullptr);
    ~ExportDialog();
private slots:
    void slotOpenFile();
public:
    QWidget *preView = new QWidget;
    QLabel *formatLabel;
    QLabel *nameLabel;
    QLabel *ratioLabel;
    QLabel *postionLabel;
    QLineEdit *ratioWidthEdit;
    QLineEdit *ratioHeightEdit;
    QLabel *ratioLabel2;
    QLineEdit *nameLineEdit;
    QComboBox *formatComboBox;
    QLineEdit *postionLineEdit;
    QPushButton *postionButton;
    QCheckBox *exportAudioCheckBox;
    QCheckBox *exportVedioCheckBox;
    QPushButton *exportPushButton;
    QPushButton *cancelPushButton;
    QCheckBox *fragmentCheckBox;
    QLineEdit* calculateLineEdit;
    QLabel *tipLabel;
    QLabel *subTipLabel;
    QWidget *screenBackgroundWidget;
    QSlider* timeSlider;
    QCheckBox *subCheckBox;
    QLabel *sumTimeLabel;
    GLWidget* m_glMonitor;
};

#endif // EXPORTDIALOG_H
