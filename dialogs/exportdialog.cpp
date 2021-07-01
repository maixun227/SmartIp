#include "exportdialog.h"

#include <QLayout>
#include <QBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

ExportDialog::ExportDialog(QWidget* parent)
    : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("导出设置");
    this->setStyleSheet(R"(
        QWidget{
            background: #2D2C39;
            border: 1px solid #5E5F72;
        }
)");
    QVBoxLayout* mainLayout = new QVBoxLayout;
    tipLabel = new QLabel("导出设置");
    tipLabel->setAlignment(Qt::AlignHCenter);
    tipLabel->setStyleSheet(R"(
        QLabel{
            width: 56px;
            height: 19px;
            font-size: 14px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: #FFFFFF;
            border: 0px;
        }
)");
    this->resize(900, 590);
    this->setMaximumSize(900,590);
    mainLayout->addSpacing(14);
    mainLayout->addWidget(tipLabel);
    mainLayout->addSpacing(19);
    preView = new QWidget;
    preView->setStyleSheet(R"(
        QWidget{
            font-size: 14px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            background: #3E3D4C;
        }
)");
    preView->resize(425, 518);
    preView->setMaximumSize(425,518);
    preView->setMinimumSize(425,518);
    QVBoxLayout *subMainLayout = new QVBoxLayout;
    subMainLayout->addSpacing(16);
    subTipLabel = new QLabel("导出视频及效果预览");
    subTipLabel->setAlignment(Qt::AlignLeft);
    subTipLabel->setStyleSheet(R"(
        QLabel{
            width: 96px;
            height: 16px;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: rgba(255, 255, 255, 0.9);
            border: 0;
        }
)");
    subMainLayout->addWidget(subTipLabel);
    subMainLayout->addSpacing(13);
    screenBackgroundWidget = new QWidget;
    screenBackgroundWidget->setMinimumSize(385, 385);
    screenBackgroundWidget->setStyleSheet(R"(
        QWidget{
            width: 385px;
            height: 385px;
            background: #000000;
        }
)");
    auto screen = pCore->getMonitor(Kdenlive::ClipMonitor);


    QVBoxLayout *screenLayout = new QVBoxLayout;
    screenLayout->addSpacing(84);
    screenLayout->addWidget(screen);
    screenLayout->addSpacing(84);
    screenBackgroundWidget->setLayout(screenLayout);
    subMainLayout->addWidget(screenBackgroundWidget);
    subMainLayout->addSpacing(13);
    timeSlider = new QSlider;
    timeSlider->setOrientation(Qt::Horizontal);
    timeSlider->setStyleSheet(R"(
        QSlider{
            width: 386px;
            height: 8px;
            background: rgba(119, 129, 244, 0.6);
            opacity: 1;
            border-radius: 500px;
            border: 0;
        }
)");
    subMainLayout->addWidget(timeSlider);
    subMainLayout->addSpacing(10);
    QHBoxLayout *sliceLayout = new QHBoxLayout;
    subCheckBox = new QCheckBox("导出所选片段");
    subCheckBox->setStyleSheet(R"(
        QCheckBox{
            width:92px;
            height:20px;
            color: #FFFFFF;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            border: 0;
        }
)");
    sliceLayout->addSpacing(43);
    sliceLayout->addWidget(subCheckBox);
    sliceLayout->addSpacing(200);
    sumTimeLabel = new QLabel;
    sumTimeLabel->setMinimumSize(76,19);
    sumTimeLabel->setStyleSheet(R"(
        QLabel{
            width: 76px;
            height: 19px;
            font-size: 14px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: rgba(255, 255, 255, 0.9);
        }
)");
    sliceLayout->addWidget(sumTimeLabel);
    sliceLayout->addSpacing(20);
    subMainLayout->addLayout(sliceLayout);
    subMainLayout->addSpacing(11);
    preView->setLayout(subMainLayout);
    QHBoxLayout *bottleLayout = new QHBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QHBoxLayout* formatLayout = new QHBoxLayout;
    formatLabel = new QLabel("导出格式");
    formatLabel->setStyleSheet(R"(
        QLabel{
            width: 48px;
            height: 16px;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: rgba(255, 255, 255, 0.9);
            opacity: 1;
            border: 0;
        }
)");
    formatComboBox = new QComboBox;
    formatComboBox->setMinimumSize(170, 30);
    formatComboBox->setStyleSheet(R"(
        QComBobox{
            width: 170px;
            height: 30px;
            background: #292833;
            border: 1px solid #5E5F72;
            opacity: 1;
            border-radius: 2px;
        }
)");
    formatLayout->addSpacing(62);
    formatLayout->addWidget(formatLabel);
    formatLayout->addSpacing(28);
    formatLayout->addWidget(formatComboBox);
    formatLayout->addSpacing(164);
    rightLayout->addSpacing(59);
    rightLayout->addLayout(formatLayout);
    rightLayout->addSpacing(30);
    QHBoxLayout *ratioLayout = new QHBoxLayout;
    ratioLabel = new QLabel("分辨率");
    ratioLabel->setStyleSheet(formatLabel->styleSheet());
    ratioLabel->resize(36,16);
    ratioWidthEdit = new QLineEdit(this);
    ratioWidthEdit->setStyleSheet(R"(
        QLineEdit{
            width: 74px;
            height: 30px;
            background: #292833;
            border: 1px solid #5E5F72;
            opacity: 1;
            border-radius: 2px;
        }
)");
    ratioHeightEdit = new QLineEdit(this);
    ratioHeightEdit->setStyleSheet(ratioWidthEdit->styleSheet());
    ratioLayout->addSpacing(83);
    ratioLayout->addWidget(ratioLabel);
    ratioLayout->addSpacing(20);
    ratioLayout->addWidget(ratioWidthEdit);
    ratioLayout->addSpacing(10);
    ratioLabel2 = new QLabel("x");
    ratioLabel2->setStyleSheet(R"(
        QLabel{
            width: 9px;
            height: 19px;
            font-size: 14px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: rgba(255, 255, 255, 0.9);
            border: 0;
        }
)");
    ratioLayout->addWidget(ratioLabel2);
    ratioLayout->addSpacing(10);
    ratioLayout->addWidget(ratioHeightEdit);
    ratioLayout->addSpacing(137);
    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLabel = new QLabel("名称");
    nameLabel->setStyleSheet(R"(
        QLabel{
            width: 24px;
            height: 16px;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: rgba(255, 255, 255, 0.9);
            border: 0;
        }
)");
    nameLineEdit = new QLineEdit;
    nameLineEdit->setStyleSheet(R"(
        QLineEdit{
            width: 208px;
            height: 30px;
            background: #292833;
            border: 1px solid #5E5F72;
            opacity: 1;
            border-radius: 2px;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
        }
)");
    nameLayout->addSpacing(94);
    nameLayout->addWidget(nameLabel);
    nameLayout->addSpacing(20);
    nameLayout->addWidget(nameLineEdit);
    nameLayout->addSpacing(106);
    rightLayout->addLayout(ratioLayout);
    rightLayout->addSpacing(30);
    rightLayout->addLayout(nameLayout);
    rightLayout->addSpacing(30);
    QHBoxLayout *positionLayout = new QHBoxLayout;
    postionLabel = new QLabel("导出位置");
    postionLabel->setStyleSheet(R"(
        QLabel{
            width: 48px;
            height: 16px;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            line-height: 20px;
            color: rgba(255, 255, 255, 0.9);
            border: 0px;
        }
)");
    positionLayout->addSpacing(70);
    positionLayout->addWidget(postionLabel);
    positionLayout->addSpacing(20);
    postionLineEdit = new QLineEdit;
    postionLineEdit->setStyleSheet(R"(
        QLineEdit{
            width: 208px;
            height: 30px;
            background: #292833;
            border: 1px solid #5E5F72;
            opacity: 1;
            border-radius: 2px;
        }
)");
    postionButton = new QPushButton;
    postionButton->setIcon(QIcon("E:/CraftRoot/build/kde/kdemultimedia/kdenlive/work/kde_based_editor/data/icon/controllers/ico_file.png"));
    postionButton->setStyleSheet(R"(
        QPushButton{
            width: 14px;
            height: 30px;
            border: 0;
        }
)");
    positionLayout->addWidget(postionLineEdit);
    positionLayout->addSpacing(-20);
    positionLayout->addWidget(postionButton);
    positionLayout->addSpacing(106);
    exportAudioCheckBox = new QCheckBox("导出音频");
    exportAudioCheckBox->setStyleSheet(R"(
        QCheckBox{
            width:68px;
            height:16px;
            color: #FFFFFF;
            font-size: 12px;
            font-family: Microsoft YaHei;
            font-weight: 400;
            border: 0;
        }
)");
    exportVedioCheckBox = new QCheckBox("导出视频");
    auto style = exportAudioCheckBox->styleSheet();
    exportVedioCheckBox->setStyleSheet(style);
    QHBoxLayout *exportBoxLayout = new QHBoxLayout;
    exportBoxLayout->addSpacing(142);
    exportBoxLayout->addWidget(exportAudioCheckBox);
    exportBoxLayout->addSpacing(50);
    exportBoxLayout->addWidget(exportVedioCheckBox);
    exportBoxLayout->addSpacing(118);
    bottleLayout->addSpacing(23);
    bottleLayout->setSpacing(0);
    bottleLayout->addWidget(preView);
    rightLayout->addLayout(positionLayout);
    rightLayout->addSpacing(27);
    rightLayout->addLayout(exportBoxLayout);
    rightLayout->addSpacing(137);
    exportPushButton = new QPushButton("确定");
    exportPushButton->setStyleSheet(R"(
        QPushButton{
            width: 86px;
            height: 30px;
            background: #292833;
            border: 1px solid #5E5F72;
            opacity: 1;
            border-radius: 2px;
        }
)");
    cancelPushButton = new QPushButton("取消");
    cancelPushButton->setStyleSheet(exportPushButton->styleSheet());
    QHBoxLayout* pushButtonLayout = new QHBoxLayout;
    pushButtonLayout->addSpacing(104);
    pushButtonLayout->addWidget(exportPushButton);
    pushButtonLayout->addSpacing(81);
    pushButtonLayout->addWidget(cancelPushButton);
    pushButtonLayout->addSpacing(95);
    rightLayout->addLayout(pushButtonLayout);
    rightLayout->addSpacing(75);
    bottleLayout->addLayout(rightLayout);
    mainLayout->addLayout(bottleLayout);
    this->setLayout(mainLayout);

    formatComboBox->addItem("根据扩展名称自动识别");
    formatComboBox->addItem("3g2");
    formatComboBox->addItem("3gp");
    formatComboBox->addItem("a64");
    formatComboBox->addItem("avi");
    formatComboBox->addItem("GIF");
    formatComboBox->addItem("h264");
    formatComboBox->addItem("mov");
    formatComboBox->addItem("mp3");
    formatComboBox->addItem("mp4");
    formatComboBox->addItem("JPEG");
    formatComboBox->addItem("WEBM");
    connect(postionButton, SIGNAL(clicked()), this, SLOT(slotOpenFile()));
}
ExportDialog::~ExportDialog(){

}

void ExportDialog::slotOpenFile(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home");
    postionLineEdit->setText(dir);
}
